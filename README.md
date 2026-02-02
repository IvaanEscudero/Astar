# Algoritmo A* para Resolución de Laberintos

![Lenguaje](https://img.shields.io/badge/Language-C++-blue.svg)
![Algoritmo](https://img.shields.io/badge/Algorithm-A*-green.svg)

## Descripción
Este proyecto es una implementación avanzada del algoritmo de búsqueda de caminos **A* (A-Star)** en C++. El programa es capaz de encontrar la ruta óptima en laberintos cargados desde archivos de texto, permitiendo movimientos en 8 direcciones (incluyendo diagonales) y calculando costes reales de desplazamiento ($1$ para movimientos ortogonales y $\sqrt{2}$ para diagonales).

Este proyecto fue desarrollado en la asignatura de Sistemas Inteligentes en la Universitat de València en 2023.

## Heurísticas Implementadas
La flexibilidad de este proyecto reside en su sistema de heurísticas intercambiables. Mediante el uso de directivas de preprocesador (`#ifdef`) en el archivo `heuristic.cpp`, puedes compilar el programa para usar diferentes métodos de estimación:

1.  **Manhattan (`manhattan`):** Basada en la distancia $L_1$. Ideal para entornos donde el movimiento es estrictamente en rejilla.
2.  **Euclídea (`euclidea`):** Basada en la distancia en línea recta ($L_2$). Es la más precisa para el movimiento diagonal que permite este programa.
3.  **No Informativa (`ni`):** Transforma el algoritmo en una búsqueda de Dijkstra al ignorar el coste estimado al objetivo ($h=0$).

## Compilación y Uso

El proyecto utiliza un `Makefile` que gestiona automáticamente la configuración de la heurística elegida.

### 1. Compilar
Para cambiar la heurística, puedes editar la variable `CHOICE` dentro del archivo `Makefile` (descomentando la que desees) o pasarla como argumento. Los comandos principales son:

```bash
# Limpiar archivos de compilaciones anteriores
make clean

# Compilar el proyecto (usará la heurística definida en el Makefile)
make
```
### 2. Ejecutar
Una vez compilado, el comando `make` generará un ejecutable cuyo nombre indica la heurística utilizada (ej. `Astar_ni`). Para ejecutarlo, pasa como parámetro uno de los archivos de mapa:

```bash
# Ejemplo usando la heurística Manhattan con el mapa 'entgrande'
./Astar_manhattan entgrande

# Ejemplo usando la búsqueda No Informativa con 'entprueba'
./Astar_ni entprueba
```
El programa mostrará el laberinto original y, tras resolverlo, imprimirá el camino óptimo marcado con colores en la consola y generará un archivo output.txt con las coordenadas.

## Estructura de Archivos
* **Astar.cpp:** Es el archivo principal y contiene la función Astar() que gestiona los nodos y el cálculo de costes.
* **Maze.cpp / .h:** Implementa la clase Maze, encargada de parsear los archivos de entrada, detectar los obstáculos de los laberintos y realizar la impresión formateada en consola.
* **heuristic.cpp / .h:** Contiene las definiciones de las funciones h(n) (heurísticas) protegidas por macros de compilación.
* **Archivos ent:** Diferentes escenarios de prueba:
    * **entprueba:** Laberinto pequeño para testeo rápido.
    * **enttest1/2:** Casos específicos de bordes y caminos sin salida.
    * **entgrande:** Laberinto de gran tamaño para probar el rendimiento.
* **Makefile:** Automatización de la compilación antes explicada.

## Notas
* El algoritmo considera movimientos en 8 direcciones (sus casillas adyacentes). Los desplazamientos diagonales tienen un coste de $\sqrt{2}$, mientras que los ortogonales $1$.
* El camino seguido se guarda en output.txt en el formato [[R1,C1],...,[Rn,Cn]].
