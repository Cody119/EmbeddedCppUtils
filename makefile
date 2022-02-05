OUT_NAME = test.a

$(OUT_NAME): test.cpp bitfield.hpp
	g++ -std=c++11 -Wall test.cpp -o $(OUT_NAME) -O2

build: $(OUT_NAME)

run: build
	./$(OUT_NAME)