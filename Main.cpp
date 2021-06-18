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
//	char usuarioReserva[20];
//
//	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
//	if (rc != SQLITE_OK) {
//		cout << "Error opening database" << endl;
//		return rc;
//	}
//	cout << "Introduzca su usuario para ver sus reservas" << endl;
//	cin >> usuarioReserva;
//	rc = verReserva(db, usuarioReserva);
//	rc = sqlite3_close(db);
//	if (rc != SQLITE_OK) {
//		printf("Error closing database\n");
//		printf("%s\n", sqlite3_errmsg(db));
//		return rc;
//	}
//	system("pause");


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


//	cout << "Introduzca el usuario en el que va a realizar la modificacion: ";
//
//
//			int eleccionNHabitacion;
//			int dia;
//			int hora;
//
//			re.getOrdenReserva(re.getNumReservas())->getIdReserva();//AQUI TENEMOS EL ID DE LA NUEVA RESERVA
//			cout << endl;
//			cout << "Ingrese el dia de la reserva que desea anyadir: ";
//			cin >> dia;
//			while(dia<1||dia>31){
//				cout<<"por favor indique un dia adecuado"<<endl;
//				cin >> dia;
//			}
//			cout << endl;
//			cout << "Ingrese la hora de llegada al hotel que desea anyadir: "<<endl;
//			cin >> hora;
//			while(hora<0||hora>24){
//				cout<<"por favor indique una hora adecuada"<<endl;
//				cin >> hora;
//			}
//			cout << "Ingrese el id de la habitacion que desea reservar: "<<endl;
//
//			cout<<"Aqui tienes las habitaciones que tenemos disponibles"<<endl;
//
//			h.imprimirHabitaciones();
//
//
//
//			cin >> eleccionNHabitacion;
//			while(h.getHabitacion(eleccionNHabitacion)==NULL){
//
//				cout<<"por favor habitacion adecuada"<<endl;
//				cin >> eleccionNHabitacion;
//			}
//
//
//			cout << endl;
//
//			usuarioActual->getReservaUsuario()->
//					anyadirReserva(new Reserva(re.getOrdenReserva(re.getNumReservas())->getIdReserva(),dia,hora,h.getHabitacion(eleccionNHabitacion)));
//			//ESTE METODO AÑADE UNA RESERVA
//
//			/* Create SQL statement */
//			char sql[] = "INSERT INTO RESERVA VALUES (";
//
//			char con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";
//
//
//
//			strcat(sql, (char*)re.getOrdenReserva(re.getNumReservas())->getIdReserva());
//			strcat(sql, con1);
//			strcat(sql, (char*)dia);
//			strcat(sql, con2);
//			strcat(sql, (char*)hora);
//			strcat(sql, con3);
//			strcat(sql, (char*)usuarioActual->getIdUsuario());//CONVERTIR INT A CHAR
//			strcat(sql, con8);
//			strcat(sql, con9);
//
//
//
//			/* Execute SQL statement */
//			rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
//			if (rc != SQLITE_OK) {
//				fprintf(stderr, "SQL error: %s\n", zErrMsg);
//				sqlite3_free(zErrMsg);
//			} else {
//				fprintf(stdout, "Reserva realizada:\n");
//			}
//			sqlite3_close(db);

//	cout << "Introduzca su nombre de usuario para realizar una reserva :"
//			<< endl;
//	cin >> nombreUsuario;
//
//	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
//	if (rc != SQLITE_OK) {
//		cout << "Error opening database" << endl;
//		return rc;
//	}
//
//	char sql[] = "SELECT * from HOTEL";
//
//	/* Execute SQL statement */
//	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
//	if (rc != SQLITE_OK) {
//		fprintf(stderr, "SQL error: %s\n", zErrMsg);
//		sqlite3_free(zErrMsg);
//	}
//	cout
//			<< "Seleccione el hotel en el que desea realizar una reserva (Su numero): ";
//	cin >> eleccionHotel;
//	char sql2[] =
//			"SELECT H.numero_habitacion, H.planta_habitacion, H.tipo_habitacion, H.precio_habitacion from HABITACION H, HOTEL M, HOTEL_TIENE_HABITACIONES L WHERE M.id_hotel = ";
//	strcat(sql2, eleccionHotel);
//	char fr100[] =
//			" AND M.id_hotel = L.id_hotel AND L.id_habitacion = H.id_habitacion";
//	strcat(sql2, fr100);
//	/* Execute SQL statement */
//	rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
//	if (rc != SQLITE_OK) {
//		fprintf(stderr, "SQL error: %s\n", zErrMsg);
//		sqlite3_free(zErrMsg);
//	}
//	cout << "Seleccione el numero de habitacion que desea reservar: ";
//	cin >> eleccionNHabitacion;
//	cout << endl << "Seleccione el dia en el que desea realizar la reserva";
//	cin >> dia;
//	cout << endl << "Seleccione la hora de entrada ";
//	cin >> hora;
//	int hotel = atoi(eleccionHotel);
//	rc = crearReserva(db, nombreUsuario, hotel, eleccionNHabitacion, dia, hora);
//	rc = sqlite3_close(db);
//	if (rc != SQLITE_OK) {
//		printf("Error closing database\n");
//		printf("%s\n", sqlite3_errmsg(db));
//		return rc;
//	}
	//return 0;
}

