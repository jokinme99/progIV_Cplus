/*
 * Usuarios.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */
#include "Usuario.h"
#include "Usuarios.h"
#include <string.h>
#include "Administrador.h"
#include "sqlite/sqlite3.h" //include para base de datos
#include <iostream>
using namespace std;


	Usuarios::Usuarios(){


		this->numUsuarios=0;


	}
	Usuarios::~Usuarios(){
		delete[] &this->numUsuarios;
		delete[] this->u;

	}

	void Usuarios::anyadirUsuario(Usuario *u){
		this->u[this->numUsuarios]= u;
		this->numUsuarios++;

	}
	void Usuarios::rellenarDeUsuarios(){

		//SEGURAMENTE SE PUEDA SUSTITUIR POR EL CONSTRUCTOR
		sqlite3 *db;
		const char *data = "LLamada a Base de datos";
		char *zErrMsg = 0;
		int rc = sqlite3_open("hotelandia_final.s3db", &db);

		char sql[] = "SELECT * from USUARIO";

		/* Execute SQL statement */
		//rc = sqlite3_exec(db, sql, &this->callbackUsuarios, (void*) data, &zErrMsg);//ARREGLAR ESTO
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			//fprintf(stdout, "Operation done successfully\n");
		}
		sqlite3_close(db);




	}
	void Usuarios::quitarUsuario(){

	}

	int Usuarios::callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas) {
		(void)data;

		cout<<contadorDeFila[5]<<endl;
		if (strcmp(contadorDeFila[5],"usuario")==0){

			Usuario *us = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1], contadorDeFila[3], contadorDeFila[2], atoi(contadorDeFila[4]));
			this->anyadirUsuario(us);
		}else{

			Usuario *us = new Usuario(atoi(contadorDeFila[0]), contadorDeFila[1], contadorDeFila[3], contadorDeFila[2], atoi(contadorDeFila[4]));

			Administrador *ad = new Administrador(us);

			this->anyadirUsuario(ad);

		}
		return 0;
	}

	void Usuarios::imprimirUsuarios(){
		for (int i = 0; i < this->numUsuarios; ++i) {
			this->u[i]->imprimirUsuario();
		}
	}

	int Usuarios::getNumUsuario(){
		return this->numUsuarios;
	}
	Reservas* Usuarios::getReservas(int idUsuario){
		int i =0;
				for (i = 0; i < this->numUsuarios;++i) {
					if (this->u[i]->getIdUsuario()==idUsuario) {
						break;
					}
				}
				return this->u[i]->getReservaUsuario();
	}

