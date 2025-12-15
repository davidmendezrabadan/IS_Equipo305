#include <iostream>
#include <fstream>
#include "funciones.h"

//GENERAR GRUPOS

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Fallo: esperado " << expected << " pero fue " << actual << std::endl; \
    } else { \
        std::cout << "OK: " << expected << " == " << actual << std::endl; \
    }

bool existeArchivo(const std::string &filename) {
    std::ifstream f(filename);
    return f.good();
}

int main() {
    auto alumnos = cargarDatos("alumnos.txt");
    auto tutores = cargarDatos("tutores.txt");
    generarGrupos(alumnos, tutores);
    ASSERT_EQUAL(true, existeArchivo("grupos.txt"));
    return 0;
}


