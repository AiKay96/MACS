# add your imports here
import base64

# reading input (don't forget strip in other challenges!)
str_hex = input().strip()
byte_array = bytearray.fromhex(str_hex)
str_base64 = base64.b64encode(byte_array).decode('ascii')

print(str_base64)
