#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para crear una matriz dinámica de tamaño nxn
int** create_matrix(int n) {
    int** matrix = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Función para liberar memoria de una matriz
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Función para llenar una matriz con valores aleatorios
void fill_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10; // Valores entre 0 y 9
        }
    }
}

// Función para imprimir una matriz
void print_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 1. Método tradicional de multiplicación de matrices
int** traditional_mult(int** A, int** B, int n) {
    int** C = create_matrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

// 2. Método Divide y Vencerás (DaC) de multiplicación de matrices
int** add_matrix(int** A, int** B, int n) {
    int** C = create_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

int** sub_matrix(int** A, int** B, int n) {
    int** C = create_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

int** dac_mult(int** A, int** B, int n) {
    int** C = create_matrix(n);
    
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int new_n = n / 2;
        
        // Dividir matrices en submatrices
        int** A11 = create_matrix(new_n);
        int** A12 = create_matrix(new_n);
        int** A21 = create_matrix(new_n);
        int** A22 = create_matrix(new_n);
        
        int** B11 = create_matrix(new_n);
        int** B12 = create_matrix(new_n);
        int** B21 = create_matrix(new_n);
        int** B22 = create_matrix(new_n);
        
        for (int i = 0; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + new_n];
                A21[i][j] = A[i + new_n][j];
                A22[i][j] = A[i + new_n][j + new_n];
                
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + new_n];
                B21[i][j] = B[i + new_n][j];
                B22[i][j] = B[i + new_n][j + new_n];
            }
        }
        
        // Multiplicaciones recursivas
        int** C11 = add_matrix(dac_mult(A11, B11, new_n), dac_mult(A12, B21, new_n), new_n);
        int** C12 = add_matrix(dac_mult(A11, B12, new_n), dac_mult(A12, B22, new_n), new_n);
        int** C21 = add_matrix(dac_mult(A21, B11, new_n), dac_mult(A22, B21, new_n), new_n);
        int** C22 = add_matrix(dac_mult(A21, B12, new_n), dac_mult(A22, B22, new_n), new_n);
        
        // Combinar resultados
        for (int i = 0; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                C[i][j] = C11[i][j];
                C[i][j + new_n] = C12[i][j];
                C[i + new_n][j] = C21[i][j];
                C[i + new_n][j + new_n] = C22[i][j];
            }
        }
        
        // Liberar memoria
        free_matrix(A11, new_n);
        free_matrix(A12, new_n);
        free_matrix(A21, new_n);
        free_matrix(A22, new_n);
        free_matrix(B11, new_n);
        free_matrix(B12, new_n);
        free_matrix(B21, new_n);
        free_matrix(B22, new_n);
        free_matrix(C11, new_n);
        free_matrix(C12, new_n);
        free_matrix(C21, new_n);
        free_matrix(C22, new_n);
    }
    
    return C;
}

