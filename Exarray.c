#include<stdio.h>
#include<stdlib.h>
#include"lambda.h"
#include"myType.h" 
#include"macroArray.h" //定义了宏的头文件（适用于内置数据类型） 
#include"macroArray2.h"// 定义了宏的头文件（适用于自定义数据类型（struct））
typedef char *string;
__ExpendArray(int) //生成包含一个int数组struct （智能int数组） 
__ExpendArray(double) //生成包含一个double数组的struct （智能double数组）
__ExpendArray(string)
__ExpendMyArray(pMytype)//同上，Mytype是一个struct，里面有一个int和一个double，pMytype是Mytype的指针 
__ExpendMyArray(pintArray)//智能数组的数组 (pintArray)是指向intArray的指针，别的数组也可以使用 
void addItemD(Array(double) *arr) {arr->addItem(arr,75.57);}/*这样的数组传到函数里不会退化成指针 */

int main()
{
	Array(int) int_array,int_array2;
	Array(double) d_array; 
	Array(string) strs;
	Array(pMytype) my_array,my_array2;
	Array(pintArray) multi_array,multi_array2,high_array;
	//*
	IniEmptyArr(string,strs);
	P1(strs,addItem,"hahaha");
	strs.addItem(&strs, "wahaha");
	//P0(strs,print);
	//*/
	IniArr(int,int_array,"2,4,6"); 
	IniArr(int,int_array2,"14");
	P1(int_array,expend,&int_array2);
	//P0(int_array,print);
	//*
	IniArr(double,d_array,"12.34, 33.44, 144.441");
	P1(d_array,setFormat,"%.2lf");
	lambda(func,double,x,x*2);
	P1(d_array,mapEvery,func);
	//*/
	IniEmptyArr(pintArray,multi_array);
	P1(multi_array,addItem,&d_array);
	P1(multi_array,addItem,&int_array2);
	P1(multi_array,addItem,&strs);
	
	printf("multi_array:\n");P0(multi_array,print);
	
	IniEmptyArr(pintArray,multi_array2);
	P1(multi_array2,addItem,getMytype(2,5.5));
	P1(multi_array2,addItem,&int_array);
	printf("multi_array2:\n");P0(multi_array2,print);
	//*//
	IniEmptyArr(pintArray,high_array);
	P1(high_array,addItem,&multi_array);
	P1(high_array,addItem,&multi_array2);
	printf("high_array:\n");P0(high_array,print);
	
	return 0;
}
