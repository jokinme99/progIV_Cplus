
/*
 * Habitaciones.cpp
 *
 *  Created on: 14 jun. 2021
 *      Author: Suhar
 */
#include "Habitaciones.h"
#include "Habitacion.h"
#include <string.h>
#include <iostream>

using namespace std;

	Habitaciones::Habitaciones(){
		this->numHabitaciones=0;


	}
	Habitaciones::~Habitaciones(){
		delete[] &this->numHabitaciones;
		delete h;
	}

	void Habitaciones::anyadirhabitacion(Habitacion *h){

		this->h[this->numHabitaciones]= h;
		numHabitaciones++;
	}
	void Habitaciones::quitarHabitacion(int){

	}
	void Habitaciones::imprimirHabitaciones(){

		for (int i = 0; i < this->numHabitaciones; ++i) {
			this->h[i]->imprimir();
		}
	}
	int Habitaciones::getNumHabitaciones(){

		return this->numHabitaciones;
	}
	Habitacion* Habitaciones::getHabitacion(int idHabitacion){
		int var = 0;
		for (var = 0; var < this->numHabitaciones; ++var) {
			if(this->h[var]->getIdHabitacion()==idHabitacion){
				break;
			}
		}
		return this->h[var];
	}


	void Habitaciones::editarHabitacion(int id, char* tipo, int precio){


		Habitacion* habitacion = getHabitacion(id);

		habitacion->setPrecioHabitacion(precio);
		habitacion->setTipoHabitacion(tipo);

	}
