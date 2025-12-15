#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>

struct Persona {
    std::string usuario;
    std::string contrasena;
    std::string modalidad;
    std::string dni;
    std::string nombre;
    std::string apellido1;
    std::string apellido2;
};

std::vector<Persona> cargarDatos(const std::string &filename);
bool login(const std::vector<Persona> &personas, const std::string &usuario, const std::string &contrasena, Persona &out);
void generarGrupos(const std::vector<Persona> &alumnos, const std::vector<Persona> &tutores);

// Mensajería
void enviarMensaje(const std::string &remitente, const std::string &destinatario, const std::string &texto, bool esAlumno);
void verMensajesAlumno(const std::string &alumno, const std::string &tutor);
void verMensajesTutor(const std::string &tutor);
void verMensajesCoordinador();

// Alertas
void crearAlerta(const std::string &alumno, const std::string &creador, const std::string &comentario);
void borrarAlerta(const std::string &alumno);
void verAlertasAlumno(const std::string &alumno);
void verAlertasTutor(const std::string &tutor);
void verAlertasCoordinador();

// Menús
void menuAlumno(const Persona &alumno, const std::vector<Persona> &tutores);
void menuTutor(const Persona &tutor, const std::vector<Persona> &alumnos);
void menuCoordinador(const Persona &coord, const std::vector<Persona> &alumnos, const std::vector<Persona> &tutores);

#endif
