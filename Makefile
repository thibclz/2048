CXX = g++
CXXFLAGS = -Wall -Iinclude
AR=/usr/bin/ar -r 

src := $(wildcard src/*.cpp)
# Appel build/%.o avec les bon nom de fichier
obj := $(subst src, build, $(src:.cpp=.o))

.PHONY: directories

all: directories lib2048.a 2048
	@echo $(obj)

2048: main.cpp lib2048.a
	$(CXX) $(CXXFLAGS) $^ -o $@
	
lib2048.a: ${obj}
	${AR} $@ $^
	
build/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

directories: build
build:
	mkdir -p $@
	
clean :
	rm -r build
	rm 2048
	rm lib2048.a
