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
		void setPosicion(Vector2f pos) { posicion = pos; }
		void setVelocidad(Vector2f vel) { velocidad = vel; }
		void setAceleracion(Vector2f acc) { aceleracion = acc; }
		Vector2f getPosition() { return posicion; }
		Sprite getSprite();
		bool pjon = true;
		

	private:
		Vector2f aceleracion;
		Vector2f velocidad;
		Vector2f posicion;
};

#endif

