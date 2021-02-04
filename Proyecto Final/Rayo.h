#ifndef RAYO_H
#define RAYO_H
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

using namespace sf;
using namespace std;

class Rayo
{
	Texture* rayot;
	Sprite* rayos;
public:
	Rayo(Vector2f nave);
	~Rayo();
	void Draw(RenderWindow* ventana);//dibujo el rayo.
	void Update(float dt);//actualizo la posicion en el eje Y.
	void setPosicion(Vector2f pos);//Seteo su posicion bajo la nave.
	Vector2f getPosition() { return posicion; };//devuelvo la posicion del rayo
	Sprite getSprite();

private:
	Vector2f aceleracion;
	Vector2f velocidad;
	Vector2f posicion;
};
#endif