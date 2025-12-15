#include <iostream>
#include <fstream>
#include "funciones.h"

//ENVIAR MENSAJE

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Fallo: esperado " << expected << " pero fue " << actual << std::endl; \
    } else { \
        std::cout << "OK: " << expected << " == " << actual << std::endl; \
    }

int contarMensajes() {
    std::ifstream f("mensajeria.txt");
    int count = 0; std::string linea;
    while (getline(f, linea)) count++;
    return count;
}

int main() {
    int antes = contarMensajes();
    enviarMensaje("i42merad", "i42gare", "Necesito ayuda con el ejercicio", true);
    int despues = contarMensajes();
    ASSERT_EQUAL(antes + 1, despues);
    return 0;
}


