#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBINATIONS 100 // Límite máximo de combinaciones posibles
#define MAX_LENGTH 5         // Longitud máxima de una combinación

const char *phone_map[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

// Función recursiva para generar combinaciones
void backtrack(char **result, int *count, char *current, const char *digits, int index) {
    if (digits[index] == '\0') { // Si llegamos al final del string de dígitos
        result[*count] = strdup(current); // Guardamos la combinación
        (*count)++;
        return;
    }

    int digit = digits[index] - '0';
    for (int i = 0; phone_map[digit][i] != '\0'; i++) {
        current[index] = phone_map[digit][i]; // Agregar letra a la combinación actual
        backtrack(result, count, current, digits, index + 1);
    }
}
// Función principal para obtener todas las combinaciones
char **letterCombinations(char *digits, int *returnSize) {
    if (digits[0] == '\0') { // Si la entrada es vacía, devolver un array vacío
        *returnSize = 0;
        return NULL;
    }

    char **result = (char **)malloc(MAX_COMBINATIONS * sizeof(char *));
    char current[MAX_LENGTH] = {0}; // Buffer para la combinación actual
    *returnSize = 0;

    backtrack(result, returnSize, current, digits, 0);

    return result;
}

// Función para imprimir las combinaciones generadas
void printCombinations(char **combinations, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("\"%s\"", combinations[i]);
        if (i < size - 1) printf(", ");
        free(combinations[i]); // Liberar memoria después de usarla
    }
    printf("]\n");
    free(combinations); // Liberar el array principal
}

// Ejemplo de uso
int main() {
    char digits[] = "23";
    int returnSize;

    char **combinations = letterCombinations(digits, &returnSize);
    printCombinations(combinations, returnSize);

    return 0;
}
