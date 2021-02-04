#include "Rayo.h"

Rayo::Rayo(Vector2f nave) {

	rayot = new Texture();
	rayos = new Sprite();

	rayot->loadFromFile("rayo.png");
	rayos->setTexture(*rayot);
	
	posicion.x = nave.x;
	posicion.y = nave.y;

	switch (rand() % 10 + 1 ) {
		case 1:
		 velocidad.y = 100.0f;
		 aceleracion.y = 100.0f; break;
		 
		case 2:
			velocidad.y = 200.0f;
			aceleracion.y = 200.0f; break;
			
		case 3:
			velocidad.y = 50.0f;
			aceleracion.y = 300.0f; break;
			
		case 4:
			velocidad.y = 100.0f;
			aceleracion.y = 20.0f; break;
			
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
			velocidad.y = 50.0f;
			aceleracion.y = 800.0f; break;
			
		case 9:
			velocidad.y = 500.0f;
			aceleracion.y = 800.0f; break;
			
		case 10:
			velocidad.y = 700.0f;
			aceleracion.y = 800.0f; break;
			
		default:break;
	}
		
	


}

void Rayo::Draw(RenderWindow* ventana) {
	ventana->draw(*rayos);
}

void Rayo::Update(float dt) {

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