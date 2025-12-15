#include "funciones.h"
#include <iostream>
using namespace std;

int main() {
    vector<Persona> alumnos = cargarDatos("alumnos.txt");
    vector<Persona> tutores = cargarDatos("tutores.txt");
    vector<Persona> coordinadores = cargarDatos("coordinadores.txt");

    generarGrupos(alumnos, tutores);

    int opcion;
    do {
        cout << "\nINICIAR SESION COMO...\n";
        cout << "0 Alumno\n1 Tutor\n2 Coordinador\n3 Salir\n";
        cin >> opcion;

        if (opcion == 3) {
            cout << "Saliendo del programa...\n";
            break;
        }

        string usuario, contrasena;
        cout << "Usuario: "; cin >> usuario;
        cout << "Contrasena: "; cin >> contrasena;

        Persona persona;
        bool acceso = false;

        if (opcion == 0) acceso = login(alumnos, usuario, contrasena, persona);
        else if (opcion == 1) acceso = login(tutores, usuario, contrasena, persona);
        else if (opcion == 2) acceso = login(coordinadores, usuario, contrasena, persona);

        if (!acceso) {
            cout << "ERROR: Usuario o contrasena incorrectos.\n";
        } else {
            cout << "Bienvenido " << persona.nombre << " " << persona.apellido1 << " " << persona.apellido2 << endl;
            if (opcion == 0) menuAlumno(persona, tutores);
            else if (opcion == 1) menuTutor(persona, alumnos);
            else if (opcion == 2) menuCoordinador(persona, alumnos, tutores);
        }

    } while (true);

    return 0;
}
