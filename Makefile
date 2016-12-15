all: square triangular honeycomb lieb

square: square.cc
	g++ -Wall -Wextra -O3 -flto -o square square.cc

triangular: triangular.cc
	g++ -Wall -Wextra -O3 -flto -o triangular triangular.cc

honeycomb: honeycomb.cc
	g++ -Wall -Wextra -O3 -flto -o honeycomb honeycomb.cc

lieb: lieb.cc
	g++ -Wall -Wextra -O3 -flto -o lieb lieb.cc

clean:
	-rm -f square triangular honeycomb lieb
	-rm -f *.svg
