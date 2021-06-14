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


		this->numUsuarios=0;


	}
	Usuarios::Usuarios(const Usuarios&){


	}
	Usuarios::~Usuarios(){


	}

	void Usuarios::anyadirUsuario(Usuario *u){
		this->u[this->numUsuarios]= u;
		this->numUsuarios++;

	}
	void Usuarios::rellenarDeUsuarios(){
//		//SEGURAMENTE SE PUEDA SUSTITUIR POR EL CONSTRUCTOR
//		sqlite3 *db;
//		const char *data = "LLamada a Base de datos";
//		char *zErrMsg = 0;
//		int rc = sqlite3_open("hotelandia_final.s3db", &db);
//
//		char sql[] = "SELECT * from USUARIO";
//
//		/* Execute SQL statement */
//		rc = sqlite3_exec(db, sql, this->callbackUsuarios, (void*) data, &zErrMsg);
//		if (rc != SQLITE_OK) {
//			fprintf(stderr, "SQL error: %s\n", zErrMsg);
//			sqlite3_free(zErrMsg);
//		} else {
//			//fprintf(stdout, "Operation done successfully\n");
//		}
//		sqlite3_close(db);




	}
	void Usuarios::quitarUsuario(){

	}

	int Usuarios::callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas) {
		(void)data;
	//	cout<<numeroColumnas<<endl;
	//	cout<<*contadorDeFila<<endl;
	//	cout<<*nombresColumnas<<endl;
		for (int i = 0; i < numeroColumnas; ++i) {
			cout<<contadorDeFila[i]<<endl;
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

