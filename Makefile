CFLAGS=-O2 -Wall -Wextra $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)

SOURCES=$(wildcard system_simulator/**/*.c system_simulator/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

all: $(OBJECTS)
	$(CC) -o simulator $(OBJECTS)

clean:
	rm -rf $(OBJECTS)
