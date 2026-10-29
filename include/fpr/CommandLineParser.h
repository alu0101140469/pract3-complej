/**
 * @file CommandLineParser.h
 * @brief Clase para analizar y validar las opciones de la línea de comandos.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#ifndef FPR_COMMAND_LINE_PARSER_H
#define FPR_COMMAND_LINE_PARSER_H

#include "fpr/Natural.h"

#include <string>

namespace fpr {

/** @brief Valores leídos desde la línea de comandos. */
struct CommandLineOptions {
    /** @brief Base de la potencia indicada mediante -x. */
    Natural base = 0;

    /** @brief Exponente de la potencia indicado mediante -y. */
    Natural exponent = 0;

    /** @brief Indica si se ha solicitado mostrar la ayuda. */
    bool showHelp = false;
};

/**
 * @class CommandLineParser
 * @brief Valida y convierte las opciones de la línea de comandos.
 */
class CommandLineParser {
public:
    /**
     * @brief Analiza los argumentos recibidos por main.
     * @param argc Número de argumentos.
     * @param argv Vector de argumentos.
     * @return Opciones validadas o una indicación para mostrar la ayuda.
     * @throws std::invalid_argument Si faltan opciones o algún valor no es natural.
     */
    [[nodiscard]] static CommandLineOptions parse(int argc, char* argv[]);

    /**
     * @brief Genera la ayuda de uso del programa.
     * @param programName Nombre del ejecutable.
     * @return Texto de ayuda.
     */
    [[nodiscard]] static std::string usage(const std::string& programName);
};

}

#endif