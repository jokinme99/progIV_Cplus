/*
 * usuario.cpp
 *
 *  Created on: May 13, 2021
 *      Author: suhar.txabarri
 */
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "Usuario.h"
#include "sqlite/sqlite3.h"
#include "Reserva.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Habitacion.h"
#include "Habitaciones.h"
#include "Reservas.h"
#include "DatosSQL.h"
#include "Trabajadores.h"
#include "Trabajador.h"
#include "Usuarios.h"

using namespace std;

Usuarios* us;


Usuario::Usuario() {
	this->idUsuario = 0;
	this->nombreUsuario = new char[1];
	this->nombreUsuario[0] = '\0';
	this->correoUsuario = new char[1];
	this->correoUsuario[0] = '\0';
	this->contrasenyaUsuario = new char[1];
	this->contrasenyaUsuario[0] = '\0';
	this->edadUsuario = 0;
	this->reservasUsuario = new Reservas();

}

Usuario::Usuario(int id, char *nombre, char *correo, char *contrasenya,
		int edad) {

	this->idUsuario = id;
	this->nombreUsuario = new char[strlen(nombre) + 1];
	strcpy(this->nombreUsuario, nombre);
	this->correoUsuario = new char[strlen(correo) + 1];
	strcpy(this->correoUsuario, correo);
	this->contrasenyaUsuario = new char[strlen(contrasenya) + 1];
	strcpy(this->contrasenyaUsuario, contrasenya);
	this->edadUsuario = edad;
	this->reservasUsuario = new Reservas();

}
Usuario::Usuario(const Usuario &u) {

	this->idUsuario = u.idUsuario;
	this->nombreUsuario = new char[strlen(u.nombreUsuario) + 1];
	strcpy(this->nombreUsuario, u.nombreUsuario);
	this->correoUsuario = new char[strlen(u.correoUsuario) + 1];
	strcpy(this->correoUsuario, u.correoUsuario);
	this->contrasenyaUsuario = new char[strlen(u.contrasenyaUsuario) + 1];
	strcpy(this->contrasenyaUsuario, u.contrasenyaUsuario);
	this->edadUsuario = u.edadUsuario;
	this->reservasUsuario = u.reservasUsuario;

}

Usuario::~Usuario() {

	delete &this->idUsuario;
	delete[] this->nombreUsuario;
	delete[] this->correoUsuario;
	delete[] this->contrasenyaUsuario;
	delete &this->edadUsuario;

	delete[] this->reservasUsuario;

}

int Usuario::getIdUsuario() const {

	return this->idUsuario;

}

char* Usuario::getNombreUsuario() const {
	return this->nombreUsuario;
}
void Usuario::setNombreUsuario(char *nombre) {
	this->nombreUsuario = (char*) malloc(sizeof(strlen(nombre)) + 1);
	strcpy(this->nombreUsuario, nombre);
}
char* Usuario::getCorreoUsuario() const {
	return this->correoUsuario;
}
void Usuario::setCorreoUsuario(char *correo) {
	this->correoUsuario = (char*) malloc(sizeof(strlen(correo)) + 1);
	strcpy(this->correoUsuario, correo);
}
char* Usuario::getContrasenyaUsuario() const {
	return this->contrasenyaUsuario;
}
void Usuario::setContrasenyaUsuario(char *contrasenya) {
	this->contrasenyaUsuario = (char*) malloc(sizeof(strlen(contrasenya)) + 1);
	strcpy(this->contrasenyaUsuario, contrasenya);
}
int Usuario::getEdadUsuario() const {
	return this->edadUsuario;
}
void Usuario::setEdadUsuario(int edad) {
	this->edadUsuario = edad;
}
char* Usuario::getTipoUsuario() {
	return "usuario";
}
Reservas* Usuario::getReservaUsuario() const {
	return this->reservasUsuario;
}
void Usuario::setReservaUsuario(Reservas *reservasUsuario) {
	this->reservasUsuario = reservasUsuario;
}

