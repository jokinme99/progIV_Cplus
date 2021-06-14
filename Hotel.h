/*
 * Hotel.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef HOTEL_H_
#define HOTEL_H_

#include "Habitacion.h"
#include "Reserva.h"
#include "Trabajador.h"

class Hotel
{
private:
	int idHotel;
	char* nombreHotel;
	char* direccionHotel;
	int telefonoHotel;
	int numEstrellas;
	Habitacion* habitacionHotel;
	//Reserva* reservaHabitacion; No hace falta, porque en Reserva podemos ver la habitacion que esta reservada
	//Y cada hotel tiene unas habitaciones especificas, por lo que al hacer la reserva de la habitacion sabemos de que hotel
	Trabajador* trabajadorHotel;
	Reserva* reservaHotel;
public:
	Hotel();
	Hotel(const int, char*, char*, int, int, Habitacion*, Reserva*, Trabajador*);
	Hotel(const Hotel&);
	~Hotel();

	int getIdHotel()const;
	void setIdHotel(const int);
	char* getNombreHotel()const;
	void setNombreHotel(char*);
	char* getDireccionHotel()const;
	void setDireccionHotel(char*);
	Habitacion* getHabitacionHotel()const;
	void setHabitacionHotel(Habitacion*);
	Reserva* getReservaHotel()const;
	void setReservaHotel(Reserva*);
	Trabajador* getTrabajadorHotel()const;
	void setTrabajadorHotel(Trabajador*);
};


#endif /* HOTEL_H_ */
