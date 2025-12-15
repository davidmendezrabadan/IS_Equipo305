#include <iostream>
#include "funciones.h"

//CONTAR ALUMNOS

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Fallo: esperado " << expected << " pero fue " << actual << std::endl; \
    } else { \
        std::cout << "OK: " << expected << " == " << actual << std::endl; \
    }

int main() {
    auto alumnos = cargarDatos("alumnos.txt");
    ASSERT_EQUAL(19, (int)alumnos.size()); 
    return 0;
}
