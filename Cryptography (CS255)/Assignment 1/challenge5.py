key = input().strip()
text = input().strip()

text_bytes = text.encode('ascii')
key_bytes = key.encode('ascii')

result = bytearray()

for i in range(len(text_bytes)):
    key_byte = key_bytes[i % len(key_bytes)]
    result.append(text_bytes[i] ^ key_byte)

print(result.hex())