void Usuario::verhoteles() {

}
void Usuario::listarHabitaciones() {

}
void Usuario::listarReservas() {

}




void Usuario::imprimirUsuario() {
	cout << "Usuario " << this->idUsuario << ": " << endl;
	cout << "Nombre: " << this->nombreUsuario << " Correo: "
			<< this->correoUsuario << endl;
	cout << "Edad: " << this->edadUsuario << " Tipo de usuario: "
			<< this->getTipoUsuario() << endl;
	cout << "Reservas: " << endl;
	cout << "----------" << endl;
	if (this->reservasUsuario->getNumReservas() == 0) {
		cout << "(este usuario no tiene reservas)" << endl;
	} else {
		this->reservasUsuario->imprimirReservas();
	}
}

char* Usuario::intAChar(int numero) {
	string s = to_string(numero);
	const char *c = s.c_str();
	return (char*) c;
}

void Usuario::anyadirReserva(Reservas *re, Habitaciones *h) { /////////////////ESTABLECER EL TAMAÑO DE LOS ARRAYS DE CARACTERES A LA QUE SE LES TIENE PREDISPUESTO

	int eleccionNHabitacion;
	int dia;
	int hora;

	//re->getOrdenReserva(re->getNumReservas())->getIdReserva();//AQUI TENEMOS EL ID DE LA NUEVA RESERVA
	cout << endl;
	cout << "Ingrese el dia de la reserva que desea anyadir: ";
	cin >> dia;
	while (dia < 1 || dia > 31) {
		cout << "por favor indique un dia adecuado" << endl;
		cin >> dia;
	}
	cout << endl;
	cout << "Ingrese la hora de llegada al hotel que desea anyadir: " << endl;
	cin >> hora;
	while (hora < 0 || hora > 24) {
		cout << "por favor indique una hora adecuada" << endl;
		cin >> hora;
	}

	cout << "Aqui tienes las habitaciones que tenemos disponibles" << endl;

	h->busquedaPersonalizada();

	cout << "Ingrese el id de la habitacion que desea reservar: " << endl;

	cin >> eleccionNHabitacion;

	//cout<<h->habitacionExiste(eleccionNHabitacion)<<endl;

	while (h->habitacionExiste(eleccionNHabitacion) == 0) {

		cout << "por favor habitacion adecuada" << endl;

		cin >> eleccionNHabitacion;
	}

	cout << endl;

	Reserva *r = new Reserva(re->getOrdenReserva(), dia, hora,
			h->getHabitacion(eleccionNHabitacion));
	this->getReservaUsuario()->anyadirReserva(r);

	re->comprobarDisponibilidad(r);

	re->anyadirReserva(r);

	//ESTE METODO AÑADE UNA RESERVA

	/* Create SQL statement */
	char sql[] = "INSERT INTO RESERVA VALUES (";

	char con[] = "'", con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")",
			con9[] = "";

	string s = to_string(r->getIdReserva());
	char const *pchar = s.c_str();  //use char const* as target type
	char con10[5];
	strcpy(con10, pchar);
	cout << pchar << endl;
	cout << con10 << endl;
	s = to_string(dia);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5];
	strcpy(con11, pchar2);
	s = to_string(hora);
	char const *pchar3 = s.c_str();  //use char const* as target type
	char con12[5];
	strcpy(con12, pchar3);
	s = to_string(this->getIdUsuario());
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5];
	strcpy(con13, pchar4);
	s = to_string(eleccionNHabitacion);
	char const *pchar5 = s.c_str();  //use char const* as target type
	char con14[5];
	strcpy(con14, pchar5);

	char *retval = new char[strlen(sql) + strlen(con) + strlen(con10)
			+ strlen(con) + strlen(con1) + strlen(con11) + strlen(con)
			+ strlen(con2) + strlen(con) + strlen(con12) + strlen(con)
			+ strlen(con3) + strlen(con) + strlen(con13) + strlen(con)
			+ strlen(con3) + strlen(con) + strlen(con14) + strlen(con)
			+ strlen(con8) + strlen(con9)];

	*retval = '\0';

	strcat(retval, sql);
	strcat(retval, con);
	strcat(retval, con10);
	strcat(retval, con);
	strcat(retval, con1);
	strcat(retval, con);
	strcat(retval, con11);
	strcat(retval, con);
	strcat(retval, con2);
	strcat(retval, con);
	strcat(retval, con12);
	strcat(retval, con);
	strcat(retval, con3);
	strcat(retval, con);
	strcat(retval, con13);  //CONVERTIR INT A CHAR
	strcat(retval, con);
	strcat(retval, con3);
	strcat(retval, con);
	strcat(retval, con14);
	strcat(retval, con);
	strcat(retval, con8);
	strcat(retval, con9);

	cout << retval << endl;

	llamadaSQL(retval);

}

