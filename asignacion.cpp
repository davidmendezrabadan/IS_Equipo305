#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Persona {
    string usuario;
    string contrasena;
    string modalidad;
    string dni;
    string nombre;
    string apellido1;
    string apellido2;
};

vector<Persona> cargarDatos(const string &filename) {
    vector<Persona> personas;
    ifstream file(filename);
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        Persona p;
        ss >> p.usuario >> p.contrasena >> p.modalidad >> p.dni 
           >> p.nombre >> p.apellido1 >> p.apellido2;
        personas.push_back(p);
    }
    return personas;
}

void generarGrupos(const vector<Persona> &alumnos, const vector<Persona> &tutores) {
    ofstream grupos("grupos.txt");
    for (auto &tutor : tutores) {
        grupos << "Tutor: " << tutor.nombre << " " << tutor.apellido1 << " " << tutor.apellido2 
               << " " << tutor.modalidad << endl;
        grupos << "Alumnos: ";
        bool primero = true;
        for (auto &alumno : alumnos) {
            if (alumno.modalidad == tutor.modalidad) {
                if (!primero) grupos << ", ";
                grupos << alumno.nombre << " " << alumno.apellido1 << " " << alumno.apellido2;
                primero = false;
            }
        }
        grupos << "\n\n";
    }
    grupos.close();
}

int main() {
    vector<Persona> alumnos = cargarDatos("alumnos.txt");
    vector<Persona> tutores = cargarDatos("tutores.txt");
    generarGrupos(alumnos, tutores);
    cout << "Archivo grupos.txt generado.\n";
    return 0;
}
