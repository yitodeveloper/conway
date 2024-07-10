#include <stdio.h>
#include <math.h>
#define numero_de_ciudades 3

int main () {
    
    int ciudad_actual = 0;                  //       0           1          2             3            4           5
    float temperaturas[numero_de_ciudades]; // [PromCiudad1,PromCiudad2,PromCiudad3,PromCiudad4,PromCiudad5,PromCiudad6,PromCiudad7]
    float suma_temperaturas = 0;
    float temperatura_minima = 50;
    float temperatura_maxima = -10; // 5
    do{
        // temperaturas[ciudad_actual] = al dato que este ingresando el usuario para la ciudad_actual
        printf("Ingrese la temperatura promedio de la ciudad %d : \n", ciudad_actual + 1);
        scanf("%f", &temperaturas[ciudad_actual]);

        if(temperaturas[ciudad_actual] < -10 || temperaturas[ciudad_actual] > 50 ){
            // Salio mal
            printf("Error: Te equivocaste. intentalo nuevamente \n");
        }else{
            // Salio todo bien

            if(temperaturas[ciudad_actual] < temperatura_minima){
                temperatura_minima = temperaturas[ciudad_actual];
            }

            if(temperaturas[ciudad_actual] > temperatura_maxima){
                temperatura_maxima = temperaturas[ciudad_actual];
            }
            suma_temperaturas = suma_temperaturas + temperaturas[ciudad_actual];
            ciudad_actual = ciudad_actual + 1;
        }
    } while(ciudad_actual < numero_de_ciudades);

    float promedio_ciudades = suma_temperaturas / numero_de_ciudades;
    printf("\nPromedio de temperatura: %f", promedio_ciudades);
    printf("\nTemperatura minima: %f", temperatura_minima);
    printf("\nTemperatura maxima: %f", temperatura_maxima);

    // Escribir archivo
    FILE* archivo;
    archivo = fopen("temperaturas.txt", "w+");
    for(int i = 0; i < numero_de_ciudades; i++){
        fprintf(archivo, "temperaturas[%d]: %f \n",i, temperaturas[i]);
    }

    fprintf(archivo,"\nLa temperatura promedio de julio fue: %f", promedio_ciudades);
    fprintf(archivo, "\nTemperatura minima: %f", temperatura_minima);
    fprintf(archivo, "\nTemperatura maxima: %f", temperatura_maxima);

    fclose(archivo);
    /*
        printf("\n\n\nArreglo final ------------------ \n");
        for(int i = 0; i < numero_de_ciudades; i++){
            printf("temperaturas[%d]: %f \n", i, temperaturas[i]);
        }
    */
   
    char nombre[50];
    int edad;
    char ciudad[50];
    FILE* archivo2;
    archivo2 = fopen("hola.txt", "r+");
    while(!feof(archivo2)){
        fscanf(archivo2, "%s %d %s", &nombre [0], &edad, &ciudad [0]);
        printf("\n Nombre: %s", nombre);
        printf("\n Edad: %d", edad);
        printf("\n Ciudad: %s", ciudad);
        printf("\n\n");
    }
    fclose(archivo2);


    // Ejercicio 2
    float consumoTotal = 0;
    float consumoAux = 0;
    FILE* archivo3;
    archivo3 = fopen("consumo_agua.txt", "r");
    while(!feof(archivo3)){
        fscanf(archivo3, "%f", &consumoAux);
        printf("\n Consumo leido: %f", consumoAux);
        consumoTotal = consumoTotal + consumoAux;
    }
    fclose(archivo2);
    float cantidad_tanques = ceil(consumoTotal / 1000);
    printf("\nEl consumo total es: %f", consumoTotal);
    printf("\nLa cantidad de tanques necesarios es: %f", cantidad_tanques);

    return 0;
}