void Usuario::modificarReserva(Habitaciones *h) {
	int numReserva, nuevoDia, nuevaHora, nuevaHabitacion;


	cout << "Estas son las reservas que estan a su nombre: " << endl;
	cout << endl;
	this->getReservaUsuario()->imprimirReservas();

	Reservas* usuarioR = this->getReservaUsuario();

	if(usuarioR->getNumReservas() <= 0){

	} else {
	cout << endl;
	cout << "Selecciona el numero de reserva que quierers modificar: ";
	cin >> numReserva;

	cout << endl;

	while (this->getReservaUsuario()->reservaExiste(numReserva) == 0) {
		cout
				<< "por favor elija una reserva adecuada o una reserva de su propiedad"
				<< endl;
		cin >> numReserva;
	}
	cout << endl;
	cout << "Estos son los datos de su reserva: " << endl;
	this->getReservaUsuario()->getReserva(numReserva)->imprimirReserva();

	cout << endl;

	cout << "introduce el nuevo dia para la reserva: " << endl;

	cin >> nuevoDia;
	while (nuevoDia < 1 || nuevoDia > 31) {
		cout << endl;
		cout << "por favor indique un dia adecuado" << endl;
		cin >> nuevoDia;
	}

	cout << endl;
	cout << "introduce la nueva hora para la entrada del hotel: " << endl;

	cin >> nuevaHora;
	while (nuevaHora < 0 || nuevaHora > 24) {
		cout << endl;
		cout << "por favor indique una hora adecuada" << endl;
		cin >> nuevaHora;
	}
	cout << endl;
	cout << "Ingrese el id de la nueva habitacion que desea reservar: " << endl;
	cout << endl;

	cout << "Aqui tienes las habitaciones que tenemos disponibles" << endl;
	cout << endl;

	h->imprimirHabitaciones();

	cin >> nuevaHabitacion;

	//cout<<h->habitacionExiste(eleccionNHabitacion)<<endl;

	while (h->habitacionExiste(nuevaHabitacion) == 0) {
		cout << endl;
		cout << "por favor habitacion que exista" << endl;
		cin >> nuevaHabitacion;
	}

	cout << endl;

	this->getReservaUsuario()->getReserva(numReserva)->setDiaReserva(nuevoDia);
	this->getReservaUsuario()->getReserva(numReserva)->setHoraReserva(
			nuevaHora);
	this->getReservaUsuario()->getReserva(numReserva)->setHabitacionReservada(
			h->getHabitacion(nuevaHabitacion));

	char sql[] = "UPDATE RESERVA SET dia_reserva ='";

	char con[] = "'", con1[] = ",", con2[] = "hora_reserva='", con3[] =
			"id_habitacion='", con8[] = " WHERE id_reserva='", con9[] = ";";

	string s = to_string(nuevoDia);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5];
	strcpy(con11, pchar2);
	s = to_string(nuevaHora);
	char const *pchar3 = s.c_str();  //use char const* as target type
	char con12[5];
	strcpy(con12, pchar3);
	s = to_string(numReserva);
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5];
	strcpy(con13, pchar4);
	s = to_string(nuevaHabitacion);
	char const *pchar5 = s.c_str();  //use char const* as target type
	char con14[5];
	strcpy(con14, pchar5);

	char *retval = new char[strlen(sql) + strlen(con11) + strlen(con)
			+ strlen(con1) + strlen(con2) + strlen(con12) + strlen(con)
			+ strlen(con1) + strlen(con3) + strlen(con14) + strlen(con)
			+ strlen(con8) + strlen(con13) + strlen(con) + strlen(con9)];

	*retval = '\0';

	strcat(retval, sql);
	strcat(retval, con11);
	strcat(retval, con);
	strcat(retval, con1);
	strcat(retval, con2);
	strcat(retval, con12);
	strcat(retval, con);
	strcat(retval, con1);
	strcat(retval, con3);
	strcat(retval, con14);  //CONVERTIR INT A CHAR
	strcat(retval, con);
	strcat(retval, con8);
	strcat(retval, con13);
	strcat(retval, con);
	strcat(retval, con9);
	cout << endl;

	cout << retval << endl;

	llamadaSQL(retval);
	}
}

