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
void inicioUsuario();//inicio sesion usuario
bool comprobarUsuario(char *usuario, char *contrasenya);
void menuUsuario();

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
	int intentos=0;

	do{

	cout<<"Introduce el nombre de usuario"<<endl;
	fgets(nombre, 10, stdin);
	//cin>>nombre;
	cout<<"Introduce la contraseña"<<endl;
	fgets(contra, 10, stdin);
	Usuario u;
	intentos++;
	}while(!comprobarUsuario(nombre, contra)||intentos==3);
	if(comprobarUsuario(nombre, contra)){
		menuUsuario();
	}else{
		cout<<"has superado el numero de intentos"<<endl;
		menuInicio();
	}
	//FALTA LA LECTURA DE USUARIOS QUE HABRA QUE LEERLA DESDE EL FICHERO


}

void menuUsuario(){

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

		//printf("Contraseña1 %s\n", ctr);
		while (ctr != NULL) {

			//	printf("Contrasña2 %s\n", ctr);

			ctr = strtok(NULL, ";");

			//	printf("cotraseña3 %s\n", ctr);

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

			cout<<"El usuario y la contraseña son correctos\n"<<endl;

			free(nombres[j]);
			free(contrasenya1[j]);

			fclose(f);

			return true;

		}

		j++;

	}

	cout<<"El usuario y la contraseña no coinciden\n"<<endl;


	return false;

	fclose(f);


}
