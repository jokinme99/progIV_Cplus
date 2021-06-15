/*
 * Reservas.cpp
 *
 *  Created on: 14 jun. 2021
 *      Author: Suhar
 */
#include "Reserva.h"
#include "Reservas.h"
#include <iostream>

using namespace std;


Reservas::Reservas(){

this->numReservas=0;

}

Reservas::Reservas(Reservas& r){
this->numReservas= r.numReservas;
for (int i = 0; i < r.numReservas; ++i) {
	this->r[i]=r.r[i];
}
}
Reservas::~Reservas(){
delete &this->numReservas;
delete[] this->r;
}
void Reservas::anyadirReserva(Reserva* r){
this->r[this->numReservas]= r;
this->numReservas++;
}
void Reservas::eliminarReserva(Reserva* r){

}
int Reservas::getNumReservas(){
	return this->numReservas;
}
void Reservas::imprimirReservas(){

	if (this->getNumReservas()==0) {
		cout<<"(este usuario no tiene reservas)"<<endl;
	}

	for (int i = 0; i < this->getNumReservas(); ++i) {
		this->r[i]->imprimeReserva();
	}
}
