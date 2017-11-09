#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char string[100];
typedef enum sex{male,female}sex;
typedef struct Student *pStudent;
typedef struct Student{
	string name;
	string class;
	string address;
	sex se;
	int age;
	double height;
}Student;
pStudent getStudent( string pr_name,string pr_class,string pr_address,sex pr_se,int pr_age,double pr_height);
void copyStudent(pStudent stu,pStudent pr_stu);
void printStudent(pStudent stu);

pStudent getStudent( string pr_name,string pr_class,string pr_address,sex pr_se,int pr_age,double pr_height)
{
	pStudent stu = (pStudent)malloc(sizeof(Student));
	strcpy(stu->name,pr_name);
	strcpy(stu->class,pr_class);
	strcpy(stu->address,pr_address);
	stu->se = pr_se;
	stu->age = pr_age;
	stu->height = pr_height;
	return stu;}
void copyStudent(pStudent stu,pStudent pr_stu)
{
	strcpy(stu->name,pr_stu->name);
	strcpy(stu->class,pr_stu->class);
	strcpy(stu->address,pr_stu->address);
	stu->se = pr_stu->se;
	stu->age = pr_stu->age;
	stu->height = pr_stu->height;
}
void printStudent(pStudent stu)
{
	printf("{ ");
	printf("name=%s ",stu->name);
	printf("class=%s ",stu->class);
	printf("address=%s ",stu->address);
	printf("se=%d ",stu->se);
	printf("age=%d ",stu->age);
	printf("height=%.2lf ",stu->height);
	printf("}\n");
}
