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


void cargarVariables(Usuarios *, Habitaciones *, Trabajadores *,Reservas *);

static int callback(void *data, int argc, char **argv, char **azColName);
int callbackUsuarios(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
int callbackReservas(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
int callbackHabitaciones(void *data, int numeroColumnas, char **contadorDeFila,
		char **nombresColumnas);
int callbackTrabajadores(void *data, int numeroColumnas, char **contadorDeFila, char **nombresColumnas, Trabajadores*);
void cargarDatosUsuarios();
void cargarDatosHabitaciones();
void cargarDatosTrabajadores();
void cargarDatosReservas();
void importarDatosUsuarios();
void verHoteles();
int crearReserva();
int modificarReserva();
int eliminarReserva();



#endif /* DATOSSQL_H_ */
