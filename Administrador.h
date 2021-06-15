/*
 * Administrador.h
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_
#include "Usuario.h"

class Administrador: public Usuario{
private:

public:

	//CONSTRUCTORES


	Administrador(Usuario*);
	Administrador(const Administrador&);
	virtual ~Administrador();

	void crearHabitaciones();
	void eliminarHabitaciones();
	void listarReservas();//usar el objeto reservasy sobreescribir el metodo de la clase pafre
	void crearReserva();//rellenarlo con datos de usuario
	void eliminarReserva();//(?)
	void listarTrabajadores();
	void CrearTrabajadores();
	void eliminarTrabajadores();
	void listarUsuarios();
	virtual char* getTipoUsuario();
	//virtual
	//void imprimirUsuario();

};

#endif /* ADMINISTRADOR_H_ */
