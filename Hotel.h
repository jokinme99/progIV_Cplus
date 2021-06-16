/*
 * Hotel.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef HOTEL_H_
#define HOTEL_H_

#include "Habitacion.h"
#include "Trabajador.h"
#include "Trabajadores.h"
#include "Habitaciones.h"

class Hotel
{
private:
	int idHotel;
	char* nombreHotel;
	char* direccionHotel;
	int telefonoHotel;
	int numEstrellas;
	Habitaciones* habitaciones;
	//Reserva* reservaHabitacion; No hace falta, porque en Reserva podemos ver la habitacion que esta reservada
	//Y cada hotel tiene unas habitaciones especificas, por lo que al hacer la reserva de la habitacion sabemos de que hotel
	Trabajadores* trabajadores;
	int numHabitacionesDisponibles;
public:
	Hotel();
	Hotel(const int, char*, char*, int, int, int numHabitacionesDisponibles);
	Hotel(const Hotel&);
	~Hotel();

	int getIdHotel()const;
	void setIdHotel(int);
	char* getNombreHotel()const;
	void setNombreHotel(char*);
	char* getDireccionHotel()const;
	void setDireccionHotel(char*);
	int getTelefonoHotel()const;
	void setTelefonoHotel(int);
	int getnumEstrellas()const;
	void setnumEstrellas(int);
	Habitacion* getHabitacionHotel()const;
	void setHabitacionHotel(Habitacion*);
	Trabajador* getTrabajadorHotel()const;
	void setTrabajadorHotel(Trabajador*);
	int getNumHabitacionesDisponibles()const;
	void setNumHabitacionesDisponibles(int );

	void imprimir();
};


#endif /* HOTEL_H_ */
