#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S 120
#define L 20
typedef char string[S];
char *toFormat(const char* type)
{
	char *format = (char *)malloc(sizeof(char)*L);
	if(strcmp(type,"int")==0)strcpy(format,"%d");
	else if(strcmp(type,"long")==0)strcpy(format,"%ld");
	else if(strcmp(type,"long long")==0)strcpy(format,"%lld");
	else if(strcmp(type,"float")==0)strcpy(format,"%.2f");
	else if(strcmp(type,"double")==0)strcpy(format,"%.2lf");
	else if(strcmp(type,"long double")==0)strcpy(format,"%.4llf");
	else if(strcmp(type,"char")==0)strcpy(format,"%c");
	else if(strcmp(type,"string")==0)strcpy(format,"%s");
	else 
		strcpy(format,"%p");
	return format;
}
void modifyStr(char *str,char c_no,char c_yes)
{
	int i=0;
	while(str[i]!='\0')
	{
		if(str[i]==c_no) str[i]=c_yes;
		i++;
	}
}
int main(int argc,char *argv[])
{
	string name,objName;
	string file;
	string buf;
	string para="",getObj="",copyobj=""; 
	string types[L];
	string names[L];
	FILE *in,*out;
	int n=0,i;
	
		printf("File:");
		scanf("%s",file);
		in = fopen(file,"rt");
		fgets(buf,L,in);
		sscanf(buf,"%s%s",name,objName);
		sprintf(buf,"%s.h",name);
		out = fopen(buf,"wt");
		fprintf(out,"#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n");
		while(1)
		{
			fgets(buf,L,in);
			
			if(buf[0]=='@') break;
			if(buf[0]=='#'&&buf[1]=='#')
			{
				sscanf(buf,"%s",buf);
				fprintf(out,"#include <%s.h>\n",buf+2);
			}
			else
			{
				fprintf(out,"%s",buf);
			}
		}
		
		while(1)
		{
			fgets(buf,L,in);
			if(buf[0]=='@') break;
			if(buf[0]==' ') continue;
			sscanf(buf,"%s%s",types[n],names[n]);
			modifyStr(types[n],'_',' ');
			sprintf(para,"%s,%s pr_%s",para,types[n],names[n]);
			n++;
		}
		para[0] = ' ';
		
		
	fclose(in);
	
	
	
	//-----------------defineObject----------------------------
	fprintf(out,"typedef struct %s *p%s;\n",name,name);
	fprintf(out,"typedef struct %s{\n",name);
	for(i=0;i<n;i++)
	{
		fprintf(out,"\t%s %s;\n",types[i],names[i]);
	}
	fprintf(out,"}%s;\n",name);
	//---------------head-------------
	fprintf(out,"p%s get%s(%s);\n",name,name,para);
	fprintf(out,"void copy%s(p%s %s,p%s pr_%s);\n",name,name,objName,name,objName);
	fprintf(out,"void print%s(p%s %s);\n",name,name,objName);
	fprintf(out,"\n");
	//---------------getObj-----------------------
	fprintf(out,"p%s get%s(%s)\n{\n",name,name,para);
	fprintf(out,"\tp%s %s = (p%s)malloc(sizeof(%s));\n",name,objName,name,name);
	for(i=0;i<n;i++)
	{
		if(strcmp(types[i],"string")==0)
			fprintf(out,"\tstrcpy(%s->%s,pr_%s);\n",objName,names[i],names[i]);
		else
			fprintf(out,"\t%s->%s = pr_%s;\n",objName,names[i],names[i]);
	}
	fprintf(out,"\treturn %s;",objName);
	fprintf(out,"}\n");
	//---------------Copy------------------
	fprintf(out,"void copy%s(p%s %s,p%s pr_%s)\n{\n",name,name,objName,name,objName);
	for(i=0;i<n;i++)
	{
		if(strcmp(types[i],"string")==0)
			fprintf(out,"\tstrcpy(%s->%s,pr_%s->%s);\n",objName,names[i],objName,names[i]);
		else
			fprintf(out,"\t%s->%s = pr_%s->%s;\n",objName,names[i],objName,names[i]);
	}
	fprintf(out,"}\n");
	//----------------Print-----------------
	fprintf(out,"void print%s(p%s %s)\n{\n",name,name,objName);
	fprintf(out,"\tprintf(\"{ \");\n");
	for(i=0;i<n;i++)
	{
		fprintf(out,"\tprintf(\"%s=%s \",%s->%s);\n",names[i],toFormat(types[i]),objName,names[i]);
	}
	fprintf(out,"\tprintf(\"}\\n\");\n}\n");
	
	printf("File saved as %s.h",name);
	
	return 0;
}
