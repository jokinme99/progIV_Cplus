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
#include <ctime>

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
int callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas);
int callbackReservas(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas);
int callbackHabitaciones(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas);
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas);

void importarDatosUsuarios();
void cargarDatosUsuarios();
void cargarDatosHabitaciones();
void cargarDatosReservas();
void cargarDatosTrabajadores();

void inicio();void iniciarSesion();void menuUsuario();void menuAdministrador();

void caso1Usuario();void caso2Usuario();int caso3Usuario();
void caso4Usuario();int caso5Usuario();int caso6Usuario();

void caso1Admin();void caso2Admin();void caso3Admin();void caso4Admin();
void caso5Admin();void caso6Admin();void caso7Admin();void caso8Admin();
void caso9Admin();void caso10Admin();void caso11Admin();void caso12Admin();
void caso13Admin();void caso14Admin();void caso15Admin();void caso16Admin();


Usuarios u;Habitaciones h;Trabajadores t;Reservas re;//variables glovales de los objetos principales con los que manejaremos el prigrama

Usuario* usuarioActual;//Variable global que indica el usuario actual en el menu

Administrador* admin;

sqlite3 *db;char *zErrMsg = 0;int rc;char *sql;const char *data = "LLamada a Base de datos";//variables globales para la base de datos


int main() {
	inicio();
	return 0;
}
void inicio() {

	importarDatosUsuarios();//Saca datos del fichero de Usuarios.txt generado por el programa de C y los importa en la base de datos

	cargarDatosUsuarios();//Carga los usuarios que estan en la base de datos en el objeto "Usuarios u"

	cargarDatosHabitaciones();//Carga las habitaciones que estan en la base de datos en el objeto "Habitaciones h"

	cargarDatosReservas();//Carga las reservas que estan en la base de datos en el objeto "Reservas re", ademas implementa las direcciones de las reservas
	//pertencecientes a cada usuario en un array de direcciones de reservas personal

	cargarDatosTrabajadores();//Carga los trabajadores que estan en la base de datos en el objeto "Trabajadores t"

	iniciarSesion();//Te lleva al inicio de sesion
}

void menuUsuario() {

	int opcion;
	do {

			cout << " ____________MODO USUARIO_______________________________"<< endl;

			cout << "|				                      "
					<< "  |" << endl;
			cout << "|							|" << endl;
			cout << "|	Elige las siguientes opciones                   |"
					<< endl;
			cout << "|	1. Ver hoteles                                  |"
					<< endl;
			cout << "|	2. Ver habitaciones			        |" << endl;
			cout << "|	3. Ver reservas				    	|" << endl;//Si no tiene mensaje por pantalla
			cout << "|	4. Hacer reserva				|" << endl;		//Solo a su nombre
			cout << "|	5. Modificar reserva		            	|" << endl;
			cout << "|	6. Eliminar reserva				|" << endl;
			cout << "|	7. Volver al menu principal                     |"
					<< endl;
			cout << "|_______________________________________________________|"
					<< endl;

			cin >> opcion;



	} while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4
			&& opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7);
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
		iniciarSesion();

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

	rc = sqlite3_open("hotelandia_final.s3db", &db);

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


	h.busquedaPersonalizada();

	system("pause");
	menuUsuario();
}
int caso3Usuario() {//VER RESERVA



	cout<<"A continuacion se le mostraran sus reservas"<<endl;

	cout<<endl;

	usuarioActual->getReservaUsuario()->imprimirReservas();

	system("pause");


	menuUsuario();
	return 0;
}



void caso4Usuario() {	//CREAR RESERVA


	usuarioActual->anyadirReserva(&re, &h);


	system("pause");



	menuUsuario();


}

