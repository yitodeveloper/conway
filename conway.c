#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {

    // 1 Recoger los datos del usuario
    int ancho, alto, configurarPatronInicial ;

    printf("Ingrese el ancho de la cuadricula: ");
    scanf("%d", &ancho);
    printf("Ingrese el alto de la cuadricula: ");
    scanf("%d", &alto);
    printf("¿Desea configurar patron inicial? (1.si/2.no) ");
    scanf("%d", &configurarPatronInicial);



    // 2 Creacion de una grilla con todas las celulas muertas
    int grilla[ancho][alto];

    for(int i = 0; i < alto; i++){
        for(int j = 0; j < ancho; j++){
            grilla[i][j] = 0;
        }
    }


    if(configurarPatronInicial == 1){
        // 3.1 Configurar el patron inicial por parte del usuario
        printf("Ingrese las coordenadas de las celulas vivas iniciales.\n");
        printf("Formato: fila columna (Ejemplo: 1 2).\n");
        printf("Ingrese '0 0' para finalizar.\n");

        int fila, columna;
        do {
            printf("Coordenadas (fila columna): ");
            scanf("%d %d", &fila, &columna);
            if (fila >= 1 && fila <= ancho && columna >= 1 && columna <= alto) {
                grilla[fila - 1][columna - 1] = 1;
            } else if (fila != 0 || columna != 0) {
                printf("Coordenadas fuera de rango. Inténtelo de nuevo.\n");
            }
        } while (fila != 0 || columna != 0);
    }else{
        // 3.2 O el patron por defecto
        grilla[1][2] = 1;
        grilla[2][3] = 1;
        grilla[3][1] = 1;
        grilla[3][2] = 1;
        grilla[3][3] = 1;
    }

    // 4. Comienza a crear nuevas generaciones
    int generacion = 0;
    printf("\n\n");
    while (1) { // Se repite eternamente

        printf("Generacion nº: %d\n", generacion);
        // Imprime Grilla en la consola
        // Se hace doble for siempre por que se accede a columnas y despues filas. para acceder a cada celda
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                // Aca determino si es viva o muerta
                int imprimirCelula = grilla[i][j];
                if (imprimirCelula == 1){
                    printf("O");
                }else{
                    printf(".");
                }
            }
            printf("\n");
        }
        // Fin de imprimir la grilla en consola

        printf("\n\n");
        // Crear nueva generacion
        // Se crea nuevaGrilla para guardar temporalmente los valores de la nueva generacion
        int nuevaGrilla[ancho][alto];

        // Se rellena con 0 toda la nueva grilla para poder trabajar sobre ella
        for(int i = 0; i < alto; i++){
            for(int j = 0; j < ancho; j++){
                nuevaGrilla[i][j] = 0;
            }
        }

        // Revisar celdas actuales
        // Doble for NO OLVIDARR
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                /*
                    . 0 . .
                    0 . . .
                    . 0 . .
                */
                // Para i con valor 0 y j con valor 0 se accede a la primera celda
                // para explorar alrededor se debe ver 1,0 2,0 2,1
                int vecinosVivos = 0;

                // Explorando alrededor de la célula seleccionada para encontrar las vivas
                // Este doble for es para explorar alrededor de la celda actual
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x == 0 && y == 0) continue; // No revisar la cela actual
                        int columnaInspeccion = i + x; // Columna a revisar
                        int filaInspeccion = j + y; // Fila a revisar

                        // Reglas de negocio
                        // Para evitar tomar celdas que no estan dentro de la grilla. Ej: -1,-1 esto es un error y si se toma se cae muereee
                        if (columnaInspeccion >= 0 && columnaInspeccion < alto && filaInspeccion >= 0 && filaInspeccion < ancho) {
                            vecinosVivos = vecinosVivos + grilla[columnaInspeccion][filaInspeccion];
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


        // Modificar grilla con valores nuevos
        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                grilla[i][j] = nuevaGrilla[i][j];
            }
        }
    
        generacion++;
        usleep(500000); // Espera de 500 milisegundos
    }
    return 0;
}