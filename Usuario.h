/*
 * Usuario.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef USUARIO_H_
#define USUARIO_H_
#include "Reserva.h"


class Usuario
{
private:

	int idUsuario;
	char* nombreUsuario;
	char* correoUsuario;
	char* contrasenyaUsuario;
	int edadUsuario;
	Reserva* reservasUsuario;
	int nReservas;//para medir cant. de reservas
public:
	Usuario();
	Usuario(const int, char*, char*, char*, int);
	Usuario(const Usuario&);
	~Usuario();

	int getIdUsuario()const;
	char* getNombreUsuario()const;
	void setNombreUsuario(char*);
	char* getCorreoUsuario()const;
	void setCorreoUsuario(char*);
	char* getContrasenyaUsuario()const;
	void setContrasenyaUsuario(char*);
	int getEdadUsuario()const;
	void setEdadUsuario(int);
	Reserva* getReservasUsuario()const;
	void setReservasUsuario(Reserva*);
	int getNReservas()const;
	void setNReservas(int);

	void verhoteles();
	void listarHabitaciones();
	void listarReservas();
	void crearReserva();
	void eliminarReserva();




};


#endif /* DATA_USUARIO_H_ */
