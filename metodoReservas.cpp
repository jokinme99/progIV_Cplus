/*
 * metodoReservas.cpp
 *
 *  Created on: 14 jun. 2021
 *      Author: jokin
 */
#include "Reserva.h"
#include <iostream>
//#include "sqlite3.h" da error
//#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include"metodoReservas.h"
#include "Habitacion.h"
using namespace std;

char* intAChar(int numero){
	string s = to_string(numero);
	const char *c = s.c_str();
    return (char*) c;
}

int crearReserva(sqlite3* db, char* nombreUsuario, int hotel, int numHabitacion, int dia, int hora){

	Reserva r;
	Habitacion h;
	char* tipoHabitacion;int planta;int precio;char* nombreHotel;
	int idUsuario;
	sqlite3_stmt *stmt2;//SELECT PARA CONSEGUIR EL ID
	char sql2[] = "SELECT id_usuario FROM USUARIO WHERE nombre_usuario = '";
	strcat(sql2, nombreUsuario);
	char fr2[] = "'";
	strcat(sql2, fr2);
	int rc = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL);
		if (rc != SQLITE_OK) {
			cout << "Error al hacer la sentencia (SELECT)" << endl;
			return rc;
		}
		do{
				rc = sqlite3_step(stmt2);
				if(rc == SQLITE_ROW){
					idUsuario = sqlite3_column_int(stmt2,0);

				}
		}while(rc == SQLITE_ROW);

		rc=sqlite3_finalize(stmt2);
		if(rc != SQLITE_OK){
			cout << "Error al finalizar la consulta(SELECT)" << endl;
			return rc;
		}
	sqlite3_stmt * stmt;

	char sql[]= "SELECT H.nombre_hotel, M.numero_habitacion, M.tipo_habitacion, M.planta_habitacion, M.precio_habitacion FROM HOTEL H, HABITACION M, HOTEL_TIENE_HABITACIONES T WHERE H.id_hotel = ? AND H.id_hotel = T.id_hotel AND T.id_habitacion = M.id_habitacion";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			cout << "Error al hacer la sentencia (SELECT)" << endl;
			return rc;
		}

	rc= sqlite3_bind_int(stmt,1,hotel);
	if(rc!=SQLITE_OK){
		cout<<"Error al bindear la consulta(SELECT)"<<endl;
		cout<<sqlite3_errmsg(db)<<endl;
		return rc;
	}
	//Ejecutamos sql
	do{
		rc = sqlite3_step(stmt);
		if(rc == SQLITE_ROW){
			strcpy(nombreHotel, (char*)sqlite3_column_text(stmt,0));
			numHabitacion = sqlite3_column_int(stmt,1);
			strcpy(tipoHabitacion, (char*)sqlite3_column_text(stmt,2));
			planta = sqlite3_column_int(stmt,3);
			precio = sqlite3_column_int(stmt,4);
			h.setNumHabitacion(numHabitacion);
			h.setPlantaHabitacion(planta);
			h.setPrecioHabitacion(precio);
			h.setTipoHabitacion(tipoHabitacion);
			r.setDiaReserva(dia);
			r.setHoraReserva(hora);
			r.setHabitacionReservada(&h);//usuarios tiene reservas no al reves

		}
	}while(rc == SQLITE_ROW);

	rc=sqlite3_finalize(stmt);
	if(rc != SQLITE_OK){
		cout << "Error al finalizar la consulta(SELECT)" << endl;
		return rc;
	}
	sqlite3_stmt *stmt3;	//crear stmt

		char sql3[] =
				"INSERT INTO RESERVA (dia_reserva,hora_reserva,id_usuario,id_habitacion) VALUES (?, ?, ?,?)";
		rc = sqlite3_prepare_v2(db, sql3, -1, &stmt3, NULL);
		if (rc != SQLITE_OK) {
			cout << "Error al hacer la sentencia (INSERT)" << endl;
			printf("%s\n", sqlite3_errmsg(db));
			return rc;
		}

		rc = sqlite3_bind_int(stmt3, 1, dia);
		rc = sqlite3_bind_int(stmt3, 2, hora);
		rc = sqlite3_bind_int(stmt3, 3, idUsuario);
		rc = sqlite3_bind_int(stmt3,4,numHabitacion);
		if (rc != SQLITE_OK) {
			cout << "Error al bindear la consulta(INSERT)" << endl;
			cout << sqlite3_errmsg(db) << endl;

			return rc;
		}
		rc = sqlite3_step(stmt3);
			if (rc == SQLITE_DONE) {

			}

			rc = sqlite3_finalize(stmt3);
			if (rc != SQLITE_OK) {
				cout << "Error al finalizar la consulta(INSERT)" << endl;
				printf("%s\n", sqlite3_errmsg(db));

				return rc;
			}

				cout << "Su reserva se ha realizado con exito" << endl;
				cout << "Los datos de la reserva son los siguientes:" << endl;
				cout << "Hotel: "<<nombreHotel<<", dia: "<<r.getDiaReserva()<<", hora: "<<r.getHoraReserva()<<", tipo habitacion: "<<r.getHabitacionReservada()->getTipoHabitacion()<<", planta: "<<r.getHabitacionReservada()->getPlantaHabitacion()<<", numero: "<<r.getHabitacionReservada()->getNumHabitacion()<<", precio: "<<r.getHabitacionReservada()->getPrecioHabitacion()<<endl;
				return SQLITE_OK;


}



