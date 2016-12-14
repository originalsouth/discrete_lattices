all: square triangular honeycomb

square: square.cc
	g++ -Wall -Wextra -O3 -flto -o square square.cc

triangular: triangular.cc
	g++ -Wall -Wextra -O3 -flto -o triangular triangular.cc

honeycomb: honeycomb.cc
	g++ -Wall -Wextra -O3 -flto -o honeycomb honeycomb.cc

clean:
	-rm -f square triangular honeycomb
	-rm -f *.svg
