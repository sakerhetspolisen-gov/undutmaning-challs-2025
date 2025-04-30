# Copy ELF-file to the emulator
cp src/stm32-fw/stm32-fw.elf src/glitch-emulator/stm32-fw.elf

# Copy ELF-file to the downloads-folder and censor the flag
sed <src/stm32-fw/stm32-fw.elf 's/undut{t0_x3cUte_oR_n0t_to_Xecut3}/THISHERETHISISWHERETHEFLAGWOULDBE/g' >/tmp/stm32-fw.elf
sed </tmp/stm32-fw.elf 's/kvalizthnstriyat/FAKEPASSWORDHERE/g' >download/stm32-fw.elf
