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

Reservas::Reservas() {

	this->numReservas = 0;

}
Reservas::Reservas(const Reservas &r) {
	this->numReservas = r.numReservas;
	for (int i = 0; i < r.numReservas; ++i) {
		this->r[i] = r.r[i];
	}
}
Reservas::~Reservas() {
	delete &this->numReservas;
	delete[] this->r;
}
void Reservas::anyadirReserva(Reserva *r) {
	this->r[this->numReservas] = r;
	this->numReservas++;
}
void Reservas::quitarReserva(int id) {
	int var;
	cout << "Llego" << endl;
	if(this->numReservas!=0){
		for (var = 0; var < this->numReservas; ++var) {
			cout << "Variable" << var << endl;
			if (this->r[var]->getIdReserva() == id) {
				cout << "Variable" << var << endl;
				if (this->numReservas>1) {
					for (int j = var; j < this->numReservas; ++j) {
						cout << "Variable j" << j << endl;
						cout << "Variable j" << this->getNumReservas() << endl;
						this->r[j] = this->r[j + 1];
				}
					delete this->r[this->numReservas];
				}else{
//					cout<<"peroque"<<endl;
//					delete this->r[(this->numReservas)-1];
//					cout<<"pasa"<<endl;
				}
			}
		}
	}
	this->numReservas--;
}

int Reservas::getNumReservas() {
	return this->numReservas;
}
void Reservas::imprimirReservas() {

	if (this->numReservas==0) {
		cout<<"(NO EXISTEN RESERVAS)"<<endl;

	}else{
		for (int i = 0; i < this->numReservas; ++i) {
			this->r[i]->imprimirReserva();
			cout<<"---------------"<<endl;
		}
	}
}

Reserva* Reservas::getReserva(int idReserva) {
	int var;
	for (var = 0; var < this->numReservas; ++var) {
		if (this->r[var]->getIdReserva() == idReserva) {
			break;
		}
	}
	return this->r[var];
}
int Reservas::getOrdenReserva(){

	return this->r[this->numReservas-1]->getIdReserva()+1;
}


void Reservas::editarReserva(int id, int dia, int hora,
		Habitacion *habitacion) {

	Reserva *reserva = getReserva(id);

	reserva->setDiaReserva(dia);
	reserva->setHoraReserva(hora);
	reserva->setHabitacionReservada(habitacion);

}

Reserva* Reservas::comprobarDisponibilidad(Reserva *reserva) {

	int var;


	for (var = 0; var < this->numReservas; ++var) {


//		cout << reserva->getDiaReserva() << endl;
//		cout << r[var]->getDiaReserva() << endl;
//
//		cout << reserva->getHabitacionReservada()->getIdHabitacion() << endl;
//		cout << r[var]->getHabitacionReservada()->getIdHabitacion() << endl;
		if (this->r[var]->getDiaReserva() == reserva->getDiaReserva() && this->r[var]->getHabitacionReservada()->getIdHabitacion() == reserva->getHabitacionReservada()->getIdHabitacion()) {

			cout << "La habitaci�n" << this->r[var]->getHabitacionReservada()->getIdHabitacion()
					<< " est�  ocupada para los siguientes d�as" << endl;

			int contador = 0;

			for (int i = 0; i < this->numReservas; i++) {

				if (r[i]->getHabitacionReservada()->getIdHabitacion()
						== reserva->getHabitacionReservada()->getIdHabitacion()) {

					cout << "D�a: " << r[i]->getDiaReserva() << endl;
				}

			}

			int dia;


			cout << endl;
			cout << "Introduce un dia que no este ocupado" << endl;

			cin >> dia;

			reserva->setDiaReserva(dia);

			comprobarDisponibilidad(reserva);

		}
	}
	return reserva;

}
bool Reservas::reservaExiste(int numReserva){

	int var = 0;
	bool verdadero= false;
	for (var = 0; var < this->numReservas; ++var) {
		if (this->r[var]->getIdReserva() == numReserva) {
			verdadero = true;
			break;
		}

	}
	return verdadero;
}
