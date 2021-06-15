/*
 * Habitaciones.H
 *
 *  Created on: 14 jun. 2021
 *      Author: Suhar
 */

#ifndef HABITACIONES_H_
#define HABITACIONES_H_
#include "Habitacion.h"

class Habitaciones{
private:
	int numHabitaciones;
	Habitacion *h[200];
public:
	Habitaciones();
	~Habitaciones();

	void anyadirhabitacion(Habitacion  *h);
	void quitarHabitacion(int);
	void imprimirHabitaciones();
	int getNumHabitaciones();
	Habitacion* getHabitacion(int idHabitacion);
};


#endif /* HABITACIONES_H_ */

