/*
 * usuario.cpp
 *
 *  Created on: May 13, 2021
 *      Author: suhar.txabarri
 */
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "Usuario.h"
#include "sqlite/sqlite3.h"

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Reserva.h"
using namespace std;

	Usuario::Usuario(){
		this->idUsuario = 0;
		this->nombreUsuario = new char[1];
		this->nombreUsuario[0] = '\0';
		this->correoUsuario = new char[1];
		this->correoUsuario[0] = '\0';
		this->contrasenyaUsuario = new char[1];
		this->contrasenyaUsuario[0] = '\0';
		this->edadUsuario = 0;
		this->reservasUsuario = NULL;
		this->nReservas = 0;


	}


	Usuario::Usuario(int id, char* nombre, char* correo, char* contrasenya, int edad){

		this->idUsuario = id;
		this->nombreUsuario = (char*)malloc(sizeof(strlen(nombre))+1);
		strcpy(this->nombreUsuario, nombre);
		this->correoUsuario = (char*)malloc(sizeof(strlen(correo))+1);
		strcpy(this->correoUsuario, correo);
		this->contrasenyaUsuario = (char*)malloc(sizeof(strlen(contrasenya))+1);
		strcpy(this->contrasenyaUsuario,contrasenya);
		this->edadUsuario=edad;
		this->nReservas = 0;


		this->reservasUsuario = NULL;



	}
	Usuario::Usuario(const Usuario& u){

		this->idUsuario =u.idUsuario;
		this->nombreUsuario=new char[strlen(u.nombreUsuario) +1];
		strcpy(this->nombreUsuario, u.nombreUsuario);
		this->correoUsuario=new char[strlen(u.correoUsuario) +1];
		strcpy(this->correoUsuario, u.correoUsuario);
		this->contrasenyaUsuario=new char[strlen(u.contrasenyaUsuario) +1];
		strcpy(this->contrasenyaUsuario, u.contrasenyaUsuario);
		this->edadUsuario=u.edadUsuario;
		this->nReservas = u.nReservas;
		for(int i=0;i<u.nReservas;i++){
			this->reservasUsuario[i] = u.reservasUsuario[i];
		}

	}
	Usuario::~Usuario(){

	delete &this->idUsuario;
	delete[] this->nombreUsuario;
	delete[] this->correoUsuario;
	delete[] this->contrasenyaUsuario;
	delete &this->edadUsuario;
	delete &this->nReservas;
	//delete[] this->reservasUsuario;


	}

	int Usuario::getIdUsuario()const{

		return this->idUsuario;

	}

	char* Usuario::getNombreUsuario()const{
		return this->nombreUsuario;
	}
	void Usuario::setNombreUsuario(char* nombre){
		this->nombreUsuario = (char*)malloc(sizeof(strlen(nombre))+1);
		strcpy(this->nombreUsuario, nombre);
	}
	char* Usuario::getCorreoUsuario()const{
		return this->correoUsuario;
	}
	void Usuario::setCorreoUsuario(char* correo){
		this->correoUsuario = (char*)malloc(sizeof(strlen(correo))+1);
		strcpy(this->correoUsuario, correo);
	}
	char* Usuario::getContrasenyaUsuario()const{
		return this->contrasenyaUsuario;
	}
	void Usuario::setContrasenyaUsuario(char* contrasenya){
		this->contrasenyaUsuario = (char*)malloc(sizeof(strlen(contrasenya))+1);
		strcpy(this->contrasenyaUsuario,contrasenya);
	}
	int Usuario::getEdadUsuario()const{
		return this->edadUsuario;
	}
	void Usuario::setEdadUsuario(int edad){
		this->edadUsuario = edad;
	}
	char* Usuario::getTipoUsuario(){
		return "usuario";
	}


	void Usuario::verhoteles(){


	}
	void Usuario::listarHabitaciones(){


	}
	void Usuario::listarReservas(){


	}

	void Usuario::eliminarReserva(){


	}

	void Usuario::imprimirUsuario(){
		cout<<"Usuario "<<this->idUsuario<<": "<<endl;
		cout<<"Nombre: "<<this->nombreUsuario<<" Correo: "<<this->correoUsuario<<endl;
		cout<<"Edad: "<<this->edadUsuario<<" Tipo de usuario: "<< this->getTipoUsuario()<<endl;
		cout<<endl;
	}
	char* Usuario::intAChar(int numero){
		string s = to_string(numero);
		const char *c = s.c_str();
	    return (char*) c;
	}

void Usuario::crearReserva(sqlite3* db, char* nombreUsuario, char* nombreHotel, char* tipoHabitacion, int dia, int hora){

	/*
	//Habria que preguntar al usuario cuantas habitaciones quiere reservar
	Reserva r;
	Habitacion h;
	int numEstrellas;
	int numHabitacionesDisponibles;
	int numHabitacion;
	int planta;
	int precio;
	int idUsuario;//Enlazar idUsuario con char usuario(Tabla Usuario)
	//int idHotel;//Enlazar con nombreHotel(Tabla hotel)
	//int idHabitacion;//Enlazar con tipoHabitacion(Tabla Habitacion)

	//idUsuario(Tabla Usuario) = idUsuario(Tabla Reserva)
	//idHotel(Tabla Hotel) = idHotel(Tabla HotelTieneHabitaciones)
	//idHabitacion(Tabla Habitacion) = idHabitacion(Tabla HotelTieneHabitaciones)
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

	char sql[]= "SELECT H.nombre_hotel, H.num_estrellas, H.num_habitaciones_disponibles, M.numero_habitacion, M.tipo_habitacion, M.planta_habitacion, M.precio_habitacion FROM HOTEL H, HABITACION M, HOTEL_TIENE_HABITACIONES T WHERE H.nombre_hotel = ? AND M.tipo_habitacion = ? AND M.planta_habitacion = ? AND H.id_hotel = T.id_hotel AND T.id_habitacion = M.id_habitacion";
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			cout << "Error al hacer la sentencia (SELECT)" << endl;
			return rc;
		}

	rc= sqlite3_bind_text(stmt,1,nombreHotel,strlen(nombreHotel),SQLITE_STATIC);//nombreHotel introducido
	rc = sqlite3_bind_text(stmt,2,tipoHabitacion,strlen(tipoHabitacion), SQLITE_STATIC);
	rc = sqlite3_bind_int(stmt,3,planta);
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
			numEstrellas = sqlite3_column_int(stmt,1);
			numHabitacionesDisponibles = sqlite3_column_int(stmt,2);
			numHabitacion = sqlite3_column_int(stmt,3);
			strcpy(tipoHabitacion, (char*)sqlite3_column_text(stmt,4));
			planta = sqlite3_column_int(stmt,5);
			precio = sqlite3_column_int(stmt,6);
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
				"INSERT INTO RESERVA (dia_reserva,hora_reserva,id_usuario) VALUES (?, ?, ?, ?, ";

		char fr3[]=")";
		char* pap=intAChar(idUsuario);
		strcat(sql3,pap);
		strcat(sql3,fr3);
		rc = sqlite3_prepare_v2(db, sql3, -1, &stmt3, NULL);
		if (rc != SQLITE_OK) {
			cout << "Error al hacer la sentencia (INSERT)" << endl;
			printf("%s\n", sqlite3_errmsg(db));
			return rc;
		}

		rc = sqlite3_bind_int(stmt3, 1, dia);
		rc = sqlite3_bind_int(stmt3, 2, hora);
		rc = sqlite3_bind_int(stmt3, 3, idUsuario);
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

	*/

}






