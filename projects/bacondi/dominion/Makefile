CFLAGS = -Wall -Wextra -fpic -coverage -std=c99 -O0

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

myAssert.o: myAssert.h myAssert.c
	gcc -c myAssert.c -g  $(CFLAGS)

myUtil.o: myUtil.h myUtil.c
	gcc -c myUtil.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o myAssert.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest1

unittest2: unittest2.c dominion.o rngs.o myAssert.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest2

unittest3: unittest3.c dominion.o rngs.o myAssert.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest3

unittest4: unittest4.c dominion.o rngs.o myAssert.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest4
	
cardtest1: cardtest1.c dominion.o rngs.o myAssert.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x cardtest1

cardtest2: cardtest2.c dominion.o rngs.o myAssert.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x cardtest2

cardtest3: cardtest3.c dominion.o rngs.o myAssert.o interface.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o myAssert.o interface.o $(CFLAGS)
	chmod +x cardtest3

cardtest4: cardtest4.c dominion.o rngs.o myAssert.o interface.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o myAssert.o interface.o $(CFLAGS)
	chmod +x cardtest4

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Running unit tests:" > unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	./unittest1 >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	./cardtest1 >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	./cardtest2 >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	./cardtest3 >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	./cardtest4 >> unittestresults.out

	gcov -b dominion.c >> unittestresults.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o myAssert.o interface.o myUtil.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o myAssert.o interface.o myUtil.o $(CFLAGS)
	chmod +x randomtestadventurer

randomtestcard1: randomtestcard1.c dominion.o rngs.o myAssert.o interface.o myUtil.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o myAssert.o interface.o myUtil.o $(CFLAGS)
	chmod +x randomtestcard1

randomtestcard2: randomtestcard2.c dominion.o rngs.o myAssert.o interface.o myUtil.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o myAssert.o interface.o myUtil.o $(CFLAGS)
	chmod +x randomtestcard2

randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2
	echo "Running random tests:" > randomtestresults.out
	
	echo "randomtestadventurer.c:" >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	
	echo "randomtestcard1.c:" >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	
	echo "randomtestcard2.c:" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out

	gcov -b dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -rf *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe testUpdateCoins unittestresults.out unittest? cardtest? randomtestadventurer randomtestcard? randomtestresults.out *.dSYM
