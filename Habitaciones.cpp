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
#include "DatosSQL.h"

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
		if(var==this->numHabitaciones){
			return NULL;
		}
	}
	return this->h[var];
}


bool Habitaciones::habitacionExiste(int idHabitacion){
	int var = 0;
	bool verdadero= false;
	for (var = 0; var < this->numHabitaciones; ++var) {
		if (this->h[var]->getIdHabitacion() == idHabitacion) {
			verdadero = true;
			break;
		}

	}
	return verdadero;
}
/////////////////////////////////////////////////////////////////////////////////////////
void Habitaciones::editarHabitacion(int id, char *tipo, int precio) {//ELIMINAR ESTA FUNCION


	Habitacion *habitacion = this->getHabitacion(id);

	habitacion->setPrecioHabitacion(precio);
	habitacion->setTipoHabitacion(tipo);

	char sql[] = "UPDATE HABITACION SET precio_habitacion ='";

	char con[] = "'",con1[] = ",", con2[] = "tipo_habitacion='", con8[] = " WHERE id_habitacion='", con9[] = ";";



	string s = to_string(precio);
	char const *pchar2 = s.c_str();  //use char const* as target type
	char con11[5]; strcpy(con11, pchar2);
	 s = to_string(id);
	char const *pchar4 = s.c_str();  //use char const* as target type
	char con13[5]; strcpy(con13, pchar4);

	strcat(sql, con11);
	strcat(sql, con);
	strcat(sql, con1);
	strcat(sql, con2);
	strcat(sql, tipo);
	strcat(sql, con);

	strcat(sql, con8);
	strcat(sql, con13);
	strcat(sql, con);
	strcat(sql, con9);
	cout<<endl;

	//cout<<sql<<endl;

	llamadaSQL(sql);

	delete habitacion;

	cout<<"esto funciona"<<endl;



}
//////////////////////////////////////////////////////////////////////////////////
void Habitaciones::busquedaPersonalizada() {

	cout << "Elige una opcion de busqueda de habitaciones" << endl;

	cout << "1. Por precio" << endl;
	cout << "2. Por tipo de habitacion" << endl;
	cout << "3. Ambas" << endl;
	cout << "4. Todas" << endl;

	int opcion;

	cin >> opcion;

	if (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4) {

		cout << "Elige una opcion valida" << endl;

		busquedaPersonalizada();

	} else {

		switch (opcion) {
		case 1: {

			int opcionPrec;

			cout << "Precio mayor (1) precio menor (2)" << endl;

			cin >> opcionPrec;

			switch (opcionPrec) {

			case 1: {

				int precio;

				cout << "Introduce un precio" << endl;

				cin >> precio;

				for (int var = 0; var < this->numHabitaciones; ++var) {

					if (this->h[var]->getPrecioHabitacion() >= precio) {

						this->h[var]->imprimir();
					}

				}

			}
				break;

			case 2: {

				int precio;

				cout << "Introduce un precio" << endl;

				cin >> precio;

				for (int var = 0; var < this->numHabitaciones; ++var) {

					if (this->h[var]->getPrecioHabitacion() <= precio) {

						this->h[var]->imprimir();
					}

				}

			}
				break;

			}

		}

			break;
		case 2: {

			char tipo[100];

			cout
					<< "Introduce un tipo -> Doble, Individual, Suite Doble o Familiar"
					<< endl;

			cin >> tipo;

			for (int var = 0; var < this->numHabitaciones; ++var) {

				if (strcmp(this->h[var]->getTipoHabitacion(), tipo) == 0) {

					this->h[var]->imprimir();
				}

			}

		}
			break;

		case 3: {

			char tipo[100];

			cout
					<< "Introduce un tipo -> Doble, Individual, Suite Doble o Familiar"
					<< endl;

			cin >> tipo;

			int precio;

			int opcionPrec;

			cout << "Precio igual mayor (1) o precio igual menor (2)" << endl;
			cin >> opcionPrec;

			cout << "Introduce un precio" << endl;

			cin >> precio;

			for (int var = 0; var < this->numHabitaciones; ++var) {

				if (opcionPrec == 1) {

					if (strcmp(this->h[var]->getTipoHabitacion(), tipo) == 0
							&& this->h[var]->getPrecioHabitacion() >= precio) {

						this->h[var]->imprimir();
					}
				} else {

					if (strcmp(this->h[var]->getTipoHabitacion(), tipo) == 0
							&& this->h[var]->getPrecioHabitacion() <= precio) {

						this->h[var]->imprimir();
					}
				}

			}


		}

		break;
		case 4: {



			for (int i = 0; i < this->numHabitaciones; ++i) {
				this->h[i]->imprimir();
			}

		}

			break;

		}

	}
}

