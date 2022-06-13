#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2 )
{
  /* todo */
	unsigned long long int tmp = 0;
	unsigned int null = 0;
	int sol = 0;
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned long long int t = 0;
	unsigned int c11 = 0;
	unsigned int c22 = 0;

	if ((length == bulkhead) && (s1 == 0) && (s2 == 0))
	{
		sol = 1;
		return sol;
	}

	if ((length <= bulkhead) || (((s1 + bulkhead)>length) || ((s2 + bulkhead)>length)))
	{
		return sol;
	}
	if ((s1 == s2))
	{
		s2 = null;

	}

	if (s1 != null)
	{
		a = length/s1;
	}
	if (s2 != null)
	{
		b = length/s2;
	}

	if (a != 0)
	{
		t = a*s1 + ((a + 1)*bulkhead);
		while (t > length)
		{
			a--;
			t = a*s1 + ((a + 1)*bulkhead);
		}
	}
	if (b != 0)
	{
		t = b*s2 + ((b + 1)*bulkhead);
		while(t > length)		
		{
			b--;
			t = b*s2 + ((b + 1)*bulkhead);
		}
	}

	if ((a == null) && (b == null))
	{
		return sol;
	}
	else if (a == null)
	{
			for(unsigned int j = 0; j <= b; j++)
			{
					tmp = s2*j+((j+1)*bulkhead);
					if (tmp == length)
					{
						c11 = null;
						c22 = j;
						sol++;
						break;
					}		
			}
	}
	else if (b == null)
	{
		for(unsigned int i = 0; i <= a; i++)
		{
					tmp = s1*i+((i+1)*bulkhead);
					if (tmp == length)
					{
						c11 = i;
						c22 = null;
						sol++;
						break;
					}	
		}
	}
	else if ((a != null) && (b != null))
	{
		for(unsigned int i = 0; i <= a; i++)
		{
			for(unsigned int j = 0; j <= b; j++)
			{
					tmp = s1*i+s2*j+((i+j+1)*bulkhead);
					if (tmp == length)
					{
						c11 = i;
						c22 = j;
						sol++;
						break;
					}
			}
		}
	}
	if (sol != 0)
	{
		*c1 = c11;
		*c2 = c22;
	}
	return sol;
}
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  unsigned int c1, c2;
  assert ( hyperloop ( 100, 4, 7, 0, &c1, &c2 ) == 4
           && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100 );
  assert ( hyperloop ( 123456, 8, 3, 3, &c1, &c2 ) == 1871
           && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456 );
  assert ( hyperloop ( 127, 12, 8, 0, &c1, &c2 ) == 0 );
  assert ( hyperloop ( 127, 12, 4, 3, &c1, &c2 ) == 1
           && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127 );
  assert ( hyperloop ( 100, 35, 0, 10, &c1, &c2 ) == 1
           && c2 == 0
           && 35 * c1 + 10 * (c1 + 1) == 100 );
  assert ( hyperloop ( 110, 30, 30, 5, &c1, &c2 ) == 1
           && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110 );
  c1 = 2;
  c2 = 7;
  assert ( hyperloop ( 110, 30, 30, 0, &c1, &c2 ) == 0 && c1 == 2 && c2 == 7 );
  c1 = 4;
  c2 = 8;
  assert ( hyperloop ( 9, 1, 2, 10, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );
  return 0;
}
#endif /* __PROGTEST__ */
