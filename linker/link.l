%{
	#include<stdio.h>
	#include<stdlib.h>
    #include<string.h>
    FILE *input_file,*input_file_;
    int bool=0;
    int labels[100];
    int count = 2056;
%}

%%
([L])([0-9]+)([:])([\n]) {  
        if(!bool)
        {
            yytext[0]='0';
            yytext[strlen(yytext)-2]='\0';
            labels[atoi(yytext)]=count;
        }
    }
([\n]) {
        if(!bool) 
            count+=2;
        else 
            printf("\n");
    }
([L])([0-9]+) {
        if(bool){
            yytext[0]='0'; 
            printf("%d",labels[atoi(yytext)]); 
        } 
    }
(.) {if(bool)
        {
        printf("%s",yytext);
        }
    }
%%

int yywrap() { 
    if(bool==1){
        return 1;
    }
    else{
        input_file_=fopen("ini.xsm","r");
        yyin=input_file_;
        bool=1;
        return 0;
    }
 }
int main(){
    count = 2056;
    char str[100];
    input_file=fopen("ini.xsm","r");
    for(int i=0;i<8;i++)
    {
        fgets(str,100,input_file);
        if(bool){
            printf("%s",str);
        }
    }
    yyin = input_file;
    yylex();
    return 0;
}
