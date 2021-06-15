/*
 * DatosSQL.cpp
 *
 *  Created on: 15 jun. 2021
 *      Author: Suhar
 */
#include "Reserva.h"
#include <iostream>
#include "sqlite/sqlite3.h"
//#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include"metodoReservas.h"
#include "Habitacion.h"
#include "Usuarios.h"
#include "Reservas.h"
#include "Habitaciones.h"
#include "Trabajadores.h"
#include "Administrador.h"
#include "sqlite/sqlite3.h"
#include <fstream>


using namespace std;

Usuarios *us;
Habitaciones *ha;
Trabajadores *tr;
Reservas *res;



sqlite3 *db; //objeto base de datos
char *zErrMsg = 0;
int rc;
char *sql; //sentencia sql
const char *data = "LLamada a Base de datos";

void cargarVariables(Usuarios *usu, Habitaciones *hab, Trabajadores *tra,Reservas *rese){

	us=usu;
	ha=hab;
	tr=tra;
	res=rese;

}

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	fprintf(stderr, "%s: \n", (const char*) data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas) {
	(void) data;

	if (strcmp(contadorDeFila[5], "usuario") == 0) {

		Usuario *us1 = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1],
				contadorDeFila[3], contadorDeFila[2], atoi(contadorDeFila[4]));
		us->anyadirUsuario(us1);
	} else {

		Usuario *us1 = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1],
				contadorDeFila[3], contadorDeFila[2], atoi(contadorDeFila[4]));

		Administrador *ad = new Administrador(us1);

		us->anyadirUsuario(ad);

	}

}

int callbackReservas(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas) {
	(void) data;

	Reserva *r = new Reserva(atoi(contadorDeFila[0]), atoi(contadorDeFila[1]),
			atoi(contadorDeFila[2]), ha->getHabitacion(atoi(contadorDeFila[4])));

	us->getReservas(atoi(contadorDeFila[3]))->anyadirReserva(r);
	res->anyadirReserva(r);

	return 0;

}

int callbackHabitaciones(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas) {
	(void) data;
	Habitacion *ha1 = new Habitacion(atoi(contadorDeFila[0]),
			atoi(contadorDeFila[1]), atoi(contadorDeFila[2]), contadorDeFila[3],
			atoi(contadorDeFila[2]));
	ha->anyadirhabitacion(ha1);
	return 0;
}
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas) {
	(void)data;
	Trabajador *tr1 = new Trabajador(atoi(contadorDeFila[0]), contadorDeFila[1], contadorDeFila[2], atoi(contadorDeFila[3]),atoi(contadorDeFila[4]));
	tr->anyadirTrabajador(tr1);
return 0;
}
void cargarDatosUsuarios() {

	rc = sqlite3_open("hotelandia_final.s3db", &db);

	char sql[] = "SELECT * from USUARIO";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackUsuarios, (void*) data, &zErrMsg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

}
void cargarDatosHabitaciones() {

	rc = sqlite3_open("hotelandia_final.s3db", &db);

	char sql[] = "SELECT * from HABITACION";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackHabitaciones, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

}
void cargarDatosTrabajadores() {

	rc = sqlite3_open("hotelandia_final.s3db", &db);

	char sql[] = "SELECT id_trabajador, nombre_trabajador, DNI_trabajador, telefono_trabajador, sueldo_trabajador FROM TRABAJADOR";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackTrabajadores, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

}

void cargarDatosReservas() {

	rc = sqlite3_open("hotelandia_final.s3db", &db);

	char sql[] = "SELECT * from RESERVA";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackReservas, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

}

