CXX = g++
CXXFLAGS = -std=c++11 -O3 -D__DEBUG__
INCLUDES = -I../seed-raw

MAINS = $(wildcard ../seed-raw/step_*)
OBJ = $(patsubst %.cpp, %.o, $(filter-out $(MAINS), $(wildcard *.cpp ../seed-raw/*.cpp)))

.PHONY: all
all: build 

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o step_ext $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	-rm step_ext
	-rm *.o
	-rm ../seed-raw/*.o