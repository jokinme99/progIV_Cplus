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

void llamadaSQL(char* sentencia);

void verHoteles();


#endif /* DATOSSQL_H_ */
