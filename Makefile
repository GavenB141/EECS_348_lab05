all: sales matrix

sales: src/sales.c
	gcc src/sales.c -o sales -Wall

matrix: src/matrix.c
	gcc src/matrix.c -o matrix -Wall

clean:
	rm sales matrix
