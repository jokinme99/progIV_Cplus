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

		cout<<sentencia<<endl;

		sqlite3 *db1=NULL; //objeto base de datos
		char *zErrMsg = 0;
		int rc;
		const char *data = "LLamada a Base de datos";

		rc = sqlite3_open("hotelandia_final.s3db", &db1);

		cout<<rc<<endl;

		rc = sqlite3_exec(db1, sentencia, callback, (void*) data, &zErrMsg);
		cout<<rc<<endl;
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);

			cout<<"Sentencia SQL insatisfactoria"<<endl;
		} else {
			cout<<"Sentencia SQL satisfactoria, actualizacion realizada" <<endl;
			//fprintf(stdout, "Reserva realizada:\n");
		}
		sqlite3_close(db1);

	}
