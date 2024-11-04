#include "Menu.h"
#include <iostream>
#include "VistaPrincipal.h"  // Asegúrate de incluir la cabecera de VistaPrincipal

Menu::Menu(int tamañoVentana)
    : ventana(sf::VideoMode(tamañoVentana, tamañoVentana), "Menu Principal") {

    fondoTextura.loadFromFile("C:/Users/altam/OneDrive/Escritorio/Estructuras de Datos/QuizProgramado/fondo.jpeg");
    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(
        static_cast<float>(tamañoVentana) / fondoTextura.getSize().x,
        static_cast<float>(tamañoVentana) / fondoTextura.getSize().y
    );

    definirBotones();
}

void Menu::definirBotones() {
    fuente.loadFromFile("C:/Users/altam/OneDrive/Escritorio/Estructuras de Datos/QuizProgramado/fuente.ttf");

    sf::Vector2f tamanoBoton(300, 80);
    sf::Vector2f posicionBoton1(100, 125);
    sf::Vector2f posicionBoton2(100, 275);

    botonNuevo = Boton("Nueva Partida", posicionBoton1, tamanoBoton, fuente);
    botonCargar = Boton("Cargar Partida", posicionBoton2, tamanoBoton, fuente);

    botonNuevo.setOutlineThickness(3);
    botonNuevo.setOutlineColor(sf::Color(214, 87, 159));

    botonCargar.setOutlineThickness(3);
    botonCargar.setOutlineColor(sf::Color(214, 87, 159));
}

void Menu::ejecutar() {
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
        }

        // Obtener la posición del mouse
        sf::Vector2f posicionMouse(static_cast<float>(sf::Mouse::getPosition(ventana).x),
            static_cast<float>(sf::Mouse::getPosition(ventana).y));

        // Verificar si se hace clic
        bool clicado = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        // Actualizar botones
        botonNuevo.actualizar(posicionMouse, clicado);
        botonCargar.actualizar(posicionMouse, clicado);

        // Verificar clic en el botón Nueva Partida
        if (botonNuevo.verificarClic(posicionMouse) && clicado) {
            ventana.close();  // Cierra el menú
            VistaPrincipal vistaPrincipal; // Crear instancia de VistaPrincipal
            vistaPrincipal.ejecutar(); // Iniciar la vista principal
        }

        ventana.clear();
        ventana.draw(fondoSprite); // Dibuja el fondo
        botonNuevo.dibujar(ventana); // Dibuja el botón nuevo
        botonCargar.dibujar(ventana); // Dibuja el botón cargar
        ventana.display();
    }
}
