#include "Game.h"

void Game::Loop() {
    // Start the game loop
   
    Clock clock;
    clock.restart();
    float dt;
        
        while (ventana->isOpen())
        {
            float dt = clock.restart().asSeconds();
            *timeTerminar = terminar->getElapsedTime();

            presen = true;
            if (timeTerminar->asSeconds() >= 40.0f) {//si pasan 30 segundos y no moriste, GANAS!
                nave->setPosicion(Vector2f(3000.0f, 3000.0f));
                terminar->restart().asSeconds();
                pasaronSeg = true;//Pasaron segundos en true para qe dibuje el ganaste
                fingan = true;//fingan en true, para que se active el metodo ganaste(), y termine el juego.

            }
            if (presen == true) {
                ventana->clear();
                ventana->draw(*presentacion);
                ventana->display();
            }

            if (presen == false) {
                ProcesarEventos();// Procesar eventos

                Actualizar(dt);// Actualizar el juego

                Dibujar();// Dibujar el juego
            }
            

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
            case Event::Closed://Cerrar ventana
                ventana->close(); break;
            case Event::KeyPressed://si presiono la letra D, seteo velocidad al sprite, lo cual afecta su posicion.
                if (event.key.code == Keyboard::D) {
                    pj->setVelocidad(Vector2f(200.0f, 0.0f));//se le asigna velocidad al sprite
                }
                if (event.key.code == Keyboard::A) {//si presiono la letra A, seteo velocidad al sprite, lo cual afecta su posicion.
                    pj->setVelocidad(Vector2f(-200.0f, 0.0f));
                }break;
                               
            case Event::KeyReleased://Si suelto la letra, se le asigna velocidad 0 para frenarlo o dejarlo quieto.
                if (event.key.code == Keyboard::D) {
                    pj->setVelocidad(Vector2f(0.0f, 0.0f));//se le asigna una velocidad en 0, asi se frena
                }
                if (event.key.code == Keyboard::A) {
                    pj->setVelocidad(Vector2f(0.0f, 0.0f));
                }break;
            case Event::MouseButtonPressed://Si presiono el boton izquiero del mouse y colisiona con el boton, reseteo juego.
                if (event.mouseButton.button == Mouse::Button::Left) {
                    if (presionBoton()) {//si presiono boton es true, osea, retorna el getglobal del sprite en colision con el mouse.
                        Restart();
                        
                    }
                }break;
            default:break;              
        }           
        
    }

}
void Game::Actualizar(float dt){ 

    Ganaste();

    if (pasaronSeg == true) {//Termino juego.
        terminarJuego();
    }
    //NAVE
    nave->Update(dt);
    if (nave->getPosicion().x >= tope.x) {//si nave llega a cierta posicion en X
        nave->setVelocidad(Vector2f(-(rand() % 300 + 50), 0.0f));//setea velocidad negativa, para que vuelva hacia el otro lado.ENTRE 500 Y 100
        nave->setAceleracion(Vector2f(-(rand() % 300 + 50), 0.0f));//setea la aceleracion para que tenga mas velocidad//ENTRE 500 Y 100
        nave->setTextura("nave2.png");
        vueltaNave->play();

    }
    else if (nave->getPosicion().x <= inicio.x) {
        nave->setVelocidad(Vector2f(rand() % 300 + 50, 0.0f));//setea velocidad negativa, para que vuelva hacia el otro lado.
        nave->setAceleracion(Vector2f(rand() % 300 + 50, 0.0f));//setea la aceleracion para que tenga mas velocidad.
        nave->setTextura2("nave.png");//Cambio de sprite para que aparezca en base al lado que se dirige.
        vueltaNave->play();
    }
    //PERSONAJE
    pj->Update(dt);   

    //RAYO  
    if ((nave->rayoCayendo != true)) {//Si el rayo no esta cayendo, llamo el metodo tirar rayo, y pongo rayo cayendo en true.
        rayo = nave->tirarRayo();//instancio un rayo bajo la nave, retornandolo con un metodo de estilo rayo.
        nave->rayoCayendo = true;
        caidaRayo->play();
        
    }    
    rayo->Update(dt);

    aparecerCorazon();//respawneo corazon random, al tener menos de 3 vidas.

    if (rayo->getPosition().y > 600.0f) {//Si rayo supera los 600 en el eje Y, coloco rayo cayendo en false, al hacer esto, se vuelve a respawnear
        nave->rayoCayendo = false;

    }       
    if ((nave->rayoCayendo) && (pj->pjon)) {//detecto colisiones siempre y cuando, haya un rayo cayendo y el pj on.
        ProcesarColisiones();
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

        if (pasaronSeg == true) {//Dibujo el sprite perdiste, y silencio los sonidos.
            if (contador == 0) {
                ventana->draw(*perdistes);
            }
            else {
                ventana->draw(*ganastes);
            }

            vueltaNave->stop();
            caidaRayo->stop();
        }
        ventana->draw(*vidass);
        ventana->draw(*corazoness1);
        ventana->draw(*corazoness2);
        ventana->draw(*corazoness3);
  
    //Actualizar la imagen de la ventana
    ventana->display();
}

void Game::ProcesarColisiones() {

    if (rayo->getSprite().getGlobalBounds().intersects(pj->getSprite().getGlobalBounds())) {//si rayo se intersecta con el limite de imagen del pj
        
        contador--;//Una vida menos
        if (contador == 2) {
            corazoness3->setPosition(3000, 3000);//el primer corazon lo saco de pantalla

        }
        else if (contador == 1) {
            corazoness2->setPosition(3000, 3000);



        }
        else if (contador <= 0) {
            corazoness1->setPosition(3000, 3000);
            nave->setPosicion(Vector2f(3000.0f, 3000.0f));//saco nave de pantalla.
            terminar->restart().asSeconds();
            perdiste->play();
            pasaronSeg = true;//Al pasar ciertos segundos, cierro la ventana.

        }
        
        
        nave->rayoCayendo = false;//pongo rayo cayendo el false, para volverlo a respawnear.
    }
    if (corazon->getSprite().getGlobalBounds().intersects(pj->getSprite().getGlobalBounds())) {//Si corazon se intersecta con el jugador.
        pickCora->play();
        corazon->setPosicion(Vector2f(1000.0f, 1000.0f));//Saco el corazon de pantalla
        posRand.x = 50 + rand() % (599 - 50);//Y saco un nuevo rand;
        respCorazon = false; //pongo en false para que se vuelva a respawnear.
        if (contador == 2) {//sumo vida y seteo el corazon nuevamente en su posicion.
            corazoness3->setPosition(210.0f, 5.0f);
            contador++;
        }
        if (contador == 1) {
            corazoness2->setPosition(180.0f, 5.0f);
            contador++;
        }

    }
        
}

void Game::terminarJuego(){//Metodo termina juego, si pasaron unos segundos, pongo el booleano en true y salgo del juego.
    
    *timeTerminar = terminar->getElapsedTime();//el tiempo que paso, lo guardo en timeterminar.

    if (timeTerminar->asSeconds() >= 2.0f && contador<=0) {//si ese tiempo transcurrido en segundos, es mayor o igual a 2 Float y el contador es 0, terminar juego.
                
        juegoterminado = true;

    }
    
}
void Game::Ganaste() {
    *timeTerminar = terminar->getElapsedTime();//Tiempo transcurrido, luego del reinicio del timing cuando llega a 30 seg.
    
    if (timeTerminar->asSeconds() >= 3.0f && fingan == true && contador > 0) {
        
        juegoterminado = true;
    }
    
    
}

void Game::aparecerCorazon() { //Metodo que aparece corazon de forma random, para obtener vidas perdidas.
    
    if (contador <= 2) {
        int numRand = rand() % 600 + 1;
        if (numRand == 5 && respCorazon == false) {//Si el numero random es 4 y respawnear coraon es falso, respawnea corazon y el tiempo lo reinicia para respawnearo otro.
            respCorazon = true;
            sacarCorazon->restart().asSeconds();
            
        }
        
    }
    
    if (respCorazon == true) {//Si es true, tiempo corazon lo iguala al  tiempo transcurrido en sacar corazon, y sea corazon en una posicion rand
          //luego de unos segundos , si el personaje no colisiona, se saca el corazon.
        *tiempoCorazon = sacarCorazon->getElapsedTime();

        corazon->setPosicion(posRand);//seteo la posicion random a corazon
        if (tiempoCorazon->asSeconds() > 2.5f) {
            posRand.x = 50 + rand() % (599 - 50);
            respCorazon = false;
            corazon->setPosicion(Vector2f(900.0f, 900.0f));
        }
        
    }
    
}

bool Game::presionBoton() {//recupero la posicion del mouse en la ventana, y la paso de pixel a coordenadas, y la guardo en un vector2f
    //Para utilizarla retornando en getglobalbounds del sprite(boton) y detectar si se presiona dentro.
    posicion_mouse = Mouse::getPosition(*ventana);
    posicion_mouse = (Vector2i)ventana->mapPixelToCoords(posicion_mouse);
    Vector2f mousepos = (Vector2f)posicion_mouse;
    
    return botons->getGlobalBounds().contains(mousepos.x, mousepos.y);
        
}

void Game::Restart() {//Al presionar el boton, se ejecuta el metodo y reinciia las variables.
    contador == 3;
    corazoness1->setPosition(150.0f, 5.0f);
    corazoness2->setPosition(180.0f, 5.0f);
    corazoness3->setPosition(210.0f, 5.0f);
    nave->setPosicion(Vector2f(0.0f, 0.0f));
    nave->rayoCayendo = false;
    pj->setPosicion(Vector2f(300.0f, 426.0f));      
    
}


Game::~Game() {
    delete ventana;
    delete rayo;
    delete nave;
    delete corazon;

}
