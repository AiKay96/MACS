from oracle import *
from helper import *
import math


def get_signature(m, n):
    inv = pow(Sign(1), -1, n)
    for i in range(2, math.isqrt(m) + 1):
        if m % i == 0:
            sig_a = Sign(i)
            sig_b = Sign(m // i)
            return (inv * sig_a * sig_b) % n


def main():
  with open('project_3_2/input.txt', 'r') as f:
    n = int(f.readline().strip())
    msg = f.readline().strip()

  Oracle_Connect()    

  m = ascii_to_int(msg)
  sigma = get_signature(m, n) 

  print(sigma)

  Oracle_Disconnect()

if __name__ == '__main__':
  main()
