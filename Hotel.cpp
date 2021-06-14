/*
 * Hotel.cpp
 *
 *  Created on: 13 jun. 2021
 *      Author: 34618
 */


#include "Habitacion.h"
#include "Hotel.h"
#include "Trabajador.h"

#include <string.h>
#include <iostream>
using namespace std;

Hotel::Hotel(){
	this->idHotel=0;
	this->nombreHotel = new char[1];
	this->nombreHotel[0] = '\0';
	this->direccionHotel = new char[1];
	this->direccionHotel[0] = '\0';
	this->telefonoHotel = 0;
	this->numEstrellas = 0;
	this->habitacionHotel = NULL;
	this->trabajadorHotel = NULL;
	this->numHabitacionesDisponibles = 0;
}
Hotel::Hotel(int idHotel, char* nombreHotel, char* direccionHotel, int telefonoHotel, int numEstrellas, Habitacion* habitacionHotel, Trabajador* trabajadorHotel, int numHabitacionesDisponibles){
	this->idHotel=idHotel;
	this->nombreHotel= new char[strlen(nombreHotel)+1];
	strcpy(this->nombreHotel,nombreHotel);
	this->direccionHotel= new char[strlen(direccionHotel)+1];
	strcpy(this->direccionHotel,direccionHotel);
	this->telefonoHotel=telefonoHotel;
	this->numEstrellas=numEstrellas;
	this->habitacionHotel=habitacionHotel;
	this->trabajadorHotel=trabajadorHotel;
	this->numHabitacionesDisponibles=numHabitacionesDisponibles;
}
Hotel::Hotel(const Hotel& h){
	this->idHotel=h.idHotel;
	this->nombreHotel= new char[strlen(h.nombreHotel)+1];
	strcpy(this->nombreHotel,h.nombreHotel);
	this->direccionHotel= new char[strlen(h.direccionHotel)+1];
	strcpy(this->direccionHotel,h.direccionHotel);
	this->telefonoHotel=h.telefonoHotel;
	this->numEstrellas=h.numEstrellas;
	this->habitacionHotel=h.habitacionHotel;
	this->trabajadorHotel=h.trabajadorHotel;
	this->numHabitacionesDisponibles=h.numHabitacionesDisponibles;
}
Hotel::~Hotel(){
	delete[]nombreHotel;
	delete[]direccionHotel;
}

int Hotel::getIdHotel()const{
	return this->idHotel;
}
void Hotel::setIdHotel(int idHotel){
	this->idHotel=idHotel;
}
char* Hotel::getNombreHotel()const{
	return this->nombreHotel;
}
void Hotel::setNombreHotel(char* nombreHotel){
	this->nombreHotel= new char[strlen(nombreHotel)+1];
	strcpy(this->nombreHotel,nombreHotel);
}
char* Hotel::getDireccionHotel()const{
	return this->direccionHotel;
}
void Hotel::setDireccionHotel(char* direccionHotel){
	this->direccionHotel= new char[strlen(direccionHotel)+1];
	strcpy(this->direccionHotel,direccionHotel);
}
int Hotel::getTelefonoHotel()const{
	return this->telefonoHotel;
}
void Hotel::setTelefonoHotel(int telefonoHotel){
	this->telefonoHotel=telefonoHotel;
}
int Hotel::getnumEstrellas()const{
	return this->numEstrellas;
}
void Hotel::setnumEstrellas(int numEstrellas){
	this->numEstrellas=numEstrellas;
}
Habitacion* Hotel::getHabitacionHotel()const{
	return this->habitacionHotel;
}
void Hotel::setHabitacionHotel(Habitacion* habitacionHotel){
	this->habitacionHotel = habitacionHotel;
}
Trabajador* Hotel::getTrabajadorHotel()const{
	return this->trabajadorHotel;
}
void Hotel::setTrabajadorHotel(Trabajador* trabajadorHotel){
	this->trabajadorHotel=trabajadorHotel;
}
int Hotel::getNumHabitacionesDisponibles()const{
	return this->numHabitacionesDisponibles;
}
void Hotel::setNumHabitacionesDisponibles(int numHabitacionesDisponibles){
	this->numHabitacionesDisponibles=numHabitacionesDisponibles;
}



