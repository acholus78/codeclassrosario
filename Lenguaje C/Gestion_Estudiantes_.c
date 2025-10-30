#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura para un estudiante
typedef struct {
    int id;
    char nombre[50];
    float promedio;
} Estudiante;

// Nombre del archivo de datos
const char* NOMBRE_ARCHIVO = "estudiantes.dat";

// --- DECLARACIÓN DE FUNCIONES ---
void mostrar_menu();
void alta_estudiante();
void mostrar_estudiantes();
void buscar_estudiante();
void modificar_estudiante();
void baja_estudiante();

// --- FUNCIÓN PRINCIPAL ---
int main() {
    int opcion;

    do {
        mostrar_menu();
        printf("Ingrese su opción: ");
        // Verifica que la entrada sea un entero
        if (scanf("%d", &opcion) != 1) {
            printf("\nOpción inválida. Por favor, ingrese un número.\n");
            // Limpia el buffer de entrada para evitar bucles
            while (getchar() != '\n');
            opcion = 0; // Fuerza a repetir el ciclo
            continue;
        }
        
        // Limpia el buffer después de leer el entero
        while (getchar() != '\n'); 

        printf("\n");
        switch (opcion) {
            case 1:
                alta_estudiante();
                break;
            case 2:
                mostrar_estudiantes();
                break;
            case 3:
                buscar_estudiante();
                break;
            case 4:
                modificar_estudiante();
                break;
            case 5:
                baja_estudiante();
                break;
            case 6:
                printf("Saliendo del sistema. ¡Hasta pronto!\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
        printf("\n----------------------------------------\n");
    } while (opcion != 6);

    return 0;
}

// --- IMPLEMENTACIÓN DE FUNCIONES ---

void mostrar_menu() {
    printf("\n--- SISTEMA ABM DE ESTUDIANTES ---\n");
    printf("1. Alta (Registrar) Estudiante\n");
    printf("2. Mostrar Todos los Estudiantes\n");
    printf("3. Buscar Estudiante por ID\n");
    printf("4. Modificar Estudiante por ID\n");
    printf("5. Baja (Eliminar) Estudiante por ID\n");
    printf("6. Salir\n");
    printf("----------------------------------\n");
}

void alta_estudiante() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "ab"); // 'ab' para añadir en modo binario
    if (archivo == NULL) {
        perror("Error al abrir el archivo para alta");
        return;
    }

    Estudiante e;
    printf("\n--- REGISTRO DE NUEVO ESTUDIANTE ---\n");
    
    printf("ID: ");
    if (scanf("%d", &e.id) != 1) {
        printf("Error de entrada. Cancelando operación.\n");
        fclose(archivo);
        return;
    }
    while (getchar() != '\n'); 

    printf("Nombre: ");
    fgets(e.nombre, 50, stdin);
    e.nombre[strcspn(e.nombre, "\n")] = 0; // Eliminar el salto de línea

    printf("Promedio: ");
    if (scanf("%f", &e.promedio) != 1) {
        printf("Error de entrada. Cancelando operación.\n");
        fclose(archivo);
        return;
    }
    while (getchar() != '\n'); 

    // Escribir el registro en el archivo
    fwrite(&e, sizeof(Estudiante), 1, archivo);
    fclose(archivo);
    
    printf("\n✅ Estudiante con ID %d registrado con éxito.\n", e.id);
}

void mostrar_estudiantes() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "rb"); // 'rb' para lectura en modo binario
    if (archivo == NULL) {
        printf("El archivo de estudiantes está vacío o no existe.\n");
        return;
    }

    Estudiante e;
    printf("\n--- LISTADO DE ESTUDIANTES ---\n");
    printf("ID\tNombre\t\t\tPromedio\n");
    printf("--\t------\t\t\t--------\n");

    // Leer y mostrar registros uno por uno
    while (fread(&e, sizeof(Estudiante), 1, archivo) == 1) {
        printf("%d\t%-20s\t%.2f\n", e.id, e.nombre, e.promedio);
    }

    fclose(archivo);
    printf("\n--- Fin del listado ---\n");
}

void buscar_estudiante() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "rb");
    if (archivo == NULL) {
        printf("No hay registros para buscar.\n");
        return;
    }

    int id_buscado;
    printf("\n--- BÚSQUEDA DE ESTUDIANTE ---\n");
    printf("Ingrese el ID del estudiante a buscar: ");
    if (scanf("%d", &id_buscado) != 1) {
        printf("Error de entrada. Cancelando operación.\n");
        fclose(archivo);
        return;
    }
    while (getchar() != '\n'); 

    Estudiante e;
    int encontrado = 0;

    // Recorrer el archivo hasta encontrar el ID
    while (fread(&e, sizeof(Estudiante), 1, archivo) == 1) {
        if (e.id == id_buscado) {
            printf("\n✅ Estudiante Encontrado:\n");
            printf("ID: %d\n", e.id);
            printf("Nombre: %s\n", e.nombre);
            printf("Promedio: %.2f\n", e.promedio);
            encontrado = 1;
            break; // Salir del bucle una vez encontrado
        }
    }

    fclose(archivo);
    if (!encontrado) {
        printf("\n❌ Error: Estudiante con ID %d no encontrado.\n", id_buscado);
    }
}

