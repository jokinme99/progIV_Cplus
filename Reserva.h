/*
 * Reserva.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef RESERVA_H_
#define RESERVA_H_

#include "Habitacion.h"

class Reserva
{
private:
	int idReserva;
	int diaReserva;
	int horaReserva;
	Habitacion* habitacionReservada;

public:
	Reserva();//constructor vacío
	Reserva(const int, int, int, Habitacion*);//constructor valores
	Reserva(const Reserva&);//constructor copia
	~Reserva();//constructor para eliminar
	int getIdReserva()const;
	void setIdReserva(int);
	int getDiaReserva()const;
	void setDiaReserva(int);
	int getHoraReserva()const;
	void setHoraReserva(int);
	Habitacion* getHabitacionReservada()const;
	void setHabitacionReservada(Habitacion*);
	void imprimirReserva();
};


#endif /* RESERVA_H_ */
