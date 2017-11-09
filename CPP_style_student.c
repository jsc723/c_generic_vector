#include <stdio.h>
#include <string.h>
 
struct Student;
 
typedef struct StudentVtbl
{
    char* (*GetName)(struct Student* This);
    void(*SetName)(struct Student* This, char*);
}StudentVtbl;
 
typedef struct Student
{
    StudentVtbl* lpVtbl;
    char name[20];
}Student;
 
char* stu_GetName(Student* This)
{
    return This->name;
}
 
void stu_SetName(Student* This, char* newName)
{
    strcpy(This->name, newName);
}
 
StudentVtbl stuVtbl = { stu_GetName, stu_SetName };
 
int main()
{
    Student stu = { &stuVtbl };
    stu.lpVtbl->SetName(&stu, "Jack");
    printf("student name = %s", stu.lpVtbl->GetName(&stu));
    return 0;
}
