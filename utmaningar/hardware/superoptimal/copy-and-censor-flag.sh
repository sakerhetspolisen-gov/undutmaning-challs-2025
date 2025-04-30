# Copy ELF-file to the emulator
cp src/stm32-fw/stm32-fw.elf src/glitch-emulator/stm32-fw.elf

# Copy ELF-file to the downloads-folder and censor the flag
sed <src/stm32-fw/stm32-fw.elf 's/undut{th3Y_c_m3_unr0llin}/THISISWHERETHEFLAGWOULDBE/g' >/tmp/stm32-fw.elf
sed </tmp/stm32-fw.elf 's/cRejzyG0odPas5wd/FAKEPASSWORDHERE/g' >download/stm32-fw.elf
