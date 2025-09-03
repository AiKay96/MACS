from oracle import *
import sys

if len(sys.argv) < 2:
    print("Usage: python forge.py <filename>")
    sys.exit(-1)

f = open(sys.argv[1])
data = f.read()
f.close()

M1 = data[0:16]
M2 = data[16:32]
M3 = data[32:48]
M4 = data[48:64]

Oracle_Connect()

first_half = M1 + M2
C2 = Mac(first_half, len(first_half))

modified_M3 = ""
for i in range(len(M3)):
    modified_M3 += chr(ord(M3[i]) ^ C2[i])
second_half = modified_M3 + M4

tag = Mac(second_half, len(second_half))
ret = Vrfy(data, len(data), tag)

if ret == 1:
    print(tag.hex())
else:
    print("Message verification failed.")

Oracle_Disconnect()
