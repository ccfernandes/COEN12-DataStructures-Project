//Chelsea Fernandes
//app1 header file

# ifndef SET_H
# define SET_H

typedef struct node NODE;
typedef struct list LIST;
typedef struct class CLASS;

CLASS *createDataSet(int range, int maxnum);
static LIST *createList();
void destroyDataSet(CLASS* sp);
LIST *searchAge(CLASS* sp, int age);
void insertion(CLASS* sp, int age, int id);
void deletion(CLASS* sp, LIST *lp, int age);
int maxAgeGap(CLASS *sp);

# endif /* SET_H */

