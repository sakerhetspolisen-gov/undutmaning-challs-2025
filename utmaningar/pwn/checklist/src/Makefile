

CFLAGS = -O2 -Wall -Wformat -Wformat=2 -Wconversion -Wimplicit-fallthrough \
-Werror=format-security \
-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 \
-D_GLIBCXX_ASSERTIONS \
-fstack-clash-protection -fstack-protector-all \
-Wl,-z,nodlopen -Wl,-z,noexecstack \
-Wl,-z,relro -Wl,-z,now \
-Wl,--as-needed -Wl,--no-copy-dt-needed-entries \
-fPIE -pie -fcf-protection=full -flto


all: checklist-org checklist-aligned

checklist-org: work.c
	clang-18 -fsanitize=cfi-icall $(CFLAGS)  -o checklist-org work.c


checklist-aligned: work.c
	clang-18 $(CFLAGS) -falign-functions=256 -o checklist-aligned work.c

clean:
	$(RM) work checklist-aligned checklist-org checklist