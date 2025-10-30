#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Necesaria para las funciones científicas (sin, cos, log, sqrt, pow)

// --- DECLARACIÓN DE FUNCIONES ---
void mostrar_menu();
void realizar_operacion(int opcion);

// --- FUNCIÓN PRINCIPAL ---
int main() {
    int opcion;

    printf("=======================================\n");
    printf("     CALCULADORA CIENTÍFICA BÁSICA\n");
    printf("=======================================\n");

    do {
        mostrar_menu();
        printf("Ingrese la opción deseada: ");
        
        // Validación básica de entrada
        if (scanf("%d", &opcion) != 1) {
            printf("\nOpción inválida. Por favor, ingrese un número.\n");
            while (getchar() != '\n'); // Limpiar buffer
            opcion = 0; 
            continue;
        }
        while (getchar() != '\n'); // Limpiar buffer

        if (opcion >= 1 && opcion <= 10) {
            realizar_operacion(opcion);
        } else if (opcion == 0) {
            printf("\nSaliendo de la calculadora. ¡Adiós!\n");
        } else {
            printf("\nOpción no válida. Intente de nuevo.\n");
        }
        
        if (opcion != 0) {
            printf("\n---------------------------------------\n");
        }

    } while (opcion != 0);

    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

void mostrar_menu() {
    printf("\n--- SELECCIONE UNA OPERACIÓN ---\n");
    // Operaciones Básicas
    printf("1. Suma (+)\n");
    printf("2. Resta (-)\n");
    printf("3. Multiplicación (*)\n");
    printf("4. División (/)\n");
    // Operaciones Científicas
    printf("5. Raíz Cuadrada (sqrt)\n");
    printf("6. Potencia (pow)\n");
    printf("7. Seno (sin - en radianes)\n");
    printf("8. Coseno (cos - en radianes)\n");
    printf("9. Tangente (tan - en radianes)\n");
    printf("10. Logaritmo Natural (ln)\n");
    // Salida
    printf("0. Salir\n");
    printf("---------------------------------------\n");
}

void realizar_operacion(int opcion) {
    double num1, num2, resultado;
    
    // Switch para manejar todas las opciones del menú
    switch (opcion) {
        // --- Operaciones Aritméticas Básicas (requieren dos números) ---
        case 1: // Suma
        case 2: // Resta
        case 3: // Multiplicación
        case 4: { // División
            printf("Ingrese el primer número: ");
            if (scanf("%lf", &num1) != 1) { goto error_entrada; }
            printf("Ingrese el segundo número: ");
            if (scanf("%lf", &num2) != 1) { goto error_entrada; }
            while (getchar() != '\n');

            if (opcion == 1) resultado = num1 + num2;
            if (opcion == 2) resultado = num1 - num2;
            if (opcion == 3) resultado = num1 * num2;
            if (opcion == 4) {
                if (num2 == 0) {
                    printf("❌ Error: División por cero no permitida.\n");
                    return;
                }
                resultado = num1 / num2;
            }
            break;
        }

        // --- Operaciones Científicas (requieren un solo número) ---
        case 5: // Raíz Cuadrada
        case 7: // Seno
        case 8: // Coseno
        case 9: // Tangente
        case 10: { // Logaritmo Natural
            printf("Ingrese el número (x): ");
            if (scanf("%lf", &num1) != 1) { goto error_entrada; }
            while (getchar() != '\n');

            if (opcion == 5) {
                if (num1 < 0) {
                    printf("❌ Error: No se puede calcular la raíz cuadrada de un número negativo.\n");
                    return;
                }
                resultado = sqrt(num1);
            }
            if (opcion == 7) resultado = sin(num1);
            if (opcion == 8) resultado = cos(num1);
            if (opcion == 9) resultado = tan(num1);
            if (opcion == 10) {
                 if (num1 <= 0) {
                    printf("❌ Error: Logaritmo solo definido para números positivos (> 0).\n");
                    return;
                }
                resultado = log(num1);
            }
            break;
        }
        
        case 6: { // Potencia (base^exponente)
            printf("Ingrese la base (x): ");
            if (scanf("%lf", &num1) != 1) { goto error_entrada; }
            printf("Ingrese el exponente (y): ");
            if (scanf("%lf", &num2) != 1) { goto error_entrada; }
            while (getchar() != '\n');
            
            resultado = pow(num1, num2);
            break;
        }
    }
    
    // Imprimir el resultado de la operación
    printf("Resultado: %.4lf\n", resultado);
    return;

    // Etiqueta para manejar errores de entrada
    error_entrada:
        while (getchar() != '\n');
        printf("❌ Error de entrada. Por favor, ingrese un valor numérico válido.\n");
}