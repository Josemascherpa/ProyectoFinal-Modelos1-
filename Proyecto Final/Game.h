#ifndef JUEGO_H
#define JUEGO_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Nave.h"
#include <iostream>
#include "Personaje.h"
#include "Rayo.h"
#include "SFML/Audio.hpp"
#include "Corazon.h"
#include <time.h>
#include<stdlib.h>
#include <ctime>

using namespace sf;
using namespace std;


class Game {
	
public:
	Game() {
		ventana = new RenderWindow(VideoMode(800, 600), "El Veloz");//Creo ventana con un tamaño de 800x600
		ventana->setFramerateLimit(60);//Seteo fraps por segundo maximos.
		fondo.loadFromFile("fondo.png");//Cargo el fondo como textura.
		fondos.setTexture(fondo);//cargo el fondo como sprite.
		srand(time(NULL));//Refresco semillas para el rand()

		//NAVE
		nave = new Nave("nave.png");
		nave->setPosicion(Vector2f(0.0f, 0.0f));//seteo posicion de la nave.
		tope.x = 600;//tope de la nave para su vuelta hacia el otro lado.
		tope.y = 0;
		inicio.x = 0;
		inicio.y = 0;

		//PERSONAJE
		pj = new Personaje("pj.png");//Instancio personaje.
				
		//SONIDOS
		vueltaNave = new Sound;
		bufferNave = new SoundBuffer;//Seteo de buffer sonido nave.
		bufferNave->loadFromFile("vueltanave.wav");//seteo sonido
		vueltaNave->setBuffer(*bufferNave);//seteo el buffer en el sonido
		vueltaNave->setVolume(5.0f);
		bufferRayo = new SoundBuffer;
		caidaRayo = new Sound;
		bufferRayo->loadFromFile("rayolanzado.wav");
		caidaRayo->setBuffer(*bufferRayo);
		caidaRayo->setVolume(5.0f);
		bufferPerdiste = new SoundBuffer;
		perdiste = new Sound;
		bufferPerdiste->loadFromFile("perdiste.wav");
		perdiste->setBuffer(*bufferPerdiste);

		//VIDAS
		vidast = new Texture;//Textura sprite Vidas:
		vidass = new Sprite;
		vidast->loadFromFile("vidas.png");
		vidass->setTexture(*vidast);
		vidass->setPosition(0.0f, 7.0f);
		corazonest = new Texture;//Textura corazones
		corazoness1 = new Sprite;
		corazoness2 = new Sprite;
		corazoness3 = new Sprite;
		corazonest->loadFromFile("corazon.png");
		corazoness1->setTexture(*corazonest);
		corazoness2->setTexture(*corazonest);
		corazoness3->setTexture(*corazonest);
		corazoness1->setPosition(150.0f, 5.0f);//posiciono los corazones
		corazoness2->setPosition(180.0f, 5.0f);
		corazoness3->setPosition(210.0f, 5.0f);

		//TERMINAR JUEGO
		terminar = new Clock();//timing para terminar el juego.
		timeTerminar = new Time();
		perdistes = new Sprite();//Sprite al finalizar el juego.
		perdistet = new Texture();
		perdistet->loadFromFile("perdiste.png");
		perdistes->setTexture(*perdistet);		
		perdistes->setPosition(200.0f, 200.0f);
		
		//Corazon
		corazon = new Corazon();//Instancio corazon luego de perder 1 vida, para poder recuperarlas.
		sacarCorazon = new Clock();//Timing para que aparezca cada cierto tiempo.
		tiempoCorazon = new Time();
		posRand.x = 50 + rand() % (599 - 50);//Posicion random donde aparecer.
		posRand.y = 540.0f;//que siempre aparezca a la misma altura en el eje Y.

		//Boton Restart
		botont = new Texture();//Textura boton restart.
		botons = new Sprite();
		botont->loadFromFile("boton.png");
		botons->setTexture(*botont);		
		botons->setPosition(750.0f, 0.0f);


		
	}
	~Game();//Destructor
	void Loop();
	void ProcesarEventos();
	void Actualizar(float dt);
	void Dibujar();
	void ProcesarColisiones();//Metodo que maneja las colisiones
	void terminarJuego();//Metodo terminar juego, luego de un tiempo, pone un booleano en true.
	void aparecerCorazon();	
	bool presionBoton();
	void Restart();
	
	

private:
	//topes nave
	Vector2f tope;
	Vector2f inicio;
	//Ventana
	RenderWindow* ventana;
	//fondo
	Texture fondo;
	Sprite fondos;
	//Nave
	Nave* nave;
	//Personaje
	Personaje* pj;
	//Rayo
	Rayo* rayo;//Creo un puntero de estilo rayo y lo igualo al metodo de rayo en nave.

	//Corazon
	Corazon* corazon;
	bool respCorazon = false;
	Clock* sacarCorazon;
	Time* tiempoCorazon;
	Vector2f posRand;
	//Sonido
	SoundBuffer* bufferNave;
	Sound* vueltaNave;
	SoundBuffer* bufferRayo;
	Sound* caidaRayo;	
	SoundBuffer* bufferPerdiste;
	Sound* perdiste;
	//Vidas
	Texture* vidast;
	Sprite* vidass;
	Texture* corazonest;
	Sprite* corazoness1;
	Sprite* corazoness2;
	Sprite* corazoness3;
	int contador=3;

	//Terminar juego
	bool juegoterminado = false;
	bool pasaronSeg = false;
	Texture* perdistet;
	Sprite* perdistes;

	Clock* terminar;
	Time* timeTerminar;

	//Boton restart
	Vector2i posicion_mouse;
	Texture* botont;
	Sprite* botons;
	
};


#endif