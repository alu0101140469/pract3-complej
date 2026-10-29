/**
 * @file main.cpp
 * @brief Punto de entrada del programa para calcular potencias mediante funciones primitivas recursivas.
 * Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
 * Curso: 2026/27 - Complejidad Computacional
 * @author Daniel Palenzuela Álvarez alu0101140469
 */

#include "fpr/CallCounter.h"
#include "fpr/CommandLineParser.h"
#include "fpr/PrimitiveRecursiveFunctions.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

/**
 * @brief Punto de entrada del programa.
 * @param argc Número de argumentos.
 * @param argv Arreglo de argumentos.
 * @return Código de salida del programa.
 */
int main(int argc, char* argv[])
{
    // Determina el nombre del programa para mostrarlo en la ayuda.
    const std::string programName = (argc > 0 && argv[0] != nullptr)
        ? argv[0]
        : "potencia_fpr";

    fpr::CommandLineOptions options;

    // Analiza los argumentos de la línea de comandos y maneja errores.
    try {
        options = fpr::CommandLineParser::parse(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << "Error de argumentos: " << error.what() << '\n';
        std::cerr << fpr::CommandLineParser::usage(programName);
        return EXIT_FAILURE;
    }

    // Muestra la ayuda si se solicitó con -h o --help.
    if (options.showHelp) {
        std::cout << fpr::CommandLineParser::usage(programName);
        return EXIT_SUCCESS;
    }

    // Crea un contador de llamadas y un conjunto de funciones primitivas recursivas.
    fpr::CallCounter counter;
    fpr::PrimitiveRecursiveFunctions functions(counter);

    // Intenta calcular la potencia y maneja posibles errores durante el cálculo.
    try {
        const fpr::Natural result =
            functions.power(options.base, options.exponent);

        // Muestra el resultado y el número de llamadas a funciones.
        std::cout << "Base (x): " << options.base << '\n'
                  << "Exponente (y): " << options.exponent << '\n'
                  << "Resultado: " << result << '\n'
                  << "Número de llamadas a funciones: "
                  << counter.getCallCount() << '\n';
    } catch (const std::exception& error) {
        // Muestra el error y el número de llamadas a funciones antes de detener el cálculo.
        std::cerr << "Error durante el cálculo: " << error.what() << '\n'
                  << "Evaluaciones contabilizadas antes de detener el cálculo: "
                  << counter.getCallCount() << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}