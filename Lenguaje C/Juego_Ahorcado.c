#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Definición del número máximo de intentos fallidos
#define MAX_INTENTOS 6

// --- DECLARACIÓN DE FUNCIONES ---
void inicializar_palabra_adivinada(const char* palabra_secreta, char* adivinada);
void dibujar_ahorcado(int errores);

// --- FUNCIÓN PRINCIPAL ---
int main() {
    // Lista de palabras posibles
    const char *palabras[] = {
        "PROGRAMACION", "ALGORITMO", "COMPILADOR", 
        "ESTRUCTURA", "FUNCION", "VARIABLE", 
        "PUNTERO", "ARREGLO", "BIBLIOTECA"
    };
    int num_palabras = sizeof(palabras) / sizeof(palabras[0]);

    // Inicializar el generador de números aleatorios para elegir una palabra
    srand(time(NULL));
    int indice_aleatorio = rand() % num_palabras;
    
    // Configuración del juego
    const char *palabra_secreta = palabras[indice_aleatorio];
    int longitud = strlen(palabra_secreta);
    char palabra_adivinada[longitud + 1];
    char letras_usadas[27] = ""; // Para almacenar las 26 letras del abecedario + '\0'
    char letra_ingresada;
    int intentos_fallidos = 0;
    int juego_terminado = 0;
    
    // Inicializar la palabra a adivinar con guiones bajos
    inicializar_palabra_adivinada(palabra_secreta, palabra_adivinada);

    printf("======================================\n");
    printf("        JUEGO DEL AHORCADO EN C\n");
    printf("======================================\n");
    printf("Adivina la palabra. Tienes %d intentos fallidos.\n\n", MAX_INTENTOS);

    // Bucle principal del juego
    while (!juego_terminado) {
        // Mostrar estado actual
        dibujar_ahorcado(intentos_fallidos);
        printf("\nPalabra: %s\n", palabra_adivinada);
        printf("Intentos restantes: %d\n", MAX_INTENTOS - intentos_fallidos);
        printf("Letras usadas: %s\n", letras_usadas);
        
        // Pedir entrada al usuario
        printf("\nIngresa una letra: ");
        if (scanf(" %c", &letra_ingresada) != 1) {
            printf("Error de lectura.\n");
            continue;
        }
        while (getchar() != '\n'); // Limpiar buffer

        // Convertir a mayúscula para trabajar consistentemente
        letra_ingresada = toupper(letra_ingresada);

        // Validación de la letra
        if (strchr(letras_usadas, letra_ingresada) != NULL) {
            printf("❌ Ya usaste la letra '%c'. Intenta con otra.\n", letra_ingresada);
            continue;
        }
        if (letra_ingresada < 'A' || letra_ingresada > 'Z') {
            printf("❌ Caracter no válido. Ingresa solo letras del alfabeto.\n");
            continue;
        }

        // Marcar la letra como usada
        strncat(letras_usadas, &letra_ingresada, 1);
        strcat(letras_usadas, " "); // Añadir espacio para mejor lectura

        // Comprobar si la letra está en la palabra secreta
        int acierto = 0;
        for (int i = 0; i < longitud; i++) {
            if (palabra_secreta[i] == letra_ingresada) {
                palabra_adivinada[i] = letra_ingresada;
                acierto = 1;
            }
        }

        if (acierto) {
            printf("✅ ¡Acierto!\n");
        } else {
            intentos_fallidos++;
            printf("🚫 Error. La letra '%c' no está en la palabra.\n", letra_ingresada);
        }

        // 1. Condición de Victoria
        if (strcmp(palabra_adivinada, palabra_secreta) == 0) {
            dibujar_ahorcado(intentos_fallidos);
            printf("\n\n🎉 ¡FELICIDADES! ¡Has adivinado la palabra!\n");
            printf("La palabra era: %s\n", palabra_secreta);
            juego_terminado = 1;
        }

        // 2. Condición de Derrota
        if (intentos_fallidos >= MAX_INTENTOS) {
            dibujar_ahorcado(intentos_fallidos);
            printf("\n\n💀 ¡Ahorcado! Se acabaron tus intentos.\n");
            printf("La palabra secreta era: %s\n", palabra_secreta);
            juego_terminado = 1;
        }
        
        printf("--------------------------------------\n");
    }

    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES AUXILIARES ---

/**
 * Inicializa el array de la palabra adivinada con guiones bajos.
 */
void inicializar_palabra_adivinada(const char* palabra_secreta, char* adivinada) {
    int longitud = strlen(palabra_secreta);
    for (int i = 0; i < longitud; i++) {
        adivinada[i] = '_';
    }
    adivinada[longitud] = '\0';
}

/**
 * Dibuja la figura del ahorcado según el número de errores.
 */
void dibujar_ahorcado(int errores) {
    printf("\n");
    printf("   +---+\n");
    printf("   |   |\n");
    printf("   %c   |\n", (errores >= 1) ? 'O' : ' ');
    printf("  %c%c%c  |\n", 
           (errores >= 3) ? '/' : ' ', 
           (errores >= 2) ? '|' : ' ', 
           (errores >= 4) ? '\\' : ' ');
    printf("  %c %c  |\n", 
           (errores >= 5) ? '/' : ' ', 
           (errores >= 6) ? '\\' : ' ');
    printf("       |\n");
    printf("=========\n");
}