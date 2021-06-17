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
#include "Reserva.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Habitacion.h"
#include "Habitaciones.h"
#include "Reservas.h"
#include "DatosSQL.h"
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
		this->reservasUsuario=new Reservas();


	}


	Usuario::Usuario(int id, char* nombre, char* correo, char* contrasenya, int edad){

		this->idUsuario = id;
		this->nombreUsuario =new char[strlen(nombre)+1];
		strcpy(this->nombreUsuario, nombre);
		this->correoUsuario =new char[strlen(correo)+1];
		strcpy(this->correoUsuario, correo);
		this->contrasenyaUsuario =new char[strlen(contrasenya)+1];
		strcpy(this->contrasenyaUsuario,contrasenya);
		this->edadUsuario=edad;
		this->reservasUsuario = new Reservas();

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
		this->reservasUsuario=u.reservasUsuario;

		}

	Usuario::~Usuario(){

	delete &this->idUsuario;
	delete[] this->nombreUsuario;
	delete[] this->correoUsuario;
	delete[] this->contrasenyaUsuario;
	delete &this->edadUsuario;

	delete[] this->reservasUsuario;


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
	Reservas* Usuario::getReservaUsuario()const{
		return this->reservasUsuario;
	}
	void Usuario::setReservaUsuario(Reservas* reservasUsuario){
		this->reservasUsuario=reservasUsuario;
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
		cout<<"Reservas: "<<endl;
		cout<<"----------"<<endl;
		if (this->reservasUsuario->getNumReservas()==0) {
			cout<<"(este usuario no tiene reservas)"<<endl;
		}else{
		this->reservasUsuario->imprimirReservas();
		}
	}

	char* Usuario::intAChar(int numero){
		string s = to_string(numero);
		const char *c = s.c_str();
	    return (char*) c;
	}
	void Usuario::anyadirReserva(Reservas* re,Habitaciones* h){

		int eleccionNHabitacion;
		int dia;
		int hora;

		//re->getOrdenReserva(re->getNumReservas())->getIdReserva();//AQUI TENEMOS EL ID DE LA NUEVA RESERVA
		cout << endl;
		cout << "Ingrese el dia de la reserva que desea anyadir: ";
		cin >> dia;
		while(dia<1||dia>31){
			cout<<"por favor indique un dia adecuado"<<endl;
			cin >> dia;
		}
		cout << endl;
		cout << "Ingrese la hora de llegada al hotel que desea anyadir: "<<endl;
		cin >> hora;
		while(hora<0||hora>24){
			cout<<"por favor indique una hora adecuada"<<endl;
			cin >> hora;
		}
		cout << "Ingrese el id de la habitacion que desea reservar: "<<endl;

		cout<<"Aqui tienes las habitaciones que tenemos disponibles"<<endl;

		h->imprimirHabitaciones();



		cin >> eleccionNHabitacion;

		//cout<<h->habitacionExiste(eleccionNHabitacion)<<endl;


		while(h->habitacionExiste(eleccionNHabitacion)==0){

			cout<<"por favor habitacion adecuada"<<endl;


			cin >> eleccionNHabitacion;
		}


		cout << endl;

		Reserva *r = new Reserva(re->getOrdenReserva(),dia,hora,h->getHabitacion(eleccionNHabitacion));
		this->getReservaUsuario()->anyadirReserva(r);
		re->anyadirReserva(r);




		//ESTE METODO A�ADE UNA RESERVA




		/* Create SQL statement */
		char sql[] = "INSERT INTO RESERVA VALUES (";

		char con[] = "'",con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")", con9[] = "";


		string s = to_string(r->getIdReserva());
		char const *pchar = s.c_str();  //use char const* as target type
		char con10[5]; strcpy(con10, pchar);
		cout<<pchar<<endl;
		cout<<con10<<endl;
		 s = to_string(dia);
		char const *pchar2 = s.c_str();  //use char const* as target type
		char con11[5]; strcpy(con11, pchar2);
		 s = to_string(hora);
		char const *pchar3 = s.c_str();  //use char const* as target type
		char con12[5]; strcpy(con12, pchar3);
		 s = to_string(this->getIdUsuario());
		char const *pchar4 = s.c_str();  //use char const* as target type
		char con13[5]; strcpy(con13, pchar4);
		s = to_string(eleccionNHabitacion);
		char const *pchar5 = s.c_str();  //use char const* as target type
		char con14[5]; strcpy(con14, pchar5);
		strcat(sql, con);
		strcat(sql, con10);
		strcat(sql, con);
		strcat(sql, con1);
		strcat(sql, con);
		strcat(sql, con11);
		strcat(sql, con);
		strcat(sql, con2);
		strcat(sql, con);
		strcat(sql, con12);
		strcat(sql, con);
		strcat(sql, con3);
		strcat(sql, con);
		strcat(sql, con13);//CONVERTIR INT A CHAR
		strcat(sql, con);
		strcat(sql, con3);
		strcat(sql, con);
		strcat(sql, con14);
		strcat(sql, con);
		strcat(sql, con8);
		strcat(sql, con9);

		cout<<sql<<endl;

		llamadaSQL(sql);


	}
	void Usuario::modificarReserva(Habitaciones* h){
		int numReserva, nuevoDia,nuevaHora, nuevaHabitacion;

		cout<<"Estas son las reservas que estan a nombre su nombre: "<<endl;
		cout<<endl;
		this->getReservaUsuario()->imprimirReservas();
		cout<<endl;
		cout<<"Selecciona el numero de reserva que quierers modificar: ";
		cin>>numReserva;

		cout<<endl;

		while(this->getReservaUsuario()->reservaExiste(numReserva)==0){
			cout<<"por favor elija una reserva adecuada o una reserva de su propiedad"<<endl;
			cin >> numReserva;
		}
		cout<<endl;
		cout<<"Estos son los datos de su reserva: "<<endl;
		this->getReservaUsuario()->getReserva(numReserva)->imprimirReserva();

		cout<<endl;

		cout<<"introduce el nuevo dia para la reserva: "<<endl;


		cin >> nuevoDia;
		while(nuevoDia<1||nuevoDia>31){
			cout<<endl;
			cout<<"por favor indique un dia adecuado"<<endl;
			cin >> nuevoDia;
		}

		cout<<endl;
		cout<<"introduce la nueva hora para la entrada del hotel: "<<endl;

				cin >> nuevaHora;
				while(nuevaHora<0||nuevaHora>24){
					cout<<endl;
					cout<<"por favor indique una hora adecuada"<<endl;
					cin >> nuevaHora;
				}
				cout<<endl;
				cout << "Ingrese el id de la nueva habitacion que desea reservar: "<<endl;
				cout<<endl;

				cout<<"Aqui tienes las habitaciones que tenemos disponibles"<<endl;
				cout<<endl;

				h->imprimirHabitaciones();

				cin >> nuevaHabitacion;

				//cout<<h->habitacionExiste(eleccionNHabitacion)<<endl;

				while(h->habitacionExiste(nuevaHabitacion)==0){
					cout<<endl;
					cout<<"por favor habitacion que exista"<<endl;
					cin >> nuevaHabitacion;
				}

				cout << endl;

				this->getReservaUsuario()->getReserva(numReserva)->setDiaReserva(nuevoDia);
				this->getReservaUsuario()->getReserva(numReserva)->setHoraReserva(nuevaHora);
				this->getReservaUsuario()->getReserva(numReserva)->setHabitacionReservada(h->getHabitacion(nuevaHabitacion));

				char sql[] = "UPDATE RESERVA SET dia_reserva ='";

				char con[] = "'",con1[] = ",", con2[] = "hora_reserva='", con3[] = "id_habitacion='", con8[] = " WHERE id_reserva='", con9[] = ";";



				string s = to_string(nuevoDia);
				char const *pchar2 = s.c_str();  //use char const* as target type
				char con11[5]; strcpy(con11, pchar2);
				 s = to_string(nuevaHora);
				char const *pchar3 = s.c_str();  //use char const* as target type
				char con12[5]; strcpy(con12, pchar3);
				 s = to_string(numReserva);
				char const *pchar4 = s.c_str();  //use char const* as target type
				char con13[5]; strcpy(con13, pchar4);
				s = to_string(nuevaHabitacion);
				char const *pchar5 = s.c_str();  //use char const* as target type
				char con14[5]; strcpy(con14, pchar5);
				strcat(sql, con11);
				strcat(sql, con);
				strcat(sql, con1);
				strcat(sql, con2);
				strcat(sql, con12);
				strcat(sql, con);
				strcat(sql, con1);
				strcat(sql, con3);
				strcat(sql, con14);//CONVERTIR INT A CHAR
				strcat(sql, con);


				strcat(sql, con8);
				strcat(sql, con13);
				strcat(sql, con);
				strcat(sql, con9);
				cout<<endl;

				cout<<sql<<endl;

				llamadaSQL(sql);


	}






