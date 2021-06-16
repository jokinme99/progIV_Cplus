/*
 * Hotel.cpp
 *
 *  Created on: 16 jun. 2021
 *      Author: 34618
 */

#include "Hotel.h"
#include <iostream>

using namespace std;

Hotel::Hotel() {

	this->idHotel = 0;
	this->nombreHotel = NULL;
	this->direccionHotel = NULL;
	this->telefonoHotel = 0;
	this->numEstrellas = 0;

	this->trabajadores[0] = NULL;
	this->numHabitacionesDisponibles = 0;
}

Hotel::Hotel(const int id, char* nombre, char* direccion, int telefono, int estrellas, int numHabitacionesDisponibles) {


}
Hotel::Hotel(const Hotel&) {

}
Hotel::~Hotel() {

}

int Hotel::getIdHotel() const {

}
void Hotel::setIdHotel(int) {

}
char* Hotel::getNombreHotel() const {

}
void Hotel::setNombreHotel(char*) {

}
char* Hotel::getDireccionHotel() const {

}
void Hotel::setDireccionHotel(char*) {

}
int Hotel::getTelefonoHotel() const {

}
void Hotel::setTelefonoHotel(int) {

}
int Hotel::getnumEstrellas() const {

}
void Hotel::setnumEstrellas(int) {

}
Habitacion* Hotel::getHabitacionHotel() const {

}
void Hotel::setHabitacionHotel(Habitacion*) {

}
Trabajador* Hotel::getTrabajadorHotel() const {

}
void Hotel::setTrabajadorHotel(Trabajador*) {

}
int Hotel::getNumHabitacionesDisponibles() const {

}
void Hotel::setNumHabitacionesDisponibles(int) {

}

void Hotel::imprimir(){


}


