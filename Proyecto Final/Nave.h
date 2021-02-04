#ifndef NAVE_H
#define NAVE_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "SFML/Audio.hpp"
#include "Rayo.h"
#include "Corazon.h"

using namespace sf;
using namespace std;

class Nave
{


public:
	
	Nave(string filename);//Constructor
	~Nave();//Destructor
	void Draw(RenderWindow* _ventana);//Dibujar
	void Update(float dt);//Comportamiento fisico
	void setPosicion(Vector2f pos) { posicion = pos; }
	void setVelocidad(Vector2f vel) { velocidad = vel; }
	void setAceleracion(Vector2f acc) { aceleracion = acc; }
	void setTextura(string filename);
	Vector2f getPosicion() { return posicion; }//posicion mas suma, para ubicar el rayo bajo la nave.
	void setTextura2(string filename);
	
	//Rayo
	Rayo* tirarRayo();
	bool rayoCayendo = false;
	
	

		
	

protected:
	Vector2f aceleracion;
	Vector2f velocidad;
	Vector2f posicion;
	Texture* navet;
	Sprite* naves;
	Texture* navet2;
	


};

#endif
