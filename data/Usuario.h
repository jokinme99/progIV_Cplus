/*
 * Usuario.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef DATA_USUARIO_H_
#define DATA_USUARIO_H_
#include "Reserva.h"

namespace data{

class Usuario
{
private:
	static int count;
	int idUsuario;
	char* nombreUsuario;
	char* correoUsuario;
	char* contrasenyaUsuario;
	int edadUsuario;
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
	bool comprobarUsuario(char *usuario, char *contrasenya);

};

}
#endif /* DATA_USUARIO_H_ */
