//app2 header file

# ifndef SET_H
# define SET_H

typedef struct student STUDENT;

void createDataSet(int maxnum);
void destroyDataSet();
int searchID(int id);
void insertion(int age, int id);
void deletion(int id);

# endif /* SET_H */


