export CMAKE_BUILD_PARALLEL_LEVEL=16

.PHONY: all test clean editor client common server build

compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

run-tests: compile-debug
	./build/cs2d_tests

all: clean run-tests

clean:
	rm -Rf build/
