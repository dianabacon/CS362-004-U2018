CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: tests.out

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	chmod +x testme

tests.out: testme
	echo "Result for running testme.c tests:" > tests.out
	echo "testme.c:" >> tests.out
	trap "./testme >> tests.out" EXIT
	echo >> tests.out
	gcov testme.c >> tests.out
	cat testme.c.gcov >> tests.out
	
clean:
	rm -f tests.out

cleanall: 
	rm -f tests.out testme *.gcda *.gcno *.gcov
