# Simulador de Tabla FAT en C++

Este proyecto implementa una **simulación básica del sistema de archivos FAT (File Allocation Table)**. Permite crear, eliminar y visualizar archivos simulados sobre un "disco" dividido en bloques, gestionado mediante una tabla FAT.

## 📁 Descripción

La FAT (File Allocation Table) es una estructura de datos usada por varios sistemas de archivos para mantener un seguimiento de los bloques que conforman los archivos en el disco. Este programa simula dicha estructura mediante:

- Un arreglo de entradas FAT.
- Funciones para gestionar archivos (crear, eliminar).
- Un menú interactivo para el usuario.

## ⚙️ Características

- Simulación de 128 bloques de disco.
- Gestión de archivos mediante punteros en la tabla FAT.
- Visualización completa de la tabla FAT.
- Inspección de los bloques de un archivo específico.
- Manejo de fragmentación y liberación de bloques.

## 🧠 Conceptos Aprendidos

- Organización de archivos mediante FAT.
- Simulación de estructuras de bajo nivel de un sistema operativo.
- Fragmentación externa e interna.
- Manejo dinámico de memoria en vectores.

## 🧪 Cómo ejecutar

1. Compila el programa:

```bash
g++ -o simulador_fat simulador_fat.cpp
```

2. Ejecuta el programa:

```bash
./simulador_fat
```

3. Usa el menú interactivo:

```
--- Menú FAT ---
1. Crear archivo
2. Eliminar archivo
3. Mostrar tabla FAT
4. Mostrar bloques de un archivo
5. Salir
```

## 📌 Estructura de Datos

```cpp
struct FATEntry {
    int nextBlock;  // Siguiente bloque del archivo (-1 si es el último)
    bool isFree;    // Estado del bloque (true = libre)
};
```

## 🧹 Fragmentación

Este simulador permite observar cómo se produce la **fragmentación externa** cuando los archivos no se almacenan en bloques contiguos. También se refleja la **fragmentación interna** si los archivos no utilizan completamente su último bloque.

## 🛠 Funciones principales

- `initializeFAT()` – Inicializa todos los bloques como libres.
- `createFile(fileSize)` – Crea un archivo de tamaño dado.
- `deleteFile(startBlock)` – Elimina un archivo desde su bloque inicial.
- `printFAT()` – Muestra la tabla FAT completa.
- `displayFileBlocks(startBlock)` – Muestra los bloques que componen un archivo.
