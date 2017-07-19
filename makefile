main:
	g++ --std=c++14 main.cpp -o main
	./main
test:
	g++ --std=c++14 CheckFuncs.cpp -o check
	./check
