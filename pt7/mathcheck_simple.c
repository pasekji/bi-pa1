#include <stdio.h>
// used global variables for easy access

enum {
	number_size = 1000,           // number_size is the maximum length of number in string
	maximum_numbers_sum = 1000             // maximum_numbers_sum is the maximum of numbers that can be added
};

int numbers_sum = 10;          // numbers_sum holds the count of numbers added + result entered by the user in the program
int max_size = 0;          // max_size is the length of the longest number


char numbers[maximum_numbers_sum][number_size];            // 2d char array storing all the numbers
int sizes[maximum_numbers_sum];            // linear int array storing the sizes of all the numbers
int solutions = 0;             // solutions variable storing count of possible solutions of equation

// "calculate_sizes" procedure calculates sizes of each number at start of the program after taking input

void calculate_sizes()
{
	for (int i = 0; i < numbers_sum; i++)
	{
		for (int j = 0; j < number_size && ((numbers[i][j] >= '?') || (numbers[i][j] >= '0' && numbers[i][j] <= '9')); j++)
		{
			sizes[i]++;
		}
	}

	max_size = sizes[0];
	for (int i = 0; i < numbers_sum; i++)
	{
		if (max_size < sizes[i])
			max_size = sizes[i];
	}
	
}

// "checkQuestionsAtIndex" function calculates the number of question marks at an index and returns the total question marks count

int checkQuestionsAtIndex(int index)
{
	int questions = 0;
	for (int i = 0; i < numbers_sum; i++)
	{
		if (sizes[i] - 1 - index >= 0 && numbers[i][sizes[i] - 1 - index] == '?')
			questions++;
	}

	return questions;
}

/*
if an index has no question marks, then "checkCorrect" function is called,
"checkCorrect" function checks if the digits at index are giving correct output,
the carry int is passed from previous index,
returns 1 for correct value,
return 0 for wrong value
*/
 
int checkCorrect(int index, int *carry)
{
	int numbers_to_add = 0;
	int sum_digit = 0;

	if (sizes[numbers_sum - 1] - 1 - index >= 0)
		sum_digit = numbers[numbers_sum - 1][sizes[numbers_sum - 1] - 1 - index] - '0';

	for (int i = 0; i < numbers_sum - 1; i++)
	{
		if (sizes[i] - 1 - index >= 0)
			numbers_to_add = numbers_to_add + numbers[i][sizes[i] - 1 - index] - '0';
	}
	numbers_to_add = numbers_to_add + *carry;

	(*carry) = numbers_to_add / 10;
	if (numbers_to_add % 10 == sum_digit)
		return 1;
	else
		return 0;
}

// "unfoundValue" procedure puts question mark again at the index after the combination has used the value

void unfoundValue(int index, int j)
{
	numbers[j][sizes[j] - 1 - index] = '?';
}

/*
"foundpossibleValue" function is called when at a specific addition is a question mark,
for a single ? at an index, it puts the correct value only at that index to avoid checking all combinations, 
e.g : if 2 + ? = 7, this function will put 5 inplace of ? instead of checking all combinations,
j is the index of digit in which the question mark is, to put the question mark again there later
*/

int foundPossibleValue(int index, int * carry, int *foundValue, int * j)
{
	int sumOrDigits = 1;
	int numbers_to_add = 0;
	int sum_digit = 0;

	if (sizes[numbers_sum - 1] - 1 - index >= 0)
	{
		if (numbers[numbers_sum - 1][sizes[numbers_sum - 1] - 1 - index] == '?')
		{
			sumOrDigits = 0;
			*j = numbers_sum - 1;
		}
		else
		{
			sum_digit = numbers[numbers_sum - 1][sizes[numbers_sum - 1] - 1 - index] - '0';
		}
	}

	int qIndex = 0;
	for (int i = 0; i < numbers_sum - 1; i++)
	{
		if (sizes[i] - 1 - index >= 0)
		{
			if (sumOrDigits != 0 && numbers[i][sizes[i] - 1 - index] == '?')
			{
				qIndex = i;
				*j = i;
			}
			else
			{
				numbers_to_add = numbers_to_add + numbers[i][sizes[i] - 1 - index] - '0';
			}
		}

	}
	numbers_to_add = numbers_to_add + *carry;
	
	if (sumOrDigits == 0)
	{
		*foundValue = (numbers_to_add % 10);

		*foundValue = numbers[numbers_sum - 1][sizes[numbers_sum - 1] - 1 - index] = (numbers_to_add % 10) + '0';
	
	}
	else  if (sumOrDigits == 1)
	{

		if (numbers_to_add % 10 <= sum_digit)
		{
			*foundValue = sum_digit - (numbers_to_add % 10);

			*foundValue = numbers[qIndex][sizes[qIndex] - 1 - index] = sum_digit - (numbers_to_add % 10) + '0';
			numbers_to_add = numbers_to_add + sum_digit - (numbers_to_add % 10);
		}
		else
		{
			*foundValue = sum_digit + 10 - (numbers_to_add % 10);

			*foundValue = numbers[qIndex][sizes[qIndex] - 1 - index] = sum_digit + 10 - (numbers_to_add % 10) + '0';
			numbers_to_add = numbers_to_add + sum_digit + 10 - (numbers_to_add % 10);
		}

	}
	*foundValue = *foundValue - '0';
	*carry = numbers_to_add / 10;
	return 1;
}

