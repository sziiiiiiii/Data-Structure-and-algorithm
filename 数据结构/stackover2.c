#include<stdio.h>
#include<string.h>
int func2(int a){
    int y;
    printf("%d",y);
    return 0;
}
int func1(int b){
    char x[10];
    //strcpy(x,"\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\xF6\xF9\x34\x01");

    strcpy(x,"1234567891120221118");//只能修改这一行代码中的字符串，使程序运行后输出结果为20221118
    return 0;
}
int main(){
    printf("nihao");

    func1(1);
    func2(0);
    printf("nihao");
}
//对于上述c语言代码，只能修改第十行代码中的字符串，使程序运行后输出结果为20221118
    