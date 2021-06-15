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
	Usuarios(const Usuarios&);
	~Usuarios();

	void anyadirUsuario(Usuario *u);
	void rellenarDeUsuarios();
	void quitarUsuario();
	int callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas);
	void imprimirUsuarios();
	int getNumUsuario();
	Reservas* getReservas(int);
};



#endif /* USUARIOS_H_ */
