#include<stdio.h>
#include<stdlib.h>
#include"lambda.h"
#include"myType.h" 
#include"macroArray.h" //�����˺��ͷ�ļ��������������������ͣ� 
#include"macroArray2.h"// �����˺��ͷ�ļ����������Զ����������ͣ�struct����
typedef char *string;
__ExpendArray(int) //���ɰ���һ��int����struct ������int���飩 
__ExpendArray(double) //���ɰ���һ��double�����struct ������double���飩
__ExpendArray(string)
__ExpendMyArray(pMytype)//ͬ�ϣ�Mytype��һ��struct��������һ��int��һ��double��pMytype��Mytype��ָ�� 
__ExpendMyArray(pintArray)//������������� (pintArray)��ָ��intArray��ָ�룬�������Ҳ����ʹ�� 
void addItemD(Array(double) *arr) {arr->addItem(arr,75.57);}/*���������鴫�������ﲻ���˻���ָ�� */

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
