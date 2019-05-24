//Chelsea Fernandes 
//app 2, dataset.c

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include "app2.h"

typedef struct student 
{
	int id;
	int age; 
}STUDENT;

//global variables 
STUDENT **array;
int count;
int length;

//creates data set (sorted array) and initiailizes variables 
void createDataSet(int maxnum)
{
	count=0;
	length=maxnum;
		
	array=malloc(sizeof(STUDENT)*maxnum);

	for(int i=0; i<maxnum; i++)//set all ages and id's to 0
	{
		array[i]=malloc(sizeof(STUDENT));	
		array[i]->id=0;		
		array[i]->age=0;
	}
}

//frees each pointer in the array  
void destroyDataSet()
{
	for(int i=0; i<count;i++)//go through array and free each pointer 
	{
		free(array[i]);
	}
}

//searches if there is a student with a specific idea. Returns the id if found and 0 if not found  
int searchID(int id)
{
	for(int i=0; i<2000; i++)//iterate through entire array
	{
		if(array[i]->id==id)//id is found, return id number 
		{
			printf("student with ID %d has been found\n", id);
			return id;
		}
	}
	printf("student with ID %d does not exist\n", id);
	return -1;
}

//inserts the student's age and id into the array
void insertion(int age, int id)
{
	array[id]->id=id;
	array[id]->age=age;
	count++;
}

//deletes the student from the array by setting the age and id to 0
void deletion(int id)
{
	int search = searchID(id);//check if the student with given id is present 
	if(search>0)//if it is, delete student 
	{
		array[id]->id=0;
		array[id]->age=0;
		count--;
		printf("deletion of student with ID %d has been completed.\n", id);
	}
	else
	{
		printf("Student does not exist, no need to delete.\n");
	}
}
