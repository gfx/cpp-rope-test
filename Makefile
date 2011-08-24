
test: rope.cpp
	g++ -Wextra -Wall -Weffc++ -o test -DTESTING rope.cpp
	./test
	rm test
