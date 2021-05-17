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
#include "sqlite/sqlite3.h" //include para base de datos
#include <sqlite3.h> //include para base de datos

#include <fstream>
#include <windows.h>


#include "Habitacion.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Hotel.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Reserva.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Trabajador.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Usuario.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos


using namespace std;
//using namespace data;

void menuInicio();

void usuarioPrincipio();//Menu usuario(iniciar sesion/registrarse)
void inicioUsuario();//inicio sesion usuario
bool comprobarUsuario(char *usuario, char *contrasenya);
void registroUsuario();
void menuUsuario();
void caso1Usuario();
void caso2Usuario();
void caso3Usuario();
void caso4Usuario();
void caso5Usuario();

void administrador();//Menu administrador(iniciar sesion/registrarse)
void registroAdministrador();//registrarse admin
void inicioAdministrador();//inicio sesion admin
void menuAdministrador();


string nombreUser;
string contraUser;//Para iniciar/registrar usuario


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
sqlite3 *db;//objeto base de datos
char *zErrMsg = 0;
int rc;
char *sql;//sentencia sql
const char *data = "LLamada a Base de datos";

int main(){
	menuInicio();
}

void menuInicio(){
	int opcion;
	do{
		cout<<"----HOTELANDIA------"<<endl;
		cout<<"1. Ingresar como usuario"<<endl;
		cout<<"2. Ingresar como administrador"<<endl;
		cout<<"3. Salir"<<endl;
		cin>>opcion;//Para meterlo por pantalla
	}while (opcion != 1 && opcion != 2 && opcion!=3);

	switch(opcion){
	case 1:{
		usuarioPrincipio();
	}break;
	case 2:{
		administrador();
	}break;
	case 3:{
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		menuInicio();
	}break;
	}
}

void usuarioPrincipio(){
	int opcion;
	do{
		cout<<"1. Iniciar sesion"<<endl;
		cout<<"2. Registrarse"<<endl;
		cout<<"3. Volver atras"<<endl;
		cin>>opcion;
	}while(opcion != 1 && opcion != 2 && opcion != 3);
	switch(opcion){
	case 1:{
		inicioUsuario();//inicio usuarios
	}break;
	case 2:{
		registroUsuario();
	}break;
	case 3:{
		menuInicio();
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		usuarioPrincipio();
	}break;
	}
}

void registroUsuario(){
	cout << "Ingresa el nombre del usuario: ";
	cin >> nombreUser;
	cout << endl;
	cout << "Ingresa la contrase�a del usuario: ";
	cin >> contraUser;
	cout << endl;
	ofstream ofs("usuariosGuardar.txt", ios::app);
	ofs << nombreUser << " " << contraUser << endl;
	ofs.close();
	cout << "Usuario creado correctamente" << endl;
	usuarioPrincipio();
}
void inicioUsuario(){//Todo inicio sesion usuario


	ifstream ifs;
		ifs.open("usuariosGuardar.txt", ios::in);
		string nom, cont, nomAu, conAu;
		bool en = false;
		cout << "Ingrese el nombre del usuario: " << endl;
		cin >> nomAu;
		cout << "Ingrese la contra del usuario: " << endl;
		cin >> conAu;
		ifs >> nom;
		while (!ifs.eof() && !en) {
			ifs >> cont;
			if (nom == nomAu && cont == conAu) {
				cout << "Bienvenido/a " << nomAu
						<< endl;
				en = true;
				system("cls");
				cout<<"---------MODO USUARIO-----"<<endl;
				menuUsuario();
			}
		}




}

