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
	Reserva* reservaHabitacion;
	Trabajador* trabajadorHotel;
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
