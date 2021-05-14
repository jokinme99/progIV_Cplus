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
	static int count;
	int idUsuario;
	char* nombreUsuario;
	char* correoUsuario;
	char* contrasenyaUsuario;
	int edadUsuario;
	Reserva* reservasUsuario;
	int nReservas;//para medir cant. de reservas
public:
	Usuario();
	Usuario(const int, char*, char*, char*, int,Reserva*,int);
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

	bool comprobarUsuario(char *usuario, char *contrasenya);

};


#endif /* DATA_USUARIO_H_ */
