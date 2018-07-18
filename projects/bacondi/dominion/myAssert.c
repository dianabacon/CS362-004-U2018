/* ----------------------------------------------------------------------- 
 * Name            : myAssert.c 
 * Author          : Diana Bacon
 * Language        : ANSI C
 * Description     : Non-catastrophic replacement for assert function
 * ----------------------------------------------------------------------- 
 */

#include <stdio.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int intAssert(char *tag, int actual, int expected)
{
#if (NOISY_TEST == 1)
	printf("%s = %d, expected = %d", tag, actual, expected);
#endif
	if (actual == expected)
	{
#if (NOISY_TEST == 1)
		printf(" PASS\n");
#endif
		return 0;		
	}
#if (NOISY_TEST == 1)
		printf(" FAIL\n");
#endif
	return 1;
}