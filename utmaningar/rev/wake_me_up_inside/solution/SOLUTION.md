# Lösningsförslag

```
$ file wake_me_up_inside_024fa20249d9c3fffa2582a582f995d9 
wake_me_up_inside_024fa20249d9c3fffa2582a582f995d9: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, BuildID[sha1]=9c016795fdf4b02104eae808a3c19c562bac259f, for GNU/Linux 3.2.0, stripped
```

```
$ ./wake_me_up_inside_024fa20249d9c3fffa2582a582f995d9 
> test

:(
```

Statisk & strippad innebär att vi med t.e.x. Ghidra endast hittar `entry` by default. Där anropas `libc_start_main` som man med lite erfarenhet vet innehåller addressen till `main` i sitt första argument.

Där inne kan vi med lite dynamisk analys hitta bl.a. en funktion som läser input (`fgets`), en funktion som skriver (`puts`/`printf`) output, en loop som gör lite grejer med både varje input-byte och array med heltal.

Vid felaktig input får vi efter 1 sekund `:(` och om vi är i t.e.x. `pwndbg` med defaultinställningar händer ingenting eftersom den override:ar signalhanteraren för SIGALRM. Detta beteende i `gdb` går att hantera med `signal` (se t.e.x. `help signal`). Att fel flagga (input) hanteras av `sleep` och `alarm` är en möjlig snubbeltråd för en som inte har erfarenhet av debuggers. Kommer vi ihåg att utnyttja t.e.x. `strace` så kan vi också se detta.

Prövar vi att skicka in flaggformatet `undut{...` och stegar genom loopen så borde vi märka att vi "överlever" 6 st iterationer eftersom loopen ser ut så här:

```
  // win iteration if md5sum(flag[i]) + thing[i] == 0 // (or `0x100000000` if not truncating to uint32_t which the program does)
  for (int i = 0; i < 26; i++) {
      x = calculate_md5(&input_buf[i], 1) + thing[i];
      alarm(1);
      sleep(x); // sleep for n seconds where n is the calculated sum, else alarm catches up to us
  }
```

Det underlättar om man inser att `calculate_md5(&input_buf[i], 1)` görs. Detta kanske görs efter man analyserar tittar på in-och returvärdet för funktionen, kanske gissar sig fram lite.

Inser man aldrig detta så kan med man med den tidigare informationen (första 6 godkända iterationerna) kan man brute-force:a byte-vis i kombination med att t.e.x. skripta mot gdb eller strace för att se hur många iterationer man klarade.

```
$ ./wake_me_up_inside_024fa20249d9c3fffa2582a582f995d9 
> undut{yyya_sn00ze_ya_l0z3}

:)
```

