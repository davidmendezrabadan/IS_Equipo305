#include <iostream>
#include "funciones.h"

//ASIGNAR TUTOR A ALUMNO

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Fallo: esperado " << expected << " pero fue " << actual << std::endl; \
    } else { \
        std::cout << "OK: " << expected << " == " << actual << std::endl; \
    }

int main() {
    auto alumnos = cargarDatos("alumnos.txt");
    Persona p;
    bool ok = login(alumnos, "i42merad", "Contraseña123", p);
    ASSERT_EQUAL(true, ok);
    ASSERT_EQUAL("David", p.nombre); 
    return 0;
}


