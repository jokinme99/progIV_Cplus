/*
 * Administrador.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#include "Administrador.h"
#include "Usuario.h"
#include "Trabajadores.h"
#include <iostream>
#include "DatosSQL.h"
using namespace std;

Administrador::Administrador(int idUsuario, char *nombreUsuario,
		char *correoUsuario, char *contrasenyaUsuario, int edadUsuario) :
		Usuario(idUsuario, nombreUsuario, correoUsuario, contrasenyaUsuario,
				edadUsuario) {

}

Administrador::Administrador(Usuario *u) :
		Usuario(*u) { //METER DATOS RELEVANTES

}
Administrador::Administrador(const Administrador &a) :
		Usuario(a) {

}
Administrador::~Administrador() {

}

void Administrador::crearHabitacion() {

}
void Administrador::eliminarHabitacion() {

}
void Administrador::listarReservas() {
	//usar el objeto reservasy sobreescribir el metodo de la clase pafre
}
void Administrador::crearReserva() {
	//rellenarlo con datos de usuario
}
void Administrador::eliminarReserva() {
	//(?)
}
void Administrador::listarTrabajadores() {

}
void Administrador::CrearTrabajador() {

}
void Administrador::eliminarTrabajador() {

}
void Administrador::listarUsuarios() {

}
char* Administrador::getTipoUsuario() {
	Usuario::getTipoUsuario();
	return "admin";
}
void Administrador::editarHabitacion(Habitaciones *h) {

	Usuario::editarHabitacion(h);

	char tipoHab[100];
	int idHab;
	int Prec;

	cout << endl;
	cout << "Aqui tienes la lista de las habitaciones" << endl;

	system("pause");

	h->imprimirHabitaciones();

	cout << endl;

	cout << "introduce el id de la habitacion que quieres modificar" << endl;

	cin >> idHab;

	while (h->habitacionExiste(idHab) == 0) {

		cout << "por favor habitacion adecuada" << endl;

		cin >> idHab;
	}

	cout << "introduce el nuevo tipo de Habitacion:" << endl;

	cin >> tipoHab;

	cout << "Introduce el nuevo precio de la Habitacion:" << endl;

	cin >> Prec;

	h->getHabitacion(idHab)->setPrecioHabitacion(Prec);
	h->getHabitacion(idHab)->setTipoHabitacion(tipoHab);

	char sql[] = "UPDATE HABITACION SET precio_habitacion ='";

	char con[] = "'", con1[] = ",", con2[] = "tipo_habitacion='", con8[] =
			" WHERE id_habitacion='", con9[] = ";";

	string s = to_string(Prec);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5];
	strcpy(con11, pchar2);
	s = to_string(idHab);
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5];
	strcpy(con13, pchar4);

	cout << endl;

	char *retVal = new char[strlen(sql) + strlen(con11) + strlen(con)
			+ strlen(con1) + strlen(con2) + strlen(tipoHab) + strlen(con)
			+ strlen(con8) + strlen(con13) + strlen(con) + 1];

	*retVal = '\0';
	strcat(retVal, sql);
	strcat(retVal, con11);
	strcat(retVal, con);
	strcat(retVal, con1);
	strcat(retVal, con2);
	strcat(retVal, tipoHab);
	strcat(retVal, con);

	strcat(retVal, con8);
	strcat(retVal, con13);
	strcat(retVal, con);

	//cout<<sql<<endl;
	cout << retVal << endl;

	llamadaSQL(retVal);

}

void Administrador::editarTrabajador(Trabajadores *trabajadores) {

	Usuario::editarTrabajador(trabajadores);

	char nombre[100];
	int idTrab;
	int sueldo;
	char dni[100];

	cout << endl;
	cout << "Aqui tienes la lista de los trabajadores" << endl;

	system("pause");

	trabajadores->imprimirTrabajadores();

	cout << endl;

	cout << "introduce el id del trabjador que quieres modificar" << endl;

	cin >> idTrab;

//
//			while(h->habitacionExiste(idHab)==0){
//
//				cout<<"por favor habitacion adecuada"<<endl;
//
//
//				cin >> idHab;
//			}

	cout << "introduce el nuevo nombre del trabajador:" << endl;

	cin >> nombre;

	cout << "introduce el nuevo dni del trabajador:" << endl;

	cin >> dni;

	cout << "Introduce el nuevo salario del trabajdor" << endl;

	cin >> sueldo;

	if (sueldo < 900) {

		cout << "El suelo no puede ser menor a 900 euros" << endl;

		cin >> sueldo;
	}

	trabajadores->getTrabajador(idTrab)->setNombreTrabajador(nombre);
	trabajadores->getTrabajador(idTrab)->setSueldoTrabajador(sueldo);
	trabajadores->getTrabajador(idTrab)->setDNITrabajador(dni);

	char sql[] = "UPDATE TRABAJADOR SET sueldo_trabajador ='";

	char con[] = "'", con1[] = ",", con2[] = "nombre_trabajador='", con3[] =
			"DNI_trabajador='", con8[] = " WHERE id_trabajador='", con9[] = ";";

	string s = to_string(sueldo);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5];
	strcpy(con11, pchar2);
	s = to_string(idTrab);
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5];
	strcpy(con13, pchar4);

	cout << endl;

	char *retVal = new char[strlen(sql) + strlen(con11) + strlen(con)
			+ strlen(con1) + strlen(con2) + strlen(nombre) + strlen(con)
			+ strlen(con1) + strlen(con3) + strlen(dni) + strlen(con)
			+ strlen(con8) + strlen(con13) + strlen(con) + 1];

	*retVal = '\0';
	strcat(retVal, sql);
	strcat(retVal, con11);
	strcat(retVal, con);
	strcat(retVal, con1);
	strcat(retVal, con2);
	strcat(retVal, nombre);
	strcat(retVal, con);
	strcat(retVal, con1);
	strcat(retVal, con3);
	strcat(retVal, dni);
	strcat(retVal, con);

	strcat(retVal, con8);
	strcat(retVal, con13);
	strcat(retVal, con);

	cout << sql << endl;
	cout << retVal << endl;

	llamadaSQL(retVal);
}
