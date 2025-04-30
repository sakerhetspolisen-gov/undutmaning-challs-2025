CC = gcc
COPTS = -O2

CONTAINER = ctf-unlocker

all: laskeblask

run:
	podman run -it --rm $(CONTAINER)

laskeblask: laskeblask.c realpassword.h
	$(CC) $< -o $@
	strip -K _start -K main -K checkpassword -K PASSWORD $@
	cp -v $@ ../download/

disas:
	objdump -M intel -d laskeblask

base64: laskeblask
	bzip2 -9c laskeblask | base64

debug:
	gdb -ex "set disassembly-flavor intel" -ex "set confirm no" -ex "source ~/gef/gef.py" laskeblask

realpassword.h: genrealpassword.py
	./$<

container: laskeblask
	podman build . -t $(CONTAINER) -f Dockerfile

podman-clean:
	podman container prune -f
	podman image prune -f

clean: podman-clean
	rm -f laskeblask
