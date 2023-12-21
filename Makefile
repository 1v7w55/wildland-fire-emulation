TARGET = wildland

SOURCES = main.c menu/menu.c core/forest.c core/simulation.c utils/input.c utils/display.c utils/memory/memory.c utils/dijkstra/dijkstra.c stack/stack.c utils/save.c config/global.c

CC = gcc

CFLAGS = -Wall -Werror

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
