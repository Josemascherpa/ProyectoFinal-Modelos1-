#include "Personaje.h"

Personaje::Personaje(string filename){

	personajet = new Texture();
	personajes = new Sprite();
	personajet->loadFromFile(filename);
	personajes->setTexture(*personajet);
	personajes->setPosition(Vector2f(300.0f, 426.0f));
	posicion.x = 300.0f;
	posicion.y = 0.0f;
	velocidad.x = 0.0f;
	velocidad.y = 0.0f;
	aceleracion.x = 0.0f;
	aceleracion.y = 0.0f;
	personajet2 = new Texture();
	personajet2->loadFromFile("pj2.png");//sprite para el otro lado al que se mueve.
	
}

Personaje::~Personaje() {

}

void Personaje::Draw(RenderWindow* _ventana) {

	_ventana->draw(*personajes);//Metodo para dibujar sprite.
	
}

void Personaje::Update(float dt) {//Delta time: tiempo transcurrido luego de cada frame

	velocidad.x += aceleracion.x * dt;//Movimiento en el eje X.
	posicion.x += velocidad.x * dt;
	posicion.y = 512;
	personajes->setPosition(posicion.x,posicion.y);//Seteo de posicion en base al movimiento.

	if (velocidad.x < 0) {//Seteo de textura y sprite dependiendo el lado al que se mueve el pj.
		personajes->setTexture(*personajet2);
	}else if(velocidad.x > 0) {
		personajes->setTexture(*personajet);
	}
	
	if ((posicion.x <= -27.0f) &&(posicion.y == 512.0f)) {//al salirse de pantalla que aparezca del otro lado el jugador.
		posicion.x = 770;

	}else if ((posicion.x >= 770) && (posicion.y == 512.0f)) {
		posicion.x = -27.0f;
	}
	

}

Sprite Personaje::getSprite() {//retornar sprite para poder obtener colisiones.
	return  *personajes;
}

