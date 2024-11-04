#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Boton.h"

class Menu {
public:
    Menu(int tamañoVentana);
    void definirBotones();
    void ejecutar();

private:
    sf::RenderWindow ventana;
    Boton botonNuevo;
    Boton botonCargar;
    sf::Texture texturaBotonNormal;
    sf::Texture texturaBotonClicado;
    sf::Font fuente;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite; // Sprite para el fondo
};

#endif // MENU_H
