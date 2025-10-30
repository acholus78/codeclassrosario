#include <stdio.h>
#include <stdlib.h>

// Definiciones del sistema
#define PIN_CORRECTO 1234
#define MAX_INTENTOS 3

// Variables de estado del cajero
float saldo_actual = 1000.00; // Saldo inicial
int pin_ingresado = 0;       // 0: No autenticado, 1: Autenticado
int intentos_pin = 0;

// --- DECLARACIÓN DE FUNCIONES ---
void mostrar_menu_principal();
void iniciar_sesion();
void consultar_saldo();
void depositar();
void retirar();

// --- FUNCIÓN PRINCIPAL ---
int main() {
    int opcion;

    printf("==========================================\n");
    printf("        BIENVENIDO AL CAJERO AUTOMÁTICO\n");
    printf("==========================================\n");

    // Llama a la función de inicio de sesión antes de entrar al menú
    iniciar_sesion();

    if (pin_ingresado) {
        do {
            mostrar_menu_principal();
            printf("Ingrese la opción deseada: ");
            
            // Validación básica de entrada
            if (scanf("%d", &opcion) != 1) {
                printf("\nOpción inválida. Por favor, ingrese un número.\n");
                while (getchar() != '\n'); // Limpiar buffer
                opcion = 0; // Forzar a repetir el ciclo
                continue;
            }
            while (getchar() != '\n'); // Limpiar buffer después de leer el entero

            printf("\n");
            switch (opcion) {
                case 1:
                    consultar_saldo();
                    break;
                case 2:
                    retirar();
                    break;
                case 3:
                    depositar();
                    break;
                case 4:
                    printf("Gracias por usar el Cajero Automático. Sesión finalizada.\n");
                    break;
                default:
                    printf("Opción no válida. Intente de nuevo.\n");
                    break;
            }
            if (opcion != 4) {
                 printf("\nPresione ENTER para continuar...\n");
                 while (getchar() != '\n');
            }
            
        } while (opcion != 4);
    } else {
        printf("\n\n❌ Sesión bloqueada. Su tarjeta ha sido retenida. ❌\n");
    }

    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

void iniciar_sesion() {
    int pin;
    
    while (intentos_pin < MAX_INTENTOS) {
        printf("\n--- INICIO DE SESIÓN ---\n");
        printf("Ingrese su PIN de 4 dígitos (Intento %d/%d): ", intentos_pin + 1, MAX_INTENTOS);
        
        if (scanf("%d", &pin) != 1) {
            printf("Error de entrada. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (pin == PIN_CORRECTO) {
            printf("\n✅ PIN correcto. Sesión iniciada con éxito.\n");
            pin_ingresado = 1;
            break; 
        } else {
            intentos_pin++;
            printf("PIN incorrecto.\n");
        }
    }
}

void mostrar_menu_principal() {
    printf("\n\n--- MENÚ DE OPERACIONES ---\n");
    printf("1. Consultar Saldo\n");
    printf("2. Retiro de Efectivo\n");
    printf("3. Depósito\n");
    printf("4. Salir\n");
    printf("---------------------------\n");
}

void consultar_saldo() {
    printf("\n--- CONSULTA DE SALDO ---\n");
    printf("Su saldo actual es: $%.2f\n", saldo_actual);
}

void retirar() {
    float monto;
    printf("\n--- RETIRO DE EFECTIVO ---\n");
    printf("Ingrese el monto a retirar: $");
    
    if (scanf("%f", &monto) != 1 || monto <= 0) {
        printf("Monto no válido. Debe ser un número positivo.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Validación de fondos
    if (monto > saldo_actual) {
        printf("\n❌ Fondos insuficientes. Su saldo es de $%.2f\n", saldo_actual);
    } else {
        saldo_actual -= monto;
        printf("\n✅ Retiro exitoso. Retiró $%.2f\n", monto);
        printf("Su nuevo saldo es: $%.2f\n", saldo_actual);
    }
}

void depositar() {
    float monto;
    printf("\n--- DEPÓSITO ---\n");
    printf("Ingrese el monto a depositar: $");
    
    if (scanf("%f", &monto) != 1 || monto <= 0) {
        printf("Monto no válido. Debe ser un número positivo.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    saldo_actual += monto;
    printf("\n✅ Depósito exitoso. Depositó $%.2f\n", monto);
    printf("Su nuevo saldo es: $%.2f\n", saldo_actual);
}