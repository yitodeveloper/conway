#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ANCHO 10
#define ALTO 10

int** crearGrilla(int ancho, int alto);
void imprimirGrilla(int generacion, int** grilla, int ancho, int alto);
int** nuevaGeneracion(int** grilla, int ancho, int alto);

int main() {
    
    int** grilla = crearGrilla(ANCHO, ALTO);
    grilla[1][2] = 1;
    grilla[2][3] = 1;
    grilla[3][1] = 1;
    grilla[3][2] = 1;
    grilla[3][3] = 1;

    int generacion = 0;

    while (1) {
        imprimirGrilla(generacion, grilla, ANCHO, ALTO);
        int** nuevaGrilla = nuevaGeneracion(grilla, ANCHO, ALTO);
        
        // Liberar la memoria de la grilla anterior
        for (int i = 0; i < ALTO; i++) {
            free(grilla[i]);
        }
        free(grilla);
        
        grilla = nuevaGrilla;
        generacion++;
        usleep(500000); // Espera de 500 milisegundos
    }
    return 0;
}

int** crearGrilla(int ancho, int alto) {
    int** grilla = (int**)malloc(alto * sizeof(int*));
    for (int i = 0; i < alto; i++) {
        grilla[i] = (int*)calloc(ancho, sizeof(int));
    }
    return grilla;
}

void imprimirGrilla(int generacion, int** grilla, int ancho, int alto) {
    printf("\033[H\033[J"); // Limpiar pantalla
    printf("Generación nº: %d\n", generacion);
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            printf("%c ", grilla[i][j] == 1 ? 'O' : '.');
        }
        printf("\n");
    }
}

int **nuevaGeneracion(int **grilla, int ancho, int alto) {
    int **nuevaGrilla = crearGrilla(ancho, alto);

    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            int vecinosVivos = 0;

            // Explorando alrededor de la célula seleccionada para encontrar las vivas
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    int ni = i + x; // Columna a revisar
                    int nj = j + y; // Fila a revisar

                    // Reglas de negocio
                    if (ni >= 0 && ni < alto && nj >= 0 && nj < ancho) {
                        vecinosVivos += grilla[ni][nj];
                    }
                }
            }

            int estaViva = grilla[i][j] == 1;

            if (estaViva) {
                // Regla 1: Para que una célula siga viva, tener 2 o 3 vecinas
                if (vecinosVivos < 2 || vecinosVivos > 3) {
                    nuevaGrilla[i][j] = 0; // Muere
                } else {
                    nuevaGrilla[i][j] = 1;
                }
            } else {
                // Regla 2: Si una célula está muerta y tiene 3 vecinas vivas, revive
                if (vecinosVivos == 3) {
                    nuevaGrilla[i][j] = 1;
                } else {
                    nuevaGrilla[i][j] = 0; // Muere
                }
            }
        }
    }

    return nuevaGrilla;
}