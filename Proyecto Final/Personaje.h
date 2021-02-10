#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace std;
using namespace sf;

class Personaje
{
	public:
		Personaje(string filename);
		~Personaje();
		Texture *personajet;
		Sprite *personajes;
		Texture* personajet2;
		void Draw(RenderWindow* _ventana);//Dibujar
		void Update(float dt);//Comportamiento fisico
		void setPosicion(Vector2f pos) { posicion = pos; }//seteo de posicion.
		void setVelocidad(Vector2f vel) { velocidad = vel; }//Seteo velocidad para el movimiento con letras.
		Vector2f getPosition() { return posicion; }//retorno posicion.
		Sprite getSprite();//retorno sprite.
		bool pjon = true;
		

	private:
		Vector2f aceleracion;
		Vector2f velocidad;
		Vector2f posicion;
};

#endif

