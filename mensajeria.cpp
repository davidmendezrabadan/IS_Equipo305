#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void enviarMensaje(const string &remitente, const string &destinatario, const string &texto, bool esAlumno) {
    ofstream file("mensajeria.txt", ios::app);
    if (esAlumno)
        file << "ALUMNO " << remitente << " -> TUTOR " << destinatario << " : " << texto << endl;
    else
        file << "TUTOR " << remitente << " -> ALUMNO " << destinatario << " : " << texto << endl;
    file.close();
}

void verMensajesAlumno(const string &alumno, const string &tutor) {
    ifstream file("mensajeria.txt");
    string linea;
    bool hay = false;
    while (getline(file, linea)) {
        if (linea.find(alumno) != string::npos && linea.find(tutor) != string::npos) {
            cout << linea << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay mensajes para mostrar.\n";
}

void verMensajesCoordinador() {
    ifstream file("mensajeria.txt");
    string linea;
    bool hay = false;
    while (getline(file, linea)) {
        cout << linea << endl;
        hay = true;
    }
    if (!hay) cout << "No hay conversaciones.\n";
}

int main() {
    enviarMensaje("i42merad", "j23perez", "Hola tutor, tengo dudas.", true);
    enviarMensaje("j23perez", "i42merad", "Claro, dime tus dudas.", false);

    cout << "\nMensajes del alumno:\n";
    verMensajesAlumno("i42merad", "j23perez");

    cout << "\nMensajes vistos por el coordinador:\n";
    verMensajesCoordinador();

    return 0;
}