int Usuario::eliminarReserva(Reservas *re) {

	int numReserva;
	char afirmacion[5];

	if (this->getReservaUsuario()->getNumReservas() == 0) {
		cout << "no tienes reservas" << endl;
		return 0;

	}

	cout << "Estas son las reservas que estan a su nombre: " << endl;
	cout << endl;
	this->getReservaUsuario()->imprimirReservas();
	cout << endl;
	cout << "Selecciona el numero de reserva que quierers Eliminar: ";
	cin >> numReserva;

	cout << endl;

	while (this->getReservaUsuario()->reservaExiste(numReserva) == 0) {
		cout
				<< "por favor elija una reserva adecuada o una reserva de su propiedad"
				<< endl;
		cin >> numReserva;
	}
	cout << endl;

	cout << "Esta seguro que desea eliminar la siguiente trserva?(diga si o no)"
			<< endl;
	cout << endl;
	this->getReservaUsuario()->getReserva(numReserva)->imprimirReserva();
	cout << endl;
	cout << "Respuesta(diga si o no):  ";
	cin >> afirmacion;
	while (strcmp(afirmacion, "si") != 0 && strcmp(afirmacion, "no") != 0) {
		cout << "por favor, elija una respuesta valida" << endl;
		cout << endl;
		cout << "Respuesta(diga si o no):  ";
		cin >> afirmacion;
	}
	if (strcmp(afirmacion, "no") == 0) {

		cout << "Entonces no cancelamos" << endl;
		return 0;
	}

	re->quitarReserva(numReserva);

	this->getReservaUsuario()->quitarReserva(numReserva);

	char sql[] = "DELETE FROM RESERVA WHERE id_reserva ='";

	char con[] = "'";

	string s = to_string(numReserva);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5];
	strcpy(con11, pchar2);

	char *retval = new char[strlen(sql) + strlen(con11) + strlen(con)];

	*retval = '\0';
	strcat(retval, sql);
	strcat(retval, con11);
	strcat(retval, con);

	cout << endl;

	//cout<<sql<<endl;

	llamadaSQL(retval);

	return 0;
}

void Usuario::editarHabitacion(Habitaciones *h) {
	cout << "no tienes permiso para esta accion" << endl;
}

void Usuario::editarTrabajador(Trabajadores *t) {
	cout << "no tienes permiso para esta accion" << endl;
}

void Usuario::anyadirHabitacion(Habitaciones *h) {
	cout << "no tienes permiso para esta accion" << endl;
}

int Usuario::eliminarHabitacion(Habitaciones *h) {
	cout << "no tienes permiso para esta accion" << endl;

	return 0;
}

void Usuario::anyadirTrabajador(Trabajadores *t) {
	cout << "no tienes permiso para esta accion" << endl;
}

int Usuario::eliminarTrabajador(Trabajadores *t) {
	cout << "no tienes permiso para esta accion" << endl;

	return 0;
}

