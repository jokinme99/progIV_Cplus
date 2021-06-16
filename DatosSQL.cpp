/*
 * DatosSQL.cpp
 *
 *  Created on: 15 jun. 2021
 *      Author: Suhar
 */
#include "Reserva.h"
#include <iostream>
#include "sqlite/sqlite3.h"
//#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include"metodoReservas.h"
#include "Habitacion.h"
using namespace std;


	static int callback(void *data, int argc, char **argv, char **azColName) {
		int i;
		fprintf(stderr, "%s: \n", (const char*) data);

		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}

		printf("\n");
		return 0;
	}

	void llamadaSQL(char* sentencia){

		sqlite3 *db; //objeto base de datos
		char *zErrMsg = 0;
		int rc;
		char *sql; //sentencia sql
		const char *data = "LLamada a Base de datos";
		rc = sqlite3_open("hotelandia_final.s3db", &db);
		rc = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			fprintf(stdout, "Reserva realizada:\n");
		}
		sqlite3_close(db);

	}
