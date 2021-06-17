/*
 * Usuario.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef USUARIO_H_
#define USUARIO_H_
#include "Reserva.h"
#include "sqlite/sqlite3.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Reservas.h"
#include "Habitacion.h"
#include "Habitaciones.h"

class Usuario
{
private:

	int idUsuario;
	char* nombreUsuario;
	char* correoUsuario;
	char* contrasenyaUsuario;
	int edadUsuario;
	Reservas *reservasUsuario;



public:
	Usuario();
	Usuario(const int, char*, char*, char*, int);
	Usuario(const Usuario&);
	~Usuario();

	void anyadirReserva(Reservas* re,Habitaciones* h );
	void modificarReserva(Habitaciones* h);
	int getIdUsuario()const;
	char* getNombreUsuario()const;
	void setNombreUsuario(char*);
	char* getCorreoUsuario()const;
	void setCorreoUsuario(char*);
	char* getContrasenyaUsuario()const;
	void setContrasenyaUsuario(char*);
	int getEdadUsuario()const;
	void setEdadUsuario(int);
	Reservas* getReservaUsuario()const;
	void setReservaUsuario(Reservas* reservasUsuario);

	int getNReservas()const;
	void setNReservas(int);
	virtual char* getTipoUsuario();
	char* intAChar(int n);



	//virtual
	void imprimirUsuario();//PORQUE OSTIAS NO ME RECONOCE ESTO

	void verhoteles();
	void listarHabitaciones();
	void listarReservas();
	int eliminarReserva(Reservas *re);





};


#endif /* DATA_USUARIO_H_ */
