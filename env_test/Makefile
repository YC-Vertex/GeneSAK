# CXX = dpcpp
CXX = g++
CXXFLAGS = -O2 -std=c++11 -g -fopenmp
LIBS = -ldl -lpthread

TEST_SRC = env_test.cpp
TEST_EXE = env_test

VTUNE_HOME = /opt/intel/oneapi/vtune/2021.5.0

ifneq ($(VTUNE_HOME),)
	CXXFLAGS += -DVTUNE_ANALYSIS
	INCLUDES += -I${VTUNE_HOME}/include
	LIBS += -L${VTUNE_HOME}/lib64 -littnotify
endif

all: build

build:
	$(CXX) $(CXXFLAGS) -o $(TEST_EXE) $(TEST_SRC) $(INCLUDES) $(LIBS)

run: 
	./$(TEST_EXE)

clean: 
	rm -f $(TEST_EXE)
