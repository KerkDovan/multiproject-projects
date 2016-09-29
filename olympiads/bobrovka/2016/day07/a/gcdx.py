import itertools
import random

a = {
    "a":            123,
    "abc":          456,
    "adskonf sjaf": 23,
}

# terms = (
# 	"a",
# 	"b",
# 	"(a // b)",
# 	"(a % b)",
# 	"(b // a)",
# 	"(b % a)",
# 	"x1",
# 	"y1",
# 	"g",
# 	"0",
# 	"1",
# )

# combs = (
# 	"%s + %s",
# 	"%s - %s",
# 	"-%s - %s",
# 	"%s * %s",
# 	"-%s * %s",
# 	"%s // %s",
# 	"-%s // %s",
# 	"%s %% %s",
# 	"-%s %% %s",
# )

def gcdx(a, b):
	if b == 0:
		return a, 1, 0
	g, x1, y1 = gcdx(b, a % b)
	x = y1
	y = (g - a * x) // b
	return g, x, y

def test(f: int, tests=100) -> int:
	try:
		for i in range(tests):
			a = random.randint(1, 100)
			b = random.randint(1, 100)
			g, x, y = f(a, b)
			assert a % g == b % g == 0
			if a * x + b * y != g:
				return False

		return True

	except ZeroDivisionError:
		return False

# def main():
# 	for a, b, c, d in itertools.product(terms, repeat=4):
# 		for sx, sy in itertools.product(combs, repeat=2):
# 			x_expr = sx % (a, b)
# 			y_expr = sy % (c, d)

# 			def gcdx(a, b):
# 				if b == 0:
# 					return a, 1, 0
# 				g, x1, y1 = gcdx(b, a % b)
# 				x = y1
# 				y = (g - a * x) // b
# 				return g, x, y

# 			try:
# 				for i in range(50):
# 					a = random.randint(1, 100)
# 					b = random.randint(1, 100)
# 					g, x, y = gcdx(a, b)
# 					# assert a % g == b % g == 0
# 					if a * x + b * y != g:
# 						break
# 				else:
# 					print("x =", x_expr)
# 					print("y =", y_expr)
# 					print()

# 			except ZeroDivisionError:
# 				pass

def main():
	print(test(gcdx, 10000))

main()
print("Done.")
