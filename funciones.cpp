#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// ---------------- CARGA DE DATOS ----------------
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

bool login(const vector<Persona> &personas, const string &usuario, const string &contrasena, Persona &out) {
    for (auto &p : personas) {
        if (p.usuario == usuario && p.contrasena == contrasena) {
            out = p;
            return true;
        }
    }
    return false;
}

// ---------------- GRUPOS ----------------
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

// ---------------- MENSAJERIA ----------------
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

void verMensajesTutor(const string &tutor) {
    ifstream file("mensajeria.txt");
    string linea;
    bool hay = false;
    while (getline(file, linea)) {
        if (linea.find(tutor) != string::npos) {
            cout << linea << endl;
            hay = true;
        }
    }
    if (!hay) cout << "No hay mensajes de alumnos.\n";
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

// ---------------- ALERTAS ----------------
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
            borrada = true; // borra la primera alerta encontrada
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

// ---------------- MENUS ----------------
void menuAlumno(const Persona &alumno, const vector<Persona> &tutores) {
    int opcion;
    string texto;
    do {
        cout << "\n--- MENU ALUMNO ---\n";
        cout << "0 Enviar mensaje a tutor\n";
        cout << "1 Ver mensajes de tutor\n";
        cout << "2 Ver alertas\n";
        cout << "3 Ver tutor asignado\n";
        cout << "4 Salir\n";
        cin >> opcion;
        switch(opcion) {
            case 0: {
                for (auto &t : tutores) if (t.modalidad == alumno.modalidad) {
                    cout << "Escriba mensaje: ";
                    cin.ignore(); getline(cin, texto);
                    enviarMensaje(alumno.usuario, t.usuario, texto, true);
                }
                break;
            }
            case 1: {
                for (auto &t : tutores) if (t.modalidad == alumno.modalidad)
                    verMensajesAlumno(alumno.usuario, t.usuario);
                break;
            }
            case 2: verAlertasAlumno(alumno.usuario); break;
            case 3: for (auto &t : tutores) if (t.modalidad == alumno.modalidad)
                        cout << "Tutor asignado: " << t.nombre << " " << t.apellido1 << " " << t.apellido2 << endl;
                    break;
            case 4: cout << "Volviendo al menu de inicio...\n"; break;
            default: cout << "Opcion invalida\n"; break;
        }
    } while(opcion != 4);
}

void menuTutor(const Persona &tutor, const vector<Persona> &alumnos) {
    int opcion;
    string texto, alumnoUser;
    do {
        cout << "\n--- MENU TUTOR ---\n";
        cout << "0 Enviar mensaje a alumno\n";
        cout << "1 Ver mensajes de alumnos\n";
        cout << "2 Crear alerta a alumno\n";
        cout << "3 Borrar alerta de alumno\n";
        cout << "4 Ver listado de alumnos\n";
        cout << "5 Salir\n";
        cin >> opcion;
        switch(opcion) {
            case 0: {
                cout << "Usuario del alumno: "; cin >> alumnoUser;
                cout << "Escriba mensaje: "; cin.ignore(); getline(cin, texto);
                enviarMensaje(tutor.usuario, alumnoUser, texto, false);
                break;
            }
            case 1: verMensajesTutor(tutor.usuario); break;
            case 2: {
                cout << "Usuario del alumno: "; cin >> alumnoUser;
                cout << "Comentario: "; cin.ignore(); getline(cin, texto);
                crearAlerta(alumnoUser, tutor.usuario, texto);
                break;
            }
            case 3: {
                cout << "Usuario del alumno: "; cin >> alumnoUser;
                borrarAlerta(alumnoUser);
                break;
            }
            case 4: for (auto &a : alumnos) if (a.modalidad == tutor.modalidad)
                        cout << a.nombre << " " << a.apellido1 << " " << a.apellido2 << endl;
                    break;
            case 5: cout << "Volviendo al menu de inicio...\n"; break;
            default: cout << "Opcion invalida\n"; break;
        }
    } while(opcion != 5);
}

void menuCoordinador(const Persona &coord, const vector<Persona> &alumnos, const vector<Persona> &tutores) {
    int opcion;
    string texto, alumnoUser;
    do {
        cout << "\n--- MENU COORDINADOR ---\n";
        cout << "0 Ver alertas\n";
        cout << "1 Ver conversaciones\n";
        cout << "2 Crear alerta a alumno\n";
        cout << "3 Borrar alerta de alumno\n";
        cout << "4 Ver listado de tutores y grupos\n";
        cout << "5 Salir\n";
        cin >> opcion;
        switch(opcion) {
            case 0: 
                verAlertasCoordinador(); 
                break;
            case 1: 
                verMensajesCoordinador(); 
                break;
            case 2: {
                cout << "Usuario del alumno: "; 
                cin >> alumnoUser;
                cout << "Comentario: "; 
                cin.ignore(); 
                getline(cin, texto);
                crearAlerta(alumnoUser, coord.usuario, texto);
                break;
            }
            case 3: {
                cout << "Usuario del alumno: "; 
                cin >> alumnoUser;
                borrarAlerta(alumnoUser);
                break;
            }
            case 4: 
                generarGrupos(alumnos, tutores);
                cout << "Archivo grupos.txt actualizado.\n";
                break;
            case 5: 
                cout << "Volviendo al menu de inicio...\n"; 
                break;
            default: 
                cout << "Opcion invalida\n"; 
                break;
        }
    } while(opcion != 5);
}