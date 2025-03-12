#include<stdio.h>
#include<string.h>

 int main(){
    int num;
    char arreglo[100];
    char arreglo2[100];

    printf("da un numero");
    scanf("%d",&num);


    sprintf(arreglo, "%d", num);

    for (int i = 0; i < strlen(arreglo); i++){
        printf("%d",i);
    }
    

    // printf("ww");
 }