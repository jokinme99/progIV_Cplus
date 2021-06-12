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


void inicio();//inicio sesion usuario
void menuUsuario();
void caso1Usuario();
void caso2Usuario();
void caso3Usuario();
void caso4Usuario();
void caso5Usuario();

void caso1Admin();
void caso2Admin();
void caso3Admin();
void caso4Admin();
void caso5Admin();
void caso6Admin();
void caso7Admin();
void caso8Admin();
void caso9Admin();

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
	inicio();

}

void inicio(){

		cout<<"----HOTELANDIA------"<<endl;
		ifstream ifs;
		ifs.open("../progIV_Cplus/Usuarios.txt", ios::in);
		string nom, cont, nomAu, conAu;
		bool en = false;
		cout << "Ingrese el nombre del usuario: " << endl;
		cin >> nomAu;
		cout << "Ingrese la contra del usuario: " << endl;
		cin >> conAu;

		while (!ifs.eof() && !en) {

			ifs >> nom;
			//ifs >> cont;
			//	cout<<nom<<"\n"<<cont<<endl;
			cout<<nom<<endl;




			if (nom == nomAu && cont == conAu) {
				cout << "Usuario y contrasenya correctos. Bienvenido " << nomAu<< endl;
				en = true;
				//parte del usuario
				system("cls");
				cout << "---MODO USUARIO---" << endl;
				menuUsuario();
				ifs.close();
			}if(nom != nomAu&&ifs.eof()){
				cout<<"El usuario no existe!"<<endl;
				//usuarioPrincipio();
				ifs.close();

			}

			else if ((nom == nomAu && cont != conAu)){
					cout << "Contrasenya incorrecta" << endl;
					//usuarioPrincipio();
					ifs.close();

				}


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
		//menuInicio();
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

					char sql[] = "SELECT DISTINCT USUARIO.nombre_usuario, RESERVA.id_reserva, HABITACION.numero_habitacion,HABITACION.planta_habitacion ,HABITACION.tipo_habitacion, HABITACION.precio_habitacion, HOTEL.nombre_hotel FROM HABITACION JOIN RESERVA_TIENE_HABITACIONES ON RESERVA_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion JOIN RESERVA ON RESERVA.id_reserva = RESERVA_TIENE_HABITACIONES.id_reserva JOIN HOTEL_TIENE_HABITACIONES ON HOTEL_TIENE_HABITACIONES.id_habitacion = HABITACION.id_habitacion JOIN HOTEL ON HOTEL.id_hotel = HOTEL_TIENE_HABITACIONES.id_hotel JOIN USUARIO ON USUARIO.id_usuario = RESERVA.id_usuario WHERE USUARIO.nombre_usuario ='";

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
			fprintf(stdout, "Reserva realizada:\n");
		}
		sqlite3_close(db);
		menuUsuario();
	}break;
	case 2:{//Iberosar
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora la reserva que desea anyadir: ";
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
			fprintf(stdout, "Reserva realizada:\n");
		}
		sqlite3_close(db);
		menuUsuario();
	}break;
	case 3:{//Barcelo
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora de la reserva que desea anyadir: ";
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
			fprintf(stdout, "Reserva realizada:\n");
		}sqlite3_close(db);
		menuUsuario();


	}break;
	case 4:{//Nh
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora de la reserva que desea anyadir: ";
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
			fprintf(stdout, "Reserva realizada:\n");
		}sqlite3_close(db);
		menuUsuario();


	}break;
	case 5:{//EuroStar
		cout << "Ingrese el id de la reserva que desea anyadir: ";
		cin >> id_res;
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia_res;
		cout << endl;
		cout << "Ingrese la hora de la reserva que desea anyadir: ";
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
			fprintf(stdout, "Reserva realizada:\n");
		}sqlite3_close(db);
		menuUsuario();

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

