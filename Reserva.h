/*
 * Reserva.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

//NO ES NECESARIO HACER .CPP DE HABITACION, HOTEL, RESERVA, TRABAJADOR, USUARIO
#include "Habitacion.h"
#ifndef RESERVA_H_
#define RESERVA_H_
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
	void getIdReserva(const int);
	int getDiaReserva()const;
	void setDiaReserva(int);
	int getHoraReserva()const;
	void setHoraReserva(int);
	Habitacion* getHabitacionReservada()const;
	void setHabitacionReservada(Habitacion*);
};


#endif /* RESERVA_H_ */
