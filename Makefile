
test: rope.cpp
	g++ -O2 -Wextra -Wall  -o test -DTESTING rope.cpp
	./test
