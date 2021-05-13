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
//#include "sqlite/sqlite3.h" //include para base de datos
//#include <sqlite3.h> //include para base de datos

#include "data/Habitacion.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "data/Hotel.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "data/Reserva.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "data/Trabajador.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
#include "data/Usuario.h"//Para acceder a los distintos metodos y poder ver/editar/eliminar datos de la base de datos
using namespace std;
using namespace data;
void menuInicio();

void usuario();//Menu usuario(iniciar sesion/registrarse)
void registroUsuario();//registrarse usuario
void inicioUsuario();//inicio sesion usuario


void administrador();//Menu administrador(iniciar sesion/registrarse)
void registroAdministrador();//registrarse admin
void inicioAdministrador();//inicio sesion admin

////Metodo para utilizar la base de datos
//static int callback(void *data, int argc, char **argv, char **azColName) {
//	int i;
//	fprintf(stderr, "%s: ", (const char*) data);
//
//	for (i = 0; i < argc; i++) {
//		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//	}
//
//	printf("\n");
//	return 0;
//}
//sqlite3 *db;//objeto base de datos
//char *zErrMsg = 0;
//int rc;
//char *sql;//sentencia sql
//const char *data = "Callback function called";

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
		//system("cls");
		usuario();
	}break;
	case 2:{
		system("cls");
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

void usuario(){
	int opcion;
	do{
		cout<<"1. Iniciar sesion"<<endl;
		cout<<"2. Volver atras"<<endl;
		cin>>opcion;
	}while(opcion != 1 && opcion != 2);
	switch(opcion){
	case 1:{
		inicioUsuario();//inicio usuarios
	}break;
	case 2:{
		menuInicio();
	}break;
	default:{
		cout<<"Introduzca un valor correcto"<<endl;
		usuario();
	}
	}
}


void inicioUsuario(){//Todo inicio sesion usuario

	char nombre[10], contra[10];

	fgets(nombre, 10, stdin);

	cout<<"Introduce el nombre de usuario"<<endl;
	fgets(nombre, 10, stdin);
	//cin>>nombre;
	cout<<"Introduce la contraseña"<<endl;
	fgets(contra, 10, stdin);

	//FALTA LA LECTURA DE USUARIOS QUE HABRA QUE LEERLA DESDE EL FICHERO


}

void administrador(){
	int opcion;
	do{
		cout<<"1. Registrarse"<<endl;
		cout<<"2. Iniciar sesion"<<endl;
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
	//Despues de registrarse llevar a menu de opciones de admin
}
void inicioAdministrador(){//Todo inicio sesion admin
	//Despues de iniciar sesion llevar a menu de opciones de admin
}

