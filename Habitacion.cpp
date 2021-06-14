/*
 * Habitacion.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Marcos
 *
 */

#include "Habitacion.h"
#include <iostream>
#include <string.h>

using namespace std;

Habitacion::Habitacion() {

	this->idHabitacion = 0;
	this->numHabitacion = 0;
	this->plantaHabitacion = 0;
	this->tipoHabitacion = new char[1];
	this->tipoHabitacion[0] = '\0';
	this->precio = 0;

}

Habitacion::Habitacion(const int id, int numHab, int planta, char *tipoHabitacion, int precio) {

	this->idHabitacion = id;
	this->numHabitacion = numHab;
	this->plantaHabitacion = planta;
	this->tipoHabitacion= new char[strlen(tipoHabitacion)+1];
	strcpy(this->tipoHabitacion,tipoHabitacion);
	this->precio = precio;
}

Habitacion::Habitacion(const Habitacion &h) {

	this->idHabitacion = h.idHabitacion;
	this->numHabitacion = h.numHabitacion;
	this->plantaHabitacion = h.plantaHabitacion;
	this->tipoHabitacion= new char[strlen(h.tipoHabitacion)+1];
	strcpy(this->tipoHabitacion,h.tipoHabitacion);
	this->precio = h.precio;
}
Habitacion::~Habitacion() {
	//altgr+4
}

int Habitacion::getIdHabitacion() const {

	return this->idHabitacion;

}
void Habitacion::setIdHabitacion(const int id) {

	this->idHabitacion = id;

}

int Habitacion::getNumHabitacion() const {

	return this->numHabitacion;
}
void Habitacion::setNumHabitacion(int numHab) {

	this->numHabitacion = numHab;
}
int Habitacion::getPlantaHabitacion() const {

	return this->plantaHabitacion;
}

void Habitacion::setPlantaHabitacion(int planta) {

	this->plantaHabitacion = planta;
}

char* Habitacion::getTipoHabitacion() const {

	return this->tipoHabitacion;
}
void Habitacion::setTipoHabitacion(char* tipo) {

	this->tipoHabitacion= new char[strlen(tipo)+1];
	strcpy(this->tipoHabitacion,tipo);
}
int Habitacion::getPrecioHabitacion() const {

	 return this->precio;
}
void Habitacion::setPrecioHabitacion(int precio) {

	this->precio = precio;

}