void menuAdministrador(){

	int opcion;
	do{
	cout<<"Elije las siguientes opciones"<<endl;
	cout<<"1. Ver habitaciones"<<endl;
	cout<<"2. Crear habitacion"<<endl;
	cout<<"3. Eliminar habitaciones"<<endl;//Si no tiene mensaje por pantalla
	cout<<"4. Ver reservas"<<endl;//Solo a su nombre
	cout<<"5. crear reservas"<<endl;//Solo a su nombre
	cout<<"6. Eliminar reserva"<<endl;
	cout<<"7. Ver trabajadores"<<endl;
	cout<<"8. Crear trabajadores"<<endl;
	cout<<"9. Eliminar trabajadores"<<endl;
	cout<<"10. Volver al menu principal"<<endl;
	cin>>opcion;
	}while(opcion< 1 || opcion >10);
	/* ABRIMOS BASE DE DATOS */
	rc = sqlite3_open("hotelandia_final.s3db", &db);
	switch(opcion){
	case 1:{
		caso1Admin();
	}break;
	case 2:{
		caso2Admin();
	}break;
	case 3:{
		caso3Admin();
	}break;
	case 4:{
		caso4Admin();
	}break;
	case 5:{
		caso5Admin();
	}break;
	case 6:{
		caso6Admin();
	}break;
	case 7:{
		caso7Admin();
	}break;
	case 8:{
		caso8Admin();
	}break;
	case 9:{
		caso9Admin();
	}break;
	case 10:{
		cout<<"Cerrando sesion..."<<endl;
		//menuInicio();
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		menuUsuario();
	}break;

	}

//OPCIONES DE ADMINISTRADOR: CREAR HABITACIÓN, ELIMINAR HABITACION, LISTAR HABITACIONES, LISTAR RESERVAS, ELIMINAR RESERVAS
}
void caso1Admin(){
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
	menuAdministrador();
}
void caso2Admin(){

	char idhab[100], nHab[100], nPlant[100], Prec[100],tipoHab[100];



	cout<<"introduce el id de habitacion"<<endl;

	cin >> idhab;

	cout<<"introduce el numero de habitacion"<<endl;

	cin >> nHab;

	cout<<"introduce el numero de planta de la habitacion"<<endl;

	cin >> nPlant;

	cout<<"introduce el tipo de habitacion"<<endl;

	cin >> tipoHab;


	cout<<"introduce el precio de la habitacion"<<endl;

	cin >> Prec;

	cout<<"TIRA"<<endl;


	char sql[200] = "INSERT INTO HABITACION VALUES (";


	cout<<"TIRA2"<<endl;

	char con1[] = ",", con2[] = ",", con3[] = "," , con4[] = "," , con8[] = ")", con9[] = "";


	strcat(sql, idhab);
	strcat(sql, con1);
	strcat(sql, nHab);
	strcat(sql, con2);
	strcat(sql, nPlant);
	strcat(sql, con3);

	strcat(sql, "'");

	strcat(sql, tipoHab);

	strcat(sql, "'");




	strcat(sql, con4);
	strcat(sql, Prec);
	strcat(sql, con8);
	strcat(sql, con9);



	cout<<sql<<endl;

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	menuAdministrador();


}
void caso3Admin(){
	char idhab[100];

	cout<<"introduce el id de habitacion para eliminarlo"<<endl;

	cin >> idhab;


	char sql[200] = "DELETE from HOTEL_TIENE_HABITACIONES WHERE id_habitacion = ";

	strcat(sql, idhab);

	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");

	}
	char sql2[200] = "DELETE from RESERVA_TIENE_HABITACIONES WHERE id_habitacion =";

	strcat(sql2, idhab);

	rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");

	}
	char sql3[200] = "DELETE from HABITACION WHERE id_habitacion =";

	strcat(sql3, idhab);

	cout<<sql3<<endl;


	rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}


	sqlite3_close(db);
	menuAdministrador();

}
void caso4Admin(){
	char sql[] = "SELECT * from RESERVA";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	menuAdministrador();
}
void caso5Admin(){
	char id_res[100],dia_res[100],hora_res[100],id_usuario[100]; int opcion1;

	cout << "Ingrese el id de la reserva que desea anyadir: ";
	cin >> id_res;
	cout << endl;
	cout << "Ingrese el dia de la reserva que desea anyadir: ";
	cin >> dia_res;
	cout << endl;
	cout << "Ingrese la hora de la reserva que desea anyadir: ";
	cin >> hora_res;
	cout << endl;
	cout << "Ingrese el id del usuario: ";
	cin >> id_usuario;
	cout << endl;

	/* Create SQL statement */
	char sql[200] = "INSERT INTO RESERVA VALUES (";

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

	cout<<id_usuario<<endl;

	cout<<sql<<endl;
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
		char id_hab[5];

		cout << "Ingrese el id de la habitación: ";

		cin >> id_hab;

		char sql1[200] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
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
		menuAdministrador();
	}break;
	case 2:{//2 Habitaciones
		rc = sqlite3_open("hotelandia_final.s3db", &db);
		char id_hab1[5], id_hab2[5];

		cout << "Ingrese el id de la habitación1: ";

		cin >> id_hab1;

		cout << "Ingrese el id de la habitación2: ";

		cin >> id_hab2;

		char sql1[200] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
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
		char sql2[200] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
		char con14[]=",", con15[]=")", con16[]="";
		strcat(sql2,id_res);
		strcat(sql2,con14);
		strcat(sql2,id_hab2);
		strcat(sql2,con15);
		strcat(sql2,con16);
		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Reserva de la 2 habitacion\n");
		}sqlite3_close(db);

		menuAdministrador();
	}break;
	case 3:{//3 Habitaciones
		rc = sqlite3_open("hotelandia_final.s3db", &db);
		char id_hab1[5], id_hab2[5], id_hab3[5];



		cout << "Ingrese el id de la habitación 1: ";

		cin >> id_hab1;

		cout << "Ingrese el id de la habitación 2: ";

		cin >> id_hab2;

		cout << "Ingrese el id de la habitación 3: ";

		cin >> id_hab3;

		char sql1[200] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
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
		char sql2[200] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
		char con17[]=",", con18[]=")", con19[]="";
		strcat(sql2,id_res);
		strcat(sql2,con17);
		strcat(sql2,id_hab3);
		strcat(sql2,con18);
		strcat(sql2,con19);
		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Reserva de la 2 habitacion\n");
		}	sqlite3_close(db);
		rc = sqlite3_open("hotelandia_final.s3db", &db);
		char sql3[200] = "INSERT INTO RESERVA_TIENE_HABITACIONES VALUES(";
		char con14[]=",", con15[]=")", con16[]="";
		strcat(sql3,id_res);
		strcat(sql3,con14);
		strcat(sql3,id_hab2);
		strcat(sql3,con15);
		strcat(sql3,con16);
		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql3, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Reserva de la 3 habitacion\n");
		}
		sqlite3_close(db);
		menuAdministrador();
	}break;
	}
	menuAdministrador();

}
void caso6Admin(){


	char idres[100];

	cout<<"introduce el id de la reserva para eliminarlo"<<endl;

	cin >> idres;


	char sql[200] = "DELETE from RESERVA_TIENE_HABITACIONES WHERE id_reserva = ";

	strcat(sql, idres);

	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");

	}
	char sql2[200] = "DELETE from RESERVA WHERE id_reserva =";

	strcat(sql2, idres);

	rc = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");

	}



	sqlite3_close(db);
	menuAdministrador();



}
void caso7Admin(){

	cout<<"hola ktal holakpasaktal"<<endl;


	char sql[] = "select * from TRABAJADOR";

	cout<<sql<<endl;
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	menuAdministrador();

}