int caso5Usuario() {//MODIFICAR RESERVA



//	rc = sqlite3_open("hotelandia_final.s3db", &db);	//abrir base de datos
//	if (rc != SQLITE_OK) {
//		cout << "Error opening database" << endl;
//		return rc;
//	}
//	rc = modificarReserva(db, usuarioActual->getNombreUsuario());//ANYADIR MODIFICAR LA HABITACION
//	rc = sqlite3_close(db);
//	if (rc != SQLITE_OK) {
//		printf("Error closing database\n");
//		printf("%s\n", sqlite3_errmsg(db));
//		return rc;
//	}

	usuarioActual->modificarReserva(&h);

	system("pause");

	menuUsuario();

	return 0;
}
int caso6Usuario() {//ELIMINAR RESERVA



//	char usuarioEliminar[20];
//	cout << "Introduzca el usuario del que quiere eliminar una reserva: ";
//	cin >> usuarioEliminar;
//	cout << endl;
//	rc = sqlite3_open("hotelandia_final.s3db", &db);
//	if (rc != SQLITE_OK) {
//		cout << "Error opening database" << endl;
//		return rc;
//	}
//	rc = eliminarReserva(db, usuarioEliminar);
//	rc = sqlite3_close(db);
//	if (rc != SQLITE_OK) {
//		printf("Error closing database\n");
//		printf("%s\n", sqlite3_errmsg(db));
//		return rc;
//	}


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
		cout << "6. Editar reserva" << endl;
		cout << "7. Anyadir reserva" << endl;
		cout << "8. Eliminar reserva" << endl;
		cout << "9. Ver trabajadores" << endl;
		cout << "10. Editar trabajador" << endl;
		cout << "11. Crear trabajador" << endl;
		cout << "12. Eliminar trabajador" << endl;
		cout << "13. Ver usuarios" << endl;//QUITABA ESTA FUNCION USUARIOS PORQUE NOSOTROS FUNCIONAMOS CON FICHEROS
		cout << "14. Editar usuario" << endl;
		cout << "15. Crear Usuario" << endl;
		cout << "16. Eliminar usuario" << endl;
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
		caso16Admin();
	}
		break;
	case 17: {
		cout << "Cerrando sesion..." << endl;
		//inicio();
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

//	char tipoHab[100];
//
//	cout << "introduce el id de la habitacion que quieres modificar" << endl;
//
//	int idHab;
//
//	cin >> idHab;
//
//	cout << "introduce el nuevo tipo de Habitacion:" << endl;
//
//	cin >> tipoHab;
//
//	cout << "Introduce el nuevo precio de la Habitacion:" << endl;
//
//	int Prec;
//	cin >> Prec;
//
//	h.editarHabitacion(idHab, tipoHab, Prec);


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
void caso6Admin() {//EDITAR RESERVA

	int idR, dia, hora;
	Habitacion *hab;
	cout << "introduce el id de la reserva que quieres modificar" << endl;


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
	re.editarReserva(idR, dia, hora, hab);

	system("pause");

	menuAdministrador();
}
void caso7Admin() {//CREAR RESERVA
	cout << "Crea una nueva reserva" << endl;

	int idH;
	int idR, diaR, horaR;

	cout << "Ingrese el id de la reserva que desea anyadir: ";
	cin >> idR;
	cout << endl;
	cout << "Ingrese el dia de la reserva que desea anyadir: ";
	cin >> diaR;
	cout << endl;
	cout << "Ingrese la hora de la reserva que desea anyadir: ";
	cin >> horaR;
	cout << " En que habitacion desea hacer la reserva?" << endl;
	h.imprimirHabitaciones();
	cout << "Introduzca un id de las habitaciones descritas" << endl;
	cin >> idH;
	Reserva *rq = new Reserva(idR, diaR, horaR, h.getHabitacion(idH));

	re.comprobarDisponibilidad(rq);

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
void caso10Admin() {//EDITAR TRABAJADOR
	usuarioActual->editarTrabajador(&t);

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

	Trabajador *tr = new Trabajador(idTrabajador, nombreTrabajador,
			dniTrabajador, telefonoTrabajador, sueldoTrabajador);
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
void caso13Admin() {//VER USUARIOS
	cout << "--USUARIOS--" << endl;

	u.imprimirUsuarios();
	system("pause");
	menuAdministrador();
}
void caso14Admin() {//EDITAR USUARIO
	//Todo: hay que arreglar para poder modificar las reservas del usuario
	char correo[100];char nombre[100];char contra[100];int edad;

		cout << "introduce el id del usuario que quieres modificar" << endl;
		int idR;
		cin >> idR;

		cout << "introduce el nombre del usuario que quieres modificar" << endl;
		cin >> correo;

		cout << "introduce el correo del usuario que quieres modificar" << endl;
		cin >> nombre;

		cout << "introduce el nombre del usuario que quieres modificar" << endl;
		cin >> contra;

		cout << "Introduce la nueva edad del usuario que quieres modificar" << endl;
		cin >> edad;
		system("pause");

		menuAdministrador();
}
void caso15Admin() {//CREAR USUARIO
	cout << "Crea un nuevo usuario: " << endl;

	//AL crear un usuario nuevo no se le añaden reservas
	int idUsuario;
	char nombreUsuario[100];
	char correoUsuario[100];
	char contrasenyaUsuario[100];
	int edadUsuario;

	cout << "Ingrese el id del usuario : ";
	cin >> idUsuario;
	cout << endl;
	cout << "Ingrese el nombre del usuario: ";
	cin >> nombreUsuario;
	cout << endl;
	cout << "Ingrese el correo del usuario: ";
	cin >> correoUsuario;
	cout << endl;
	cout << "Ingrese la contrasenya del usuario: ";
	cin >> contrasenyaUsuario;
	cout << endl;
	cout << "Ingrese la edad del usuario: ";
	cin >> edadUsuario;
	cout << endl;

	Usuario *us = new Usuario(idUsuario, nombreUsuario, correoUsuario, contrasenyaUsuario, edadUsuario);
	u.anyadirUsuario(us);
	system("pause");
	menuAdministrador();
}
void caso16Admin() {//ELIMINAR USUARIO
	int idR;
	u.imprimirUsuarios();
	cout << "introduce el id del usuario para eliminarlo" << endl;

	cin >> idR;

	u.quitarUsuario(idR);

	u.getNumUsuarios();
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
				usuarioActual=u.getUsuario(nomAu);

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
	//			cout << cNum << endl;

				ifs.close();

				if (strcmp(cNum, "usuario") == 0) {
					menuUsuario();//HAY QUE AÑADIR COMO PARAMETRO LA DIRECCION DEL USUARIO QUE VA A ACCEDER AL MENÚ
				} else {
					//cout << "---MODO ADMINISTRADOR---" << endl;
					menuAdministrador();//HAY QUE AÑADIR COMO PARAMETRO LA DIRECCION DEL USUARIO QUE VA A ACCEDER AL MENÚ
				}

			}
			if (nom != nomAu && ifs.eof()) {
				cout << "El usuario no existe!" << endl;	//AL SALIR VUELVE AQUI
				cout << "Introduce un nombre de usuario valido" << endl;
				cout<< endl;
				//usuarioPrincipio();
				ifs.close();

			}

			else if ((nom == nomAu && cont != conAu)) {
				cout << "Contrasenya incorrecta" << endl;
				cout << "Introduce una contraseña valida" << endl;
				cout<< endl;

				//usuarioPrincipio();
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
	//cout << numeroColumnas << endl;

	if (strcmp(contadorDeFila[5], "usuario") == 0) {
		//cout << 1 << endl;
		//cout << contadorDeFila[1] << endl;
		Usuario *us = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1],
				contadorDeFila[2], contadorDeFila[3], atoi(contadorDeFila[4]));
		u.anyadirUsuario(us);
	} else {

		//cout << 2 << endl;

//		cout << atoi(contadorDeFila[0]) << contadorDeFila[1]
//				<< contadorDeFila[2] << contadorDeFila[3]
//				<< atoi(contadorDeFila[4]) << endl;
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

	char sql[] =
			"SELECT id_trabajador, nombre_trabajador, DNI_trabajador, telefono_trabajador, sueldo_trabajador FROM TRABAJADOR";

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
	//cout<<counter<<endl;

	ifstream ifs;
	ifs.open("../progIV_Cplus/Usuarios.txt", ios::in);

	char sql[] = "DELETE FROM USUARIO";

	rc = sqlite3_open("hotelandia_final.s3db", &db);

	//cout<<rc<<endl;

	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
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

		rc = sqlite3_open("hotelandia_final.s3db", &db);
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
