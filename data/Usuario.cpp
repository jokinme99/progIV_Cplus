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
using namespace std;
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

};







