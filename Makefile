
test: rope.cpp
	g++ -O2 -Wextra -Wall  -o test -DTESTING rope.cpp
	./test


v8: strcat.js
	node strcat.js 2>/dev/null

