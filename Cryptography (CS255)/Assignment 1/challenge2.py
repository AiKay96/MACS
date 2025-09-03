hex1 = input().strip()
hex2 = input().strip()

bytes1 = bytes.fromhex(hex1)
bytes2 = bytes.fromhex(hex2)

xor_bytes = bytearray()
for i in range(len(bytes1)):
    xor_bytes.append(bytes1[i] ^ bytes2[i])

xor_hex = xor_bytes.hex()
print(xor_hex)