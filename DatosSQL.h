/*
 * DatosSQL.h
 *
 *  Created on: 15 jun. 2021
 *      Author: Suhar
 */

#ifndef DATOSSQL_H_
#define DATOSSQL_H_
#include "Usuarios.h"
#include "Reservas.h"
#include "Habitaciones.h"
#include "Trabajadores.h"
#include "sqlite/sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName);
int callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas, Usuarios*);
int callbackReservas(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas, Reservas*);
int callbackHabitaciones(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas, Habitaciones*);
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas, Trabajadores*);
void cargarDatosUsuarios(Usuarios*);
void cargarDatosHabitaciones(Habitaciones*);
void cargarDatosTrabajadores(Trabajadores*);
void cargarDatosReservas(Reservas*);
void importarDatosUsuarios();



#endif /* DATOSSQL_H_ */
