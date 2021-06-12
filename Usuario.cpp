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

	Usuario::Usuario(){
		this->idUsuario = 0;
		this->nombreUsuario = new char[1];
		this->nombreUsuario[0] = '\0';
		this->correoUsuario = new char[1];
		this->correoUsuario[0] = '\0';
		this->contrasenyaUsuario = new char[1];
		this->contrasenyaUsuario[0] = '\0';
		this->edadUsuario = 0;
		this->reservasUsuario = NULL;
		this->nReservas = 0;

	}


	Usuario::Usuario(int id, char* nombre, char* correo, char* contrasenya, int edad){

		this->idUsuario = id;
		this->nombreUsuario = (char*)malloc(sizeof(strlen(nombre))+1);
		strcpy(this->nombreUsuario, nombre);
		this->correoUsuario = (char*)malloc(sizeof(strlen(correo))+1);
		strcpy(this->correoUsuario, correo);
		this->contrasenyaUsuario = (char*)malloc(sizeof(strlen(contrasenya))+1);
		strcpy(this->contrasenyaUsuario,contrasenya);
		this->edadUsuario=edad;
		this->nReservas = 0;

			this->reservasUsuario = NULL;



	}
	Usuario::Usuario(const Usuario& u){

		this->idUsuario =u.idUsuario;
		this->nombreUsuario=new char[strlen(u.nombreUsuario) +1];
		strcpy(this->nombreUsuario, u.nombreUsuario);
		this->correoUsuario=new char[strlen(u.correoUsuario) +1];
		strcpy(this->correoUsuario, u.correoUsuario);
		this->contrasenyaUsuario=new char[strlen(u.contrasenyaUsuario) +1];
		strcpy(this->contrasenyaUsuario, u.contrasenyaUsuario);
		this->edadUsuario=u.edadUsuario;
		this->nReservas = u.nReservas;
		for(int i=0;i<u.nReservas;i++){
			this->reservasUsuario[i] = u.reservasUsuario[i];
		}

	}
	Usuario::~Usuario(){

	delete &this->idUsuario;
	delete[] this->nombreUsuario;
	delete[] this->correoUsuario;
	delete[] this->contrasenyaUsuario;
	delete &this->edadUsuario;
	delete &this->nReservas;
	//delete[] this->reservasUsuario;


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

	void verhoteles();
	void listarHabitaciones();
	void listarReservas();
	void crearReserva();
	void eliminarReserva();










