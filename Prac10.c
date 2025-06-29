#include <stdio.h>
#include <string.h>

#define N 4      
#define CAP 4     

int main(void) {
    // Definición de los objetos
    const char *names[N] = { "Guitarra", "Laptop", "Estéreo", "iPhone" };
    int peso[N]  = { 1, 3, 4, 1 };
    int valor[N] = { 1500, 2000, 3000, 2000 };

    // Tabla DP de (N+1) x (CAP+1), inicializada a 0
    int dp[N+1][CAP+1];
    memset(dp, 0, sizeof(dp));

    // Llenado de la tabla
    for (int i = 1; i <= N; i++) {
        for (int w = 0; w <= CAP; w++) {
            if (peso[i-1] > w) {
                // no cabe, heredamos
                dp[i][w] = dp[i-1][w];
            } else {
                // max entre no cogerlo o cogerlo
                int sin_obj = dp[i-1][w];
                int con_obj = dp[i-1][w - peso[i-1]] + valor[i-1];
                dp[i][w] = (con_obj > sin_obj) ? con_obj : sin_obj;
            }
        }
    }

    // Valor óptimo
    int max_valor = dp[N][CAP];

    // Reconstrucción de la solución
    int w = CAP;
    int seleccion[N];
    int count = 0;
    for (int i = N; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            // el objeto i-1 fue incluido
            seleccion[count++] = i-1;
            w -= peso[i-1];
        }
    }

    // Imprimir resultados
    printf("Capacidad máxima: %d lb\n", CAP);
    printf("Valor máximo obtenido: $%d\n\n", max_valor);
    printf("Objetos seleccionados:\n");
    for (int i = count-1; i >= 0; i--) {
        int idx = seleccion[i];
        printf("  - %s (peso %dlb, valor $%d)\n",
               names[idx], peso[idx], valor[idx]);
    }

    return 0;
}
