/*
 * Main.cpp
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "sqlite/sqlite3.h"
#include <fstream>
#include <windows.h>

#include "Habitacion.h"
#include "Hotel.h"
#include "Reserva.h"
#include "Reservas.h"
#include "Trabajador.h"
#include "Usuario.h"
#include "Usuarios.h"
#include "Administrador.h"
#include "Habitaciones.h"
#include "MetodoReservas.h"
#include "Trabajadores.h"

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName);
int callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
int callbackReservas(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
int callbackHabitaciones(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
void inicio(); //inicio sesion usuario
void importarDatosUsuarios();
void cargarDatosUsuarios();
void cargarDatosHabitaciones();
void cargarDatosReservas();
void cargarDatosTrabajadores();
void menuUsuario();
void caso1Usuario();
void caso2Usuario();
int caso3Usuario();
int caso4Usuario();
int caso5Usuario();
int caso6Usuario();

void caso1Admin();
void caso2Admin();
void caso3Admin();
void caso4Admin();
void caso5Admin();
void caso6Admin();
void caso7Admin();
void caso8Admin();
void caso9Admin();
void caso10Admin();
void caso11Admin();
void caso12Admin();
void caso13Admin();
void caso14Admin();
void caso15Admin();
void caso16Admin();

void menuAdministrador();

Usuarios u;
Habitaciones h;
Trabajadores t;
Reservas re;
Usuario usuarioActual;
string nombreUser;
string contraUser; //Para iniciar/registrar usuario
sqlite3 *db; //objeto base de datos
char *zErrMsg = 0;
int rc;
char *sql; //sentencia sql
const char *data = "LLamada a Base de datos";

//Metodo para utilizar la base de datos
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
	cout<<numeroColumnas<<endl;


	if (strcmp(contadorDeFila[5], "usuario") == 0) {
		cout<<1<<endl;
		cout<< contadorDeFila[1]<< endl;
		Usuario *us = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1],
				contadorDeFila[2], contadorDeFila[3], atoi(contadorDeFila[4]));
		u.anyadirUsuario(us);
	}
	else {

		cout<<2<<endl;

		cout<<atoi(contadorDeFila[0])<< contadorDeFila[1]<<
				contadorDeFila[2]<<contadorDeFila[3]<<atoi(contadorDeFila[4])<<endl;
		Administrador *ad = new Administrador(atoi(contadorDeFila[0]), contadorDeFila[1],
				contadorDeFila[2], contadorDeFila[3], atoi(contadorDeFila[4]));
		u.anyadirUsuario(ad);

	}

	return 0;
}

int callbackReservas(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas) {
	(void) data;

	Reserva *r = new Reserva(atoi(contadorDeFila[0]), atoi(contadorDeFila[1]),
			atoi(contadorDeFila[2]), h.getHabitacion(atoi(contadorDeFila[4])));

	u.getReservas(atoi(contadorDeFila[3]))->anyadirReserva(r);
	re.anyadirReserva(r);

	return 0;

}

int callbackHabitaciones(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas) {
	(void) data;
	Habitacion *ha = new Habitacion(atoi(contadorDeFila[0]),
			atoi(contadorDeFila[1]), atoi(contadorDeFila[2]), contadorDeFila[3],
			atoi(contadorDeFila[2]));
	h.anyadirhabitacion(ha);
	return 0;
}
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas) {
	(void)data;
	Trabajador *tr = new Trabajador(atoi(contadorDeFila[0]), contadorDeFila[1], contadorDeFila[2], atoi(contadorDeFila[3]),atoi(contadorDeFila[4]));
	t.anyadirTrabajador(tr);
return 0;
}

//int callbackHoteles(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas) {
//	(void)data;
//	Hotel *ht = new Hotel(atoi(contadorDeFila[0]), contadorDeFila[1], contadorDeFila[2], atoi(contadorDeFila[3]),atoi(contadorDeFila[4]));
//
//return 0;
//}

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

//aqui
int main() {
	inicio();
	return 0;
}
void inicio() {

	cout << "---MODO ADMINISTRADOR---" << endl;

	ifstream ifs;
	importarDatosUsuarios();

	cargarDatosUsuarios();

	//u.imprimirUsuarios();
	//u.imprimirUsuarios();

	cargarDatosHabitaciones();
	h.imprimirHabitaciones();

	cargarDatosTrabajadores();
	//t.imprimirTrabajadores();
	cargarDatosReservas();

	t.imprimirTrabajadores();



	u.imprimirUsuarios();

	//crear metodo devolver usuario con id de usuario, prueba id 1 y prueba a hacer print de las reservas


//	u.getUsuario(8)->imprimirUsuario();
//	cout<<u.getUsuario(1)->getReservaUsuario()->getNumReservas()<<endl;
//	u.getUsuario(1)->getReservaUsuario()->imprimirReservas();


	//u.imprimirUsuarios();
	////////////////////////////////////////////
	// GENERAR UN OBJETO USUARIOS Y RELLENARLA CON UNA FUNCION DE LA CLASE
	// GENERAR UN OBJETO RESERVAS Y RELLENARLO CON LA BASE DE DATOS
	// GENERAR UN OBJETO HABITACIONES Y RELLENARLO CON LA BASE DE DATOS
	// GENERAR UN OBJETO TRABAJADORES Y RELLENARLO DE LA BASE DE DATOS(?)
	// HOTEL(?)
	///////////////////////////////////////////////

	ifs.open("../progIV_Cplus/Usuarios.txt", ios::in);

//		cout<<ifs.tellg()<<endl;

	char nom[20], cont[20], nomAu[20], conAu[20];
	string linea;
	bool en = false;
	cout << "Ingrese el nombre del usuario: " << endl;
	cin >> nomAu;
	cout << "Ingrese la contrasenya del usuario: " << endl;
	cin >> conAu;

	while (!ifs.eof() && !en) {
		//cout<<ifs.tellg()<<endl;
		//ifs >> nom;
		char cNum[20];
		ifs.getline(cNum, 256, ':');
		ifs.getline(cNum, 256, ';');
		ifs.getline(cNum, 256, ':');
		ifs.getline(cNum, 256, ';');
		strcpy(nom, cNum);
		ifs.getline(cNum, 256, ':');
		ifs.getline(cNum, 256, ';');
		strcpy(cont, cNum);

		ifs.getline(cNum, 256, ':');
		ifs.getline(cNum, 256, ';');
		ifs.getline(cNum, 256, ':');
		ifs.getline(cNum, 256, ';');
		ifs.getline(cNum, 256, ':');
		ifs.getline(cNum, 256, ';');

//			cout<<cont<<endl;

//			cout<<nom<<" "<<cont<<endl;
//			cout<<nomAu<<" "<<conAu<<endl;

		if (strcmp(nom, nomAu) == 0 && strcmp(cont, conAu) == 0) {
			cout << "Usuario y contrasenya correctos. Bienvenido " << nomAu
					<< endl;
			en = true;

			//parte del usuario
			system("cls");
			cout << endl;
//				cout<<cNum<<endl;
//				ifs.getline(cNum, 256, ':');
//				ifs.getline(cNum, 256, ';');
//				ifs.getline(cNum, 256, ':');
//				ifs.getline(cNum, 256, ';');
//				ifs.getline(cNum, 256, ':');
//				ifs.getline(cNum, 256, ';');
			cout << cNum << endl;

			ifs.close();

			if (strcmp(cNum, "usuario") == 0) {
				cout << "---MODO USUARIO---" << endl;
				menuUsuario();//HAY QUE A�ADIR COMO PARAMETRO LA DIRECCION DEL USUARIO QUE VA A ACCEDER AL MEN�
			} else {
				cout << "---MODO ADMINISTRADOR---" << endl;
				menuAdministrador();//HAY QUE A�ADIR COMO PARAMETRO LA DIRECCION DEL USUARIO QUE VA A ACCEDER AL MEN�
			}

		}
		if (nom != nomAu && ifs.eof()) {
			cout << "El usuario no existe!" << endl;//AL SALIR VUELVE AQUI
			//usuarioPrincipio();
			ifs.close();

		}

		else if ((nom == nomAu && cont != conAu)) {
			cout << "Contrasenya incorrecta" << endl;
			//usuarioPrincipio();
			ifs.close();

		}

		getline(ifs, linea);

	}
	ifs.close();

}

void menuUsuario() {

	int opcion;
	do {
		cout << "Elije las siguientes opciones" << endl;
		cout << "1. Ver hoteles" << endl;
		cout << "2. Ver habitaciones" << endl;
		cout << "3. Ver reservas" << endl;	//Si no tiene mensaje por pantalla
		cout << "4. Hacer reserva" << endl;			//Solo a su nombre
		cout << "5. Modificar reserva" << endl;
		cout << "6. Eliminar reserva" << endl;
		cout << "7. Volver al menu principal" << endl;
		cin >> opcion;
	} while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4
			&& opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7);
	/* ABRIMOS BASE DE DATOS */
	rc = sqlite3_open("hotelandia_final.s3db", &db);
	switch (opcion) {
	case 1: {
		caso1Usuario();
	}
		break;
	case 2: {
		caso2Usuario();
	}
		break;
	case 3: {
		caso3Usuario();
	}
		break;
	case 4: {
		caso4Usuario();
	}
		break;
	case 5: {
		caso5Usuario();
	}
		break;
	case 6: {
		caso6Usuario();
	}
		break;
	case 7: {
		system("cls");
		cout << "Cerrando sesion..." << endl;
		inicio();

	}
		break;
	default: {
		cout << "Introduzca un valor correcto" << endl;
		menuUsuario();
	}
		break;

	}
}
void caso1Usuario() {//VER HOTELES
	/* Create SQL statement */
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
	menuUsuario();
}
void caso2Usuario() {//VER HABITACIONES
	cout << "--HABITACIONES--" << endl;


	h.imprimirHabitaciones();
	//h.busquedaPersonalizada();

		system("pause");
	menuUsuario();
}
int caso3Usuario() {//VER RESERVA
	char usuarioReserva[20];

	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
	if (rc != SQLITE_OK) {
		cout << "Error opening database" << endl;
		return rc;
	}
	cout << "Introduzca su usuario para ver sus reservas" << endl;
	cin >> usuarioReserva;
	rc = verReserva(db, usuarioReserva);
	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) {
		printf("Error closing database\n");
		printf("%s\n", sqlite3_errmsg(db));
		return rc;
	}
	system("pause");
	menuUsuario();
	return 0;
}
int caso4Usuario() {//CREAR RESERVA
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
	menuUsuario();
	return 0;
}
int caso5Usuario() {//MODIFICAR RESERVA
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
	menuUsuario();
	return 0;
}
int caso6Usuario() {//ELIMINAR RESERVA
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
	menuUsuario();
	return 0;
}


