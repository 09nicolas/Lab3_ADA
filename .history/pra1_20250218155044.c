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
        // printf("%d",i);

        arreglo2[strlen(arreglo)-1]=arreglo[i];
        printf("s");
    }

    //comparar si son iguales

    for (int i = 0; i < strlen(arreglo); i++){
        printf("arreglo: %s",arreglo[i]);
        printf("arreglo2: %s", arreglo2[i]);
        if(arreglo[i]!=arreglo2[i]){
            return -1;
        }
    }

    printf("Los numeros son palindromos");
    
    

    // printf("ww");
 }