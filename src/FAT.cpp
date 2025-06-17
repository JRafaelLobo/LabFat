#include <iostream>
#include <vector>

using namespace std;

// Número total de bloques del "disco"
const int DISK_SIZE = 128;

// Estructura para representar una entrada en la FAT
struct FATEntry
{
    int nextBlock; // Índice del siguiente bloque (-1 si es el último)
    bool isFree;   // true si el bloque está libre
};

// Tabla FAT simulada
vector<FATEntry> fatTable(DISK_SIZE);

// Inicializar la FAT (todos los bloques libres)
void initializeFAT()
{
    for (int i = 0; i < DISK_SIZE; ++i)
    {
        fatTable[i].isFree = true;
        fatTable[i].nextBlock = -1;
    }
}

// Eliminar un archivo dado su bloque inicial
void deleteFile(int startBlock)
{
    int idBlock = startBlock;
    while (idBlock != -1)
    {
        int siguienteBloque = fatTable[idBlock].nextBlock;
        fatTable[idBlock].nextBlock = -1;
        fatTable[idBlock].isFree = true;
        idBlock = siguienteBloque;
    }
}

// Crear un archivo de tamaño dado (en bloques)
// Retorna el índice del bloque inicial o -1 si no hay suficiente espacio
int createFile(int fileSize)
{
    int filellenado = 0;
    int idAnterior = -1, idInicial = -1;
    for (size_t i = 0; i < DISK_SIZE; i++)
    {
        if (!fatTable[i].isFree)
        {
            continue;
        }
        if (idAnterior == -1)
        {
            idAnterior = i;
            idInicial = i;
            fatTable[i].isFree = false;
            filellenado++;
            if (filellenado >= fileSize)
            {
                fatTable[i].nextBlock = -1;
                break;
            }
            continue;
        }
        fatTable[idAnterior].nextBlock = i;
        fatTable[i].isFree = false;
        idAnterior = i;
        filellenado++;
        if (filellenado >= fileSize)
        {
            fatTable[i].nextBlock = -1;
            break;
        }
    }
    if (filellenado < fileSize)
    {
        deleteFile(idInicial);
        idInicial = -1;
    }

    return idInicial;
}

// Mostrar el estado actual de la FAT
void printFAT()
{
    cout << "\nÍndice\tLibre\tSiguiente\n";
    for (int i = 0; i < DISK_SIZE; ++i)
    {
        cout << i << "\t" << (fatTable[i].isFree ? "Sí" : "No") << "\t"
             << fatTable[i].nextBlock << "\n";
    }
}

// Mostrar los bloques que pertenecen a un archivo
void displayFileBlocks(int startBlock)
{
    cout << "\nÍndice\tLibre\tSiguiente\n";
    int idBlock = startBlock;
    while (idBlock != -1)
    {
        int siguienteBloque = fatTable[idBlock].nextBlock;
        cout << idBlock << "\t" << (fatTable[idBlock].isFree ? "Sí" : "No") << "\t"
             << fatTable[idBlock].nextBlock << "\n";
        idBlock = siguienteBloque;
    }
}

// Menú interactivo
void menu()
{
    int option, size, startBlock;

    do
    {
        cout << "\n--- Menú FAT ---\n";
        cout << "1. Crear archivo\n";
        cout << "2. Eliminar archivo\n";
        cout << "3. Mostrar tabla FAT\n";
        cout << "4. Mostrar bloques de un archivo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Tamaño del archivo (en bloques): ";
            cin >> size;
            startBlock = createFile(size);
            if (startBlock != -1)
                cout << "Archivo creado. Bloque inicial: " << startBlock << "\n";
            else
                cout << "No hay espacio suficiente para el archivo.\n";
            break;

        case 2:
            cout << "Bloque inicial del archivo a eliminar: ";
            cin >> startBlock;
            deleteFile(startBlock);
            cout << "Archivo eliminado.\n";
            break;

        case 3:
            printFAT();
            break;

        case 4:
            cout << "Bloque inicial del archivo: ";
            cin >> startBlock;
            displayFileBlocks(startBlock);
            break;

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opción inválida.\n";
        }

    } while (option != 5);
}

int main()
{
    initializeFAT();
    menu();
    return 0;
}
