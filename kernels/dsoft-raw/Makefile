CXX = g++
CXXFLAGS = -std=c++11 -O3 -D__DEBUG__
INCLUDES =

OBJ = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: all
all: build 

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o step_ext $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	-rm step_index
	-rm *.o