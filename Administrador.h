/*
 * Administrador.h
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_
#include "Usuario.h"
#include "Habitaciones.h"
#include "Trabajadores.h"
class Administrador: public Usuario{
private:

public:

	//CONSTRUCTORES

	Administrador(int idUsuario,
	char* nombreUsuario,
	char* correoUsuario,
	char* contrasenyaUsuario,
	int edadUsuario);


	Administrador(Usuario*);
	Administrador(const Administrador&);
	virtual ~Administrador();

	void crearHabitacion();
	void eliminarHabitacion();
	void listarReservas();//usar el objeto reservasy sobreescribir el metodo de la clase pafre
	void crearReserva();//rellenarlo con datos de usuario
	void eliminarReserva();//(?)
	void listarTrabajadores();
	void CrearTrabajador();
	void eliminarTrabajador();
	void listarUsuarios();
	virtual char* getTipoUsuario();
	virtual void editarHabitacion(Habitaciones*);
	//virtual
	//void imprimirUsuario();

	virtual void editarTrabajador(Trabajadores*);
	virtual void anyadirHabitacion(Habitaciones*);
	virtual int eliminarHabitacion(Habitaciones*);

};

#endif /* ADMINISTRADOR_H_ */