void menuAdministrador() {

	int opcion;
	do {
		cout << "Elije las siguientes opciones" << endl;
		cout << "1. Ver habitaciones" << endl;
		cout << "2. Editar habitacion" << endl;
		cout << "3. Anyadir habitacion" << endl;
		cout << "4. Eliminar habitacion" << endl;
		cout << "5. Ver reservas" << endl;
		cout << "6. Editar reserva" << endl;
		cout << "7. Anyadir reserva" << endl;
		cout << "8. Eliminar reserva" << endl;
		cout << "9. Ver trabajadores" << endl;
		cout << "10. Editar trabajador" <<endl;
		cout << "11. Crear trabajador" << endl;
		cout << "12. Eliminar trabajador" << endl;
		cout << "13. Ver usuarios" << endl;
		cout << "14. Editar usuario"<<endl;
		cout << "15. Crear Usuario" <<endl;
		cout << "16. Eliminar usuario"<<endl;
		cout << "17. Volver al menu principal" << endl;
		cin >> opcion;
	} while (opcion < 1 || opcion > 17);
	/* ABRIMOS BASE DE DATOS */
	rc = sqlite3_open("hotelandia_final.s3db", &db);
	switch (opcion) {
	case 1: {
		caso1Admin();
	}
		break;
	case 2: {
		caso2Admin();
	}
		break;
	case 3: {
		caso3Admin();
	}
		break;
	case 4: {
		caso4Admin();
	}
		break;
	case 5: {
		caso5Admin();
	}
		break;
	case 6: {
		caso6Admin();
	}
		break;
	case 7: {
		caso7Admin();
	}
		break;
	case 8: {
		caso8Admin();
	}
		break;
	case 9: {
		caso9Admin();
	}
		break;
	case 10: {
		caso10Admin();
	}
		break;
	case 11: {
		caso11Admin();
	}break;
	case 12: {
		caso12Admin();
	}break;
	case 13: {
		caso13Admin();
	}break;
	case 14: {
		caso14Admin();
	}
		break;
	case 15: {
		caso15Admin();
	}
		break;
	case 16: {
		caso16Admin();
	}break;
	case 17: {
			cout << "Cerrando sesion..." << endl;
			inicio();
			system("exit");
	}
		break;
	default: {
		cout << "Introduzca un valor correcto" << endl;
		menuUsuario();
	}
		break;

	}

}
void caso1Admin() {//VER HABITACION
	cout << "--HABITACIONES--" << endl;

	h.imprimirHabitaciones();
	system("pause");
	menuAdministrador();
}
void caso2Admin() {//EDITAR HABITACION

	char tipoHab[100];

	cout << "introduce el id de la habitacion que quieres modificar" << endl;

	int idHab;

	cin >> idHab;

	cout << "introduce el nuevo tipo de Habitacion:" << endl;

	cin >> tipoHab;

	cout << "Introduce el nuevo precio de la Habitacion:" << endl;

	int Prec;
	cin >> Prec;

	h.editarHabitacion(idHab, tipoHab, Prec);

	system("pause");

	menuAdministrador();

}
void caso3Admin() {//CREAR HABITACION
	cout << "Crea una nueva habitacion" << endl;

	char  tipo[100];

	int num_hab;
	int planta;
	int id_hab;
	int precio;

	cout << "Ingrese el id de la habitacion que desea anyadir: ";
	cin >> id_hab;
	cout << endl;
	cout << "Ingrese el numero de la habitacion que desea anyadir: ";
	cin >> num_hab;
	cout << endl;
	cout << "Ingrese la planta de la habitacion que desea anyadir: ";
	cin >> planta;
	cout << endl;
	cout << "Ingrese el tipo de habitacion que desea anyadir: ";
	cin >> tipo;
	cout << endl;
	cout << "Ingrese el precio de la habitacion: ";
	cin >> precio;
	cout << endl;

	Habitacion* hab = new Habitacion(id_hab, num_hab, planta, tipo, precio);
	h.anyadirhabitacion(hab);
	system("pause");
	menuAdministrador();

}
void caso4Admin() {//ELIMINAR HABITACION
	//AL ELIMINAR HABITACION SE DEBERIA QUITAR UNA FILA DE LA TABLA HOTEL_TIENE_HABITACIONES??
	int idhab;
	h.imprimirHabitaciones();
		cout << "introduce el id de habitacion para eliminarlo" << endl;

		cin >> idhab;

		h.quitarHabitacion(idhab);

		h.getNumHabitaciones();
		system("pause");
		menuAdministrador();
}
void caso5Admin(){//VER RESERVAS
	cout << "--RESERVAS--" << endl;

	re.imprimirReservas();
	system("pause");
	menuAdministrador();
}
void caso6Admin(){//EDITAR RESERVA
	int idR,dia,hora; Habitacion* hab;
		cout << "introduce el id de la reserva que quieres modificar" << endl;

		//int idR;

		cin >> idR;

		cout << "introduce el dia que quieres modificar: " << endl;

		cin >> dia;

		cout << "Introduce la hora que quieres modificar: " << endl;

		cin >> hora;
		hab = re.getReserva(idR)->getHabitacionReservada();

		char tipoHab[100];

		cout << "introduce el nuevo tipo de Habitacion:" << endl;

		cin >> tipoHab;

		cout << "Introduce el nuevo precio de la Habitacion:" << endl;

		int Prec;
		cin >> Prec;

		hab->setPrecioHabitacion(Prec);
		hab->setTipoHabitacion(tipoHab);
		re.editarReserva(idR,dia,hora,hab);

		system("pause");

		menuAdministrador();
}
void caso7Admin() {//CREAR RESERVA
	cout << "Crea una nueva reserva" << endl;

	int idH;
	int idR,diaR,horaR;

	cout << "Ingrese el id de la reserva que desea anyadir: ";
	cin >> idR;
	cout << endl;
	cout << "Ingrese el dia de la reserva que desea anyadir: ";
	cin >> diaR;
	cout << endl;
	cout << "Ingrese la hora de la reserva que desea anyadir: ";
	cin >> horaR;
	cout<<" En que habitacion desea hacer la reserva?"<<endl;
	h.imprimirHabitaciones();
	cout<<"Introduzca un id de las habitaciones descritas"<<endl;
	cin>>idH;
	Reserva* rq = new Reserva(idR,diaR,horaR,h.getHabitacion(idH));
	re.anyadirReserva(rq);
	system("pause");
	menuAdministrador();

}
void caso8Admin() {//ELIMINAR RESERVA
	int idR;
	re.imprimirReservas();
	cout << "introduce el id de la reserva a eliminar: " << endl;
	cin >> idR;
	re.quitarReserva(idR);
	re.getNumReservas();
	system("pause");
	menuAdministrador();

}
void caso9Admin() {//VER TRABAJADORES

	cout << "--TRABAJADORES--" << endl;

	t.imprimirTrabajadores();
	system("pause");
	menuAdministrador();

}
void caso10Admin(){//EDITAR TRABAJADOR
	float sueldo;

	cout << "Introduce el id del trabajador que quieres modificar" << endl;

	int idTra;

	cin >> idTra;

	cout << "Introduce el nuevo sueldo del trabajador" << endl;

	cin >> sueldo;

	t.editarTrabajador(idTra, sueldo);

	system("pause");

	menuAdministrador();
}
void caso11Admin() {//CREAR TRABAJADOR

	cout << "Crea un nuevo trabajador" << endl;

	int idTrabajador;
	char nombreTrabajador[100];
	char dniTrabajador[9];
	int telefonoTrabajador;
	float sueldoTrabajador;

	cout << "Ingrese el id del trabajador que desea anyadir: ";
	cin >> idTrabajador;
	cout << endl;
	cout << "Ingrese el nombre del trabajador que desea anyadir: ";
	cin >> nombreTrabajador;
	cout << endl;
	cout << "Ingrese el DNI del trabajador que desea anyadir: ";
	cin >> dniTrabajador;
	cout << endl;
	cout << "Ingrese el telefono del trabajador que desea anyadir: ";
	cin >> telefonoTrabajador;
	cout << endl;
	cout << "Ingrese el sueldo del trabajador que desea anyadir: ";
	cin >> sueldoTrabajador;
	cout << endl;

	Trabajador* tr = new Trabajador(idTrabajador, nombreTrabajador, dniTrabajador, telefonoTrabajador, sueldoTrabajador);
	t.anyadirTrabajador(tr);
	system("pause");
	menuAdministrador();

}
void caso12Admin() {//ELIMINAR TRABAJADOR
	int idtr;
	t.imprimirTrabajadores();
	cout << "introduce el id del trabajador para eliminarlo" << endl;

	cin >> idtr;

	t.quitarTrabajador(idtr);

	t.getNumTrabajadores();
	system("pause");
	menuAdministrador();

}
void caso13Admin(){//VER USUARIOS

}
void caso14Admin(){//EDITAR USUARIO

}
void caso15Admin(){//CREAR USUARIO

}
void caso16Admin(){//ELIMINAR USUARIO

}

