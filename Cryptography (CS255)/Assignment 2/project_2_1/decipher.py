import sys
from oracle import *


def attack_block_on_index(blocks, index):
    prev_block = blocks[index - 1].copy()
    hacked_bytes = [0] * 16
    original_plaintext = [0] * 16

    for padding_len in range(1, 17):
        pos = 15 - padding_len + 1
        original_byte = prev_block[pos]
        for guess in range(256):
            prev_block[pos] = guess
            for hacked_pos in range(pos + 1, 16):
                prev_block[hacked_pos] = hacked_bytes[hacked_pos] ^ padding_len

            test_data = []
            for i in range(index - 1):
                test_data += blocks[i]
            test_data += prev_block + blocks[index]

            result = Oracle_Send(test_data, index + 1)
            if result == 1:
                hacked_bytes[pos] = guess ^ padding_len
                original_plaintext[pos] = hacked_bytes[pos] ^ original_byte
                break

    return original_plaintext


if len(sys.argv) < 2:
    print("Usage: python decipher.py <filename>")
    sys.exit(-1)

f = open(sys.argv[1])
data = f.read()
f.close()

blocks = []
ciphertext = bytes.fromhex(data)
for i in range(0, len(ciphertext), 16):
    blocks.append(list(ciphertext[i:i + 16]))

Oracle_Connect()

plaintext_blocks = []
for block_index in range(1, len(blocks)):
    plaintext_blocks.append(attack_block_on_index(blocks, block_index))

plaintext = []
for block in plaintext_blocks:
    for byte in block:
        plaintext.append(byte)

padding_length = plaintext[-1]
if 1 <= padding_length <= 16:
    plaintext = plaintext[:-padding_length]

result = bytes(plaintext).decode('ascii')
print(result)

Oracle_Disconnect()