/*
"markFirstQuestion" procedure finds the first question mark at index and marks the value passed at given index,
stores the number index in j to put question mark again later
*/
 
void markFirstQuestion(int index, int value, int *j)
{
	for (int i = 0; i < numbers_sum; i++)
	{
		if (sizes[i] - 1 - index >= 0 && numbers[i][sizes[i] - 1 - index] == '?')
		{
			numbers[i][sizes[i] - 1 - index] = value + '0';
			(*j) = i;
			return;
		}
	}

}

// "unmarkFirstQuestion" procedure puts question mark again to check other combinations

void unmarkFirstQuestion(int index, int j)
{
	numbers[j][sizes[j] - 1 - index] = '?';
}

/*
"calculatePossibilitiesNext" is the recursive procedure,
int index is index number,
int questions are the total questions at specific index,
int carry is the carry of previous index passed
*/
 
void calculatePossibilitiesNext(int index, int questions, int carry, int previousIndexCombination)
{
	
	if (index >= max_size)             // solution found as index has checked all the previous indices and none condition has been violated
	{
		if (carry == 0)
		{
			// if first solution, print on screen
			if (solutions == 0)
			{

				printf("%s", numbers[0]);
				for (int i = 1; i < numbers_sum - 1; i++)
				{
					printf("+%s", numbers[i]);
				}
				printf("=");
				printf("%s\n", numbers[numbers_sum - 1]);
			}
			solutions++;
		}
		return;
	}
	else if (questions == 0)           // if questions are 0, checks all values are correct at that index
	{
		if (checkCorrect(index, &carry))
		{	
			int q = checkQuestionsAtIndex(index + 1);
			calculatePossibilitiesNext(index + 1, q, carry, previousIndexCombination);
		}
		else
		{
			return;
		}


	}
	else if (questions == 1)           // if there is only one question mark, puts value of the required digit in place of question mark
	{

		int foundValue = 0;
		int j = 0;
		if (foundPossibleValue(index, &carry, &foundValue, &j))
		{
			int q = checkQuestionsAtIndex(index + 1);
			calculatePossibilitiesNext(index + 1, q, carry, previousIndexCombination);
			unfoundValue(index, j);
		}
		else
		{
			return;
		}
	}
	else if (questions > 1)            // if question marks are more than one at index, checks different combinations for different values of ?
	{
		for (int i = 0; i <= 9; i++)
		{
			int j = 0;
			markFirstQuestion(index, i, &j);
			calculatePossibilitiesNext(index, questions - 1, carry, 1);
			unmarkFirstQuestion(index, j);

		}
	}

}

// "calculatePossibilities" procedure calculates the question marks at index 0 and calls the recursive "calculatePossibilitiesNext" procedure

void calculatePossibilities()
{
	int index = 0;
	int q = checkQuestionsAtIndex(index);
	calculatePossibilitiesNext(index, q, 0, 0);
}


int main()
{
	int InputN = 0;            // specifying current input is nth number
	char inputChar = 0;            // to get input char
    printf("Priklad:\n");

	// input taking and error handling
	
	/*
	This loop is reading LHS of equation
	character by character. 
	This loop terminates
	when equal sign occurs.
	*/
	while (1)
	{
		char* arr = numbers[InputN++];
		int index = 0;

		/*
		This loop take next character and check its
		validity and if valid put into array of numbers
		and terminates when + or = sign occur.
		*/

		while (1) {

			scanf("%c", &inputChar);             // reading character by characer

			if (inputChar == '+' || inputChar == '=')
			{
				break;          // break if + or = is found 
			}
			else if (inputChar == '\n')
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
			else if ((inputChar >= '0' && inputChar <= '9') || inputChar == '?')
			{
				arr[index++] = inputChar;
			}
			else
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
		}
		arr[index] = 0;
		if (index == 0)
		{
            printf("Nespravny vstup.\n");
			return 0;
		}
		if (inputChar == '=')
		{
			break;
		}
	}


	// this block is to take input on the right hand side of equation
	{
		char* arr = numbers[InputN++];
		int index = 0;
		
		/*
		This loop take next character and check its
		validity and if valid put into array of numbers
		and successfully terminates when new line character occurs.
		*/
        
		while (1) {

			scanf("%c", &inputChar);
			if (inputChar == '\n')
			{
				break;
			}
			else if ((inputChar >= '0' && inputChar <= '9') || inputChar == '?')
			{
				arr[index++] = inputChar;
			}
			else
			{
				printf("Nespravny vstup.\n");
				return 0;
			}
		}

		arr[index] = 0;

		if (index == 0)
		{
            printf("Nespravny vstup.\n");
			return 0;
		}
	}

	numbers_sum = InputN;

	// to calculate sizes of the different numbers, used in the accessing the values
	calculate_sizes();
	
	// recursive procedure that generates and checks combinations
	calculatePossibilities();

	if (solutions == 0)
	{
		printf("Nelze dosahnout.\n");
	}
	else
	{
		printf("Celkem: %d\n", solutions);
	}

	return 0;
}
