CC = gcc
CFLAGS = -Wall -Wextra

	
matrixtest: matrix_tests.c matrix.c
	$(CC) $(CFLAGS) -o matrixtest matrix_tests.c matrix.c
	
run: matrixtest
	./matrixtest 
clean:
	rm -f matrixtest

