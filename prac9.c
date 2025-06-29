#include <stdio.h>
#include <stdlib.h>

// Función que calcula la cantidad de agua atrapada
int trap(int* height, int n) {
    int left = 0, right = n - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            // Procesamos lado izquierdo
            if (height[left] >= left_max) {
                left_max = height[left];
            } else {
                water += left_max - height[left];
            }
            left++;
        } else {
            // Procesamos lado derecho
            if (height[right] >= right_max) {
                right_max = height[right];
            } else {
                water += right_max - height[right];
            }
            right--;
        }
    }
    return water;
}

int main(void) {
    int n;
    // Leemos número de barras
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Entrada inválida para n\n");
        return 1;
    }

    int *height = malloc(n * sizeof(int));
    if (!height) {
        perror("malloc");
        return 1;
    }

    // Leemos alturas
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &height[i]) != 1) {
            fprintf(stderr, "Error leyendo height[%d]\n", i);
            free(height);
            return 1;
        }
    }

    int result = trap(height, n);
    printf("%d\n", result);

    free(height);
    return 0;
}
