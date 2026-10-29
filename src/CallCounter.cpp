/**
 * @file CallCounter.cpp
 * @brief Implementación de la clase CallCounter para contar evaluaciones de funciones.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#include "fpr/CallCounter.h"

#include <stdexcept>

namespace fpr {

/**
 * @brief Registra una evaluación de función.
 * @throws std::runtime_error Si se supera el límite de seguridad.
 */
void CallCounter::recordCall()
{
    // Verifica si se ha alcanzado el límite de seguridad antes de incrementar el contador.
    if (calls_ >= kMaximumFunctionCalls) {
        throw std::runtime_error(
            "Se ha alcanzado el límite de 50 000 000 evaluaciones de funciones. "
            "Pruebe con valores más pequeños.");
    }

    // Incrementa el contador de evaluaciones de funciones.
    ++calls_;
}

/**
 * @brief Devuelve el número de evaluaciones contabilizadas.
 * @return Número de llamadas registradas.
 */
CallCount CallCounter::getCallCount() const noexcept
{
    return calls_;
}

}