void caso8Admin(){

	char idtr[100], ntr[100], dnitr[100], tfntr[100],sldtr[100], idhotel[100];

	cout << "Ingrese el id del trabajador: ";
	cin >> idtr;
	cout << endl;
	cout << "Ingrese el nombre del trabajador: ";
	cin >> ntr;
	cout << endl;
	cout << "Ingrese el dni del trabajador: ";
	cin >> dnitr;
	cout << endl;
	cout << "Ingrese el telefono del trabajador: ";
	cin >> tfntr;
	cout << endl;
	cout << "Ingrese el salario del trabajador: ";
	cin >> sldtr;
	cout << endl;
	cout << "Ingrese el hotel en el que trabaja el trabajador: ";
	cin >> idhotel;
	cout << endl;

	char sql[200] = "INSERT INTO TRABAJADOR VALUES(";
	char con11[]=",", con12[]=")", con13[]="";
	strcat(sql,idtr);
	strcat(sql,con11);
	strcat(sql,ntr);
	strcat(sql,con11);
	strcat(sql,dnitr);
	strcat(sql,con11);
	strcat(sql,tfntr);
	strcat(sql,con11);
	strcat(sql,sldtr);
	strcat(sql,con11);
	strcat(sql,idhotel);
	strcat(sql,con12);
	strcat(sql,con13);

	cout<<sql<<endl;
	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Numero de habitaciones a reservar:\n");
	}
	sqlite3_close(db);
	menuAdministrador();



}
void caso9Admin(){

	char idtr[100];

	cout<<"introduce el id del trabajador para eliminarlo"<<endl;

	cin >> idtr;


	char sql[200] = "DELETE from TRABAJADOR WHERE id_trabajador = ";

	strcat(sql, idtr);

	rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");

	}

	sqlite3_close(db);
	menuAdministrador();

}
