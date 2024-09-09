# Makefile for compiling main.cpp

# Compiler
CC = g++

# Compiler flags
CFLAGS = -O1 -Wall -std=c++11 -Wno-missing-braces

# Include directories
INCLUDES = -I include/

# Library directories
LIBDIRS = -L lib/

# Libraries to link against
# Use different libraries based on the operating system
ifeq ($(OS),Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt
    endif
    ifeq ($(UNAME_S),Darwin)
        LIBS = -lraylib -framework IOKit -framework Cocoa -framework OpenGL
    endif
endif

# Source files
SRC = src/main.cpp

# Output executable
OUTPUT = game

all: $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUT) $(SRC) $(LIBDIRS) $(LIBS)