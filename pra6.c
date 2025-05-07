#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 1000

// Funciones auxiliares
bool es_primo(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void generar_fibonacci_filtrado(int fib[], int *size, int k) {
    int a = 0, b = 1, c;
    int pos = 2; // empezamos en la posición 2 (0 y 1 ya están)
    int temp[MAX];
    int temp_size = 2;
    temp[0] = 0;
    temp[1] = 1;

    while (1) {
        c = a + b;
        if (c > k) break;
        temp[temp_size++] = c;
        a = b;
        b = c;
        pos++;
    }

    int j = 0;
    for (int i = 0; i < temp_size; i++) {
        if (!es_primo(i + 1)) { // posiciones son 1-indexed
            fib[j++] = temp[i];
        }
    }
    *size = j;
}

void greedy_fib_sum(int fib[], int size, int k) {
    int resultado[MAX];
    int res_size = 0;
    int idx = size - 1;

    while (k > 0) {
        while (idx >= 0 && fib[idx] > k) {
            idx--;
        }
        if (idx < 0) break;
        resultado[res_size++] = fib[idx];
        k -= fib[idx];
        idx--; // para no usar el mismo número otra vez
    }

    printf("Terminos seleccionados: ");
    int suma = 0;
    for (int i = 0; i < res_size; i++) {
        printf("%d ", resultado[i]);
        suma += resultado[i];
    }
    printf("\nSuma: %d\n", suma);
    printf("Cantidad de terminos: %d\n", res_size);
}

int main() {
    int dia = 25;
    int mes = 12;
    int anio = 1995;

    int K = dia * 100 + mes * 10 + (anio % 100); // 2715

    int fib[MAX];
    int size;

    generar_fibonacci_filtrado(fib, &size, K);

    printf("Fibonacci filtrado: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    greedy_fib_sum(fib, size, K);

    return 0;
}
