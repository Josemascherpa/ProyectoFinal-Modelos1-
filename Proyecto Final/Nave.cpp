#include "Nave.h"

Nave::Nave(string filename) {//seteo la textura al instanciar el objeto en Game.
	navet = new Texture();
	navet->loadFromFile(filename);//seteo textura
	naves = new Sprite();
	naves->setTexture(*navet);
	posicion.x = 0.0f;
	posicion.y = 0.0f;
	velocidad.x = 50.0f;
	velocidad.y = 0.0f;
	aceleracion.x = 10.0f;
	aceleracion.y = 0.0f;
	navet2 = new Texture();
	navet2->loadFromFile("nave2.png");

}

void Nave::Draw(RenderWindow* _ventana) {

	_ventana->draw(*naves);

}

void Nave::Update(float dt) {
	velocidad.x += aceleracion.x * dt;//A velocidad le sumo una aceleracion en base al delta time
	posicion.x += velocidad.x * dt;//a esa velocidad con aceleracion, se lo paso a la posicion del pj.
	naves->setPosition(posicion);//esta posicion al ser un vector2f, recibe la suma de velocidad y aceleracion multiplicados por dt en base al eje X

}

void Nave::setTextura(string filename) {//seteo textura al cambiar a velocidad negativa, cuando vuelve hacia el lado contrario.
	navet->loadFromFile(filename);

}

void Nave::setTextura2(string filename) {//vuelvo a setear la textura, para acomodar el lado hacia donde va.
	navet->loadFromFile(filename);

}

Rayo* Nave::tirarRayo() {
	
	
	return new Rayo(naves->getPosition()+Vector2f(100.0f,175.0f));//El puntero de estilo rayo en Game, es un nuevo rayo.
	
	
}



Nave::~Nave() {}