int caso5Usuario() {//MODIFICAR RESERVA




	usuarioActual->modificarReserva(&h);

	system("pause");

	menuUsuario();

	return 0;
}
int caso6Usuario() {//ELIMINAR RESERVA



	usuarioActual->eliminarReserva(&re);

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
		cout << "6. Anyadir reserva" << endl;
		cout << "7. Eliminar reserva" << endl;
		cout << "8. Ver trabajadores" << endl;
		cout << "9. Editar trabajador" << endl;
		cout << "10. Crear trabajador" << endl;
		cout << "11. Eliminar trabajador" << endl;
		cout << "12. Ver usuarios" << endl;//QUITABA ESTA FUNCION USUARIOS PORQUE NOSOTROS FUNCIONAMOS CON FICHEROS
		cout << "13. Editar usuario" << endl;
		cout << "14. Crear Usuario" << endl;
		cout << "15. Eliminar usuario" << endl;
		cout << "16. Volver al menu principal" << endl;
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
	}
		break;
	case 12: {
		caso12Admin();
	}
		break;
	case 13: {
		caso13Admin();
	}
		break;
	case 14: {
		caso14Admin();
	}
		break;
	case 15: {
		caso15Admin();
	}
		break;

	case 16: {
		cout << "Cerrando sesion..." << endl;
		iniciarSesion();
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

	h.busquedaPersonalizada();

	system("pause");

	menuAdministrador();

}
void caso2Admin() {//EDITAR HABITACION




	usuarioActual->editarHabitacion(&h);

	cout << "volviendo al menu" << endl;


	system("pause");

	menuAdministrador();

}
void caso3Admin() {//CREAR HABITACION


	usuarioActual->anyadirHabitacion(&h);

	system("pause");
	menuAdministrador();

}
void caso4Admin() {//ELIMINAR HABITACION
	//AL ELIMINAR HABITACION SE DEBERIA QUITAR UNA FILA DE LA TABLA HOTEL_TIENE_HABITACIONES??

	usuarioActual->eliminarHabitacion(&h);

	system("pause");
	menuAdministrador();
}
void caso5Admin() {//VER RESERVAS
	cout << "--RESERVAS--" << endl;

	re.imprimirReservas();
	system("pause");
	menuAdministrador();
}

void caso6Admin() {//CREAR RESERVA

	usuarioActual->eliminarReserva(&re);
	system("pause");
	menuAdministrador();

}
void caso7Admin() {//ELIMINAR RESERVA

	usuarioActual->eliminarReserva(&re);
	re.getNumReservas();
	system("pause");
	menuAdministrador();

}
void caso8Admin() {//VER TRABAJADORES

	cout << "--TRABAJADORES--" << endl;

	t.imprimirTrabajadores();
	system("pause");
	menuAdministrador();

}
void caso9Admin() {//EDITAR TRABAJADOR
	usuarioActual->editarTrabajador(&t);

	system("pause");

	menuAdministrador();
}
void caso10Admin() {//CREAR TRABAJADOR


	usuarioActual->anyadirTrabajador(&t);


	system("pause");
	menuAdministrador();

}
void caso11Admin() {//ELIMINAR TRABAJADOR

	usuarioActual->eliminarTrabajador(&t);

	system("pause");
	menuAdministrador();

}
void caso12Admin() {//VER USUARIOS
	cout << "--USUARIOS--" << endl;

	u.imprimirUsuarios();
	system("pause");
	menuAdministrador();
}
void caso13Admin() {//EDITAR USUARIO


	u.editarUsuarios(&u);

		menuAdministrador();
}
void caso14Admin() {//CREAR USUARIO
	cout << "Crea un nuevo usuario: " << endl;

	u.anyadirUsuario(&u);
	system("pause");
	menuAdministrador();
}
void caso15Admin() {//ELIMINAR USUARIO

	u.eliminarUsuario(&u);


	system("pause");
	menuAdministrador();
}
void iniciarSesion(){

	ifstream ifs;

	ifs.open("../progIV_Cplus/Usuarios.txt", ios::in);

	char nom[20], cont[20], nomAu[20], conAu[20];
	string linea;
	bool en = false;
	while(!en){

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


			if (strcmp(nom, nomAu) == 0 && strcmp(cont, conAu) == 0) {
				cout << "Usuario y contrasenya correctos. Bienvenido " << nomAu
						<< endl;
				system("pause");
				en = true;
				usuarioActual= u.getUsuario(nomAu);

				//parte del usuario
				system("cls");
				cout << endl;


				ifs.close();

				if (strcmp(cNum, "usuario") == 0) {
					menuUsuario();//HAY QUE A�ADIR COMO PARAMETRO LA DIRECCION DEL USUARIO QUE VA A ACCEDER AL MEN�
				} else {
					//cout << "---MODO ADMINISTRADOR---" << endl;
					menuAdministrador();//HAY QUE A�ADIR COMO PARAMETRO LA DIRECCION DEL USUARIO QUE VA A ACCEDER AL MEN�
				}

			}
			if (nom != nomAu && ifs.eof()) {
				cout << "El usuario no existe!" << endl;	//AL SALIR VUELVE AQUI
				cout << "Introduce un nombre de usuario valido" << endl;
				cout<< endl;
				iniciarSesion();
				ifs.close();

			}

			else if ((nom == nomAu && cont != conAu)) {
				cout << "Contrasenya incorrecta" << endl;
				cout << "Introduce una contrase�a valida" << endl;
				cout<< endl;

				iniciarSesion();
				ifs.close();

			}

			getline(ifs, linea);

		}
		ifs.close();
	}

}

