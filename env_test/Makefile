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

all: build_fast build_slow

build_fast:
	$(CXX) $(CXXFLAGS) -o $(TEST_EXE)_fast $(TEST_SRC) $(INCLUDES) $(LIBS) -DMM_FAST

build_slow:
	$(CXX) $(CXXFLAGS) -o $(TEST_EXE)_slow $(TEST_SRC) $(INCLUDES) $(LIBS) -DMM_SLOW

run_fast:
	./$(TEST_EXE)_fast

run_slow:
	./$(TEST_EXE)_slow

clean: 
	rm -f $(TEST_EXE)_*
