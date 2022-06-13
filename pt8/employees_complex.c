#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar
{
	struct TCar              * m_Next;
	char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
	struct TEmployee         * m_Next;
	struct TCar              * m_Car;
	char                     * m_Name;


} TEMPLOYEE;

typedef struct TOffice
{
	TEMPLOYEE                * m_Emp;
	TCAR                     * m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */
/*

void print(TOFFICE* o)
{
if (o != NULL)
{
TEMPLOYEE* e = o->m_Emp;
TCAR* c = o->m_Car;

printf("Cars\n");
while (c != NULL)
{
if (c->m_Model != NULL)
{
printf(c->m_Model);
printf("\n");
}
c = c->m_Next;
}
printf("\n");

printf("Employees\n");
while (e != NULL)
{
if (e->m_Name != NULL)
{
printf(e->m_Name);
printf(" ");
}
if (e->m_Car != NULL && e->m_Car->m_Model != NULL)
{
printf("<--");
printf(e->m_Car->m_Model);
printf("\n");
}
e = e->m_Next;

}
printf("\n");
printf("\n");
}
}*/



TEMPLOYEE        * newEmployee(const char      * name,
                                TEMPLOYEE       * root)
{
	TEMPLOYEE * c = (TEMPLOYEE *)malloc(sizeof(TEMPLOYEE));

	//copying name
	if (name != NULL)
	{
		c->m_Name = strdup(name);

		/*c->m_Name = (char*)malloc(strlen(name) + 1);
		strcpy(c->m_Name, name);*/
	}
	else
	{
		/*c->m_Name = (char*)malloc(sizeof(""));
		c->m_Name[0] = 0;*/

		c->m_Name = NULL;
	}
	c->m_Car = NULL;
	c->m_Next = root;
	return c;

}



TCAR        * newCar(const char      * model,
                        TCAR       * root)
{
	TCAR * c = (TCAR *)malloc(sizeof(TCAR));
	//copying name
	if (model != NULL)
	{
		c->m_Model = strdup(model);

		/*c->m_Model = (char*)malloc(strlen(model)+1);
		strcpy(c->m_Model, model);*/
	}
	else
	{
		/*c->m_Model = (char*)malloc(sizeof(""));
		c->m_Model[0] = 0;*/


		c->m_Model = NULL;

	}
	c->m_Next = root;
	return c;

}



TOFFICE          * initOffice()
{
	/* todo */
	TOFFICE * c = (TOFFICE*)malloc(sizeof(TOFFICE));
	c->m_Emp = NULL;
	c->m_Car = NULL;
	return c;


}
void               addEmployee(TOFFICE         * office,
                                const char      * name)
{
	/* todo */
	if (office != NULL)
	{
		office->m_Emp = newEmployee(name, office->m_Emp);
	}
}
void               addCar(TOFFICE         * office,
                            const char      * model)
{
	/* todo */
	if (office != NULL)
	{
		office->m_Car = newCar(model, office->m_Car);
	}



}
TOFFICE          * cloneOffice(TOFFICE         * office)
{
	/* todo */
	if (office != NULL)
	{


		TOFFICE * o = (TOFFICE*)malloc(sizeof(TOFFICE));
		o->m_Emp = NULL;
		o->m_Car = NULL;

		//creating copies of nodes next to each other	

		TEMPLOYEE* e = office->m_Emp;
		TEMPLOYEE* e_copy = e;

		TCAR* c = office->m_Car;

		while (e != NULL)
		{
			TEMPLOYEE * copy_employee = (TEMPLOYEE *)malloc(sizeof(TEMPLOYEE));
			TEMPLOYEE* save_next = e->m_Next;
			//copying name
			if (e->m_Name != NULL)
			{
				copy_employee->m_Name = strdup(e->m_Name);/*
                copy_employee->m_Name = (char *)malloc(strlen(e->m_Name) + 1);
                strcpy(copy_employee->m_Name, e->m_Name);*/
			}
			else
			{
				/*copy_employee->m_Name = (char*)malloc(sizeof(""));
				copy_employee->m_Name[0] = 0;
				*/

				copy_employee->m_Name = NULL;
			}
			e->m_Next = copy_employee;
			copy_employee->m_Car = NULL;
			copy_employee->m_Next = save_next;

			e = save_next;
		}

		if (office->m_Emp != NULL)
			o->m_Emp = office->m_Emp->m_Next;

		while (c != NULL)
		{
			TCAR * copy_car = (TCAR *)malloc(sizeof(TCAR));
			TCAR* save_next = c->m_Next;
			//copying model
			if (c->m_Model != NULL)
			{
				copy_car->m_Model = strdup(c->m_Model);
				/*
				copy_car->m_Model = (char *)malloc(strlen(c->m_Model)+1);
				strcpy(copy_car->m_Model, c->m_Model);*/
			}
			else
			{
				/*copy_car->m_Model = (char*)malloc(sizeof(""));
				copy_car->m_Model[0] = 0;
				*/
				copy_car->m_Model = NULL;
			}

			c->m_Next = copy_car;
			copy_car->m_Next = save_next;

			c = save_next;
		}
		if (office->m_Car != NULL)
			o->m_Car = office->m_Car->m_Next;

		e = e_copy;
		while (e != NULL)
		{
			if (e->m_Car != NULL)
			{
				e->m_Next->m_Car = e->m_Car->m_Next;
			}
			e = e->m_Next->m_Next;
		}


		//separating lists
		e = office->m_Emp;
		c = office->m_Car;

		while (e != NULL)
		{
			TEMPLOYEE* copy_e = e->m_Next;
			e->m_Next = copy_e->m_Next;

			if (copy_e->m_Next != NULL)
				copy_e->m_Next = copy_e->m_Next->m_Next;

			e = e->m_Next;
		}

		while (c != NULL)
		{
			TCAR* copy_c = c->m_Next;
			c->m_Next = copy_c->m_Next;

			if (copy_c->m_Next != NULL)
				copy_c->m_Next = copy_c->m_Next->m_Next;

			c = c->m_Next;
		}

		return o;
	}
	else
	{
		return NULL;
	}

}
void               freeOffice(TOFFICE         * office)
{
	/* todo */
	if (office != NULL)
	{
		TEMPLOYEE* e = office->m_Emp;
		TCAR* c = office->m_Car;

		while (e != NULL)
		{
			TEMPLOYEE* temp = e->m_Next;
			if (e->m_Name != NULL)
				free(e->m_Name);
			free(e);
			e = temp;
		}

		while (c != NULL)
		{
			TCAR* temp = c->m_Next;
			if (c->m_Model != NULL)
				free(c->m_Model);
			free(c);
			c = temp;
		}

		free(office);
		office = NULL;
	}

}

#ifndef __PROGTEST__
int main(int argc, char * argv[])
{
	TOFFICE * a, *b;
	char tmp[100];

	assert(sizeof (TOFFICE) == 2 * sizeof (void *));
	assert(sizeof (TEMPLOYEE) == 3 * sizeof (void *));
	assert(sizeof (TCAR) == 2 * sizeof (void *));
	a = initOffice();
	addEmployee(a, "Peter");
	addEmployee(a, "John");
	addEmployee(a, "Joe");
	addEmployee(a, "Maria");
	addCar(a, "Skoda Octavia");
	addCar(a, "VW Golf");
	a->m_Emp->m_Car = a->m_Car;
	a->m_Emp->m_Next->m_Next->m_Car = a->m_Car->m_Next;
	a->m_Emp->m_Next->m_Next->m_Next->m_Car = a->m_Car;
	assert(a->m_Emp
		&& !strcmp(a->m_Emp->m_Name, "Maria")
		&& a->m_Emp->m_Car == a->m_Car);
	assert(a->m_Emp->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Name, "Joe")
		&& a->m_Emp->m_Next->m_Car == NULL);
	assert(a->m_Emp->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Name, "John")
		&& a->m_Emp->m_Next->m_Next->m_Car == a->m_Car->m_Next);
	assert(a->m_Emp->m_Next->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter")
		&& a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car);
	assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL);
	assert(a->m_Car
		&& !strcmp(a->m_Car->m_Model, "VW Golf"));
	assert(a->m_Car->m_Next
		&& !strcmp(a->m_Car->m_Next->m_Model, "Skoda Octavia"));
	assert(a->m_Car->m_Next->m_Next == NULL);
	b = cloneOffice(a);
	strncpy(tmp, "Moe", sizeof (tmp));
	addEmployee(a, tmp);
	strncpy(tmp, "Victoria", sizeof (tmp));
	addEmployee(a, tmp);
	strncpy(tmp, "Peter", sizeof (tmp));
	addEmployee(a, tmp);
	strncpy(tmp, "Citroen C4", sizeof (tmp));
	addCar(a, tmp);
	b->m_Emp->m_Next->m_Next->m_Next->m_Car = b->m_Car->m_Next->m_Next;
	assert(a->m_Emp
		&& !strcmp(a->m_Emp->m_Name, "Peter")
		&& a->m_Emp->m_Car == NULL);
	assert(a->m_Emp->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Name, "Victoria")
		&& a->m_Emp->m_Next->m_Car == NULL);
	assert(a->m_Emp->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Name, "Moe")
		&& a->m_Emp->m_Next->m_Next->m_Car == NULL);
	assert(a->m_Emp->m_Next->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Name, "Maria")
		&& a->m_Emp->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next);
	assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Name, "Joe")
		&& a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Car == NULL);
	assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "John")
		&& a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next->m_Next);
	assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
		&& !strcmp(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "Peter")
		&& a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Car == a->m_Car->m_Next);
	assert(a->m_Emp->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
	assert(a->m_Car
		&& !strcmp(a->m_Car->m_Model, "Citroen C4"));
	assert(a->m_Car->m_Next
		&& !strcmp(a->m_Car->m_Next->m_Model, "VW Golf"));
	assert(a->m_Car->m_Next->m_Next
		&& !strcmp(a->m_Car->m_Next->m_Next->m_Model, "Skoda Octavia"));
	assert(a->m_Car->m_Next->m_Next->m_Next == NULL);
	assert(b->m_Emp
		&& !strcmp(b->m_Emp->m_Name, "Maria")
		&& b->m_Emp->m_Car == b->m_Car);
	assert(b->m_Emp->m_Next
		&& !strcmp(b->m_Emp->m_Next->m_Name, "Joe")
		&& b->m_Emp->m_Next->m_Car == NULL);
	assert(b->m_Emp->m_Next->m_Next
		&& !strcmp(b->m_Emp->m_Next->m_Next->m_Name, "John")
		&& b->m_Emp->m_Next->m_Next->m_Car == b->m_Car->m_Next);
	assert(b->m_Emp->m_Next->m_Next->m_Next
		&& !strcmp(b->m_Emp->m_Next->m_Next->m_Next->m_Name, "Peter")
		&& b->m_Emp->m_Next->m_Next->m_Next->m_Car == NULL);
	assert(b->m_Emp->m_Next->m_Next->m_Next->m_Next == NULL);
	assert(b->m_Car
		&& !strcmp(b->m_Car->m_Model, "VW Golf"));
	assert(b->m_Car->m_Next
		&& !strcmp(b->m_Car->m_Next->m_Model, "Skoda Octavia"));
	assert(b->m_Car->m_Next->m_Next == NULL);
	freeOffice(a);
	freeOffice(b);
	return 0;
}
#endif /* __PROGTEST__ */