void modificar_estudiante() {
    // Necesitamos dos archivos: el original para leer y uno temporal para escribir las modificaciones
    FILE *original = fopen(NOMBRE_ARCHIVO, "rb");
    FILE *temporal = fopen("temp.dat", "wb"); 

    if (original == NULL || temporal == NULL) {
        perror("Error al abrir archivos para modificación");
        if (original) fclose(original);
        if (temporal) fclose(temporal);
        return;
    }

    int id_modificar;
    printf("\n--- MODIFICAR ESTUDIANTE ---\n");
    printf("Ingrese el ID del estudiante a modificar: ");
    if (scanf("%d", &id_modificar) != 1) {
        printf("Error de entrada. Cancelando operación.\n");
        fclose(original);
        fclose(temporal);
        return;
    }
    while (getchar() != '\n'); 

    Estudiante e;
    int encontrado = 0;

    while (fread(&e, sizeof(Estudiante), 1, original) == 1) {
        if (e.id == id_modificar) {
            encontrado = 1;
            printf("\nEstudiante encontrado. Ingrese los nuevos datos:\n");
            
            // Re-ingreso del Nombre
            printf("Nuevo Nombre (Actual: %s): ", e.nombre);
            fgets(e.nombre, 50, stdin);
            e.nombre[strcspn(e.nombre, "\n")] = 0;

            // Re-ingreso del Promedio
            printf("Nuevo Promedio (Actual: %.2f): ", e.promedio);
            if (scanf("%f", &e.promedio) != 1) {
                printf("Error de entrada en promedio. El registro NO será modificado correctamente.\n");
                while (getchar() != '\n'); 
            }
            while (getchar() != '\n'); 
            
            printf("\n✅ Registro modificado con éxito.\n");
        }
        // Escribir el registro (modificado o sin modificar) en el archivo temporal
        fwrite(&e, sizeof(Estudiante), 1, temporal);
    }

    fclose(original);
    fclose(temporal);

    if (!encontrado) {
        printf("\n❌ Error: Estudiante con ID %d no encontrado. No se realizó ninguna modificación.\n", id_modificar);
        remove("temp.dat"); // Eliminar el archivo temporal si no se encontró nada
    } else {
        // Renombrar el archivo temporal al nombre del original
        remove(NOMBRE_ARCHIVO); 
        rename("temp.dat", NOMBRE_ARCHIVO); 
    }
}

void baja_estudiante() {
    // Se utiliza la misma lógica de archivos temporales que en la modificación
    FILE *original = fopen(NOMBRE_ARCHIVO, "rb");
    FILE *temporal = fopen("temp.dat", "wb"); 

    if (original == NULL || temporal == NULL) {
        perror("Error al abrir archivos para baja");
        if (original) fclose(original);
        if (temporal) fclose(temporal);
        return;
    }

    int id_eliminar;
    printf("\n--- ELIMINAR ESTUDIANTE ---\n");
    printf("Ingrese el ID del estudiante a eliminar: ");
    if (scanf("%d", &id_eliminar) != 1) {
        printf("Error de entrada. Cancelando operación.\n");
        fclose(original);
        fclose(temporal);
        return;
    }
    while (getchar() != '\n'); 

    Estudiante e;
    int encontrado = 0;

    while (fread(&e, sizeof(Estudiante), 1, original) == 1) {
        if (e.id == id_eliminar) {
            encontrado = 1;
            printf("\n🗑️ Estudiante con ID %d (%s) eliminado con éxito.\n", e.id, e.nombre);
            // NOTA: No escribimos este registro en el archivo temporal, logrando la "baja".
        } else {
            // Escribir todos los demás registros en el archivo temporal
            fwrite(&e, sizeof(Estudiante), 1, temporal);
        }
    }

    fclose(original);
    fclose(temporal);

    if (!encontrado) {
        printf("\n❌ Error: Estudiante con ID %d no encontrado. No se realizó ninguna eliminación.\n", id_eliminar);
        remove("temp.dat"); // Eliminar el archivo temporal si no se encontró nada
    } else {
        // Renombrar el archivo temporal al nombre del original
        remove(NOMBRE_ARCHIVO); 
        rename("temp.dat", NOMBRE_ARCHIVO); 
    }
}