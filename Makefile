all: sales

sales: src/sales.c
	gcc sales.c -o sales

clean:
	rm sales
