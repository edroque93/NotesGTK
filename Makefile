CC = gcc
GTK_CF = `pkg-config --cflags gtk+-3.0`
SQL_CF = `pkg-config --cflags sqlite3`
GTK_LD = `pkg-config --libs gtk+-3.0`
SQL_LD = `pkg-config --libs sqlite3`
CFLAGS = -g -std=c99 $(GTK_CF) $(SQL_CF)
LDFLAGS = $(GTK_LD) $(SQL_LD)
WARNINGS = -Wall -Wno-deprecated-declarations
FORMAT = clang-format
SOURCES = $(shell find src/ -iname *.c)
HEADERS = $(shell find src/ -iname *.h)
OBJECTS = $(SOURCES:src/%.c=obj/%.o)
EXE = notesgtk

.PHONY: all clean format

all: $(EXE)

$(EXE): $(OBJECTS)
	@echo Linking
	@$(CC) $(OBJECTS) -o $(EXE) $(LDFLAGS)

obj/%.o: src/%.c
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $(WARNINGS) -MMD -o $@ $<

clean:
	@rm -rf $(EXE) obj/

format:
	@echo Formatting files
	@$(FORMAT) -i $(SOURCES) $(HEADERS)

-include obj/*.d
