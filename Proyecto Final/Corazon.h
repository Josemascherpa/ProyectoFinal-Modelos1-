#ifndef CORAZON_H
#define CORAZON_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace std;
using namespace sf;

class Corazon
{
	Texture* corazont;
	Sprite* corazons;
	public:
		Corazon();
		~Corazon();
		
		void Draw(RenderWindow* ventana);//dibujo el rayo.
		void setPosicion(Vector2f pos);
		Sprite getSprite() { return *corazons; };
		Vector2f getPosition() { return posicion; };//devuelvo la posicion del rayo
		
private:		
		Vector2f posicion;
		

};

#endif