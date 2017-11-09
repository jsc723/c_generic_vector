#ifndef MYTYPE_H
#define MYTYPE_H
typedef struct Mytype *pMytype;
typedef struct Mytype{
	void (*print)(pMytype);
	char *(*toString)(pMytype);
	void (*copy)(pMytype,pMytype);
	int a;
	double b;
}Mytype;
pMytype constructMytype(pMytype pm_src);

void myTypePrint(pMytype pm)
{
	printf("%s",pm->toString(pm));
}
char *myTypeToString(pMytype pm)
{
	char *str = malloc(sizeof(char)*100);
	sprintf(str,"{ a=%d b=%.1lf }",pm->a,pm->b);
	return str;
}
void myTypeCopy(pMytype pm_this,pMytype pm_src)
{
	pm_this->a = pm_src->a;
	pm_this->b = pm_src->b;
}

pMytype getMytype(int a1,double b1)
{
	pMytype obj = (pMytype)malloc(sizeof(Mytype));
	obj->a = a1;
	obj->b = b1;
	obj->print = &myTypePrint;
	obj->copy = &myTypeCopy;
	obj->toString = &myTypeToString;
	return obj;
}
pMytype copyMytype(pMytype pm_src)
{
	return getMytype(pm_src->a,pm_src->b);
}
#endif
