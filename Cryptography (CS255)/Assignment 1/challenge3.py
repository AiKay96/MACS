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


str_hex = input().strip()
byte_array = bytes.fromhex(str_hex)

best_score = 0
best_message = ""

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
        best_message = message

print(best_message)
