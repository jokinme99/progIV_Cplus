/*
 * Habitacion.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef HABITACION_H_
#define HABITACION_H_

#include "Hotel.h"

class Habitacion
{

private:

	Hotel* hotel;
	int idHabitacion;
	int numHabitacion;
	int plantaHabitacion;
	char* tipoHabitacion;
	int precio;

public:
	Habitacion();
	Habitacion(const int, int, int, char*);
	Habitacion(const Habitacion& h);
	~Habitacion();//altgr+4

	int getIdHabitacion()const;
	void setIdHabitacion(const int);
	int getNumHabitacion()const;
	void setNumHabitacion(int);
	int getPlantaHabitacion()const;
	void setPlantaHabitacion(int);
	char* getTipoHabitacion()const;
	void setTipoHabitacion(char*);
	int getPrecioHabitacion()const;
	void setPrecioHabitacion(int);

	void imprimir();
		

};


#endif /* HABITACION_H_ */
