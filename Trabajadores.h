/*
 * Trabajadores.h
 *
 *  Created on: 15 jun. 2021
 *      Author: jokin
 */

#ifndef TRABAJADORES_H_
#define TRABAJADORES_H_
#include "Trabajador.h"

class Trabajadores{
private:
	int numTrabajadores;
	Trabajador *t[200];
public:
	Trabajadores();
	~Trabajadores();

	void anyadirTrabajador(Trabajador  *t);
	void quitarTrabajador(int);
	void imprimirTrabajadores();
	int getNumTrabajadores();
	Trabajador* getTrabajador(int idTrabajador);
	void editarTrabajador(int, float);
	bool trabajadorExiste(int);
};


#endif /* TRABAJADORES_H_ */
