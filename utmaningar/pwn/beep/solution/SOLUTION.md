### Lösningsförslag

Buffer overflow på stacken som leder till att man kan skriva över integer-variabeln `x` för att nå den "döda" koden `if (x == 1337) system("cat flag");`.
