# LC - compilador L
SHELL = /bin/sh
.POSIX:

# LC versao
VERSION = 1.0.0

CC=gcc
CFLAGS= -ansi -W -Wall

PROJ_NAME = main

all: clean options $(PROJ_NAME)

options:
	@echo $(PROJ_NAME) build options:
	@echo "CFLAGS = $(CFLAGS)"

$(PROJ_NAME):
	$(CC) -o $@ $(PROJ_NAME).c

%.o: %.c %.h
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(PROJ_NAME)

run:
	./$(PROJ_NAME)

debug_gdb:
	gcc -o $(PROJ_NAME).o $(PROJ_NAME) -g
	gdb ./$(PROJ_NAME).o

.PHONY: all options clean
