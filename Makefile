CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./includes
LDFLAGS = 
SRCDIR = src
INCDIR = includes
DATADIR = data
BINDIR = bin

_VPATH = $(SRCDIR)
VPATH = $(_VPATH)

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/central_comando

all: setup $(EXECUTABLE)

setup:
	@mkdir -p $(BINDIR)
	@mkdir -p $(DATADIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BINDIR) $(DATADIR)
	

run: all
	@$(EXECUTABLE)

.PHONY: all setup clean run