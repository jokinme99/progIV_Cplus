/*
 * Reserva.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */
#include "Reserva.h"
#include "Habitacion.h"
#include <string.h>
#include <iostream>
using namespace std;

Reserva::Reserva(){
	this->idReserva=0;
	this->diaReserva=0;
	this->horaReserva=0;
	this->usuarioReserva=0;
	this->habitacionReservada = NULL;
}
Reserva::Reserva(int idReserva,int diaReserva, int horaReserva,Usuario* usuarioReserva, Habitacion* habitacionReservada){
	this->idReserva=idReserva;
	this->diaReserva=diaReserva;
	this->horaReserva=horaReserva;
	this->usuarioReserva=usuarioReserva;
	this->habitacionReservada=habitacionReservada;
}
Reserva::Reserva(const Reserva& r){
	this->idReserva=r.idReserva;
	this->diaReserva=r.diaReserva;
	this->horaReserva=r.horaReserva;
	this->usuarioReserva=r.usuarioReserva;
	this->habitacionReservada=r.habitacionReservada;
}
Reserva::~Reserva(){

}


int Reserva::getIdReserva()const{
	return this->idReserva;
}
void Reserva::setIdReserva(int id){
	this->idReserva=id;
}
int Reserva::getDiaReserva()const{
	return this->diaReserva;
}
void Reserva::setDiaReserva(int dia){
	this->diaReserva=dia;
}
int Reserva::getHoraReserva()const{
	return this->horaReserva;
}
void Reserva::setHoraReserva(int hora){
	this->horaReserva=hora;
}
Habitacion* Reserva::getHabitacionReservada()const{
	return this->habitacionReservada;
}

void Reserva::setHabitacionReservada(Habitacion* habitacion){
	this->habitacionReservada=habitacion;
}
Usuario* Reserva::usuarioReserva()const{
	return this->usuarioReserva;
}

void Reserva::setusuarioReserva(Usuario* usuarioReserva){
	this->usuarioReserva=usuarioReserva;
}


