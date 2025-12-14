#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void crearAlerta(const string &alumno, const string &creador, const string &comentario) {
    ofstream file("alertas.txt", ios::app);
    file << "ALERTA alumno=" << alumno << " creador=" << creador << " \"" << comentario << "\"\n";
    file.close();
}

void borrarAlerta(const string &alumno) {
    ifstream file("alertas.txt");
    ofstream temp("temp.txt");
    string linea;
    bool borrada = false;
    while (getline(file, linea)) {
        if (linea.find("alumno=" + alumno) != string::npos && !borrada) {
            borrada = true;
            continue;
        }
        temp << linea << endl;
    }
    file.close();
    temp.close();
    remove("alertas.txt");
    rename("temp.txt", "alertas.txt");
    if (borrada) cout << "Alerta borrada.\n";
    else cout << "No se encontró alerta para ese alumno.\n";
}

void verAlertasAlumno(const string &alumno) {
    ifstream file("alertas.txt");
    string linea;
    bool hay = false;
    while (getline(file, linea)) {
        if (linea.find("alumno=" + alumno) != string::npos) {
            cout << linea << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay alertas.\n";
}

void verAlertasTutor(const string &tutor) {
    ifstream file("alertas.txt");
    string linea;
    bool hay = false;
    while (getline(file, linea)) {
        if (linea.find("creador=" + tutor) != string::npos) {
            cout << linea << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay alertas creadas.\n";
}

void verAlertasCoordinador() {
    ifstream file("alertas.txt");
    string linea;
    bool hay = false;
    while (getline(file, linea)) {
        cout << linea << endl;
        hay = true;
    }
    if (!hay) cout << "No hay alertas.\n";
}

int main() {
    crearAlerta("i42merad", "j23perez", "No entregó práctica de laboratorio");
    crearAlerta("a56gomez", "m45ruiz", "Faltó a clase sin justificar");

    cout << "\nAlertas del alumno i42merad:\n";
    verAlertasAlumno("i42merad");

    cout << "\nAlertas creadas por el tutor j23perez:\n";
    verAlertasTutor("j23perez");

    cout << "\nTodas las alertas vistas por el coordinador:\n";
    verAlertasCoordinador();

    borrarAlerta("i42merad");

    cout << "\nAlertas después de borrar:\n";
    verAlertasCoordinador();

    return 0;
}
