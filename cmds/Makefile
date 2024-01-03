CC = gcc
CFLAGS = -Wall

SRCDIR = src
BINDIR = bin

# Get the list of C files in the src directory
SRCFILES = $(wildcard $(SRCDIR)/*.c)

# Generate corresponding executable names
EXECUTABLES = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%, $(SRCFILES))

all: $(EXECUTABLES)

$(BINDIR)/%: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BINDIR)/*

.PHONY: all clean