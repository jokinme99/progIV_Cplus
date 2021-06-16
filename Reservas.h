/*
 * Reservas.h
 *
 *  Created on: 14 jun. 2021
 *      Author: Suhar
 */

#ifndef RESERVAS_H_
#define RESERVAS_H_
#include "Reserva.h"
#include "Habitacion.h"

class Reservas{
private:
	Reserva *r[100];
	int numReservas;
public:
	Reservas();
	Reservas(const Reservas& r);
	~Reservas();

	void anyadirReserva(Reserva  *r);
	void quitarReserva(int);
	void imprimirReservas();
	int getNumReservas();
	Reserva* getReserva(int idReserva);
	Reserva* getOrdenReserva(int ordenReserva);
	void editarReserva(int, int, int, Habitacion*);
};


#endif /* RESERVAS_H_ */
