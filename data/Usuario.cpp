/*
 * usuario.cpp
 *
 *  Created on: May 13, 2021
 *      Author: suhar.txabarri
 */
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "Usuario.h"
namespace data{



	int Usuario::count = 0;



	Usuario::Usuario(){

		this->idUsuario =0;
		this->nombreUsuario=0;
		this->correoUsuario=0;
		this->contrasenyaUsuario=0;
		this->edadUsuario=0;
	}
	Usuario::Usuario(int id, char* nombre, char* correo, char* contrasenya, int edad){

		this->idUsuario = count++;
		this->nombreUsuario = (char*)malloc(sizeof(strlen(nombre))+1);
		strcpy(this->nombreUsuario, nombre);
		this->correoUsuario = (char*)malloc(sizeof(strlen(correo))+1);
		strcpy(this->correoUsuario, correo);
		this->contrasenyaUsuario = (char*)malloc(sizeof(strlen(contrasenya))+1);
		strcpy(this->contrasenyaUsuario,contrasenya);
		this->edadUsuario=edad;



	}
	Usuario::Usuario(const Usuario& u){

		this->idUsuario =count++;
		this->nombreUsuario=u.nombreUsuario;
		this->correoUsuario=u.correoUsuario;
		this->contrasenyaUsuario=u.contrasenyaUsuario;
		this->edadUsuario=u.edadUsuario;

	}
	Usuario::~Usuario(){

	delete &this->idUsuario;
	delete[] this->nombreUsuario;
	delete[] this->correoUsuario;
	delete[] this->contrasenyaUsuario;
	delete &this->edadUsuario;


	}

	int Usuario::getIdUsuario()const{

		return this->idUsuario;

	}

	char* Usuario::getNombreUsuario()const{
		return this->nombreUsuario;
	}
	void Usuario::setNombreUsuario(char* nombre){
		this->nombreUsuario = (char*)malloc(sizeof(strlen(nombre))+1);
		strcpy(this->nombreUsuario, nombre);
	}
	char* Usuario::getCorreoUsuario()const{
		return this->correoUsuario;
	}
	void Usuario::setCorreoUsuario(char* correo){
		this->correoUsuario = (char*)malloc(sizeof(strlen(correo))+1);
		strcpy(this->correoUsuario, correo);
	}
	char* Usuario::getContrasenyaUsuario()const{
		return this->contrasenyaUsuario;
	}
	void Usuario::setContrasenyaUsuario(char* contrasenya){
		this->contrasenyaUsuario = (char*)malloc(sizeof(strlen(contrasenya))+1);
		strcpy(this->contrasenyaUsuario,contrasenya);
	}
	int Usuario::getEdadUsuario()const{
		return this->edadUsuario;
	}
	void Usuario::setEdadUsuario(int edad){
		this->edadUsuario = edad;
	}
	bool Usuario::comprobarUsuario(char *usuario, char *contrasenya){

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

				printf("El usuario y la contraseña son correctos\n");

				free(nombres[j]);
				free(contrasenya1[j]);

				fclose(f);

				return true;

			}

			j++;

		}

		printf("El usuario y la contraseña no coinciden\n");

		return false;

		fclose(f);


	}

};







