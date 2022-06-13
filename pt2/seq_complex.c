#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int convertToBaseHigherL(int decn, int base)
{
	int i = 1;
	int j;
	int temp;
	int digits = 0;
	char convertedNumber[100];
	while(decn != 0)
	{
		temp = decn % base;
		if(temp < 10)
		{
			temp = temp + 48;
		}
		else
		{
			temp = temp + 55;
		}
		convertedNumber[i++] = temp;
		decn = decn / base;
	}
	for (j = i -1 ; j > 0 ; j--)
	{
		if (!isspace(convertedNumber[j]))
		{
			digits++;
		}
	}
	return digits;
}

int convertToBaseHigherZ(int decn, int base)
{
	int i = 1;
	int j;
	int temp;
	char convertedNumber[100];
	int nullCounter = 0;
	while(decn != 0)
	{
		temp = decn % base;
		if(temp < 10)
		{
			temp = temp + 48;
		}
		else
		{
			temp = temp + 55;
		}
		convertedNumber[i++]= temp;
		decn = decn / base;
	}
	for (j = i -1 ; j > 0 ; j--)
	{
		if (convertedNumber[j] == '0')
		{
			nullCounter++;
		}	
	}
	return nullCounter;
}

int convertToBaseHigherS(int decn, int base)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	char convertedNumber[100];
	int nullSeq = 0;
	int nullLength = 1;
	while(decn != 0)
	{
		temp = decn % base;
		if(temp < 10)
		{
			temp = temp + 48;
		}
		else
		{
			temp = temp + 55;
		}
		convertedNumber[i++]= temp;
		decn = decn / base;
	}
	for(j = 1; j < i; j++)
	{
		if (convertedNumber[j] == '0')
		{
			if(convertedNumber[j] == convertedNumber[j-1])
				nullLength++;
			else
        		{	
            			if(nullLength > nullSeq)
                			nullSeq = nullLength;
            			if(nullSeq > i-1-j)
                			return nullSeq;
            			nullLength = 1;
        		}
		}
	}
    	return (nullLength > nullSeq) ? nullLength : nullSeq;
}

int main()
{
	float a;

	printf("Zadejte intervaly:\n");
	while (scanf("%f",&a) != EOF) 
	{
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
		int toBase = 0;

		if(scanf("r %d : < %d ; %d > %c", &toBase, &decn1, &decn2, &op) == 4)
		{	
			if ((abs(decn1) - abs(decn2)) > 0)
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
			if (decn1 < 0 || decn2 < 0)
			{
				printf("Nespravny vstup.\n");
				return 0;			
			}
			if (toBase >= 2 && toBase < 37)
			{
				if (op == lenght)
				{
					while(decn1 <= decn2)
					{	
						if (decn1 == 0)
							allcountd++;
						countd = convertToBaseHigherL(decn1, toBase);
						allcountd = allcountd + countd;
						decn1++;
					}
					printf("Cifer: %d\n", allcountd);
				}
				else if (op == zero)
				{
					while(decn1 <= decn2)
					{
						if (decn1 == 0)
							allcountz++;
						countz = convertToBaseHigherZ(decn1, toBase);
						allcountz = allcountz + countz;
						decn1++;
					}
					printf("Nul: %d\n", allcountz);
				}
				else if (op == seq)
				{
					if (decn1 == 0)
						zeroseq++;
					while(decn1 <= decn2)
					{
						if (decn1 == 0)
						{
							allcountz++;
							//zeroseq++;
						}
						countz = convertToBaseHigherZ(decn1, toBase);
						allcountz = allcountz + countz;
						tmpzeroseq = convertToBaseHigherS(decn1, toBase);
						if (tmpzeroseq > zeroseq)
							zeroseq = tmpzeroseq;
						decn1++;
					}
					if (zeroseq > allcountz)
						zeroseq = allcountz;
					printf("Sekvence: %d\n", zeroseq);
				}
				else
				{
					printf("Nespravny vstup.\n");
					return 0;
				}
			}
			else
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
		}
		else if (scanf("< %d ; %d > %c", &decn1, &decn2, &op) == 3)
		{
			toBase = 10;
			if ((abs(decn1) - abs(decn2)) > 0)
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
			if (decn1 < 0 || decn2 < 0)
			{
				printf("Nespravny vstup.\n");
				return 0;			
			}
			if (op == lenght)
			{
				while(decn1 <= decn2)
				{	
					if (decn1 == 0)
						allcountd++;
					countd = convertToBaseHigherL(decn1, toBase);
					allcountd = allcountd + countd;
					decn1++;
				}
				printf("Cifer: %d\n", allcountd);
			}
			else if (op == zero)
			{
				while(decn1 <= decn2)
				{
					if (decn1 == 0)
						allcountz++;
					countz = convertToBaseHigherZ(decn1, toBase);
					allcountz = allcountz + countz;
					decn1++;
				}
				printf("Nul: %d\n", allcountz);
			}
			else if (op == seq)
			{
				while(decn1 <= decn2)
				{
					if (decn1 == 0)
					{
						allcountz++;
						//zeroseq++;
					}
					countz = convertToBaseHigherZ(decn1, toBase);
					allcountz = allcountz + countz;
					tmpzeroseq = convertToBaseHigherS(decn1, toBase);
					if (tmpzeroseq > zeroseq)
						zeroseq = tmpzeroseq;
					decn1++;
				}
				if (zeroseq > allcountz)
					zeroseq = allcountz;
				printf("Sekvence: %d\n", zeroseq);
			}
			else
			{
				printf("Nespravny vstup.\n");
				return 0;
			}	
		}
		else
		{
			printf("Nespravny vstup.\n");
			return 0;
		}
	}
	return 0;
}

