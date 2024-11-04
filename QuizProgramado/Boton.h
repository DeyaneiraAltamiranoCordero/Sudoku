#ifndef BOTON_H
#define BOTON_H

#include <SFML/Graphics.hpp>

class Boton {

private:
    sf::RectangleShape rectangulo;
    sf::Text texto;
    bool clicado = false;

public:
    Boton();
    Boton(const std::string& textoStr, const sf::Vector2f& posicion, const sf::Vector2f& tamano, const sf::Font& fuente);

    void dibujar(sf::RenderWindow& ventana) ;
    bool verificarClic(const sf::Vector2f& posicionMouse);

    void setTexto(const std::string& nuevoTexto);
    void setOutlineThickness(float grosor);
    void setOutlineColor(const sf::Color& color);
    void setCharacterSize(unsigned int size);

    const sf::RectangleShape& obtenerForma() const;
    const sf::Text& obtenerTexto() const;

    void actualizar(const sf::Vector2f& posicionMouse, bool clicado);
    bool estaClicado() const;
    bool isHovered(const sf::Vector2f& posicionMouse) const;

};

#endif // BOTON_H
