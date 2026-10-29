/**
 * @file CommandLineParser.cpp
 * @brief Implementación de la clase CommandLineParser para analizar y validar las opciones de la línea de comandos.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#include "fpr/CommandLineParser.h"

#include <charconv>
#include <string_view>
#include <system_error>
#include <stdexcept>

namespace fpr {
namespace {

/**
 * @brief Convierte un texto a un número natural.
 * @param text Texto que representa un número natural.
 * @param optionName Nombre de la opción para mensajes de error.
 * @return Número natural convertido.
 * @throws std::invalid_argument Si el texto no es un número natural válido.
 */
Natural parseNatural(const char* text, const char* optionName)
{
    // Convierte el texto a un número natural usando std::from_chars.
    const std::string_view token(text);
    Natural value = 0;
    const char* const begin = token.data();
    const char* const end = begin + token.size();
    const auto parsed = std::from_chars(begin, end, value);

    // Verifica si la conversión se realizó correctamente y si todo el token fue consumido.
    if (token.empty() || parsed.ec != std::errc{} || parsed.ptr != end) {
        throw std::invalid_argument(
            std::string("El valor de ") + optionName +
            " debe ser un número natural no negativo dentro del rango uint64_t.");
    }

    return value;
}

}

/**
 * @brief Analiza los argumentos recibidos por main.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @return Opciones validadas o una indicación para mostrar la ayuda.
 * @throws std::invalid_argument Si faltan opciones o algún valor no es natural.
 */
CommandLineOptions CommandLineParser::parse(int argc, char* argv[])
{
    // Verifica si se solicita la ayuda con -h o --help.
    if (argc == 2 && (std::string_view(argv[1]) == "-h" ||
                      std::string_view(argv[1]) == "--help")) {
        CommandLineOptions options;
        options.showHelp = true;
        return options;
    }

    CommandLineOptions options;
    bool hasBase = false;
    bool hasExponent = false;

    // Itera sobre los argumentos para analizar las opciones -x y -y.
    for (int index = 1; index < argc; ++index) {
        const std::string_view argument(argv[index]);

        // Verifica si se solicita la ayuda con -h o --help.
        if (argument == "-h" || argument == "--help") {
            throw std::invalid_argument(
                "Las opciones de ayuda deben usarse por separado.");
        }

        // Verifica si el argumento es una opción válida (-x o -y).
        if (argument != "-x" && argument != "-y") {
            throw std::invalid_argument(
                "Opción desconocida: " + std::string(argument));
        }

        // Verifica si hay un valor numérico después de la opción.
        if (index + 1 >= argc) {
            throw std::invalid_argument(
                "Falta el valor numérico después de " +
                std::string(argument));
        }

        // Convierte el siguiente argumento a un número natural.
        const Natural value = parseNatural(argv[++index], argument.data());

        // Asigna el valor a la opción correspondiente y verifica duplicados.
        if (argument == "-x") {
            if (hasBase) {
                throw std::invalid_argument(
                    "La opción -x no puede repetirse.");
            }

            options.base = value;
            hasBase = true;
        } else {
            if (hasExponent) {
                throw std::invalid_argument(
                    "La opción -y no puede repetirse.");
            }

            options.exponent = value;
            hasExponent = true;
        }
    }

    // Verifica que ambas opciones -x y -y hayan sido proporcionadas.
    if (!hasBase || !hasExponent) {
        throw std::invalid_argument(
            "Debe especificar las dos opciones: -x <n> y -y <n>.");
    }

    return options;
}

/**
 * @brief Genera la ayuda de uso del programa.
 * @param programName Nombre del ejecutable.
 * @return Texto de ayuda.
 */
std::string CommandLineParser::usage(const std::string& programName)
{
    return "Uso: " + programName + " -x <n> -y <n>\n"
           "  -x <n>   Base natural de la potencia (incluye 0).\n"
           "  -y <n>   Exponente natural de la potencia (incluye 0).\n"
           "  -h       Muestra esta ayuda.\n"
           "Ejemplo: " + programName + " -x 2 -y 3\n";
}

}