/*
 * Reserva.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

//NO ES NECESARIO HACER .CPP DE HABITACION, HOTEL, RESERVA, TRABAJADOR, USUARIO

#ifndef RESERVA_H_
#define RESERVA_H_
class Reserva
{
private:
	int idReserva;
	int diaReserva;
	int horaReserva;
	int numHabitaciones;

public:
	Reserva();//constructor vacío
	Reserva(const int, int, int, int, char*);//constructor valores
	Reserva(const Reserva&);//constructor copia
	~Reserva();//constructor para eliminar
	int getIdReserva()const;
	void getIdReserva(const int);
	int getDiaReserva()const;
	void setDiaReserva(int);
	int getHoraReserva()const;
	void setHoraReserva(int);
	int getNumHabitaciones()const;
	void setNumHabitaciones(int);
};


#endif /* RESERVA_H_ */
