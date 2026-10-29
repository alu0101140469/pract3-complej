# Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales

## 1. Información del proyecto

* **Alumno:** Daniel Palenzuela Álvarez alu0101140469
* **Asignatura:** Complejidad Computacional
* **Curso:** 2026/27
* **Práctica 3:** Implementación de Funciones Primitivas Recursivas de Números Naturales
* **Repositorio Github:** [https://github.com/alu0101140469/pract3-complej](https://github.com/alu0101140469/pract3-complej)

## 2. Funcionamiento general

El programa construye la potencia a partir de operaciones más sencillas. No utiliza directamente `pow()` ni una operación de potencia de una biblioteca, sino que implementa funciones básicas y las combina mediante las definiciones recursivas correspondientes.

El flujo general es el siguiente:

```text
Argumentos de la consola (-x y -y)
              |
              v
     CommandLineParser
     Validación de argumentos
              |
              v
       main.cpp crea
  CallCounter y las funciones FPR
              |
              v
       power(x, y)
              |
              v
  Funciones básicas, suma y producto
              |
              v
 Mostrar resultado y evaluaciones
```

### 2.1. Funciones básicas

La implementación utiliza las siguientes funciones básicas:

- **Función cero:** `Z() = 0`. Devuelve el natural cero.
- **Función sucesor:** `S(n) = n + 1`. Devuelve el siguiente número natural.
- **Función de proyección:** `P¹₁(x) = x`. Devuelve el primer argumento recibido.

A partir de ellas se construyen la suma, la multiplicación y la potencia.

### 2.2. Definición de la suma

La suma se define por recursión primitiva sobre el segundo argumento:

`suma(x,0) = x`

`suma(x,y+1) = S(suma(x,y))`

El caso base devuelve `x` mediante la proyección, y para cada unidad del segundo argumento se aplica el sucesor una vez. Por ejemplo, `suma(3, 2)` empieza en 3 y aplica el sucesor dos veces, obteniendo 5.

### 2.3. Definición de la multiplicación

La multiplicación se construye utilizando la suma:

`mult(x,0) = Z()`

`mult(x,y+1) = suma(x,mult(x,y))`

El producto comienza en cero y suma `x` tantas veces como indica `y`. Por ejemplo, `mult(3, 4)` equivale a sumar 3 cuatro veces y devuelve 12.

### 2.4. Definición de la potencia

La potencia se construye a partir de la multiplicación:

`potencia(x,0) = S(Z()) = 1`

`potencia(x,y+1) = mult(x,potencia(x,y))`

El caso base devuelve 1, y después se multiplica repetidamente por la base hasta alcanzar el exponente indicado. Por la definición adoptada, `0^0` devuelve 1.

En el código, las etapas recursivas se ejecutan mediante bucles en lugar de crear una llamada recursiva nativa de C++ para cada paso. Los bucles siguen la recurrencia y el contador registra también las etapas recursivas lógicas.

## 3. Compilación y pruebas

### Compilación con Make

Desde el directorio raíz del proyecto, ejecutar:

```bash
make
```

El ejecutable se genera en `build/potencia_fpr`.

### Ejecutar las pruebas

```bash
make test
```

Este objetivo ejecuta las pruebas de las funciones matemáticas y las pruebas de la interfaz de línea de comandos.

### Limpiar los archivos generados

```bash
make clean
```

Elimina los objetos y ejecutables generados dentro de `build/` y vuelve a crear ese directorio con su fichero marcador `.gitkeep`.

## 4. Ejecución del programa

El programa exige los dos argumentos siguientes:

- `-x <n>`: base natural de la potencia.
- `-y <n>`: exponente natural de la potencia.

Las opciones se pueden introducir en cualquier orden. Por ejemplo:

```bash
./build/potencia_fpr -x 2 -y 3
```

Salida obtenida para ese ejemplo:

```text
Base (x): 2
Exponente (y): 3
Resultado: 8
Número de llamadas a funciones: 61
```

También se pueden probar casos límite:

```bash
./build/potencia_fpr -x 2 -y 0
./build/potencia_fpr -x 0 -y 5
./build/potencia_fpr -x 0 -y 0
```

La definición utilizada produce, respectivamente, `1`, `0` y `1`.

Para mostrar la ayuda:

```bash
./build/potencia_fpr -h
```

## 5. Contador de evaluaciones y límites

La clase `CallCounter` registra las evaluaciones de las funciones. El código contabiliza las llamadas a las funciones básicas y a las operaciones matemáticas, así como las etapas recursivas lógicas que corresponden a las definiciones anteriores. Estas etapas se registran explícitamente porque se ejecutan con bucles y no mediante llamadas recursivas nativas de C++.

Por tanto, el número mostrado representa las evaluaciones contabilizadas según esta convención; no representa el número de instrucciones de máquina ni el número total de operaciones internas que realiza el procesador. El valor depende de las definiciones y del método de conteo utilizados.

Se aplican dos límites importantes:

- **Límite de evaluaciones:** el contador detiene el cálculo si se alcanza el máximo de 50.000.000 evaluaciones.
- **Rango numérico:** los naturales y los resultados se representan mediante `std::uint64_t`. Si se detecta que una operación de sucesor excedería el rango representable, el programa informa del desbordamiento.

Estos límites evitan ejecuciones excesivamente largas y resultados numéricos que no puedan representarse con el tipo utilizado.

## 6. Estructura del proyecto

```text
practica3_fpr/
├── src/
│   ├── main.cpp
│   ├── CallCounter.cpp
│   ├── CommandLineParser.cpp
│   └── PrimitiveRecursiveFunctions.cpp
├── include/
│   └── fpr/
│       ├── Natural.h
│       ├── CallCounter.h
│       ├── CommandLineParser.h
│       └── PrimitiveRecursiveFunctions.h
├── build/
│   └── .gitkeep
├── tests/
│   ├── test_potencia.cpp
│   └── test_cli.sh
├── Makefile
└── README.md
```

## 7. Descripción de los ficheros y las clases

### 7.1. `src/main.cpp`

Es el punto de entrada del programa. Interpreta los argumentos mediante `CommandLineParser`, crea un objeto `CallCounter` y un objeto `PrimitiveRecursiveFunctions` que comparte ese contador. Después llama a `power(x, y)`, muestra la base, el exponente, el resultado y el número de evaluaciones. Si se produce una excepción, presenta el error y termina con un código de salida distinto de cero.

### 7.2. `include/fpr/Natural.h`

Define el alias `fpr::Natural` como `std::uint64_t`. Se utiliza para representar los números naturales, incluido el cero, dentro del rango de un entero sin signo de 64 bits. Centralizar el tipo facilita cambiar su representación en una futura ampliación.

### 7.3. `include/fpr/CallCounter.h` y `src/CallCounter.cpp`

La clase `CallCounter` mantiene el atributo privado `calls_`, que contiene el total de evaluaciones contabilizadas.

- `recordCall()` incrementa el contador y comprueba antes que no se haya alcanzado el límite máximo.
- `getCallCount()` devuelve el total acumulado sin modificar el estado del objeto.
- `kMaximumFunctionCalls` establece el límite de seguridad de 50 millones de evaluaciones.

Cuando se alcanza el límite, `recordCall()` lanza una excepción para que el programa detenga el cálculo e informe del problema.

### 7.4. `include/fpr/CommandLineParser.h` y `src/CommandLineParser.cpp`

La estructura `CommandLineOptions` almacena la base, el exponente y un indicador que señala si se ha solicitado mostrar la ayuda.

La clase `CommandLineParser` separa la validación de la entrada de la lógica matemática:

- `parse(argc, argv)` interpreta `-x` y `-y`, verifica que ambas opciones estén presentes, rechaza duplicados y opciones desconocidas y convierte los valores a `Natural`.
- `usage(programName)` genera el texto que explica cómo invocar el programa.

La conversión numérica se realiza con `std::from_chars`, comprobando que el argumento completo sea un entero no negativo y que quepa en el tipo utilizado.

### 7.5. `include/fpr/PrimitiveRecursiveFunctions.h` y `src/PrimitiveRecursiveFunctions.cpp`

La clase `PrimitiveRecursiveFunctions` contiene la implementación matemática principal. Su constructor recibe una referencia a `CallCounter`, compartida por los diferentes métodos, para que todas las evaluaciones queden registradas en el mismo total.

Sus métodos principales son:

- `zero()`: registra la evaluación de la función cero y devuelve `0`.
- `successor(value)`: registra la evaluación y devuelve `value + 1`, comprobando antes el posible desbordamiento.
- `projectionFirst(value)`: registra y devuelve el primer argumento.
- `addition(x, y)`: implementa la suma mediante el caso base de proyección y aplicaciones del sucesor.
- `multiplication(x, y)`: implementa el producto mediante sumas repetidas, comenzando por el caso base cero.
- `power(x, y)`: implementa la potencia mediante multiplicaciones repetidas, comenzando por el caso base `S(Z()) = 1`.

En `addition`, `multiplication` y `power`, los bucles ejecutan las etapas de la recurrencia sin producir una cadena de llamadas recursivas nativas. Las etapas recursivas teóricas se registran explícitamente en el contador para mantener la convención de conteo documentada.

### 7.6. `tests/test_potencia.cpp`

Contiene pruebas unitarias sencillas para comprobar que la suma y la multiplicación producen resultados correctos. También prueba varias potencias, entre ellas `2^3`, `2^0`, `0^5`, `0^0`, `3^4` y `1^100`. Comprueba además que el contador registre evaluaciones.

### 7.7. `tests/test_cli.sh`

Prueba el ejecutable completo desde la consola. Comprueba el resultado de `2^3`, el caso `0^0`, y verifica que se rechacen una base negativa y una línea de comandos incompleta.

### 7.8. `Makefile`

Define los objetivos `all`, `test`, `clean` y `help`. `make` compila el ejecutable, `make test` compila y ejecuta las pruebas, y `make clean` elimina los artefactos generados.


### 7.9. `build/.gitkeep`

- `build/.gitkeep` mantiene el directorio `build/` en el proyecto aunque no haya artefactos de compilación.

## 8. Pruebas realizadas

Las pruebas se ejecutan con:

```bash
make test
```

La batería de pruebas cubre las operaciones de suma y multiplicación, potencias con distintos casos base y valores, y la validación de argumentos por línea de comandos.