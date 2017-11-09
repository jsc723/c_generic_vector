#ifndef LAMBDA_H
#define LAMBDA_H

#define lambda2(name,type_in,input,type_out,result) type_out name(type_in input) {return result;}

#define __LAMBDA3(name,type,input,result) type name(type input) {return result;}

#define __LAMBDA2(prename,line,type,input,result)  __LAMBDA3(prename##line,type,input,result)

#define __LAMBDA1(line,type,input,result) __LAMBDA2(_anonymous,line,type,input,result)

#define LAMBDA(type,input,result) __LAMBDA1(__LINE__,type,input,result)

#define lambda __LAMBDA3

#define anol(n) _anonymous##n


int (*int_func(const char *process))(int);

int (*int_func(const char *process))(int)
{
	int n;
	sscanf(process,"%d",&n);
	lambda(f,int,x,x*n);
	return f;
}

#endif
