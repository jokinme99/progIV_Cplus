/*
 * Hoteles.h
 *
 *  Created on: 16 jun. 2021
 *      Author: 34618
 */

#ifndef HOTELES_H_
#define HOTELES_H_

#include "Hotel.h"

class Hoteles{
private:
	int numHoteles;
	Hotel *h[200];
public:
	Hoteles();
	~Hoteles();

	void anyadirHotel(Hotel  *h);
	void quitarHotel(int);
	void imprimirHoteles();
	int getNumHoteles();
	Hotel* getHotel(int idHotel);
	void editarHotel(int, float);
};

#endif /* HOTELES_H_ */
