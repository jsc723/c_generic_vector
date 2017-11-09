#ifndef MACROARRAY_H
#define MACROARRAY_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef enum{false,true} bool;

int __strArrLen(const char* str);
bool decideFormat(char* format,const char* type);


//#define arrlen(a) (sizeof(a)/sizeof(a[0]))
#define Str_Max 128
#define Arr_Max 100
#define _flen_ 16

//#define arrWithSize(a) a , arrlen(a)

#define Array(T) T##Array
#define pArray(T) p##T##Array 
//--------------------------------------------------------------------

#define __ExpendArray(T) \
__DefArr(T) \
__DefSetFormat(T) \
__DefAddItem(T) \
__DefExpend(T)\
__DefDelete(T)\
__DefPrintArr(T) \
__DefMapArr(T)\
__DefToString(T)\
__DefIniArrFuc(T) \
__DefStrToArr(T) 



//--------------------------------------------------------------------
#define P0(Inst,Method) Inst.Method(&(Inst))
#define P1(Inst,Method,Arg) Inst.Method(&(Inst),Arg)
#define P2(Inst,Method,Arg1,Arg2) Inst.Method(&(Inst),Arg1,Arg2)
#define P3(Inst,Method,Arg1,Arg2,Arg3) Inst.Method(&(Inst),Arg1,Arg2,Arg3)

//-------------------------------------------- 
//定义结构体 



#define __DefArr(T) \
typedef struct T##Array *p##T##Array;\
typedef struct T##Array\
{\
	\
	void (*print)(p##T##Array);\
	char *(*toString)(p##T##Array);\
	void (*setFormat)(p##T##Array,const char*);\
	void (*addItem)(p##T##Array,T);\
	void (*expend)(p##T##Array,p##T##Array);\
	void (*delItemAt)(p##T##Array,int);\
	void (*mapEvery)(p##T##Array,T (*f)(T term));\
	\
	T array[Arr_Max];\
	int length;\
	char format[_flen_];\
	char typeName[_flen_*2];\
	bool containsPointer;\
	\
}T##Array;

//帮助简化初始化的宏 
#define IniArr(t,arr,str) Ini##t##Arr( &arr , __strTo##t##Arr(str), __strArrLen(str) )
#define IniEmptyArr(T,arr) Ini##T##Arr( &arr ,NULL,0)

//定义初始化结构体的宏 
#define __DefIniArrFuc(T) \
void Ini##T##Arr( T##Array *arr, T c_array[] , int len)\
{\
	int i;\
	arr->length = len;\
	strcpy(arr->typeName,#T);\
	arr->containsPointer = decideFormat(arr->format,#T);\
	arr->setFormat = &__setEx##T##Format;\
	\
	arr->addItem = &__add##T##Item;\
	arr->expend = &__expend##T;\
	arr->delItemAt = &__del##T##At;\
	arr->mapEvery = &__map##T##Arr;\
	arr->print = &__printEx##T##Arr;\
	arr->toString = &__a##T##ArrToString;\
	\
	if(!arr->containsPointer)\
	{\
		for(i=0;i<len;i++)\
		{\
			arr->array[i] = c_array[i];\
		}\
	}\
	free(c_array);\
}


//定义 转换一个字符串到相应类型的数组 的函数 
#define __DefStrToArr(T) \
T *__strTo##T##Arr(const char* str)\
{\
	int i=0,len=__strArrLen(str),t;\
	T *temp;\
	char type[] = #T ;\
	char format[_flen_];\
	const char *pstr = str;\
	decideFormat(format,type);\
	temp = (T *)malloc(len*sizeof(T));\
	for(i=0;i<len;i++)\
	{\
		sscanf(pstr,format,temp+i);\
		while(1)\
		{\
			pstr++;\
			if(pstr[0]==','||pstr[0]=='\0')\
				break;\
		}\
		pstr++;\
	}\
	return temp;\
}


//定义打印数组的函数 
#define __DefPrintArr(T)\
void __printEx##T##Arr( T##Array *arr)\
{\
	printf("%s\n",arr->toString(arr));\
}

//定义设置数组元素用printf打印的格式的函数 
#define __DefSetFormat(T)\
void __setEx##T##Format( T##Array *arr, const char *format)\
{\
	strcpy(arr->format,format);\
}
//定义给数组后面添加元素的函数 
#define __DefAddItem(T)\
void __add##T##Item(T##Array *arr,T thing)\
{\
	arr->array[arr->length] = thing;\
	arr->length++;\
}
//定义给数组后面添加一个数组 
#define __DefExpend(T)\
void __expend##T(T##Array *arr,T##Array *things)\
{\
	int i=0;\
	for(i=0;i<things->length;i++)\
		arr->addItem(arr,things->array[i]);\
}
//删除数组制定位置的元素 
#define __DefDelete(T)\
void __del##T##At(T##Array *arr,int index)\
{\
	if(arr->length <= index)\
		return;\
	int i;\
	for(i = index+1;i<arr->length;i++)\
		arr->array[i-1] = arr->array[i];\
	arr->length--;\
}
//map函数 
#define __DefMapArr(T)\
void __map##T##Arr(T##Array *arr,T (*f)(T term))\
{\
	int i;\
	for(i=0;i<arr->length;i++)\
		arr->array[i] = f(arr->array[i]);\
}
//toString函数 
#define __DefToString(T)\
char *__a##T##ArrToString(p##T##Array arr) \
{\
	char *buffer = malloc(sizeof(char)*Str_Max);\
	char f[_flen_];\
	buffer[0] = '\0';\
	sprintf(f,"%%s %s",arr->format);\
	sprintf(buffer,"{");\
	int i;\
	for(i=0;i<arr->length;i++)\
	{\
		sprintf(buffer,f,buffer,arr->array[i]);\
		if(i<arr->length-1) \
			sprintf(buffer,"%s, ",buffer);\
	}\
	sprintf(buffer,"%s }",buffer);\
	return buffer;\
}
//计算由一个字符串给出的数组的长度（通过数逗号） 
int __strArrLen(const char* str)
{
	int len = 0,i;
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]==',')
		{
			len++;
			str[i] == ' ';
		}
	}
	return (i==0)?0:(len+1);
}

//把给出的类型转换为相应的printf用的标示符 
bool decideFormat(char* format,const char* type)
{
	if(strcmp(type,"int")==0)strcpy(format,"%d");
	else if(strcmp(type,"long")==0)strcpy(format,"%ld");
	else if(strcmp(type,"long long")==0)strcpy(format,"%lld");
	else if(strcmp(type,"float")==0)strcpy(format,"%f");
	else if(strcmp(type,"double")==0)strcpy(format,"%lf");
	else if(strcmp(type,"long double")==0)strcpy(format,"%llf");
	else if(strcmp(type,"char")==0)strcpy(format,"%c");
	else if(strcmp(type,"string")==0)strcpy(format,"%s");
	else 
	{
		strcpy(format,"%p");
		return true;
	}
	return false;
}


#endif




	
