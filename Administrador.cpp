/*
 * Administrador.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#include "Administrador.h"
#include "Usuario.h"
#include "Trabajadores.h"
#include "Trabajador.h"
#include <iostream>
#include "DatosSQL.h"
#include <string.h>

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



void Administrador::anyadirHabitacion(Habitaciones *habitaciones) { /////////////////ESTABLECER EL TAMAÑO DE LOS ARRAYS DE CARACTERES A LA QUE SE LES TIENE PREDISPUESTO

	int idHabitacion;
	int numHabitacion;
	int plantaHabitacion;
	char tipoHabitacion[20];
	int precio;

	//re->getOrdenReserva(re->getNumReservas())->getIdReserva();//AQUI TENEMOS EL ID DE LA NUEVA RESERVA
	cout << endl;
	cout << "Ingrese el identificador de la habitación: ";
	cin >> idHabitacion;

	cout << endl;
	cout << "Ingrese el número de la habitación del 1 al 399: " << endl;

	while (numHabitacion < 1 || numHabitacion > 399) {
		cout << "Introduzca un número de habitación adecuado" << endl;
		cin >> numHabitacion;
	}

	if (numHabitacion >= 1 && numHabitacion < 100) {

		plantaHabitacion = 1;
	} else if (numHabitacion >= 100 && numHabitacion < 200) {

		plantaHabitacion = 2;
	} else if (numHabitacion >= 200 && numHabitacion < 300) {
		plantaHabitacion = 3;
	} else {
		plantaHabitacion = 4;
	}

	cout << endl;
	cout
			<< "Ingrese el tipo de habitacion; Doble, Individual, Familiar, Suite:";

	cin >> tipoHabitacion;


	char doble[] = "Doble";
	char individual[] = "Individual";
	char familiar[] = "Familiar";
	char suite[] = "Suite";

	while (strcmp(tipoHabitacion, doble) != 0 &&  strcmp(tipoHabitacion, individual) != 0
					&&  strcmp(tipoHabitacion, familiar) != 0 &&  strcmp(tipoHabitacion, suite) != 0) {

		cout << endl;
		cout
				<< "Ingrese el tipo de habitacion correcto; Doble, Individual, Familiar, Suite:";

		cin >> tipoHabitacion;


	}

	cout << endl;
	cout << "Ingrese el precio de la habitación";

	cin >> precio;

	cout << endl;

	Habitacion *h = new Habitacion(idHabitacion, numHabitacion,
			plantaHabitacion, tipoHabitacion, precio);

	habitaciones->anyadirhabitacion(h);

	//ESTE METODO AÑADE UNA RESERVA

	/* Create SQL statement */
	char sql[] = "INSERT INTO HABITACION VALUES (";

	char con[] = "'", con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")",
			con9[] = "";

	string s = to_string(idHabitacion);
	char const *pchar = s.c_str();  //use char const* as target type
	char con10[5];
	strcpy(con10, pchar);
	cout << pchar << endl;
	cout << con10 << endl;
	s = to_string(numHabitacion);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5];
	strcpy(con11, pchar2);
	s = to_string(plantaHabitacion);
	char const *pchar3 = s.c_str();  //use char const* as target type
	char con12[5];
	strcpy(con12, pchar3);
	s = to_string(precio);
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5];
	strcpy(con13, pchar4);

	char *retval = new char[strlen(sql) + strlen(con) + strlen(con10)
			+ strlen(con) + strlen(con1) + strlen(con11) + strlen(con)
			+ strlen(con2) + strlen(con) + strlen(con12) + strlen(con)
			+ strlen(con3) + strlen(con) + strlen(tipoHabitacion) + strlen(con)
			+ strlen(con3) + strlen(con) + strlen(con13) + strlen(con)
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
	strcat(retval, tipoHabitacion);  //CONVERTIR INT A CHAR
	strcat(retval, con);
	strcat(retval, con3);
	strcat(retval, con);
	strcat(retval, con13);
	strcat(retval, con);
	strcat(retval, con8);
	strcat(retval, con9);

	cout << retval << endl;

	llamadaSQL(retval);

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

int Administrador::eliminarHabitacion(Habitaciones *h) {

	int numHabitacion;
	char afirmacion[5];

	cout << "Estas son las habitaciones actuales " << endl;
	cout << endl;
	h->imprimirHabitaciones();
	cout << endl;
	cout << "Selecciona el numero de habitacion que quierers Eliminar: ";

	cin >> numHabitacion;

	cout << endl;

	while (h->habitacionExiste(numHabitacion) == 0) {
		cout << "por favor elija una habitacion adecuada" << endl;
		cin >> numHabitacion;
	}
	cout << endl;

	cout << "Esta seguro que desea eliminar la siguiente trserva?(diga si o no)"
			<< endl;
	cout << endl;
	h->getHabitacion(numHabitacion);
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

	h->quitarHabitacion(numHabitacion);

	char sql[] = "DELETE FROM HABITACION WHERE id_habitacion ='";

	char con[] = "'";

	string s = to_string(numHabitacion);
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

void Administrador::anyadirTrabajador(Trabajadores *trabajadores) { /////////////////ESTABLECER EL TAMAÑO DE LOS ARRAYS DE CARACTERES A LA QUE SE LES TIENE PREDISPUESTO

	int idTrabajador;
	char nombreTrabajador[100];
	char dniTrabajador[9];
	int telefonoTrabajador;
	float sueldoTrabajador;


	char nombre[20];



	cout
	<< "Ingrese el identificador del trabajdor del trabajador que desea anyadir: ";
	cin >> idTrabajador;
	cout << endl;

	while (trabajadores->trabajadorExiste(idTrabajador) != 0) {
		cout << "Ya hay un trabajador con ese identificaro, introduce otro"
				<< endl;
		cin >> idTrabajador;
	}
	cout << "Ingrese el nombre del trabajador que desea anyadir: ";
	cin >> nombreTrabajador;
	strcpy(nombre,nombreTrabajador);
	cout << endl;
	cout << "Ingrese el DNI del trabajador que desea anyadir: ";
	cin >> dniTrabajador;

	while (strlen(dniTrabajador) != 9) {

		cout << "El dni tiene que tener 9 caracteres" << endl;
		cin >> dniTrabajador;
	}
	cout << endl;
	cout << "Ingrese el telefono del trabajador que desea anyadir: ";
	cin >> telefonoTrabajador;
	cout << endl;

	cout << telefonoTrabajador << endl;
	cout << "Ingrese el sueldo del trabajador que desea anyadir: ";
	cin >> sueldoTrabajador;
	cout << endl;

	while (sueldoTrabajador < 900) {

		cout << "El sueldo no puede ser menor a 900" << endl;
		cin >> sueldoTrabajador;
	}

	Trabajador *tr = new Trabajador(idTrabajador, nombreTrabajador,
			dniTrabajador, telefonoTrabajador, sueldoTrabajador);

	trabajadores->anyadirTrabajador(tr);

	int id_hotel = rand() % 10 + 1;

	//ESTE METODO AÑADE UNA RESERVA

	/* Create SQL statement */
	char sql[] = "INSERT INTO TRABAJADOR VALUES (";

	char con[] = "'", con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")",
			con9[] = "";

	string s = to_string(idTrabajador);
	char const *pchar = s.c_str();  //use char const* as target type
	char con10[5];
	strcpy(con10, pchar);
	cout << pchar << endl;
	cout << con10 << endl;
	s = to_string(telefonoTrabajador);
	char const *pchar2 = s.c_str();  //use char const* as target type
	cout << pchar << endl;
	char con11[200];
	strcpy(con11, pchar2);
	s = to_string(sueldoTrabajador);
	char const *pchar3 = s.c_str();  //use char const* as target type
	char con12[5];
	strcpy(con12, pchar3);
	s = to_string(id_hotel);
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5];
	strcpy(con13, pchar4);

	cout << nombre << endl;
	cout << dniTrabajador << endl;
	cout << con11 << endl;
	cout << con12 << endl;
	cout << con13 << endl;
	char *retval = new char[strlen(sql) + strlen(con) + strlen(con10)
			+ strlen(con) + strlen(con1) + strlen(nombre)
			+ strlen(con) + strlen(con2) + strlen(con) + strlen(dniTrabajador)
			+ strlen(con) + strlen(con3) + strlen(con) + strlen(con11)
			+ strlen(con) + strlen(con3) + strlen(con) + strlen(con12)
			+ strlen(con) + strlen(con3) + strlen(con) + strlen(con13)
			+ strlen(con) + strlen(con8) + strlen(con9)];

	*retval = '\0';

	strcat(retval, sql);
	strcat(retval, con);
	strcat(retval, con10);
	strcat(retval, con);
	strcat(retval, con1);
	strcat(retval, con);
	strcat(retval, nombre);
	strcat(retval, con);
	strcat(retval, con2);
	strcat(retval, con);
	strcat(retval, dniTrabajador);
	strcat(retval, con);
	strcat(retval, con3);
	strcat(retval, con);
	strcat(retval, con11);  //CONVERTIR INT A CHAR
	strcat(retval, con);
	strcat(retval, con3);
	strcat(retval, con);
	strcat(retval, con12);
	strcat(retval, con);
	strcat(retval, con3);
	strcat(retval, con);
	strcat(retval, con13);
	strcat(retval, con);
	strcat(retval, con8);
	strcat(retval, con9);

	cout << retval << endl;

	llamadaSQL(retval);

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

int Administrador::eliminarTrabajador(Trabajadores *t) {

	int numTrabajador;
	char afirmacion[5];

	cout << "Estas son las habitaciones actuales " << endl;
	cout << endl;
	t->imprimirTrabajadores();
	cout << endl;
	cout << "Selecciona el numero de trabajador que quierers Eliminar: ";

	cin >> numTrabajador;

	cout << endl;

	while (t->trabajadorExiste(numTrabajador) == 0) {
		cout << "por favor elija un trabajador adecuado" << endl;
		cin >> numTrabajador;
	}
	cout << endl;

	cout << "Esta seguro que desea eliminar la siguiente trserva?(diga si o no)"
			<< endl;
	cout << endl;

	cout << numTrabajador << endl;

	t->getTrabajador(numTrabajador);
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

	t->quitarTrabajador(numTrabajador);

	char sql[] = "DELETE FROM Trabajador WHERE id_trabajador ='";

	char con[] = "'";

	string s = to_string(numTrabajador);
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

