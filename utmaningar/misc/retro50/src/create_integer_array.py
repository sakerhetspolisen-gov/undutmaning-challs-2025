flag = "MINER WILLY IS STUCK IN A WAREHOUSE. USE CHEAT CODE 6031769."

assert flag.upper() == flag, "Flag must be uppercase."
assert len(flag) % 3 == 0, "Length must be a multiple of 3."
assert len(flag) // 3 <= 21, "Too long."

alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ$.%0123456789"
text_numbers = []
for i in range(0, len(flag), 3):
    f0 = alphabet.index(flag[i+0])
    f1 = alphabet.index(flag[i+1])
    f2 = alphabet.index(flag[i+2])
    num = f0*40**2 + f1*40 + f2
    text_numbers.append(num)

print("decoded numbers:", text_numbers)
print()

random_numbers = [36598, 43405, 13627, 31524, 23032, 16518, 23221, 30688, 5349, 41086, 19774, 42331, 23090, 20846, 32661, 18309, 22526, 23619, 15548, 40516, 22084]
obfuscated_numbers = [a+b for a,b in zip(random_numbers, text_numbers)]

string = ", ".join(map(str, obfuscated_numbers))
print("write this to insert new flag in old program (use SHIFT-D to write DATA):")
print("10 DATA " + string)