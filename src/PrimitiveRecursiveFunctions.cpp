/**
 * @file PrimitiveRecursiveFunctions.cpp
 * @brief Implementación de funciones primitivas recursivas.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#include "fpr/PrimitiveRecursiveFunctions.h"

#include <limits>
#include <stdexcept>

namespace fpr {

/**
 * @brief Construye el conjunto de funciones asociado a un contador.
 * @param counter Contador compartido durante el cálculo.
 */
PrimitiveRecursiveFunctions::PrimitiveRecursiveFunctions(
    CallCounter& counter) noexcept
    : counter_(counter)
{
}

/**
 * @brief Función constante cero: Z() = 0.
 * @return El número natural cero.
 */
Natural PrimitiveRecursiveFunctions::zero()
{
    counter_.recordCall();
    return 0;
}

/**
 * @brief Función sucesor: S(n) = n + 1.
 * @param value Número natural de entrada.
 * @return El sucesor de value.
 * @throws std::overflow_error Si el sucesor no cabe en Natural.
 */
Natural PrimitiveRecursiveFunctions::successor(Natural value)
{
    // Registra la evaluación de la función sucesor.
    counter_.recordCall();

    // Verifica si el sucesor de value excede el rango de Natural.
    if (value == std::numeric_limits<Natural>::max()) {
        throw std::overflow_error(
            "El resultado supera el rango de los números naturales "
            "representables por este programa (uint64_t).");
    }

    // Devuelve el sucesor de value.
    return value + 1;
}

/**
 * @brief Proyección identidad de una variable P_1^1(x) = x.
 * @param value Valor que se proyecta.
 * @return El mismo valor recibido.
 */
Natural PrimitiveRecursiveFunctions::projectionFirst(Natural value)
{
    counter_.recordCall();
    return value;
}

/**
 * @brief Calcula la suma mediante recursión primitiva.
 * @param x Primer sumando.
 * @param y Segundo sumando.
 * @return x + y.
 * @details add(x, 0) = P_1^1(x); add(x, S(y)) = S(add(x, y)).
 */
Natural PrimitiveRecursiveFunctions::addition(Natural x, Natural y)
{
    // add(x, 0) = P_1^1(x); add(x, S(y)) = S(add(x, y)).
    // Se contabilizan las y evaluaciones recursivas internas sin usar la pila.
    counter_.recordCall();

    // Cada iteración representa una evaluación de la función add en la recursión.
    for (Natural step = 0; step < y; ++step) {
        counter_.recordCall();
    }

    // Comienza con el valor proyectado y aplica sucesor y recursión.
    Natural result = projectionFirst(x);

    // Aplica sucesor y recursión y veces.
    for (Natural step = 0; step < y; ++step) {
        result = successor(result);
    }

    return result;
}

/**
 * @brief Calcula el producto mediante la suma y recursión primitiva.
 * @param x Primer factor.
 * @param y Segundo factor.
 * @return x * y.
 * @details mul(x, 0) = Z(); mul(x, S(y)) = add(x, mul(x, y)).
 */
Natural PrimitiveRecursiveFunctions::multiplication(Natural x, Natural y)
{
    // mul(x, 0) = Z(); mul(x, S(y)) = add(x, mul(x, y)).
    // Cada iteración contabiliza una evaluación interna de multiplicación.
    counter_.recordCall();

    // Cada iteración representa una evaluación de la función mul en la recursión.
    for (Natural step = 0; step < y; ++step) {
        counter_.recordCall();
    }

    // Comienza con el valor cero y aplica suma y recursión y veces.
    Natural result = zero();

    // Aplica suma y recursión y veces.
    for (Natural step = 0; step < y; ++step) {
        result = addition(x, result);
    }

    return result;
}

/**
 * @brief Calcula x elevado a y como función primitiva recursiva.
 * @param x Base natural.
 * @param y Exponente natural.
 * @return x elevado a y, según la definición recursiva, x^0 = 1, también
 *         cuando x = 0.
 * @details pow(x, 0) = S(Z()); pow(x, S(y)) = mul(x, pow(x, y)).
 */
Natural PrimitiveRecursiveFunctions::power(Natural x, Natural y)
{
    // pow(x, 0) = S(Z()); pow(x, S(y)) = mul(x, pow(x, y)).
    // Se registran las evaluaciones recursivas del exponente, y luego se
    // evalúan las composiciones en orden ascendente, desde el caso base.
    counter_.recordCall();

    // Cada iteración representa una evaluación de la función pow en la recursión.
    for (Natural step = 0; step < y; ++step) {
        counter_.recordCall();
    }

    // Comienza con el valor 1 (sucesor de cero) y aplica multiplicación y recursión y veces.
    Natural result = successor(zero());

    // Aplica multiplicación y recursión y veces.
    for (Natural step = 0; step < y; ++step) {
        result = multiplication(x, result);
    }

    return result;
}

}