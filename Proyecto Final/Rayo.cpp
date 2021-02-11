#include "Rayo.h"

Rayo::Rayo(Vector2f nave) {

	rayot = new Texture();
	rayos = new Sprite();

	rayot->loadFromFile("rayo.png");
	rayos->setTexture(*rayot);
	
	posicion.x = nave.x;
	posicion.y = nave.y;

	switch (rand() % 13 + 1 ) {//Velocidad random cada vez que instancio un rayo.
		case 1:
		 velocidad.y = 200.0f;
		 aceleracion.y = 500.0f; break;
		 
		case 2:
			velocidad.y = 400.0f;
			aceleracion.y = 400.0f; break;
			
		case 3:
			velocidad.y = 100.0f;
			aceleracion.y = 300.0f; break;
			
		case 4:
			velocidad.y = 500.0f;
			aceleracion.y = 3000.0f; break;
			
		case 5:
			velocidad.y = 300.0f;
			aceleracion.y = 300.0f; break;
			
		case 6:
			velocidad.y = 400.0f;
			aceleracion.y = 400.0f; break;
			
		case 7:
			velocidad.y = 500.0f;
			aceleracion.y = 500.0f; break;
			
		case 8:
			velocidad.y = 800.0f;
			aceleracion.y = 800.0f; break;
			
		case 9:
			velocidad.y = 500.0f;
			aceleracion.y = 800.0f; break;
			
		case 10:
			velocidad.y = 700.0f;
			aceleracion.y = 800.0f; break;
		case 11:
			velocidad.y = 1000.0f;
			aceleracion.y = 800.0f; break;
		case 12:
			velocidad.y = 900.0f;
			aceleracion.y = 900.0f; break;
		case 13:
			velocidad.y = 1200.0f;
			aceleracion.y = 1200.0f; break;
		default:break;
	}
		
	


}

void Rayo::Draw(RenderWindow* ventana) {
	ventana->draw(*rayos);
}

void Rayo::Update(float dt) {//Caida del rayo en base a su posicion.

	velocidad.y += aceleracion.y * dt;
	posicion.y += velocidad.y * dt;
	rayos->setPosition(posicion);
	
}

void Rayo::setPosicion(Vector2f pos) {


	rayos->setPosition(pos);

}

Sprite Rayo::getSprite(){
	
	return *rayos;

}

Rayo::~Rayo() {

}