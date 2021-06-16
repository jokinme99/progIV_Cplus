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
	void Usuarios::quitarUsuario(int id){
		int var;
		cout<<"Llego"<<endl;
		for(var=0;var<this->numUsuarios;++var){
			cout<<"Variable"<<var<<endl;
			if(this->u[var]->getIdUsuario()==id){
				cout<< "Variable"<< var<<endl;
				numUsuarios--;
				for(int j=var;j<this->numUsuarios;++j){
					cout<<"Variable j"<<j<<endl;
					cout<<"Variable j"<<this->getNumUsuarios()<<endl;
					this->u[j] = this->u[j+1];
				}
			}
		}
	}


	void Usuarios::imprimirUsuarios(){
		for (int i = 0; i < this->numUsuarios; ++i) {
			this->u[i]->imprimirUsuario();
		}
	}

	int Usuarios::getNumUsuarios(){
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
//				return new Reservas();
	}

	Usuario* Usuarios::getUsuario(int id){
		int i;
		for (i = 0; i < this->numUsuarios; ++i) {
			if (this->u[i]->getIdUsuario()==id) {
				break;
			}
		}
		return this->u[i];
	}

	//Todo:arreglar
	void Usuarios::editarUsuario(int id, char* nombre, char* correo, char* contrasenya, int edad /* ,Reservas* reserva */){
		Usuario* usuario = getUsuario(id);
		usuario->setNombreUsuario(nombre);
		usuario->setCorreoUsuario(correo);
		usuario->setContrasenyaUsuario(contrasenya);
		usuario->setEdadUsuario(id);
		//usuario->setReservaUsuario(reserva);
	}
