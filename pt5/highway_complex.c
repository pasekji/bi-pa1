#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26

struct Change
{
	int start;
	int end;
	float charge;
	struct Change *next;
};

// from A-Z
struct Change changeHeads[MAX];
float charges[MAX];
void printIt()
{
    char i;
    struct Change *r;
	for(i = 'A'; i <= 'Z'; i++)
	{
	    r = &changeHeads[i-'A'];
	    if(r->next==NULL)continue;
	    printf("\n\t%c =>",i);
	    r= r->next;
		while(r!=NULL)
        {
            printf("\t\t[%d - %d : %f]\n",r->start,r->end,r->charge);
            r = r->next;
        }

	}
}
int insert(struct Change *changeHeads,int start,int end,float charge)
{
    if(start>=end)
        return 0;
	struct Change *newcharge = (struct Change *)malloc(sizeof(struct Change));
	if(newcharge==NULL)
	{
		printf("Nespravny vstup.\n");
		exit(0);
	}
	newcharge->start = start;
	newcharge->end = end;
	newcharge->charge = charge;
	newcharge->next = changeHeads->next;
	changeHeads->next = newcharge;
	return 1;
}
void merge(struct Change *changeHeads)
{
    struct Change * root = changeHeads->next;
    struct Change * nextchange;
    if(root==NULL)
        return;
    nextchange = root->next;
    while(nextchange!=NULL)
    {
        if(root->end==nextchange->start  && root->charge==nextchange->charge)
        {
            root->end = nextchange->end;
            root->next = nextchange->next;
            free(nextchange);
            nextchange = root->next;

        }
        else
        {
            root = nextchange;
            nextchange = nextchange->next;
        }
    }
}
void insertRecursive(struct Change *ch,int start,int end,float charge){
    struct Change * root = ch->next;
    struct Change * prev = ch;
    if(root==NULL)
    {
        //first change, or the end of list
        insert(ch,start,end,charge);
	}
	else if(end <= root->start)
    {
	    // 1
        insert(ch,start,end,charge);
	}
	else if(start >= root->end)
    {
	    // 6
	    insertRecursive(root,start,end,charge);
	}
	else if(start < root->start && end <= root->end)
    {
	    //2
	    if(( end == root->end || charge==root->charge))
        {
            // 2'
            root->charge = charge;
            root->start = start;
	    }
	    else
        {
	        //2
            root->start = end;
            insert(prev,start,end,charge);
	    }
	}
	else if(start >= root->start && end <= root->end)
    {
	    //4
	    float c = root->charge;
	    int e =root->end;
        int s = root->start;
	    if(charge!=root->charge)
        {
            if(start==root->start)
            {
                //4 & 4'
                root->end = end;
                root->charge = charge;
                insert(root,end,e,c);

            }
            else
            {
                if(end==root->end)
                {
                    // 4'''
                    root->start = start;
                    root->charge = charge;
                    insert(prev,s,start,c);
                }else
                {
                    // 4''
                    root->end = start;
                    insertRecursive(root,start,end,charge);
                    insertRecursive(root,end,e,c);
                }
            }
	    }
	}
	else if(start <= root->start  && end > root->end)
    {
        //3
        root->start = start;
        root->charge = charge;
        insertRecursive(root,root->end,end,charge);
	}
	else if(start >= root->start  && start < root->end && end > root->end)
    {
        //5
        if(start == root->start)
        {
            //5'
            root->charge = charge;
            insertRecursive(root,root->end,end,charge);

        }
        else if(root->charge != charge)
        {
            //5''
            root->end = start;
            insertRecursive(root,start,end,charge);

        }
        else
        {
            //5'''
            insertRecursive(root,root->end,end,charge);
            merge(root);

        }
	}
}
float getCharge(struct Change *change,int start,int end)
{
	float f = 0.0;
	if(change == NULL || start < 0 || end < 0 || (start >= end))
		return f;
	if(start >= change->start && start <= change->end)
	{
		if(end <= change->end)
		{
            f = (float)(end - start)*change->charge;
		}
		else
		{
			f =(float) (change->end - start)*change->charge;
			f += getCharge(change->next,change->end,end);
		}
	}
	else if(start <= change->start)
 	{
		if(end <= change->start)
		{
			return 0.0;
		}
		else if(end > change->start && end<= change->end)
		{
			f =(float) (end - change->start)*change->charge;
		}
		else if(end >= change->end)
		{
			f =(float) (change->end - change->start)*change->charge;
			f += getCharge(change->next,change->end,end);
		}
	}
	else if(start >= change->end)
	{
		f = getCharge(change->next,start,end);
	}
	return f;
}

void initCharges(float charges[])
{
    int i;
	for(i = 0; i < MAX; i++)
	{
		charges[i] = 0.0;
	}
}

void initChangeHeads(struct Change changeHeads[])
{
	int i;
	//set all to 0s and NULL
	for(i = 0; i < MAX; i++)
	{
		changeHeads[i].next = NULL;
		changeHeads[i].start = 0;
		changeHeads[i].end = 0;
		changeHeads[i].charge = 0.0;
	}
}

void getChange(struct Change changeHeads[])
{
	struct Change tempChange;
	char fee;
	int cnt = scanf(" [ %d - %d : %c = %f ] ",&tempChange.start,&tempChange.end,&fee,&tempChange.charge);
	if(cnt == 0 || fee > 'Z' || fee < 'A' || tempChange.start < 0 || tempChange.end < 0 || tempChange.start >= tempChange.end || tempChange.charge < 0)
	{
		printf("Nespravny vstup.\n");
		exit(0);
	}
	insertRecursive(&changeHeads[fee-'A'],tempChange.start,tempChange.end,tempChange.charge);
}

void calculateChargeForAllFees(struct Change changeHeads[],float charges[],int start,int end)
{
	char i;
	for(i = 'A'; i <= 'Z'; i++)
	{
		charges[i-'A'] = getCharge(&changeHeads[i-'A'],start,end);
	}
}

char getNextNotZeroCharge(float charges[],char currentFee)
{
	char i ;
	for(i = currentFee + 1; i <= 'Z'; i++)
	{
		if(charges[i-'A'] > 0.0)
		{
			return i;
		}
	}
	return 'Z'+1;
}

void printAllCharges(float charges[])
{
	char i ;
	for(i = 'A'; i <= 'Z'; i++)
	{
		if(charges[i-'A'] > 0.0)
		{
			printf(" %c=%.6f",i,charges[i-'A']);
			i = getNextNotZeroCharge(charges,i);
			if(i <= 'Z')
			{
				i--;
				printf(",");
			}
		}
	}
	puts("");
}

int main()
{
	printf("Zmeny:\n");
	initChangeHeads(changeHeads);
	char c;
	while((c = getchar()) != '}')
	{
		//get next change
		getChange(changeHeads);
	}
	printf("Hledani:\n");
	int x,y,start,end;
	int print = 0;
	while(getchar() != EOF)
	{
		initCharges(charges);
		if(scanf("%d %d", &x, &y) == 2)
		{
			print = 0;
		}
		if(x < 0 || y < 0 || x == y)
		{
			printf("Nespravny vstup.\n");
			return 0;
		}
		if(x < y)
		{
			start = x;
			end = y;
		}
		else
		{
			start = y;
			end = x;
		}
		if(print < 1)
		{
			printf("%d - %d:", x, y);
			calculateChargeForAllFees(changeHeads,charges,start,end);
			printAllCharges(charges);
			print++;
		}
	}
	return 0;
}
