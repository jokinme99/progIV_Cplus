/*
 * Usuarios.h
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#ifndef USUARIOS_H_
#define USUARIOS_H_
#include "Usuario.h"
#include "sqlite/sqlite3.h"
class Usuarios{
private:
	Usuario *u;
	int numUsuarios;
public:

	Usuarios();
	Usuarios(const Usuarios&);
	~Usuarios();


	void rellenarDeUsuarios();
	void quitarUsuario();

};


#endif /* USUARIOS_H_ */
