#include "Corazon.h"

Corazon::Corazon() {

	corazont = new Texture();
	corazons = new Sprite();

	corazont->loadFromFile("corazon1.png");
	corazons->setTexture(*corazont);
	corazons->setPosition(900.0f, 900.0f);
	
}

void Corazon::Draw(RenderWindow* ventana) {
	ventana->draw(*corazons);
}

void Corazon::setPosicion(Vector2f pos) {
	posicion = pos;
	corazons->setPosition(pos);
}

Corazon::~Corazon() {}