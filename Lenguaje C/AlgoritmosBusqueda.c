#include <stdio.h>

// Definición de constantes
#define TAMANO_MAX 10

// --- FUNCIÓN DE ORDENAMIENTO: BURBUJA (Bubble Sort) ---

/**
 * Ordena un array de enteros en orden ascendente utilizando el método de burbuja.
 * El método de burbuja compara elementos adyacentes y los intercambia si están
 * en el orden incorrecto, repitiendo el proceso hasta que el array esté ordenado.
 *
 * @param arr El array de enteros a ordenar.
 * @param n El número de elementos en el array.
 */
void bubble_sort(int arr[], int n) {
    int i, j, temp;
    // Ciclo externo para el número de pasadas
    for (i = 0; i < n - 1; i++) {
        // Ciclo interno para las comparaciones e intercambios
        for (j = 0; j < n - i - 1; j++) {
            // Si el elemento actual es mayor que el siguiente, se intercambian
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// --- FUNCIÓN DE BÚSQUEDA: BINARIA O DICOTÓMICA (Binary Search) ---

/**
 * Busca un valor específico en un array ordenado.
 * NOTA: Este algoritmo requiere que el array esté previamente ordenado.
 *
 * @param arr El array de enteros (debe estar ordenado).
 * @param izquierda El índice inicial de la búsqueda (generalmente 0).
 * @param derecha El índice final de la búsqueda (n-1).
 * @param valor_buscado El valor que se desea encontrar.
 * @return El índice del elemento si es encontrado, o -1 si no se encuentra.
 */
int binary_search(int arr[], int izquierda, int derecha, int valor_buscado) {
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        // Si el valor está en el medio, se devuelve el índice
        if (arr[medio] == valor_buscado) {
            return medio;
        }

        // Si el valor es mayor, se busca en la mitad derecha
        if (arr[medio] < valor_buscado) {
            izquierda = medio + 1;
        }
        // Si el valor es menor, se busca en la mitad izquierda
        else {
            derecha = medio - 1;
        }
    }

    // Si el elemento no se encuentra
    return -1; 
}


// --- FUNCIÓN AUXILIAR: IMPRIMIR ARRAY ---
void imprimir_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// --- FUNCIÓN PRINCIPAL (Demostración) ---
int main() {
    int numeros[TAMANO_MAX] = {64, 34, 25, 12, 22, 11, 90, 15, 7, 42};
    int n = TAMANO_MAX;
    int valor_a_buscar = 22;
    int indice_encontrado;

    printf("--- DEMOSTRACIÓN DE ALGORITMOS ---\n");
    printf("Array original: ");
    imprimir_array(numeros, n);

    // 1. ORDENAMIENTO POR BURBUJA
    printf("\n[1] Aplicando Ordenamiento por Burbuja...\n");
    bubble_sort(numeros, n);

    printf("Array ordenado: ");
    imprimir_array(numeros, n);

    // 2. BÚSQUEDA BINARIA
    printf("\n[2] Aplicando Búsqueda Binaria (Dicotómica)...\n");
    printf("Valor a buscar: %d\n", valor_a_buscar);
    
    // La búsqueda binaria se realiza sobre el array ya ordenado
    indice_encontrado = binary_search(numeros, 0, n - 1, valor_a_buscar);

    if (indice_encontrado != -1) {
        printf("✅ Valor %d encontrado en el índice: %d\n", valor_a_buscar, indice_encontrado);
    } else {
        printf("❌ Valor %d no encontrado en el array.\n", valor_a_buscar);
    }
    
    // Segundo ejemplo de búsqueda (valor no existente)
    valor_a_buscar = 100;
    printf("\nValor a buscar: %d\n", valor_a_buscar);
    indice_encontrado = binary_search(numeros, 0, n - 1, valor_a_buscar);

    if (indice_encontrado != -1) {
        printf("✅ Valor %d encontrado en el índice: %d\n", valor_a_buscar, indice_encontrado);
    } else {
        printf("❌ Valor %d no encontrado en el array.\n", valor_a_buscar);
    }

    return 0;
}