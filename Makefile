TARGET = wildland

SOURCES = main.c menu/menu.c core/forest.c core/simulation.c utils/input.c utils/display.c utils/memory.c utils/dijkstra.c stack/stack.c

CC = gcc

CFLAGS = -Wall -Werror

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
