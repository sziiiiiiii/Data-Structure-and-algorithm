#include<stdio.h>
#include<string.h>
int func2(char *a){
    char x[10];
    strcpy(x,a);
    return 0;
}
int func1(){
    func2("this is a test string");
    return 0;
}
int main(){
    func1();
}



/*#include<stdio.h>
void why_here(void){
    printf("why");
    exit(0);
}
void f(){
    int buff[1];
    buff[2]=(int)why_here;
}
int main(){
   f();
}*/