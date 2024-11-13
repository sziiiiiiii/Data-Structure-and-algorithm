#include<stdio.h>
void func(void) {
    printf("why");
    //exit(0);
}
void f() {
    int buff[1];
    buff[2] = (int)func;
    return;
}
int main() {
    f();
}