void menuUsuario(){

	int opcion;
	do{
	cout<<"Elije las siguientes opciones"<<endl;
	cout<<"1. Ver hoteles"<<endl;
	cout<<"2. Ver habitaciones"<<endl;
	cout<<"3. Ver reserva"<<endl;//Si no tiene mensaje por pantalla
	cout<<"4. Hacer reserva"<<endl;//Solo a su nombre
	cout<<"5. Eliminar reserva"<<endl;
	cout<<"6. Volver al menu principal"<<endl;
	cin>>opcion;
	}while(opcion!= 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 4 && opcion != 5 && opcion !=6);
	/* ABRIMOS BASE DE DATOS */
	rc = sqlite3_open("hotelandia_final.s3db", &db);
	switch(opcion){
	case 1:{
		caso1Usuario();
	}break;
	case 2:{
		caso2Usuario();
	}break;
	case 3:{
		caso3Usuario();
	}break;
	case 4:{
		caso4Usuario();
	}break;
	case 5:{
		caso5Usuario();
	}break;
	case 6:{
		cout<<"Cerrando sesion..."<<endl;
		menuInicio();
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		menuUsuario();
	}break;

	}
}
void caso1Usuario(){
	/* Create SQL statement */
				sql = "SELECT * from HOTEL";

				/* Execute SQL statement */
				rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
				if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				} else {
					//fprintf(stdout, "Operation done successfully\n");
				}
				sqlite3_close(db);
				menuUsuario();
}
void caso2Usuario(){
	/* Create SQL statement */
				sql = "SELECT * from HABITACION";

				/* Execute SQL statement */
				rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
				if (rc != SQLITE_OK) {
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				} else {
					//fprintf(stdout, "Operation done successfully\n");
				}
				sqlite3_close(db);
				menuUsuario();
}
void caso3Usuario(){
	char nom[100];
					cout << "Introduzca su nombre de usuario para ver que reservas tiene" << endl;
					cin >> nom;
					cout << endl;
					/* Create SQL statement */
					//char sql[] = "SELECT USUARIO.nombre_usuario,RESERVA.id_reserva,RESERVA.dia_reserva,RESERVA.hora_reserva FROM RESERVA JOIN USUARIO ON USUARIO.id_usuario = RESERVA.id_usuario WHERE USUARIO.nombre_usuario ='";

					char sql[] = "SELECT USUARIO.nombre_usuario, RESERVA.id_reserva, HABITACION.numero_habitacion,HABITACION.planta_habitacion ,HABITACION.tipo_habitacion, HABITACION.precio_habitacion, HOTEL.nombre_hotel FROM HABITACION JOIN RESERVA_TIENE_HABITACIONES ON RESERVA_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion JOIN RESERVA ON RESERVA.id_reserva = RESERVA_TIENE_HABITACIONES.id_reserva JOIN HOTEL_TIENE_HABITACIONES ON HOTEL_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion JOIN HOTEL ON HOTEL.id_hotel = HOTEL_TIENE_HABITACIONES.id_hotel JOIN USUARIO ON USUARIO.id_usuario = RESERVA.id_usuario WHERE USUARIO.nombre_usuario ='";

					strcat(sql, nom);

					char fr2[] = "'";

					strcat(sql, fr2);

					/* Execute SQL statement */
					rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
					if (rc != SQLITE_OK) {
						fprintf(stderr, "SQL error: %s\n", zErrMsg);
						sqlite3_free(zErrMsg);
					} else {
						//fprintf(stdout, "Operation done successfully\n");
					}//Desea ver que habitaciones estan reservadas??

					cout<<"Las reservas tienen las siguientes habitaciones:"<<endl;
					//char sql[] = "SELECT HABITACION.numero_habitacion,HABITACION.planta_habitacion ,HABITACION.tipo_habitacion, HABITACION.precio_habitacion FROM HABITACION JOIN RESERVA_TIENE_HABITACIONES ON RESERVA_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion AND JOIN  ON RESERVA ON RESERVA.id_reserva = RESERVA_TIENE_HABITACIONES.id_reserva AND JOIN USUARIO ON USUARIO.id_usuario = RESERVA.id_usuario WHERE USUARIO.nombre_usuario ='";
					sqlite3_close(db);
					menuUsuario();
}
void caso4Usuario(){
	int opcion;
	do{
	cout<<"Hotel que quiere hacer la reserva:"<<endl;
	cout<<"1. Hotel Melia"<<endl;
	cout<<"2. Iberostar Hotel"<<endl;
	cout<<"3. Barcelo Hotel"<<endl;
	cout<<"4. Nh Hotel"<<endl;
	cout<<"5. Eurostar Hotel"<<endl;
	cin>>opcion;
	}while(opcion!=1&&opcion!=2&&opcion!=3&&opcion!=4&&opcion!=5);
	char id_res[100],dia_res[100],hora_res[100],id_usuario[100];int opcion1;
	switch(opcion){
	case 1:{//Melia
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora del restaurante que desea anyadir: ";
		cin >> hora_res;
		cout << endl;
		cout << "Ingrese el id de su usuario: ";
		cin >> id_usuario;//Tiene que ser el tuyo-> COMPROBAR!!!
		cout << endl;

		/* Create SQL statement */
		char sql[] = "INSERT INTO RESERVA VALUES (";

		char con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";

		strcat(sql, id_res);
		strcat(sql, con1);
		strcat(sql, dia_res);
		strcat(sql, con2);
		strcat(sql, hora_res);
		strcat(sql, con3);
		strcat(sql, id_usuario);
		strcat(sql, con8);
		strcat(sql, con9);


		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Numero de habitaciones a reservar:\n");
		}
		sqlite3_close(db);

		do{
			cout<<"1. 1 Habitacion"<<endl;
			cout<<"2. 2 Habitaciones"<<endl;
			cout<<"3. 3 Habitaciones"<<endl;
			cin>>opcion1;
		}while(opcion1!=1 && opcion1!=2&&opcion1!=3);
		switch(opcion1){
		case 1:{//1 habitacion
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab[]="1";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 2:{//2 Habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="2", id_hab2[]="6";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}sqlite3_close(db);

			menuUsuario();
		}break;
		case 3:{//3 Habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="3", id_hab2[]="5", id_hab3[]="7";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}	sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql3[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con17[]=",", con18[]=")", con19[]="";
			strcat(sql1,id_res);
			strcat(sql1,con17);
			strcat(sql1,id_hab3);
			strcat(sql1,con18);
			strcat(sql1,con19);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}	sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 3 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		}
		menuUsuario();
	}break;
	case 2:{//Iberosar
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora del restaurante que desea anyadir: ";
		cin >> hora_res;
		cout << endl;
		cout << "Ingrese el id de su usuario: ";
		cin >> id_usuario;//Tiene que ser el tuyo-> COMPROBAR!!!
		cout << endl;

		/* Create SQL statement */
		char sql[] = "INSERT INTO RESERVA VALUES (";

		char con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";

		strcat(sql, id_res);
		strcat(sql, con1);
		strcat(sql, dia_res);
		strcat(sql, con2);
		strcat(sql, hora_res);
		strcat(sql, con3);
		strcat(sql, id_usuario);
		strcat(sql, con8);
		strcat(sql, con9);


		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Numero de habitaciones a reservar:\n");
		}
		sqlite3_close(db);

		do{
			cout<<"1. 1 Habitacion"<<endl;
			cout<<"2. 2 Habitaciones"<<endl;
			cout<<"3. 3 Habitaciones"<<endl;
			cin>>opcion1;
		}while(opcion1!=1 && opcion1!=2&&opcion1!=3);
		switch(opcion1){
		case 1:{//1 habitacion
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab[]="13";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la habitacion\n");
			}
			sqlite3_close(db);
					menuUsuario();
		}break;
		case 2:{//2 habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="9", id_hab2[]="10";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();

		}break;
		case 3:{//3 habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="4", id_hab2[]="7", id_hab3[]="12";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql3[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con17[]=",", con18[]=")", con19[]="";
			strcat(sql1,id_res);
			strcat(sql1,con17);
			strcat(sql1,id_hab3);
			strcat(sql1,con18);
			strcat(sql1,con19);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 3 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		}

	}break;
	case 3:{//Barcelo
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora del restaurante que desea anyadir: ";
		cin >> hora_res;
		cout << endl;
		cout << "Ingrese el id de su usuario: ";
		cin >> id_usuario;//Tiene que ser el tuyo-> COMPROBAR!!!
		cout << endl;

		/* Create SQL statement */
		char sql[] = "INSERT INTO RESERVA VALUES (";

		char con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";

		strcat(sql, id_res);
		strcat(sql, con1);
		strcat(sql, dia_res);
		strcat(sql, con2);
		strcat(sql, hora_res);
		strcat(sql, con3);
		strcat(sql, id_usuario);
		strcat(sql, con8);
		strcat(sql, con9);


		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Numero de habitaciones a reservar:\n");
		}sqlite3_close(db);

		do{
			cout<<"1. 1 Habitacion"<<endl;
			cout<<"2. 2 Habitaciones"<<endl;
			cout<<"3. 3 Habitaciones"<<endl;
			cin>>opcion1;
		}while(opcion1!=1 && opcion1!=2&&opcion1!=3);
		switch(opcion1){
		case 1:{//1 Habitacion
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab[]="20";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";//Repetir este proceso * numero de habitas
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 2:{
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="16", id_hab2[]="17";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 3:{
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="19", id_hab2[]="17", id_hab3[]="15";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql3[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con17[]=",", con18[]=")", con19[]="";
			strcat(sql1,id_res);
			strcat(sql1,con17);
			strcat(sql1,id_hab3);
			strcat(sql1,con18);
			strcat(sql1,con19);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 3 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		}
	}break;
	case 4:{//Nh
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora del restaurante que desea anyadir: ";
		cin >> hora_res;
		cout << endl;
		cout << "Ingrese el id de su usuario: ";
		cin >> id_usuario;//Tiene que ser el tuyo-> COMPROBAR!!!
		cout << endl;

		/* Create SQL statement */
		char sql[] = "INSERT INTO RESERVA VALUES (";

		char con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";

		strcat(sql, id_res);
		strcat(sql, con1);
		strcat(sql, dia_res);
		strcat(sql, con2);
		strcat(sql, hora_res);
		strcat(sql, con3);
		strcat(sql, id_usuario);
		strcat(sql, con8);
		strcat(sql, con9);


		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Numero de habitaciones a reservar:\n");
		}sqlite3_close(db);

		do{
			cout<<"1. 1 Habitacion"<<endl;
			cout<<"2. 2 Habitaciones"<<endl;
			cout<<"3. 3 Habitaciones"<<endl;
			cin>>opcion1;
		}while(opcion1!=1 && opcion1!=2&&opcion1!=3);
		switch(opcion1){
		rc = sqlite3_open("hotelandia_final.s3db", &db);
		case 1:{//1 Habitacion
			char id_hab[]="12";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";//Repetir este proceso * numero de habitas
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva realizada\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 2:{//2 habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="11", id_hab2[]="9";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 3:{//3 Habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="8", id_hab2[]="6", id_hab3[]="15";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql3[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con17[]=",", con18[]=")", con19[]="";
			strcat(sql1,id_res);
			strcat(sql1,con17);
			strcat(sql1,id_hab3);
			strcat(sql1,con18);
			strcat(sql1,con19);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 3 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		}
	}break;
	case 5:{//EuroStar
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora del restaurante que desea anyadir: ";
		cin >> hora_res;
		cout << endl;
		cout << "Ingrese el id de su usuario: ";
		cin >> id_usuario;//Tiene que ser el tuyo-> COMPROBAR!!!
		cout << endl;

		/* Create SQL statement */
		char sql[] = "INSERT INTO RESERVA VALUES (";

		char con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";

		strcat(sql, id_res);
		strcat(sql, con1);
		strcat(sql, dia_res);
		strcat(sql, con2);
		strcat(sql, hora_res);
		strcat(sql, con3);
		strcat(sql, id_usuario);
		strcat(sql, con8);
		strcat(sql, con9);


		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Numero de habitaciones a reservar:\n");
		}sqlite3_close(db);

		do{
			cout<<"1. 1 Habitacion"<<endl;
			cout<<"2. 2 Habitaciones"<<endl;
			cout<<"3. 3 Habitaciones"<<endl;
			cin>>opcion1;
		}while(opcion1!=1 && opcion1!=2&&opcion1!=3);
		switch(opcion1){
		case 1:{//1 habitacion
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab[]="10";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";//Repetir este proceso * numero de habitas
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva realizada\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 2:{//2 habitaciones
			char id_hab1[]="7", id_hab2[]="2";
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		case 3:{//3 habitaciones
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char id_hab1[]="9", id_hab2[]="5", id_hab3[]="8";
			char sql1[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con11[]=",", con12[]=")", con13[]="";
			strcat(sql1,id_res);
			strcat(sql1,con11);
			strcat(sql1,id_hab1);
			strcat(sql1,con12);
			strcat(sql1,con13);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 1 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql3[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con17[]=",", con18[]=")", con19[]="";
			strcat(sql1,id_res);
			strcat(sql1,con17);
			strcat(sql1,id_hab3);
			strcat(sql1,con18);
			strcat(sql1,con19);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 2 habitacion\n");
			}sqlite3_close(db);
			rc = sqlite3_open("hotelandia_final.s3db", &db);
			char sql2[] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
			char con14[]=",", con15[]=")", con16[]="";
			strcat(sql1,id_res);
			strcat(sql1,con14);
			strcat(sql1,id_hab2);
			strcat(sql1,con15);
			strcat(sql1,con16);
			/* Execute SQL statement */
			rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			} else {
				fprintf(stdout, "Reserva de la 3 habitacion\n");
			}
			sqlite3_close(db);
			menuUsuario();
		}break;
		}
	}break;

	}
}
void caso5Usuario(){
	char nom[100];
	cout << "Introduzca su nombre de usuario para ver que reservas tiene" << endl;
						cin >> nom;
						cout << endl;
						/* Create SQL statement */
						char sql[] = "SELECT USUARIO.nombre_usuario, RESERVA.id_reserva, HABITACION.numero_habitacion,HABITACION.planta_habitacion ,HABITACION.tipo_habitacion, HABITACION.precio_habitacion, HOTEL.nombre_hotel FROM HABITACION JOIN RESERVA_TIENE_HABITACIONES ON RESERVA_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion JOIN RESERVA ON RESERVA.id_reserva = RESERVA_TIENE_HABITACIONES.id_reserva JOIN HOTEL_TIENE_HABITACIONES ON HOTEL_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion JOIN HOTEL ON HOTEL.id_hotel = HOTEL_TIENE_HABITACIONES.id_hotel JOIN USUARIO ON USUARIO.id_usuario = RESERVA.id_usuario WHERE USUARIO.nombre_usuario ='";
						//ARREGLAR ESTA SENTENCIA

						strcat(sql, nom);

						char fr2[] = "'";

						strcat(sql, fr2);

						/* Execute SQL statement */
						rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
						if (rc != SQLITE_OK) {
							fprintf(stderr, "SQL error: %s\n", zErrMsg);
							sqlite3_free(zErrMsg);
						} else {
							fprintf(stdout, "Estas son las reservas que contiene el usuario introducido\n");}
							char nom1[100];
								cout << "Ingrese el numero de la reserva que desea eliminar " << endl;
								cin >> nom1;
								cout << endl;
								/* Create SQL statement */
								char sql1[] = "DELETE from RESERVA WHERE ID_RESERVA= ";

								strcat(sql1, nom1);

								char fr3[] = "";

								strcat(sql1, fr3);

								/* Execute SQL statement */
								rc = sqlite3_exec(db, sql1, callback, (void*) data, &zErrMsg);
								if (rc != SQLITE_OK) {
									fprintf(stderr, "SQL error: %s\n", zErrMsg);
									sqlite3_free(zErrMsg);
								} else {
									fprintf(stdout, "Reserva eliminada\n");
								}

									/* Create SQL statement */
									char sql2[] = "DELETE from RESERVA_TIENE_HABITACIONES WHERE ID_RESERVA= ";

									strcat(sql2, nom1);

									char fr4[] = "";

									strcat(sql2, fr4);

									/* Execute SQL statement */
									rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
									if (rc != SQLITE_OK) {
										fprintf(stderr, "SQL error: %s\n", zErrMsg);
										sqlite3_free(zErrMsg);
									} else {
										//fprintf(stdout, "Reserva eliminada\n");
									}


								sqlite3_close(db);
								menuUsuario();
}
void administrador(){
	int opcion;
	do{
		cout<<"1. Registrarse"<<endl;//METODO QUE REGISTRE AL USUARIO
		cout<<"2. Iniciar sesion"<<endl;//METODO QUE COMPRUEBE QUE EL USUARIO EXISTE
		cout<<"3. Volver atras"<<endl;
		cin>>opcion;
	}while(opcion != 1 && opcion != 2 && opcion != 3);
	switch(opcion){
	case 1:{
		registroAdministrador();//registro administrador
	}break;
	case 2:{
		inicioAdministrador();//inicio sesion administrador
	}break;
	case 3:{
		menuInicio();
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		administrador();
	}
	}
}

void registroAdministrador(){//Todo registrarse admin
	cout << "Ingresa el nombre del administrador: ";
	cin >> nombreUser;
	cout << endl;
	cout << "Ingresa la contrase�a del administrador: ";
	cin >> contraUser;
	cout << endl;
	ofstream ofs("administradorGuardar.txt", ios::app);
	ofs << nombreUser << " " << contraUser << endl;
	ofs.close();
	cout << "Usuario creado correctamente" << endl;
	administrador();

}
void inicioAdministrador(){//Todo inicio sesion admin
	ifstream ifs;
		ifs.open("administradorGuardar.txt", ios::in);
		string nom, cont, nomAu, conAu;
		bool en = false;
		cout << "Ingrese el nombre del administrador: " << endl;
		cin >> nomAu;
		cout << "Ingrese la contra del administrador: " << endl;
		cin >> conAu;
		ifs >> nom;
		while (!ifs.eof() && !en) {
			ifs >> cont;
			if (nom == nomAu && cont == conAu) {
				cout << "Bienvenido/a " << nomAu
						<< endl;
				en = true;
				system("cls");
				cout<<"---------MODO USUARIO-----"<<endl;
				administrador();
			}
		}

	//OPCIONES DE ADMINISTRADOR: CREAR HABITACI�N, ELIMINAR HABITACION, LISTAR HABITACIONES, LISTAR RESERVAS, ELIMINAR RESERVAS
}
void menuAdministrador(){

}

bool comprobarUsuario(char *usuario, char *contrasenya){

	FILE *f;

	f = fopen("Usuarios.txt", "r");

	int counter = 0;
	char linea;

	for (linea = getc(f); linea != EOF; linea = getc(f))
		if (linea == '\n') // Increment count if this character is newline
			counter = counter + 1;

	fclose(f);

	f = fopen("Usuarios.txt", "r");

	char *ptr;
	char c[256];

	int c_nombres = 0;
	char **nombres;

	nombres = (char**) malloc(counter * sizeof(char*));

	int q;
	for (q = 0; q < counter; q++) {

		nombres[q] = (char*) malloc(16 * sizeof(char));

	}

	while (fgets(c, sizeof(c), f)) {

		ptr = strtok(c, ";");

		ptr = strtok(ptr, ":");

		//printf("%s\n", ptr);
		while (ptr != NULL) {

			ptr = strtok(NULL, ":");

			//printf("%s\n", ptr);
			if (ptr != NULL) {

			//	printf("valor de i %i\n", c_nombres);
				strcpy(nombres[c_nombres], ptr);

			//	printf("Usuario guardado %s\n", nombres[c_nombres]);

			}
		}
		c_nombres++;

	}

	fclose(f);

	f = fopen("Usuarios.txt", "r");

	char **contrasenya1;

	contrasenya1 = (char**) malloc(counter * sizeof(char*));

	int h;
	for (q = 0; h < counter; h++) {

		contrasenya1[h] = (char*) malloc(16 * sizeof(char));

	}

	char *ctr;

	int c_contrasenya = 0;

	while (fgets(c, sizeof(c), f)) {

		//printf("Prueba %s", c);

		ctr = strtok(c, ";");

		//printf("Contrase�a1 %s\n", ctr);
		while (ctr != NULL) {

			//	printf("Contras�a2 %s\n", ctr);

			ctr = strtok(NULL, ";");

			//	printf("cotrase�a3 %s\n", ctr);

			if (ctr != NULL) {

				const char ch = ':';
				char *ret;

				ret = strchr(ctr, ch);

				//  printf("String after |%c| is - |%s|\n", ch, ret + 1);

				strcpy(contrasenya1[c_contrasenya], ret + 1);

			}
			ctr = NULL;
		}

		c_contrasenya++;

	}

	int j = 0;

	while (j < counter) {

	//	printf("El usuario a comporbar es %s y el de el array  %s y la contra a buscar es %s y la contrra es %s\n", usuario, nombres[j], contrasenya, contrasenya1[j]);

		if (0 == strcmp(usuario, nombres[j])
				&& 0 == strcmp(contrasenya, contrasenya1[j])) {

			cout<<"El usuario y la contrase�a son correctos\n"<<endl;

			free(nombres[j]);
			free(contrasenya1[j]);

			fclose(f);

			return true;

		}

		j++;

	}

	cout<<"El usuario y la contrase�a no coinciden\n"<<endl;


	return false;

	fclose(f);


}
//	sqlite3 *db;
//	int res;
//
//	char palabra[] = "prueba.s3db";
//
//	res = sqlite3_open(palabra , &db);
//
//	char nombre[10], contra[10];
//	int intentos=0;
//
//			else if ((nom == nomAu && cont != conAu) || (nom != nomAu && cont == conAu)){
//				cout << "Usuario o contrasenya introducidos son incorrectos" << endl;
//				inicioUsuario();
//			}
//			ifs >> nom;
//		}
//		ifs.close();
//
//		if (!en) {
//			cout << "El usuario introducido no existe" << endl;
//			inicioUsuario();
//		}

//	char nombre[10], contra[10];
//	int intentos=0;
//
//	do{
//
//	cout<<"Introduce el nombre de usuario"<<endl;
//	fgets(nombre, 10, stdin);
//	//cin>>nombre;
//	cout<<"Introduce la contrase�a"<<endl;
//	fgets(contra, 10, stdin);
//	Usuario u;
//	intentos++;
//	}while(!comprobarUsuario(nombre, contra)||intentos==3);
//	if(comprobarUsuario(nombre, contra)){
//		menuUsuario();
//	}else{
//		cout<<"has superado el numero de intentos"<<endl;
//		menuInicio();
//	}
//	//FALTA LA LECTURA DE USUARIOS QUE HABRA QUE LEERLA DESDE EL FICHERO
