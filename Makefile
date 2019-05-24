CFLAGS=-O2 -Wall -Wextra -pthread $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)

SOURCES=$(wildcard system_simulator/**/*.c system_simulator/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(OBJECTS)
	$(CC) -o simulator -pthread $(OBJECTS)

clean:
	rm -rf $(OBJECTS)
