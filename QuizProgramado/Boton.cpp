#include "Boton.h"

Boton::Boton() {
   
}

Boton::Boton(const std::string& textoStr, const sf::Vector2f& posicion, const sf::Vector2f& tamano, const sf::Font& fuente) {
    rectangulo.setSize(tamano);
    rectangulo.setPosition(posicion);
    rectangulo.setFillColor(sf::Color(240, 163, 206));
    rectangulo.setOutlineThickness(2);
    rectangulo.setOutlineColor(sf::Color(240, 163, 206));

    texto.setFont(fuente);
    texto.setString(textoStr);
    texto.setCharacterSize(24);
    texto.setFillColor(sf::Color(165, 32, 107));

    sf::FloatRect textBounds = texto.getLocalBounds();
    texto.setOrigin(textBounds.width / 2, textBounds.height / 2);
    texto.setPosition(posicion.x + tamano.x / 2, posicion.y + tamano.y / 2 + textBounds.height / 4);
}

void Boton::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(rectangulo);
    ventana.draw(texto);
}

bool Boton::verificarClic(const sf::Vector2f& posicionMouse) {
    return rectangulo.getGlobalBounds().contains(posicionMouse);
}

void Boton::setTexto(const std::string& nuevoTexto) {
    texto.setString(nuevoTexto);
}

void Boton::setOutlineThickness(float grosor) {
    rectangulo.setOutlineThickness(grosor);
}

void Boton::setOutlineColor(const sf::Color& color) {
    rectangulo.setOutlineColor(color);
}
void Boton::setCharacterSize(unsigned int size) {
    texto.setCharacterSize(size);
    sf::FloatRect textBounds = texto.getLocalBounds();
    texto.setOrigin(textBounds.width / 2, textBounds.height / 2);
    texto.setPosition(rectangulo.getPosition().x + rectangulo.getSize().x / 2, rectangulo.getPosition().y + rectangulo.getSize().y / 2 + textBounds.height / 4);
}

const sf::RectangleShape& Boton::obtenerForma() const {
    return rectangulo;
}

const sf::Text& Boton::obtenerTexto() const {
    return texto;
}

void Boton::actualizar(const sf::Vector2f& posicionMouse, bool clicIzquierdoPresionado) {
    if (isHovered(posicionMouse)) {
        rectangulo.setFillColor(sf::Color(200, 50, 150));
        clicado = clicIzquierdoPresionado;

        if (clicado) {
            rectangulo.setFillColor(sf::Color(150, 30, 130));
        }
    }
    else {
        rectangulo.setFillColor(sf::Color(243, 159, 206));
        clicado = false;
    }
}
bool Boton::isHovered(const sf::Vector2f& posicionMouse) const {
    return rectangulo.getGlobalBounds().contains(posicionMouse);
}

bool Boton::estaClicado() const
{
    return clicado;
}
