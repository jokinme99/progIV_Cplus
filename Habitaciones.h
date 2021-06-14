/*
 * habitaciones.h
 *
 *  Created on: 14 jun. 2021
 *      Author: 34618
 */

#ifndef HABITACIONES_H_
#define HABITACIONES_H_


#include "Habitacion.h"


class Habitaciones{

private:
	Habitacion *habitaciones[200];
	int numHabitaciones;
public:

	Habitaciones();
	Habitaciones(const Habitaciones&);
	~Habitaciones();

	void anyadirHabitacion(Habitacion *h);
	void rellenarDeUsuarios();
	void quitarHabitacion();
	int callbackHabitacion(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas);
	void imprimirUsuarios();
	int getNumUsuario();
};

#endif /* HABITACIONES_H_ */
