/*
 * Usuario.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef DATA_USUARIO_H_
#define DATA_USUARIO_H_
#include "Reserva.h"
class Usuario
{
private:
	int idUsuario;
	char* nombreUsuario;
	char* correoUsuario;
	char* contrasenyaUsuario;
	int edadUsuario;
	Reserva* reservaUsuario;
public:
	Usuario();
	Usuario(const int, char*, char*, char*, int, Reserva*);
	Usuario(const Usuario&);
	~Usuario();

	int getIdUsuario()const;
	void setIdUsuario(const int);
	char* getNombreUsuario()const;
	void setNombreUsuario(char*);
	char* getCorreoUsuario()const;
	void setCorreoUsuario(char*);
	char* getContrasenyaUsuario()const;
	void setContrasenyaUsuario(char*);
	int getEdadUsuario()const;
	void setEdadUsuario(int);
	Reserva* getReservaUsuario()const;
	void setReservaUsuario(Reserva*);

};


#endif /* DATA_USUARIO_H_ */
