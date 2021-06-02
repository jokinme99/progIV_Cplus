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
//#include <sqlite3.h> //include para base de datos
#include <fstream>
#include <windows.h>

#include "Habitacion.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Hotel.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Reserva.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Trabajador.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "Usuario.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos


using namespace std;

void menuInicio();

void usuarioPrincipio();//Menu usuario(iniciar sesion/registrarse)
void inicioUsuario();//inicio sesion usuario
void registroUsuario();
void menuUsuario();
void caso1Usuario();
void caso2Usuario();
void caso3Usuario();
void caso4Usuario();
void caso5Usuario();

void administradorPrincipio();//Menu administrador(iniciar sesion/registrarse)
void registroAdministrador();//registrarse admin
void inicioAdministrador();//inicio sesion admin
void menuAdministrador();


string nombreUser;
string contraUser;//Para iniciar/registrar usuario
sqlite3 *db;//objeto base de datos
char *zErrMsg = 0;
int rc;
char *sql;//sentencia sql
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
		administradorPrincipio();
	}break;
	case 3:{
		system("exit");
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
	ifstream ifs;
	ifs.open("usuariosGuardar.txt", ios::in);
	string nom, cont, nomAu, conAu, line;
	bool en = false;
	cout << "Ingrese el nombre del usuario: " << endl;
	cin >> nomAu;
	cout << "Ingrese la contrasenya del usuario: " << endl;
	cin >> conAu;
	ifs >> nom;
	while (!ifs.eof() && !en) {
		ifs >> cont;
		getline(ifs,line);

		cout << line<< '\n';

		if (nom == nomAu) {
			cout << "El usuario introducido ya existe! " << nomAu<< endl;
			en = true;
			usuarioPrincipio();
			ifs.close();

		}if(nom != nomAu){
			ifs.close();
			ofstream ofs("usuariosGuardar.txt", ios::app);
			ofs << nomAu << " " << conAu << endl;
			ofs.close();
			cout << "Usuario creado correctamente" << endl;
			usuarioPrincipio();
		}
	}ifs.close();
}

void inicioUsuario(){


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
				cout << "Usuario y contrasenya correctos. Bienvenido " << nomAu<< endl;
				en = true;
				//parte del usuario
				system("cls");
				cout << "---MODO USUARIO---" << endl;
				menuUsuario();
				ifs.close();
			}if(nom != nomAu){
				cout<<"El usuario no existe!"<<endl;
				usuarioPrincipio();
				ifs.close();

			}

			else if ((nom == nomAu && cont != conAu) || (nom != nomAu && cont == conAu)){
					cout << "Contrasenya incorrecta" << endl;
					usuarioPrincipio();
					ifs.close();

				}
				ifs >> nom;

			}
		ifs.close();

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
				menuUsuario();
}

void caso2Usuario(){
	/* Create SQL statement */
				char sql[] = "SELECT * from HABITACION";

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
									char sql2[] = "DELETE * from RESERVA_TIENE_HABITACIONES WHERE ID_RESERVA= ";

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

void administradorPrincipio(){
	int opcion;
	do{
		cout<<"1. Registrarse"<<endl;
		cout<<"2. Iniciar sesion"<<endl;
		cout<<"3. Volver atras"<<endl;
		cin>>opcion;
	}while(opcion != 1 && opcion != 2 && opcion != 3);
	switch(opcion){
	case 1:{
		registroAdministrador();
	}break;
	case 2:{
		inicioAdministrador();
	}break;
	case 3:{
		menuInicio();
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		administradorPrincipio();
	}
	}
}

void registroAdministrador(){
	ifstream ifs;
	ifs.open("administradorGuardar.txt", ios::in);
	string nom, cont, nomAu, conAu;
	bool en = false;
	cout << "Ingrese el nombre del admin: " << endl;
	cin >> nomAu;
	cout << "Ingrese la contrasenya del admin: " << endl;
	cin >> conAu;
	ifs >> nom;
	while (!ifs.eof() && !en) {
		ifs >> cont;
		if (nom == nomAu) {
			cout << "El admin introducido ya existe! " << nomAu<< endl;
			en = true;
			administradorPrincipio();
			ifs.close();

		}if(nom != nomAu){
			ifs.close();
			ofstream ofs("administradorGuardar.txt", ios::app);
			ofs << nomAu << " " << conAu << endl;
			ofs.close();
			cout << "Administrador creado correctamente" << endl;
			administradorPrincipio();
		}
	}ifs.close();
}

void inicioAdministrador(){

	ifstream ifs;
		ifs.open("administradorGuardar.txt", ios::in);
		string nom, cont, nomAu, conAu;
		bool en = false;
		cout << "Ingrese el nombre del administrador: " << endl;
		cin >> nomAu;
		cout << "Ingrese la contra del administrador: " << endl;
		cin >> conAu;

		while (!ifs.eof() && !en) {
			ifs >> nom;
			ifs >> cont;

			cout <<nom<<" "<<cont<<endl;

			if (nom == nomAu && cont == conAu) {
				cout << "Administrador y contrasenya correctos. Bienvenido " << nomAu << endl;
				en = true;
				//parte del usuario
				system("cls");
				cout << "---MODO ADMINISTRADOR---" << endl;
				menuAdministrador();
				ifs.close();
			}if(nom != nomAu && ifs.eof()){
				cout<<"El administrador no existe!"<<endl;
				administradorPrincipio();
				ifs.close();

			}

			else if ((nom == nomAu && cont != conAu) || (nom != nomAu && cont == conAu)){
					cout << "Contrasenya incorrecta" << endl;
					administradorPrincipio();
					ifs.close();

				}
				ifs >> nom;

			}
		ifs.close();

}

void menuAdministrador(){
//OPCIONES DE ADMINISTRADOR: CREAR HABITACIÓN, ELIMINAR HABITACION, LISTAR HABITACIONES, LISTAR RESERVAS, ELIMINAR RESERVAS
}
