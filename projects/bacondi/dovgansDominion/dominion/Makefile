CFLAGS = -Wall -Wextra -fpic -coverage -std=c99 -O0 -lm
GCC = /usr/local/common/gcc-7.3.0/bin/gcc
GCOV = /usr/local/common/gcc-7.3.0/bin/gcov

rngs.o: rngs.h rngs.c
	$(GCC) -c rngs.c -g  $(CFLAGS)

myAssert.o: myAssert.h myAssert.c
	$(GCC) -c myAssert.c -g  $(CFLAGS)

myUtil.o: myUtil.h myUtil.c
	$(GCC) -c myUtil.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(GCC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(GCC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	$(GCC)  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	$(GCC) -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	$(GCC) -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	$(GCC) -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	$(GCC) -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	$(GCC) -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	$(GCOV) dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o myAssert.o
	$(GCC) -o unittest1 -g  unittest1.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest1

unittest2: unittest2.c dominion.o rngs.o myAssert.o
	$(GCC) -o unittest2 -g  unittest2.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest2

unittest3: unittest3.c dominion.o rngs.o myAssert.o
	$(GCC) -o unittest3 -g  unittest3.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest3

unittest4: unittest4.c dominion.o rngs.o myAssert.o
	$(GCC) -o unittest4 -g  unittest4.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x unittest4
	
cardtest1: cardtest1.c dominion.o rngs.o myAssert.o
	$(GCC) -o cardtest1 -g  cardtest1.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x cardtest1

cardtest2: cardtest2.c dominion.o rngs.o myAssert.o
	$(GCC) -o cardtest2 -g  cardtest2.c dominion.o rngs.o myAssert.o $(CFLAGS)
	chmod +x cardtest2

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2
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

	$(GCOV) -b dominion.c >> unittestresults.out

	cat dominion.c.gcov >> unittestresults.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o myAssert.o interface.o myUtil.o
	$(GCC) -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o myAssert.o interface.o myUtil.o $(CFLAGS)
	chmod +x randomtestadventurer

randomtestcard1: randomtestcard1.c dominion.o rngs.o myAssert.o interface.o myUtil.o
	$(GCC) -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o myAssert.o interface.o myUtil.o $(CFLAGS)
	chmod +x randomtestcard1

randomtestadventurer.out: randomtestadventurer
	echo "randomtestadventurer.c:" > randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	$(GCOV) -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	echo "randomtestcard1.c:" > randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	$(GCOV) -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

player: player.c interface.o
	$(GCC) -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -rf *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe testUpdateCoins unittestresults.out unittest? cardtest? randomtestadventurer randomtestcard? *.dSYM
