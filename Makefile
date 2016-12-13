square: square.cc
	g++ -Wall -Wextra -O3 -flto -o square square.cc

clean:
	rm -f square
	-rm -f *.svg
