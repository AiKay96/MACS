import base64


def score_english(text):
    score = 0
    common_letters = "ETAOINSHRDLCUMWFGYPBVKJXQZ"

    for char in text:
        if char.isalpha():
            score += 2
        elif char == ' ':
            score += 1
        elif char in '.,!?':
            score += 1
        elif ord(char) < 32 or ord(char) > 126:
            score -= 10
        if char.upper() in common_letters:
            score += (26 - common_letters.index(char.upper()))

    return score


def hamming_distance(bytes1, bytes2):
    distance = 0
    for i in range(len(bytes1)):
        xor_byte = bytes1[i] ^ bytes2[i]
        while xor_byte:
            distance += xor_byte & 1
            xor_byte >>= 1
    return distance


def find_key_sizes(text):
    scores = []

    for key_size in range(2, 51):
        distances = []

        for i in range(3):
            x1 = i * key_size
            x2 = x1 + key_size
            y1 = x2
            y2 = y1 + key_size

            if y2 <= len(text):
                block1 = text[x1:x2]
                block2 = text[y1:y2]
                distances.append(hamming_distance(block1, block2) / key_size)

        avg_distance = sum(distances) / len(distances)
        scores.append((avg_distance, key_size))

    scores.sort()
    return [keysize for score, keysize in scores[:3]]


def single_byte_xor(byte_array):
    best_score = 0
    best_key = 0

    for key in range(256):
        decrypted = bytearray()
        for byte in byte_array:
            decrypted.append(byte ^ key)
        try:
            message = decrypted.decode('ascii')
        except:
            continue
        score = score_english(message)
        if score > best_score:
            best_score = score
            best_key = key

    return best_key


def get_key(text, key_size):
    transposed = []

    for col in range(key_size):
        column = bytearray()
        for i in range(col, len(text), key_size):
            column.append(text[i])
        transposed.append(column)

    key_bytes = bytearray()
    for column in transposed:
        key_bytes.append(single_byte_xor(column))

    return key_bytes


str_base64 = input().strip()
text = base64.b64decode(str_base64)
key_sizes = find_key_sizes(text)

best_score = 0
best_message = ""

for key_size in key_sizes:
    key_bytes = get_key(text, key_size)
    result = bytearray()

    for i in range(len(text)):
        key_byte = key_bytes[i % len(key_bytes)]
        result.append(text[i] ^ key_byte)

    message = result.decode('ascii')
    score = score_english(message)

    if score > best_score:
        best_score = score
        best_message = message

print(best_message)
