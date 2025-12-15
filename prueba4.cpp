#include <iostream>
#include <fstream>
#include "funciones.h"

//CREAR ALERTA

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Fallo: esperado " << expected << " pero fue " << actual << std::endl; \
    } else { \
        std::cout << "OK: " << expected << " == " << actual << std::endl; \
    }

bool contieneAlerta(const std::string &alumno) {
    std::ifstream f("alertas.txt");
    std::string linea;
    while (getline(f, linea)) {
        if (linea.find("alumno=" + alumno) != std::string::npos) return true;
    }
    return false;
}

int main() {
    crearAlerta("i42merad", "i42gare", "No entregó la práctica");
    ASSERT_EQUAL(true, contieneAlerta("i42merad"));
    return 0;
}