// 3. Método de Strassen de multiplicación de matrices
int** strassen_mult(int** A, int** B, int n) {
    int** C = create_matrix(n);
    
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    } else {
        int new_n = n / 2;
        
        // Dividir matrices en submatrices
        int** A11 = create_matrix(new_n);
        int** A12 = create_matrix(new_n);
        int** A21 = create_matrix(new_n);
        int** A22 = create_matrix(new_n);
        
        int** B11 = create_matrix(new_n);
        int** B12 = create_matrix(new_n);
        int** B21 = create_matrix(new_n);
        int** B22 = create_matrix(new_n);
        
        for (int i = 0; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + new_n];
                A21[i][j] = A[i + new_n][j];
                A22[i][j] = A[i + new_n][j + new_n];
                
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + new_n];
                B21[i][j] = B[i + new_n][j];
                B22[i][j] = B[i + new_n][j + new_n];
            }
        }
        
        // Calcular los productos de Strassen
        int** P1 = strassen_mult(A11, sub_matrix(B12, B22, new_n), new_n);
        int** P2 = strassen_mult(add_matrix(A11, A12, new_n), B22, new_n);
        int** P3 = strassen_mult(add_matrix(A21, A22, new_n), B11, new_n);
        int** P4 = strassen_mult(A22, sub_matrix(B21, B11, new_n), new_n);
        int** P5 = strassen_mult(add_matrix(A11, A22, new_n), add_matrix(B11, B22, new_n), new_n);
        int** P6 = strassen_mult(sub_matrix(A12, A22, new_n), add_matrix(B21, B22, new_n), new_n);
        int** P7 = strassen_mult(sub_matrix(A11, A21, new_n), add_matrix(B11, B12, new_n), new_n);
        
        // Calcular las submatrices de C
        int** C11 = add_matrix(sub_matrix(add_matrix(P5, P4, new_n), P2, new_n), P6, new_n);
        int** C12 = add_matrix(P1, P2, new_n);
        int** C21 = add_matrix(P3, P4, new_n);
        int** C22 = sub_matrix(sub_matrix(add_matrix(P5, P1, new_n), P3, new_n), P7, new_n);
        
        // Combinar resultados
        for (int i = 0; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                C[i][j] = C11[i][j];
                C[i][j + new_n] = C12[i][j];
                C[i + new_n][j] = C21[i][j];
                C[i + new_n][j + new_n] = C22[i][j];
            }
        }
        
        // Liberar memoria
        free_matrix(A11, new_n);
        free_matrix(A12, new_n);
        free_matrix(A21, new_n);
        free_matrix(A22, new_n);
        free_matrix(B11, new_n);
        free_matrix(B12, new_n);
        free_matrix(B21, new_n);
        free_matrix(B22, new_n);
        free_matrix(P1, new_n);
        free_matrix(P2, new_n);
        free_matrix(P3, new_n);
        free_matrix(P4, new_n);
        free_matrix(P5, new_n);
        free_matrix(P6, new_n);
        free_matrix(P7, new_n);
        free_matrix(C11, new_n);
        free_matrix(C12, new_n);
        free_matrix(C21, new_n);
        free_matrix(C22, new_n);
    }
    
    return C;
}

// Menú principal
int main() {
    srand(time(NULL)); // Inicializar semilla para números aleatorios
    
    int n, choice;
    clock_t start, end;
    double cpu_time_used;
    
    printf("Laboratorio 5: Multiplicación de Matrices\n");
    printf("Ingrese el tamaño de las matrices (potencia de 2): ");
    scanf("%d", &n);
    
    // Verificar que n sea potencia de 2
    if ((n & (n - 1)) != 0) {
        printf("Error: El tamaño debe ser una potencia de 2.\n");
        return 1;
    }
    
    // Crear y llenar matrices A y B
    int** A = create_matrix(n);
    int** B = create_matrix(n);
    fill_matrix(A, n);
    fill_matrix(B, n);
    
    printf("\nMatriz A:\n");
    print_matrix(A, n);
    printf("\nMatriz B:\n");
    print_matrix(B, n);
    
    printf("\nSeleccione el método de multiplicación:\n");
    printf("1. Método tradicional\n");
    printf("2. Método Divide y Vencerás (DaC)\n");
    printf("3. Método de Strassen\n");
    printf("Opción: ");
    scanf("%d", &choice);
    
    int** C;
    
    switch(choice) {
        case 1:
            start = clock();
            C = traditional_mult(A, B, n);
            end = clock();
            break;
        case 2:
            start = clock();
            C = dac_mult(A, B, n);
            end = clock();
            break;
        case 3:
            start = clock();
            C = strassen_mult(A, B, n);
            end = clock();
            break;
        default:
            printf("Opción no válida.\n");
            free_matrix(A, n);
            free_matrix(B, n);
            return 1;
    }
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nMatriz resultante C:\n");
    print_matrix(C, n);
    printf("\nTiempo de ejecución: %f segundos\n", cpu_time_used);
    
    // Liberar memoria
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
    
    return 0;
}