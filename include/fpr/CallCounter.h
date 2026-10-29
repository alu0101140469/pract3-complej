/**
 * @file CallCounter.h
 * @brief Clase para contar las evaluaciones de funciones durante el cálculo.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#ifndef FPR_CALL_COUNTER_H
#define FPR_CALL_COUNTER_H

#include <cstdint>

namespace fpr {

/** @brief Número de evaluaciones de funciones contabilizadas. */
using CallCount = std::uint64_t;

/**
 * @class CallCounter
 * @brief Cuenta las evaluaciones de funciones usadas durante el cálculo.
 *
 * El contador incluye las funciones básicas (cero, sucesor y proyección) y
 * cada evaluación de las funciones recursivas, incluidas sus etapas recursivas.
 * Se establece un límite de seguridad para evitar cálculos desmesurados.
 */
class CallCounter {
public:
    /** @brief Máximo de evaluaciones admitidas en una ejecución. */
    static constexpr CallCount kMaximumFunctionCalls = 50'000'000ULL;

    /**
     * @brief Registra una evaluación de función.
     * @throws std::runtime_error Si se supera el límite de seguridad.
     */
    void recordCall();

    /**
     * @brief Devuelve el número de evaluaciones contabilizadas.
     * @return Número de llamadas registradas.
     */
    [[nodiscard]] CallCount getCallCount() const noexcept;

private:
    /** @brief Total acumulado de evaluaciones de funciones. */
    CallCount calls_ = 0;
};

}

#endif