//METODOS PARA RESERVAR ESPACIO PARA LOS DATOS DE LA BD
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

		Usuario *us = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1],
				contadorDeFila[2], contadorDeFila[3], atoi(contadorDeFila[4]));
		u.anyadirUsuario(us);
	} else {


		Administrador *ad = new Administrador(atoi(contadorDeFila[0]),
				contadorDeFila[1], contadorDeFila[2], contadorDeFila[3],
				atoi(contadorDeFila[4]));
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
			atoi(contadorDeFila[4]));
	h.anyadirhabitacion(ha);
	return 0;
}
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas) {
	(void) data;
	Trabajador *tr = new Trabajador(atoi(contadorDeFila[0]), contadorDeFila[1],
			contadorDeFila[2], atoi(contadorDeFila[3]),
			atoi(contadorDeFila[4]));
	t.anyadirTrabajador(tr);
	return 0;
}

//METODOS PARA SELECCIONAR LOS DATOS DE LA BD Y CARGARLOS
void cargarDatosUsuarios() {

	rc = sqlite3_open("../progIV_Cplus/hotelandia_final.s3db", &db);

	char sql[] = "SELECT * from USUARIO";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackUsuarios, (void*) data, &zErrMsg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

	}
	sqlite3_close(db);

}
void cargarDatosHabitaciones() {

	rc = sqlite3_open("../progIV_Cplus/hotelandia_final.s3db", &db);

	char sql[] = "SELECT * from HABITACION";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackHabitaciones, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

	}
	sqlite3_close(db);

}
void cargarDatosTrabajadores() {

	rc = sqlite3_open("../progIV_Cplus/hotelandia_final.s3db", &db);

	char sql[] =
			"SELECT id_trabajador, nombre_trabajador, DNI_trabajador, telefono_trabajador, sueldo_trabajador FROM TRABAJADOR";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callbackTrabajadores, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

	}
	sqlite3_close(db);

}
void cargarDatosReservas() {

	rc = sqlite3_open("../progIV_Cplus/hotelandia_final.s3db", &db);

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

//IMPORTA LOS DATOS DE USUARIOS DE LOS FICHEROS A LA BASE DE DATOS
void importarDatosUsuarios() {

	FILE *f = fopen("../progIV_Cplus/Usuarios.txt", "r");

	int counter = 0;
	char linea;
	char cadena[20], id[20], nom[20], cont[20], correo[30], edad[5], tipo[10];

	for (linea = getc(f); linea != EOF; linea = getc(f))
		if (linea == '\n')
			counter = counter + 1;

	fclose(f);


	ifstream ifs;
	ifs.open("../progIV_Cplus/Usuarios.txt", ios::in);

	char sql[] = "DELETE FROM USUARIO";

	rc = sqlite3_open("hotelandia_final.s3db", &db);



	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

	}
	sqlite3_close(db);
	//cout<<rc<<endl;
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

		rc = sqlite3_open("../progIV_Cplus/hotelandia_final.s3db", &db);
		//cout<<rc<<endl;
		/* Execute SQL statement */
		rc = sqlite3_exec(db, retVal, callback, (void*) data, &zErrMsg);
		//cout<<rc<<endl;
		if (rc != SQLITE_OK) {

			//cout<<"Reserva no realizada:"<<endl;

			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			//fprintf(stdout, "Operation done successfully\n");
		}
		sqlite3_close(db);

	}

}
