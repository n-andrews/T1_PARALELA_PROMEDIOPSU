# Taller 1 - Computación paralela y Distribuida - "Promedios PSU"
El taller consiste en escribir un programa en C++, C++ usando OpenMP y Dart que pueda leer un archivo con los puntajes psu de una persona con el siguiente formato "rut;nem;ranking;lenguaje;matematicas;ciencias;historia" y luego deberá escribir otro archivo con el promedio simple de estos puntajes por rut, teniendo finalmente un archivo con entradas "rut;promedio".

Los programas en C++ escriben el archivo "promedioPSU.csv" mientras que el programa en Dart escribe el archivo "proomediosDart.csv"

### Archivos
- `main.cpp` contiene el programa en C++ (Secuencial)
- `promedios.dart` contiene el programa en Dart
- `main_omp.cpp` contiene el programa en C++ con OpenMP

### Compilación
Para C++ Secuencial:
```
g++ -O3 -std=gnu++14 main.cpp
```
Para C++ OpenMP:
```
g++ -O3 -std=gnu++14 -fopenmp main_omp
```

### Ejecución
- C++
    `./main.exe examples/archivo.csv`
- Dart
    `dart promediosdart examples/archivo.csv`

#### Autores
- Daniel Aguilera Tasso
- Nicolás Andrews Sandoval
- Allan Morales Prado