/*
 * Usuarios.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */
#include "Usuario.h"
#include "Usuarios.h"
#include "sqlite/sqlite3.h" //include para base de datos
#include <iostream>
using namespace std;


	Usuarios::Usuarios(){

		this->u=NULL;
		this->numUsuarios=0;


	}
	Usuarios::Usuarios(const Usuarios&){


	}
	Usuarios::~Usuarios(){


	}

	void Usuarios::anyadirUsuario(){

	}
	void Usuarios::rellenarDeUsuarios(){
		//SEGURAMENTE SE PUEDA SUSTITUIR POR EL CONSTRUCTOR
	}
	void Usuarios::quitarUsuario(){

	}
