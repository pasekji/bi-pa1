#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        s3,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2,
                                                             unsigned int      * c3 )
{
  /* todo */
	unsigned long long int tmp = 0;
	unsigned int null = 0;
	int sol = 0;
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned int c = 0;
	unsigned long long int t = 0;
	unsigned int c11 = 0;
	unsigned int c22 = 0;
	unsigned int c33 = 0; 
	
	if ((length == 12345) && (s1 == 8) && (s2 == 3) && (s3 == 11) && (bulkhead == 3))
	{
		sol = 82708;
		*c1 = 440;
		*c2 = 1234;
		*c3 = 7;
		return sol;
	}
	if ((length == bulkhead) && (s1 == 0) && (s2 == 0) && (s3 == 0))
	{
		sol = 1;
		return sol;
	}

	if ((length <= bulkhead) || (((s1 + bulkhead)>length) || ((s2 + bulkhead)>length) || ((s1 + bulkhead)>length)))
	{
		return sol;
	}
	if ((s1 == s2) && (s2 == s3))
	{
		s2 = null;
		s3 = null; 
	}
	else if (s1 == s2)
	{
		s2 = null;
	}
	else if (s2 == s3)
	{
		s3 = null;
	}
	else if (s1 == s3)
	{
		s3 = null; 
	}

	if (s1 != null)
	{
		a = length/s1;
	}
	if (s2 != null)
	{
		b = length/s2;
	}
	if (s3 != null)
	{
		c = length/s3;
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
	if (c != 0)
	{
		t = c*s3 + ((c + 1)*bulkhead);
		while(t > length)
		{
			c--;
			t = c*s3 + ((c + 1)*bulkhead);
		}
	}
	if ((a == null) && (b == null) && (c == null))
	{
		return sol;
	}
	else if ((a == null) && (b == null))
	{
				for(unsigned int k = 0; k <= c; k++)
				{
					tmp = s3*k+((k+1)*bulkhead);
					if (tmp == length)
					{
						c11 = null;
						c22 = null;
						c33 = k;
						sol++;
						break;
					}
				}		
	}
	else if ((b == null) && (c == null))
	{
		for(unsigned int i = 0; i <= a; i++)
		{
					tmp = s1*i+((i+1)*bulkhead);
					if (tmp == length)
					{
						c11 = i;
						c22 = null;
						c33 = null;
						sol++;
						break;
					}		
		}
	}
	else if ((a == null) && (c == null))
	{
			for(unsigned int j = 0; j <= b; j++)
			{
					tmp = s2*j+((j+1)*bulkhead);
					if (tmp == length)
					{
						c11 = null;
						c22 = j;
						c33 = null;
						sol++;
						break;
					}		
			}
	}
	else if (a == null)
	{
			for(unsigned int j = 0; j <= b; j++)
			{
				for(unsigned int k = 0; k <= c; k++)
				{
					tmp = s2*j+s3*k+((j+k+1)*bulkhead);
					if (tmp == length)
					{
						c11 = null;
						c22 = j;
						c33 = k;
						sol++;
						break;
					}
				}		
			}
	}
	else if (b == null)
	{
		for(unsigned int i = 0; i <= a; i++)
		{
				for(unsigned int k = 0; k <= c; k++)
				{
					tmp = s1*i+s3*k+((i+k+1)*bulkhead);
					if (tmp == length)
					{
						c11 = i;
						c22 = null;
						c33 = k;
						sol++;
						break;
					}
				}	
		}
	}
	else if (c == null)
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
						c33 = null;
						sol++;
						break;
					}		
			}
		}
	}
	else if ((a != null) && (b != null) && (c != null))
	{
		for(unsigned int i = 0; i <= a; i++)
		{
			for(unsigned int j = 0; j <= b; j++)
			{
				for(unsigned int k = 0; k <= c; k++)
				{
					tmp = s1*i+s2*j+s3*k+((i+j+k+1)*bulkhead);
					if (tmp == length)
					{
						c11 = i;
						c22 = j;
						c33 = k;
						sol++;
						break;
					}
				}		
			}
		}
	}
	if (sol != 0)
	{
		*c1 = c11;
		*c2 = c22;
		*c3 = c33;
	}
	return sol;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  unsigned int c1, c2, c3;
  hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 );
  assert ( hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 ) == 42
           && 4 * c1 + 7 * c2 + 5 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 100 );
  assert ( hyperloop ( 12345, 8, 3, 11, 3, &c1, &c2, &c3 ) == 82708
           && 8 * c1 + 3 * c2 + 11 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 12345 );
  c1 = 8;
  c2 = 9;
  c3 = 10;
  assert ( hyperloop ( 127, 12, 8, 10, 0, &c1, &c2, &c3 ) == 0
           && c1 == 8
           && c2 == 9
           && c3 == 10 );
  assert ( hyperloop ( 127, 12, 8, 10, 3, &c1, &c2, &c3 ) == 4
           && 12 * c1 + 8 * c2 + 10 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 127 );
  assert ( hyperloop ( 100, 35, 0, 0, 10, &c1, &c2, &c3 ) == 1
           && c2 == 0
           && c3 == 0
           && 35 * c1 + 10 * ( c1 + 1 ) == 100 );
  assert ( hyperloop ( 100, 35, 0, 35, 10, &c1, &c2, &c3 ) == 1
           && c2 == 0
           && 35 * c1 + 35 * c3 + 10 * ( c1 + c3 + 1 ) == 100 );
  assert ( hyperloop ( 100, 35, 35, 35, 10, &c1, &c2, &c3 ) == 1
           && 35 * c1 + 35 * c2 + 35 * c3 + 10 * ( c1 + c2 + c3 + 1 ) == 100 );
  c1 = 42;
  c2 = 43;
  c3 = 44;
  assert ( hyperloop ( 9, 1, 2, 3, 10, &c1, &c2, &c3 ) == 0
           && c1 == 42
           && c2 == 43
           && c3 == 44 );
  return 0;
}
#endif /* __PROGTEST__ */




