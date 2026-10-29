/**
 * @file PrimitiveRecursiveFunctions.h
 * @brief Implementación de funciones primitivas recursivas.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#ifndef FPR_PRIMITIVE_RECURSIVE_FUNCTIONS_H
#define FPR_PRIMITIVE_RECURSIVE_FUNCTIONS_H

#include "fpr/CallCounter.h"
#include "fpr/Natural.h"

namespace fpr {

/**
 * @class PrimitiveRecursiveFunctions
 * @brief Implementa cero, sucesor, proyección, suma, multiplicación y potencia.
 *
 * La suma, multiplicación y potencia se construyen mediante recursión
 * primitiva iterativa, el contador registra sus evaluaciones y funciones básicas.
 */
class PrimitiveRecursiveFunctions {
public:
    /**
     * @brief Construye el conjunto de funciones asociado a un contador.
     * @param counter Contador compartido durante el cálculo.
     */
    explicit PrimitiveRecursiveFunctions(CallCounter& counter) noexcept;

    /**
     * @brief Función constante cero: Z() = 0.
     * @return El número natural cero.
     */
    [[nodiscard]] Natural zero();

    /**
     * @brief Función sucesor: S(n) = n + 1.
     * @param value Número natural de entrada.
     * @return El sucesor de value.
     * @throws std::overflow_error Si el sucesor no cabe en Natural.
     */
    [[nodiscard]] Natural successor(Natural value);

    /**
     * @brief Proyección identidad de una variable: P_1^1(x) = x.
     * @param value Valor que se proyecta.
     * @return El mismo valor recibido.
     */
    [[nodiscard]] Natural projectionFirst(Natural value);

    /**
     * @brief Calcula la suma mediante recursión primitiva.
     * @param x Primer sumando.
     * @param y Segundo sumando.
     * @return x + y.
     * @details add(x, 0) = P_1^1(x); add(x, S(y)) = S(add(x, y)).
     */
    [[nodiscard]] Natural addition(Natural x, Natural y);

    /**
     * @brief Calcula el producto mediante la suma y recursión primitiva.
     * @param x Primer factor.
     * @param y Segundo factor.
     * @return x * y.
     * @details mul(x, 0) = Z(); mul(x, S(y)) = add(x, mul(x, y)).
     */
    [[nodiscard]] Natural multiplication(Natural x, Natural y);

    /**
     * @brief Calcula x elevado a y como función primitiva recursiva.
     * @param x Base natural.
     * @param y Exponente natural.
     * @return x elevado a y; según la definición recursiva, x^0 = 1, también
     *         cuando x = 0.
     * @details pow(x, 0) = S(Z()); pow(x, S(y)) = mul(x, pow(x, y)).
     */
    [[nodiscard]] Natural power(Natural x, Natural y);

private:
    /** @brief Contador utilizado por todas las funciones del conjunto. */
    CallCounter& counter_;
};

}

#endif