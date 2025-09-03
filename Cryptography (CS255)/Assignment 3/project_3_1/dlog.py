import math


# Find x such that g^x = h (mod p)
# 0 <= x <= max_x
def discrete_log(p, g, h, max_x):
    B = math.isqrt(max_x) + 1

    mp = {}
    inv = pow(g, p-2, p)
    gx1 = 1
    for x1 in range(B):
        left = (h * gx1) % p
        mp[left] = x1
        gx1 = (gx1 * inv) % p
	    
    gB = pow(g, B, p)

    gBx0 = 1
    for x0 in range(B):
        if gBx0 in mp:
            return x0 * B + mp[gBx0]
        gBx0 *= gB
        gBx0 %= p

    return None

def main():
	p = int(input().strip())
	g = int(input().strip())
	h = int(input().strip())
	max_x = 1 << 40 # 2^40

	dlog = discrete_log(p, g, h, max_x)
	print(dlog)

if __name__ == '__main__':
	main()
