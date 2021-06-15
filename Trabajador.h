/*
 * Trabajador.h
 *
 *  Created on: 11 may. 2021
 *      Author: jokin
 */

#ifndef TRABAJADOR_H_
#define TRABAJADOR_H_
class Trabajador
{
private:
	int idTrabajador;
	char* nombreTrabajador;
	char* dniTrabajador;
	int telefonoTrabajador;
	float sueldoTrabajador;

public:

	Trabajador();
	Trabajador(const int, char*, char*, int, float);
	Trabajador(const Trabajador&);
	~Trabajador();

	int getIdTrabajador()const;
	void setIdTrabajador(const int);
	char* getNombreTrabajador()const;
	void setNombreTrabajador(char*);
	char* getDNITrabajador()const;
	void setDNITrabajador(char*);
	int getTelefonoTrabajador()const;
	void setTelefonoTrabajador(int);
	float getSueldoTrabajador()const;
	void setSueldoTrabajador(float);

	void imprimir();

};


#endif /* TRABAJADOR_H_ */
