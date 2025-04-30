from sage.all import *
from pwn import remote
from pwn import process
import itertools
import random
import time

"""
degree = 1  # Degree in challenge
max_degree_search = 4; ms = list("x")
max_degree_search = 2; ms = list("xy")

degree = 2  # Degree in challenge
max_degree_search = 20; ms = list("x")
max_degree_search = 8; ms = list("xy")
max_degree_search = 4; ms = list("xyz")

degree = 3  # Degree in challenge
max_degree_search = ???; ms = list("x")
max_degree_search = 15; ms = list("xy")  # Under 7 minutes with matrix dimensions (1700, 17716)
max_degree_search = 10 ms = list("xyz")  # 80 minutes with matrix dimensions (4454, 47126)
max_degree_search = 6; ms = list("xyzw")  # 120 minutes
"""

degree = 3  # Degree in challenge
max_degree_search = 15
ms = list("xy")
cs = [f"c{i}" for i in range(degree)]
gens = polygens(ZZ, ms+cs)
ms = gens[:len(ms)]
cs = gens[len(ms):]

def local(m):
	out = m**degree
	for i in range(degree):
		out += cs[i]*m**i
	return out


query_monomials = list(itertools.product(range(max_degree_search+1), repeat=len(ms)))
query_monomials.remove((0,)*len(ms))

symbolic_base = []  # List of polynomials
for exps in query_monomials:
	mon = prod(var**exp for var, exp in zip(ms, exps))
	symbolic_base.append(local(mon))
lazy_base = [[i] for i in range(len(query_monomials))]  # Encodes which monomials to use for evaluation with integers later


def generate_combinations(base_gens, bound):
	# Keep track of polynomials to process
	to_process = base_gens.copy()
	processed = {}

	while to_process:
		cur_sym, cur_lazy = to_process.popitem()
		assert cur_sym not in processed
		processed[cur_sym] = cur_lazy

		# Try multiplying each polynomial from the original set
		for gen_sym, gen_lazy in base_gens.items():
			new_sym = cur_sym*gen_sym

			if new_sym in processed:
				continue
			# if new_sym.degree() <= bound:
			if max(new_sym.degrees()[:len(ms)]) <= bound:
				to_process[new_sym] = cur_lazy+gen_lazy

	return processed

print(len(ms), max_degree_search)
combinations = generate_combinations({sym: laz for sym, laz in zip(symbolic_base, lazy_base)}, max_degree_search)
# for combo_sym, combo_lazy in combinations.items():
# 	print(combo_sym)
symbolic_base = list(combinations.keys())
lazy_base = [combinations[sym] for sym in symbolic_base]
print(len(ms), max_degree_search)

# Create matrix of coefficient vectors
mons = set()  # Monomials as exponent-tuple: x²y⁵z⁰ -> (2,5,0)
for poly in symbolic_base:
	# print(poly)
	mons.update(poly.dict().keys())
mons = sorted(list(mons), reverse=True)

mon2col = {mon: i for i, mon in enumerate(mons)}
M = matrix(ZZ, len(symbolic_base), len(mons))
for row, poly in enumerate(symbolic_base):
	for mon, coef in poly.dict().items():
		col = mon2col[mon]
		M[row,col] = coef
print("Matrix:")
# print(M)
print("dimensions:", M.dimensions())

# Find good linear combinations of the basis polynomials to get "zero"
# Flint implementation is much faster than default (pari)
ker = M.left_kernel_matrix(algorithm="flint") # In older sage versions use ker = (M.T).right_kernel_matrix(algorithm="flint")
print("Kernel:")
print(ker)

assert ker.nrows() > 0, f"no solutions, choose better queries or basis. {len(ms)}, {max_degree_search}"


# Now pre-computation is done connect to the service


def oracle(m: int) -> int:
	service.recv(numb=len(b'\nOptions:\n1. Query oracle\n2. Get flag\n3. Quit\nPlease choose an option: '))
	service.sendline(b"1")
	service.sendline(str(m).encode())
	# return int(service.recvline().strip().split()[-1])
	a = service.recvuntil(b"\n")
	try:
		return int(a.strip().split()[-1])
	except:
		print(a)
		exit(-1)
def get_flag(n: int) -> str:
	service.recv(numb=len(b'\nOptions:\n1. Query oracle\n2. Get flag\n3. Quit\nPlease choose an option: '))
	service.sendline(b"2")
	service.sendline(str(n).encode())
	return service.recvall().decode().split()[-1]


# service = process("python3 algebra_challenge.py", shell=True)  # This is for local testing
service = remote("undutmaning-algebra.chals.io", 443, ssl=True)

kns = []
# From tuple/symbolic encoding evaluate to integers
for _ in range(4):
	while True:  # This can be so much more efficient
		ms_val = [random.randrange(2, 100) for _ in range(len(ms))]
		integer_queries = [prod([m_val**exp for m_val, exp in zip(ms_val, mon_exps)]) for mon_exps in query_monomials]
		if all(2 <= num <= 2**128 for num in integer_queries):
			break
	query_answers = [oracle(prod([m_val**exp for m_val, exp in zip(ms_val, mon_exps)])) for mon_exps in query_monomials]
	vec = vector(prod(query_answers[i] for i in query_indices) for query_indices in lazy_base)
	# vec[i] is the integer value of what symbolic_base[i] evaluates to, given input ms_val

	for ker_row in ker:
		kn = abs(ker_row*vec)
		if kn == 0:
			print("try another input")
			continue

		print("Solution list:")
		for coef, query_indices in zip(ker_row, lazy_base):
			if coef == 0:
				continue
			coef_str = str(coef)
			if coef > 0:
				coef_str = " " + coef_str
			print(f"\t{coef_str}: {query_indices}")
		print("Multiple of n:", kn)
		kns.append(kn)

kn = gcd(kns)
print("Hopefully n:", kn)

print()
print(get_flag(kn))
print("Solved with options:", len(ms), max_degree_search)
