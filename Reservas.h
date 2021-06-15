/*
 * Reservas.h
 *
 *  Created on: 14 jun. 2021
 *      Author: Suhar
 */

#ifndef RESERVAS_H_
#define RESERVAS_H_
#include "Reserva.h"

class Reservas{
private:
	Reserva *r[100];
	int numReservas;
public:
	Reservas();
	Reservas(Reservas&);
	~Reservas();

	void anyadirReserva(Reserva*);
	void eliminarReserva(Reserva*);
	int getNumReservas();
	void imprimirReservas();
};


#endif /* RESERVAS_H_ */
