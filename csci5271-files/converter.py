import math
import sys

def hex2ascii(input):
	by = bytes.fromhex(input)
	return by.decode("ASCII")



if (len(sys.argv) != 3):
	print("usage: converter.py <ARG> <VAL> where <ARG> is:")
	print("-ha:  hex to ascii")
	print("-ah:  ascii to hex")
	print("-64a: base64 to ascii")
	print("-a64: ascii to base64")
arg = sys.argv[1]
val = sys.argv[2]

if arg == "-ha":
	print(hex2ascii(val))
else:
	print("sorry :(")
