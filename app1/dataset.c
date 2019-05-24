//Chelsea Fernandes
//app1, dataset.c

#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "app1.h"

typedef struct node
{
	int id;
	struct node *prev;
	struct node *next;

}NODE;

typedef struct list
{
	int count;//number of students correlating to a certain age
	struct node *head;

}LIST;

typedef struct class
{
	int maxage;//max age of students in the class
	int minage;//min age of students in the class
	int count;//overall number of students in the class
	int length;//max number of students in class (3000)
	LIST **array;//array of LIST pointers pointing to list of IDs
	int arraysize;//number of slots in array (12);
}CLASS;

//allocates memory and initiates variables 
CLASS *createDataSet(int range, int maxnum)
{
	CLASS *sp = malloc(sizeof(CLASS)); //create memory
	assert(sp!=NULL);
	sp->maxage=18; //initialize all the values 
	sp->minage=30;
	sp->count=0;
	sp->length=maxnum;
	sp->arraysize=range;

	sp->array=malloc(sizeof(LIST*)*(sp->arraysize));//there are 12 dif ages
	assert(sp->array!=NULL);

	for(int i=0; i<13; i++)//initialize the linked lists 
	{
		sp->array[i]=createList();
	}
	return sp;
}

//creates the linked list, gets called by createDataSet
static LIST *createList()
{
	LIST *lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->head=malloc(sizeof(NODE));
	assert(lp->head!=NULL);
	lp->count=0;
	lp->head->prev=lp->head;
	lp->head->next=lp->head;
	return lp;
}

//frees all pointers associated with CLASS 
void destroyDataSet(CLASS *sp)
{
	assert(sp!=NULL);
	for(int i=0; i<12; i++)//iterate through age array
	{
		if(sp->array[i]->count>1)
		{
			NODE *pTail=sp->array[i]->head->prev;
			NODE *pDel=sp->array[i]->head;
			while(sp->array[i]->head!=pTail)//free all nodes, oldest to newest
			{
				pDel=sp->array[i]->head;
				sp->array[i]->head=pDel->next;
				free(pDel);
			}
			free(pTail);//free tail of id list
			free(sp->array[i]);//free dummy node of the if list
		}
	}
	free(sp);
}

//goes to index that corresponds to age and retrieves the linked list that is pointed to by that index
LIST *searchAge(CLASS *sp, int age)
{
	int index = age-18;
	assert(sp!=NULL);
	if(sp->array[index]->count>0)//if there are are people with that age, return that list of ids
	{
		printf("Students with an age of %d exist in the set\n", age);
		return sp->array[index];
	}
	else
	{
		printf("Students with an age of %d DO NOT exist in the set\n", age);
		return NULL;
	}
}

//inserts a new student's age and id and determines the new maximum and minimum age (if applicable)
void insertion(CLASS *sp, int age, int id)
{
	int index = age-18;

	assert(sp!=NULL&&age>0&&id>0);
	NODE *pNew = malloc(sizeof(NODE));
	assert(pNew!=NULL);

	pNew->next=sp->array[index]->head->next;
	pNew->prev=sp->array[index]->head;
	pNew->next->prev=pNew;
	sp->array[index]->head->next=pNew;

	pNew->id=id;
	sp->count++;
	sp->array[index]->count++;

	if(age>sp->maxage)//determine new minimum and maximum ages for entire class 
	{
		sp->maxage=age;
	}
	if(age<sp->minage)
	{
		sp->minage=age;
	}
}

//deletes all ids of the same age 
void deletion(CLASS *sp, LIST *lp, int age)//takes in list determined by search function
{
	assert(sp!=NULL);
	int temp = lp->count;
	NODE *pTail=lp->head->prev;
	NODE *pDel=lp->head;
	int i=0;
	while(lp->head->next!=pTail)//free all nodes, oldest to newest
	{
		pDel=lp->head;
		lp->head=pDel->next;
		free(pDel);
		i++;
		lp->count--;
		sp->count--;
	}
	
	if(lp->count==1)//if only the dummy node exists, deletion was completed 
	{
		printf("Deletion of the %d students with an age of %d has been completed.\n", temp, age);
	}
	else
	{
		printf("Deletion not completed\n");
	}

	for(int j=0; j<12; j++)//go through the list array and determine the new max and min age if applicable
	{
		if(sp->array[j]->count>0)
		{
			if((j+18)>sp->maxage)
			{
				sp->maxage=(j+18);
			}
			if((j+18)<sp->minage)
			{
				sp->minage=(j+18);
			}
		}
	}
}

//determines the max age gap and returns the value 
int maxAgeGap(CLASS *sp)
{
	printf("\nMax age: %d\nMin age: %d\n", sp->maxage,sp->minage);
	assert(sp!=NULL);
	return sp->maxage-sp->minage;
	
}

