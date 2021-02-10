#include "Personaje.h"

Personaje::Personaje(string filename){

	personajet = new Texture();
	personajes = new Sprite();
	personajet->loadFromFile(filename);
	personajes->setTexture(*personajet);
	personajes->setPosition(Vector2f(300.0f, 426.0f));
	posicion.x = 0.0f;
	posicion.y = 0.0f;
	velocidad.x = 0.0f;
	velocidad.y = 0.0f;
	aceleracion.x = 0.0f;
	aceleracion.y = 0.0f;
	personajet2 = new Texture();
	personajet2->loadFromFile("pj2.png");
	
}

Personaje::~Personaje() {

}

void Personaje::Draw(RenderWindow* _ventana) {

	_ventana->draw(*personajes);
	
}

void Personaje::Update(float dt) {

	velocidad.x += aceleracion.x * dt;
	posicion.x += velocidad.x * dt;
	posicion.y = 512;
	personajes->setPosition(posicion.x,posicion.y);

	if (velocidad.x < 0) {
		personajes->setTexture(*personajet2);
	}else if(velocidad.x > 0) {
		personajes->setTexture(*personajet);
	}
	
	if ((posicion.x <= -27.0f) &&(posicion.y == 512.0f)) {
		posicion.x = 770;

	}else if ((posicion.x >= 770) && (posicion.y == 512.0f)) {
		posicion.x = -27.0f;
	}
	

}

Sprite Personaje::getSprite() {
	return  *personajes;
}

