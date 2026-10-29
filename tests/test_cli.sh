#!/usr/bin/env bash
# Programa de prueba para la línea de comandos del programa de potencia.
# Práctica 3: Implementación de Funciones Primitivas Recursivas de Números Naturales
# Daniel Palenzuela Álvarez alu0101140469

set -euo pipefail

program="${1:-./build/potencia_fpr}"

output="$($program -x 2 -y 3)"
grep -q '^Resultado: 8$' <<< "$output"
grep -Eq '^Número de llamadas a funciones: [1-9][0-9]*$' <<< "$output"

output="$($program -y 0 -x 0)"
grep -q '^Resultado: 1$' <<< "$output"

if "$program" -x -1 -y 3 >/dev/null 2>&1; then
    echo "FALLO: se aceptó una base negativa." >&2
    exit 1
fi

if "$program" -x 2 >/dev/null 2>&1; then
    echo "FALLO: se aceptó una línea de comandos incompleta." >&2
    exit 1
fi

echo "Todas las pruebas de línea de comandos han terminado correctamente."