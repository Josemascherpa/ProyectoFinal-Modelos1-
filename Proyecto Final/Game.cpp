#include "Game.h"

void Game::Loop() {
    // Start the game loop

    Clock clock;
    clock.restart();
    float dt;
    while (ventana->isOpen())
    {
        float dt = clock.restart().asSeconds();
        
        ProcesarEventos();// Procesar eventos
        
        Actualizar(dt);// Actualizar el juego
        
        Dibujar();// Dibujar el juego

        if (juegoterminado == true) {
            
            break;
        }

    }

}
void Game::ProcesarEventos()
{
    sf::Event event;
    while (ventana->pollEvent(event))
    {
        // Cerrar ventana
        switch (event.type) {
            case Event::Closed:
                ventana->close(); break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::D) {
                    pj->setVelocidad(Vector2f(200.0f, 0.0f));//se le asigna velocidad al sprite
                }
                if (event.key.code == Keyboard::A) {
                    pj->setVelocidad(Vector2f(-200.0f, 0.0f));
                }break;
                               
            case Event::KeyReleased:
                if (event.key.code == Keyboard::D) {
                    pj->setVelocidad(Vector2f(0.0f, 0.0f));//se le asigna una velocidad en 0, asi se frena
                }
                if ((event.type == event.KeyReleased) && (event.key.code == Keyboard::A)) {
                    pj->setVelocidad(Vector2f(0.0f, 0.0f));
                }break;
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Button::Left) {
                    if (presionBoton()) {
                        Restart();
                        cout << "Apredato" << endl;
                        
                    }
                }break;
            default:break;              
        }           
        
    }

}
void Game::Actualizar(float dt)
{        
    if (pasaronSeg == true) {
        terminarJuego();
    }
    //NAVE
    nave->Update(dt);
    if (nave->getPosicion().x >= tope.x) {//si nave llega a cierta posicion en X
        nave->setVelocidad(Vector2f(-50.0f, 0.0f));//setea velocidad negativa, para que vuelva hacia el otro lado.
        nave->setAceleracion(Vector2f(-50.0f, 0.0f));//setea la aceleracion para que tenga mas velocidad
        nave->setTextura("nave2.png");
        vueltaNave->play();

    }
    else if (nave->getPosicion().x <= inicio.x) {
        nave->setVelocidad(Vector2f(50.0f, 0.0f));//setea velocidad negativa, para que vuelva hacia el otro lado.
        nave->setAceleracion(Vector2f(50.0f, 0.0f));//setea la aceleracion para que tenga mas velocidad.
        nave->setTextura2("nave.png");
        vueltaNave->play();
    }
    //PERSONAJE
    pj->Update(dt);    
    //RAYO  
    if ((nave->rayoCayendo != true)) {//Si el rayo no esta cayendo, llamo el metodo tirar rayo, y pongo rayo cayendo en true.
        rayo = nave->tirarRayo();
        nave->rayoCayendo = true;
        caidaRayo->play();
        
    }    
    rayo->Update(dt);
    aparecerCorazon();
    if (rayo->getPosition().y > 600.0f) {//Si rayo supera los 600 en el eje Y, lo rayo cayendo en false.
        nave->rayoCayendo = false;

    }       
    if ((nave->rayoCayendo) && (pj->pjon)) {
        ProcesarColisiones(ventana);
    }
    
}

void Game::Dibujar()
{
    // Limpiar la venatana
    ventana->clear();

    // Dibujar el sprite
    ventana->draw(fondos);

    ventana->draw(*botons);

    nave->Draw(ventana);

    pj->Draw(ventana);

    rayo->Draw(ventana);
    
    corazon->Draw(ventana);

    if (pasaronSeg == true) {
        ventana->draw(*perdistes);
        vueltaNave->stop();
        caidaRayo->stop();
    }
    ventana->draw(*vidass);
    ventana->draw(*corazoness1);
    ventana->draw(*corazoness2);
    ventana->draw(*corazoness3);
    // Actualizar la imagen de la ventana
    ventana->display();
}

void Game::ProcesarColisiones(RenderWindow *ventana) {

    if (rayo->getSprite().getGlobalBounds().intersects(pj->getSprite().getGlobalBounds())) {
        
        contador--;
        if (contador == 2) {
            corazoness3->setPosition(3000, 3000);

        }
        else if (contador == 1) {
            corazoness2->setPosition(3000, 3000);



        }
        else if (contador <= 0) {
            corazoness1->setPosition(3000, 3000);
            nave->setPosicion(Vector2f(3000.0f, 3000.0f));
            terminar->restart().asSeconds();
            perdiste->play();
            pasaronSeg = true;

        }
        nave->rayoCayendo = false;
    }
    if (corazon->getSprite().getGlobalBounds().intersects(pj->getSprite().getGlobalBounds())) {
        corazon->setPosicion(Vector2f(1000.0f, 1000.0f));
        posRand.x = 50 + rand() % (599 - 50);
        respCorazon = false;
        if (contador == 2) {
            corazoness3->setPosition(210.0f, 5.0f);
            contador++;
        }
        if (contador == 1) {
            corazoness2->setPosition(180.0f, 5.0f);
            contador++;
        }

    }
        
}

void Game::terminarJuego(){
    
    *timeTerminar = terminar->getElapsedTime();

    if (timeTerminar->asSeconds() >= 2.0f && contador<=0) {
                
        juegoterminado = true;

    }
    cout << timeTerminar->asSeconds() << endl;


}

void Game::aparecerCorazon() { 

    if (contador <= 2) {
        int numRand = rand() % 600 + 1;
        if (numRand == 4 && respCorazon == false) {
            respCorazon = true;
            sacarCorazon->restart().asSeconds();
            
        }
        
    }
    
    if (respCorazon == true) {
          

        *tiempoCorazon = sacarCorazon->getElapsedTime();

        corazon->setPosicion(posRand);
        if (tiempoCorazon->asSeconds() > 2.5f) {
            respCorazon = false;
            corazon->setPosicion(Vector2f(900.0f, 900.0f));
        }
        
    }
    
}

bool Game::presionBoton() {
    posicion_mouse = Mouse::getPosition(*ventana);
    posicion_mouse = (Vector2i)ventana->mapPixelToCoords(posicion_mouse);
    Vector2f mousepos = (Vector2f)posicion_mouse;
    
    return botons->getGlobalBounds().contains(mousepos.x, mousepos.y);
        
}

void Game::Restart() {
    contador == 3;
    corazoness1->setPosition(150.0f, 5.0f);
    corazoness2->setPosition(180.0f, 5.0f);
    corazoness3->setPosition(210.0f, 5.0f);
    nave->setPosicion(Vector2f(0.0f, 0.0f));
    pj->setPosicion(Vector2f(300.0f, 426.0f));
    
}

Game::~Game() {
    delete ventana;
    delete rayo;
    delete nave;
    delete corazon;

}