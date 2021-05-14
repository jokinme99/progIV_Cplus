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

void administrador();//Menu administrador(iniciar sesion/registrarse)
void registroAdministrador();//registrarse admin
void inicioAdministrador();//inicio sesion admin

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
	cout << "Ingresa la contraseña del usuario: ";
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
//	cout<<"Introduce la contraseña"<<endl;
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
	rc = sqlite3_open("hotelandia_db.s3db", &db);
	switch(opcion){
	case 1:{
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
	}break;
	case 2:{
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
	}break;
	case 3:{
		char nom[100];
				cout << "Introduzca su nombre de usuario para ver que reservas tiene" << endl;
				cin >> nom;
				cout << endl;
				/* Create SQL statement */
				char sql[] = "SELECT * FROM RESERVA JOIN USUARIO_TIENE_RESERVAS ON USUARIO_TIENE_RESERVAS.id_reserva = RESERVA.id_reserva AND JOIN USUARIO ON USUARIO.id_usuario = USUARIO_TIENE_RESERVAS.id_producto WHERE USUARIO.nombre_usuario = '";
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
					fprintf(stdout, "Operation done successfully\n");
				}
				sqlite3_close(db);
				menuUsuario();

	}break;
	case 4:{

	}break;
	case 5:{

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
	//Despues de registrarse llevar a menu de opciones de admin
}
void inicioAdministrador(){//Todo inicio sesion admin
	//Despues de iniciar sesion llevar a menu de opciones de admin

	//OPCIONES DE ADMINISTRADOR: CREAR HABITACIÓN, ELIMINAR HABITACION, LISTAR HABITACIONES, LISTAR RESERVAS, ELIMINAR RESERVAS
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
