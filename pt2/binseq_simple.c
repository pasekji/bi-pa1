#include <stdio.h>
#include <string.h>
#include <math.h>

long convertToBin(int decn)
{
	long binn = 0;
	long zbytek;
	long a = 1;
	while(decn != 0)
    	{
		zbytek = decn % 2;
		binn = binn + zbytek * a;
		a = a * 10;
		decn = decn / 2;
	}
	return binn;
}

int digits(long binn)
{

    return (long) log10(binn) + 1;
}

int nullCount(long binn)
{
	int count=0;
	if(binn==0)
        	return 1;
   	while(binn!=0)
	{
        	if ((binn & 1) == 0)
		{
			count++;
		}
        	binn=binn >> 1;
	}
	return count;
}

int nullSeq(long binn)
{
	int count = 0;
	int maxcount = 0;

	if(binn==0)
	{
		return 1;
	}

	while(binn!=0)
	{
		if ((binn & 1) == 0)
		{
			count++;
			if (count > maxcount)
			{
                		maxcount = count;
			}
		}
		else
		{
			count = 0;
		}
		binn=binn >> 1;
	}
	return maxcount;
}
int main()
{
	long binn;
	int decn1;
	int decn2;
	int countd;
	int allcountd = 0;
	int countz = 0;
	int allcountz = 0;
	int zeroseq = 0;
	int tmpzeroseq;
	char op='0';
	char lenght = 'l';
	char zero = 'z';
	char seq = 's';


	printf("Zadejte interval:\n");
	if(scanf(" < %d ; %d > %c", &decn1, &decn2, &op) == 3)
	{
		if ((decn1 - decn2) > 0)
		{
			printf("Nespravny vstup.\n");
			return 0;
		}
		else if (decn1 < 0)
		{
			printf("Nespravny vstup.\n");
			return 0;
		}
		else
		{
			while(decn1 <= decn2)
			{
				binn = convertToBin(decn1);
				countd = digits(binn);
				allcountd = allcountd + countd;
				countz = nullCount(decn1);
				tmpzeroseq = nullSeq(decn1);
				if (tmpzeroseq > zeroseq)
					zeroseq = tmpzeroseq;
				allcountz = allcountz + countz;
				decn1++;
			}

			if (op == lenght)
			{
				printf("Cifer: %d\n", allcountd);
			}
			else if (op == zero)
			{
				printf("Nul: %d\n", allcountz);
			}
			else if (op == seq)
			{
				printf("Sekvence: %d\n", zeroseq);
			}
			else
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
		}
	}
	else
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	return 0;
}

