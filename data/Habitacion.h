/*
 * Habitacion.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef HABITACION_H_
#define HABITACION_H_

class Habitacion
{

private:
	int idHabitacion;
	int numHabitacion;
	int plantaHabitacion;
	char* tipoHabitacion;
	float precioHabitacion;
	bool reservadaHabitacion;//boolean true(reservada)

public:
	Habitacion();
	Habitacion(const int, int, int, char*, float, bool);
	Habitacion(const Habitacion&);
	~Habitacion();//altgr+4

	int getIdHabitacion()const;
	void setIdHabitacion(const int);
	int getNumHabitacion()const;
	void setNumHabitacion(int);
	int getPlantaHabitacion()const;
	void setPlantaHabitacion(int);
	char* getTipoHabitacion()const;
	void setTipoHabitacion(char*);
	float getPrecioHabitacion()const;
	void setPrecioHabitacion(float);
	bool getReservadaHabitacion()const;
	void setReservadaHabitacion(bool);
		

};


#endif /* HABITACION_H_ */
