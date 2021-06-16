/*
 * Usuarios.h
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#ifndef USUARIOS_H_
#define USUARIOS_H_
#include "Usuario.h"
#include "Reservas.h"
#include "sqlite/sqlite3.h"
class Usuarios{

private:
	Usuario *u[200];
	int numUsuarios;
public:

	Usuarios();
	~Usuarios();

	void anyadirUsuario(Usuario *u);
	void rellenarDeUsuarios();
	void quitarUsuario(int);
	void imprimirUsuarios();
	int getNumUsuarios();
	Reservas* getReservas(int);
	Usuario* getUsuario(int);
	//Usuario* getUsuario(char*);
	void editarUsuario(int id, char*, char*, char*, int /* ,Reservas* */);

};



#endif /* USUARIOS_H_ */
