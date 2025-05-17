CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -g

SRCDIR = src
INCDIR = include
BINDIR = bin
BUILDDIR = build
TARGET = $(BINDIR)/huffman_tool.exe

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

all: $(BINDIR) $(BUILDDIR) $(TARGET)

$(BINDIR):
	mkdir $(BINDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	-del /Q "$(BUILDDIR)\*.o" 2>nul || echo No object files found.
	-del /Q "$(TARGET)" 2>nul || echo No executable found.

.PHONY: all clean run
