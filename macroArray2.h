/* 
假设这个数组包含的struct myType已经实现了以下方法(函数名也要一致)：
void myTypePrint(pMytype);
*/ 
#ifndef MACROARRAY2_H
#define MACROARRAY2_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"macroArray.h"

extern int __strArrLen(const char* str);
extern bool decideFormat(char* format,const char* type);

//--------------------------------------------------------------------

#define __ExpendMyArray(T) \
__DefArr(T) \
__DefSetFormat(T) \
__DefAddItem(T) \
__DefExpend(T)\
__DefPrintArr(T) \
__DefMyDelete(T)\
__DefMyToString(T)\
__DefMyIniArrFuc(T) 


//--------------------------------------------------------------------


#define __DefMyIniArrFuc(T) \
void Ini##T##Arr( T##Array *arr, T c_array[] , int len)\
{\
	int i;\
	arr->length = len;\
	strcpy(arr->typeName,#T);\
	arr->containsPointer = decideFormat(arr->format,#T);\
	arr->addItem = &__add##T##Item;\
	arr->expend = &__expend##T;\
	arr->delItemAt = &__del##T##At;\
	arr->print = &__printEx##T##Arr;\
	arr->toString = &__a##T##MyArrToString;\
	free(c_array);\
}


#define __DefMyDelete(T)\
void __del##T##At(T##Array *arr,int index)\
{\
	if(arr->length <= index)\
		return;\
	int i;\
	T p = arr->array[index];\
	for(i = index+1;i<arr->length;i++)\
		arr->array[i-1] = arr->array[i];\
	arr->length--;\
	free(p);\
}

#define __DefMyToString(T) \
char *__a##T##MyArrToString(p##T##Array arr) \
{\
	char *buffer = malloc(sizeof(char)*Str_Max);\
	buffer[0] = '\0';\
	sprintf(buffer,"{");\
	int i;\
	for(i=0;i<arr->length;i++)\
	{\
		sprintf(buffer,"%s %s",buffer,arr->array[i]->toString(arr->array[i]));\
		if(i<arr->length-1) \
			sprintf(buffer,"%s, ",buffer);\
	}\
	sprintf(buffer,"%s }",buffer);\
	return buffer;\
}

#endif




	
