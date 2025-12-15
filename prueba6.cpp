#include <iostream>
#include <fstream>
#include "funciones.h"

//COMPROBAR BORRADO DE ALERTA

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Fallo: esperado " << expected << " pero fue " << actual << std::endl; \
    } else { \
        std::cout << "OK: " << expected << " == " << actual << std::endl; \
    }


bool existeAlerta(const std::string &alumnoUser) {
    std::ifstream f("alertas.txt");
    std::string linea;
    while (getline(f, linea)) {
        if (linea.find("alumno=" + alumnoUser) != std::string::npos) {
            return true;
        }
    }
    return false;
}

int main() {

    crearAlerta("e09sami", "i42gare", "Prueba de borrado");
    bool creada = existeAlerta("e09sami");
    ASSERT_EQUAL(true, creada);


    borrarAlerta("e09sami");
    bool borrada = !existeAlerta("e09sami");
    ASSERT_EQUAL(true, borrada);

    return 0;
}

