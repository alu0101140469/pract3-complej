/**
 * @file test_potencia.cpp
 * @brief Pruebas unitarias para la función de potencia mediante funciones primitivas recursivas.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#include "fpr/CallCounter.h"
#include "fpr/PrimitiveRecursiveFunctions.h"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

/**
 * @brief Verifica que la potencia calculada coincida con el valor esperado.
 * @param base Base de la potencia.
 * @param exponent Exponente de la potencia.
 * @param expected Valor esperado de la potencia.
 * @return true si la potencia coincide con el valor esperado, false en caso contrario.
 */
bool checkPower(
    fpr::Natural base,
    fpr::Natural exponent,
    fpr::Natural expected)
{
    // Crea un contador de llamadas y un conjunto de funciones primitivas recursivas.
    fpr::CallCounter counter;
    fpr::PrimitiveRecursiveFunctions functions(counter);

    // Calcula la potencia usando funciones primitivas recursivas.
    const fpr::Natural actual = functions.power(base, exponent);

    // Verifica si el resultado coincide con el valor esperado.
    if (actual != expected) {
        std::cerr << "FALLO: " << base << "^" << exponent
                  << " produjo " << actual
                  << ", se esperaba " << expected << ".\n";

        return false;
    }

    // Verifica que el contador haya registrado llamadas.
    if (counter.getCallCount() == 0) {
        std::cerr << "FALLO: el contador no registró llamadas.\n";
        return false;
    }

    return true;
}

/**
 * @brief Verifica que la suma y multiplicación produzcan los resultados correctos.
 * @return true si ambas operaciones producen los resultados esperados, false en caso contrario.
 */
bool checkAdditionAndMultiplication()
{
    // Crea un contador de llamadas y un conjunto de funciones primitivas recursivas para la suma.
    fpr::CallCounter additionCounter;
    fpr::PrimitiveRecursiveFunctions additionFunctions(additionCounter);

    // Verifica que la suma de 7 y 5 produzca 12.
    if (additionFunctions.addition(7, 5) != 12) {
        std::cerr << "FALLO: 7 + 5 no produjo 12.\n";
        return false;
    }

    // Crea un contador de llamadas y un conjunto de funciones primitivas recursivas para la multiplicación.
    fpr::CallCounter multiplicationCounter;
    fpr::PrimitiveRecursiveFunctions multiplicationFunctions(
        multiplicationCounter);

    // Verifica que la multiplicación de 3 y 4 produzca 12.
    if (multiplicationFunctions.multiplication(3, 4) != 12) {
        std::cerr << "FALLO: 3 * 4 no produjo 12.\n";
        return false;
    }

    return true;
}

}

/**
 * @brief Punto de entrada para las pruebas unitarias.
 * @return Código de salida del programa.
 */
int main()
{
    // Ejecuta las pruebas de suma, multiplicación y potencia, y verifica que todas pasen.
    const bool passed =
        checkAdditionAndMultiplication() &&
        checkPower(2, 3, 8) &&
        checkPower(2, 0, 1) &&
        checkPower(0, 5, 0) &&
        checkPower(0, 0, 1) &&
        checkPower(3, 4, 81) &&
        checkPower(1, 100, 1);

    if (!passed) {
        return EXIT_FAILURE;
    }

    std::cout
        << "Todas las pruebas de funciones FPR han terminado correctamente.\n";

    return EXIT_SUCCESS;
}