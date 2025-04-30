# Variabler för kompilator och flaggor
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = uptime_helper
SRC = uptime_helper.c

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
	./$(TARGET) uptime_helper
