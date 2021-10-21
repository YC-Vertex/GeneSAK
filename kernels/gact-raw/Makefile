CXX = g++
CXXFLAGS = -std=c++11 -O3 -D__DEBUG__
INCLUDES = -I../seed-raw -I../dsoft-raw

MAINS = $(wildcard ../seed-raw/step_* ../dsoft-raw/step_*)
OBJ = $(patsubst %.cpp, %.o, $(filter-out $(MAINS), $(wildcard *.cpp ../seed-raw/*.cpp ../dsoft-raw/*.cpp)))

.PHONY: all
all: build 

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o step_align $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

run:
	./step_align

.PHONY: clean
clean:
	-rm step_align
	-rm *.o
	-rm ../seed-raw/*.o
	-rm ../dsoft-raw/*.o