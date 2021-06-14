/*
 * metodoReservas.h
 *
 *  Created on: 14 jun. 2021
 *      Author: jokin
 */

#ifndef METODORESERVAS_H_
#define METODORESERVAS_H_

#include "sqlite/sqlite3.h"

int crearReserva(sqlite3* db, char* nombreUsuario, int hotel, int numHabitacion, int dia, int hora);
char* intAChar(int numero);


#endif /* METODORESERVAS_H_ */
