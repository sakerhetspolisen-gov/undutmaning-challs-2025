# Variabler för kompilator och flaggor
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = status
SRC = status.c

# Standardmålet
all: $(TARGET)

# Regler för att bygga binären
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Rensa byggfiler
clean:
	rm -f $(TARGET)

# Kör programmet med ett exempelargument
run: $(TARGET)
	./$(TARGET) status
