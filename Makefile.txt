# Makefile for Library Management System

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = library

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
