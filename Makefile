all: sales

sales: src/sales.c
	gcc src/sales.c -o sales

clean:
	rm sales