void importarDatosUsuarios() { //IMPORTA LOS DATOS DE USUARIOS DE LOS FICHEROS A LA BASE DE DATOS

	FILE *f = fopen("../progIV_Cplus/Usuarios.txt", "r");

	int counter = 0;
	char linea;
	char cadena[20], id[20], nom[20], cont[20], correo[30], edad[5], tipo[10];

	for (linea = getc(f); linea != EOF; linea = getc(f))
		if (linea == '\n')
			counter = counter + 1;

	fclose(f);
	//cout<<counter<<endl;

	ifstream ifs;
	ifs.open("../progIV_Cplus/Usuarios.txt", ios::in);

	char sql[] = "DELETE FROM USUARIO";

	rc = sqlite3_open("hotelandia_final.s3db", &db);

	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

	for (int i = 0; i < counter; ++i) {

		char sql1[] = "INSERT INTO USUARIO VALUES ('";

		ifs.getline(cadena, 256, ':');
		ifs.getline(id, 256, ';');
		ifs.getline(cadena, 256, ':');
		ifs.getline(nom, 256, ';');
		ifs.getline(cadena, 256, ':');
		ifs.getline(cont, 256, ';');
		ifs.getline(cadena, 256, ':');
		ifs.getline(correo, 256, ';');
		ifs.getline(cadena, 256, ':');
		ifs.getline(edad, 256, ';');
		ifs.getline(cadena, 256, ':');
		ifs.getline(tipo, 256, ';');

//		cout<<sql<<endl;

		char *retVal = new char[strlen(sql1) + strlen(id) + strlen(nom)
				+ strlen(cont) + strlen(correo) + strlen(edad) + strlen(tipo)
				+ 18];

		*retVal = '\0';

		strcat(retVal, sql1);
		strcat(retVal, id);
		strcat(retVal, "','");
		strcat(retVal, nom);
		strcat(retVal, "','");
		strcat(retVal, cont);
		strcat(retVal, "','");
		strcat(retVal, correo);
		strcat(retVal, "','");
		strcat(retVal, edad);
		strcat(retVal, "','");
		strcat(retVal, tipo);
		strcat(retVal, "')");

		//cout<<retVal<<endl;

		rc = sqlite3_open("hotelandia_final.s3db", &db);
		/* Execute SQL statement */
		rc = sqlite3_exec(db, retVal, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			//fprintf(stdout, "Operation done successfully\n");
		}
		sqlite3_close(db);

	}

}
void verHoteles(){

	char sql[] = "SELECT * from HOTEL";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	system("pause");
}
int crearReserva(){
	char nombreUsuario[20];
	char eleccionHotel[100];
	int eleccionNHabitacion;
	int dia;
	int hora;
	cout << "Introduzca su nombre de usuario para realizar una reserva :"
			<< endl;
	cin >> nombreUsuario;

	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
	if (rc != SQLITE_OK) {
		cout << "Error opening database" << endl;
		return rc;
	}

	char sql[] = "SELECT * from HOTEL";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	cout
			<< "Seleccione el hotel en el que desea realizar una reserva (Su numero): ";
	cin >> eleccionHotel;
	char sql2[] =
			"SELECT H.numero_habitacion, H.planta_habitacion, H.tipo_habitacion, H.precio_habitacion from HABITACION H, HOTEL M, HOTEL_TIENE_HABITACIONES L WHERE M.id_hotel = ";
	strcat(sql2, eleccionHotel);
	char fr100[] =
			" AND M.id_hotel = L.id_hotel AND L.id_habitacion = H.id_habitacion";
	strcat(sql2, fr100);
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	cout << "Seleccione el numero de habitacion que desea reservar: ";
	cin >> eleccionNHabitacion;
	cout << endl << "Seleccione el dia en el que desea realizar la reserva";
	cin >> dia;
	cout << endl << "Seleccione la hora de entrada ";
	cin >> hora;
	int hotel = atoi(eleccionHotel);
	rc = crearReserva(db, nombreUsuario, hotel, eleccionNHabitacion, dia, hora);
	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) {
		printf("Error closing database\n");
		printf("%s\n", sqlite3_errmsg(db));
		return rc;
	}
	system("pause");
}
int modificarReserva(){
	char usuarioModificar[20];
	cout << "Introduzca el usuario en el que va a realizar la modificacion: ";
	cin >> usuarioModificar;
	cout << endl;
	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
	if (rc != SQLITE_OK) {
		cout << "Error opening database" << endl;
		return rc;
	}
	rc = modificarReserva(db, usuarioModificar);//ANYADIR MODIFICAR LA HABITACION
	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) {
		printf("Error closing database\n");
		printf("%s\n", sqlite3_errmsg(db));
		return rc;
	}
	system("pause");


}

int eliminarReserva(){
	char usuarioEliminar[20];
	cout << "Introduzca el usuario del que quiere eliminar una reserva: ";
	cin >> usuarioEliminar;
	cout << endl;
	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
	if (rc != SQLITE_OK) {
		cout << "Error opening database" << endl;
		return rc;
	}
	rc = eliminarReserva(db, usuarioEliminar);
	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) {
		printf("Error closing database\n");
		printf("%s\n", sqlite3_errmsg(db));
		return rc;
	}
	system("pause");
}
