all: square triangular

square: square.cc
	g++ -Wall -Wextra -O3 -flto -o square square.cc

triangular: triangular.cc
	g++ -Wall -Wextra -O3 -flto -o triangular triangular.cc

clean:
	-rm -f square triangular
	-rm -f *.svg
