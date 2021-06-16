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

Habitaciones::Habitaciones() {
	this->numHabitaciones = 0;

}
Habitaciones::~Habitaciones() {
	delete[] &this->numHabitaciones;
	delete h;
}

void Habitaciones::anyadirhabitacion(Habitacion *h) {

	this->h[this->numHabitaciones] = h;
	numHabitaciones++;
}
void Habitaciones::quitarHabitacion(int id) {

	int var = 0;

	cout << "Llego" << endl;
	for (var = 0; var < this->numHabitaciones; ++var) {

		cout << "Variable" << var << endl;
		if (this->h[var]->getIdHabitacion() == id) {

			cout << "Variable" << var << endl;
			numHabitaciones--;
			for (int j = var; j < this->numHabitaciones; ++j) {

				cout << "Variable j" << j << endl;
				cout << "Variable j" << this->getNumHabitaciones() << endl;
				this->h[j] = this->h[j + 1];

			}

		}
	}
}

void Habitaciones::imprimirHabitaciones() {

	for (int i = 0; i < this->numHabitaciones; ++i) {
		this->h[i]->imprimir();
	}
}
int Habitaciones::getNumHabitaciones() {

	return this->numHabitaciones;
}
Habitacion* Habitaciones::getHabitacion(int idHabitacion) {
	int var = 0;
	for (var = 0; var < this->numHabitaciones; ++var) {
		if (this->h[var]->getIdHabitacion() == idHabitacion) {
			break;
		}
	}
	return this->h[var];
}

void Habitaciones::editarHabitacion(int id, char *tipo, int precio) {

	Habitacion *habitacion = getHabitacion(id);

	habitacion->setPrecioHabitacion(precio);
	habitacion->setTipoHabitacion(tipo);

}

void Habitaciones::busquedaPersonalizada() {

	cout << "Elige una opcion de busqueda" << endl;

	cout << "1. Por precio" << endl;
	cout << "2. Por tipo de habitacion" << endl;
	cout << "3. Ambas" << endl;

	int opcion;

	cin << opcion;

	if (opcion != 1 && opcion != 2 && opcion != 3) {

	} else {

		switch (opcion) {
		case 1: {

			int opcionPrec;

			cout << "Precio mayor (1) precio menor (2)" << endl;

			cin << opcionPrec;

			switch (opcionPrec) {

			case 1: {

				int precio;

				cout << "Introduce un precio" << endl;

				cin << precio;

				for (int var = 0; var < this->numHabitaciones; ++var) {

					if (this->h[var]->getPrecioHabitacion() <= precio) {

						this->h[var]->imprimir();
					}

				}

			}
				break;

			case 2: {

				int precio;

				cout << "Introduce un precio" << endl;

				cin << precio;

				for (int var = 0; var < this->numHabitaciones; ++var) {

					if (this->h[var]->getPrecioHabitacion() >= precio) {

						this->h[var]->imprimir();
					}

				}

			}
				break;

			}

		}

			break;
		case 2: {

		}
			break;

		case 3: {

		}
			break;

		}

	}

}
