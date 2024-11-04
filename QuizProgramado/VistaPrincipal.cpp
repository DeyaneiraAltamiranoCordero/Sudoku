    #include "VistaPrincipal.h"

    VistaPrincipal::VistaPrincipal()
        : ventana(sf::VideoMode(540, 725), "Sudoku"), tableroLimpiado(false) {
        celdaSeleccionada = { -1, -1 };
        cargarFuente();
        configurarBotones();
        configurarMensajes();
    }
    
    //Configuraciones
    void VistaPrincipal::cargarFuente() {
        if (!fuente.loadFromFile("../QuizProgramado/fuente.ttf")) {
            std::cerr << "Error al cargar la fuente" << std::endl;
        }
    }

    void VistaPrincipal::configurarBotones() {
        sf::Vector2f tamanoBoton(145, 50);
        int yArriba = 580;
        int yAbajo = 650;

        // Configura la posición de cada botón
        botonNuevo = Boton("Nuevo", sf::Vector2f(30, yArriba), tamanoBoton, fuente);
        botonReintentar = Boton("Reintentar", sf::Vector2f(190, yArriba), tamanoBoton, fuente);
        botonResolver = Boton("Resolver", sf::Vector2f(350, yArriba), tamanoBoton, fuente);
        botonGuardar = Boton("Guardar", sf::Vector2f(30, yAbajo), tamanoBoton, fuente);
        botonCargar = Boton("Cargar", sf::Vector2f(190, yAbajo), tamanoBoton, fuente);
        botonLimpiar = Boton("Limpiar", sf::Vector2f(350, yAbajo), tamanoBoton, fuente);

        //Tamaño de letra
        botonNuevo.setCharacterSize(12);
        botonReintentar.setCharacterSize(12);
        botonResolver.setCharacterSize(12);
        botonGuardar.setCharacterSize(12);
        botonCargar.setCharacterSize(12);
        botonLimpiar.setCharacterSize(12);

        //Borde
        botonNuevo.setOutlineThickness(3);
        botonNuevo.setOutlineColor(sf::Color(214, 87, 159));
        botonReintentar.setOutlineThickness(3);
        botonReintentar.setOutlineColor(sf::Color(214, 87, 159));
        botonResolver.setOutlineThickness(3);
        botonResolver.setOutlineColor(sf::Color(214, 87, 159));
        botonGuardar.setOutlineThickness(3);
        botonGuardar.setOutlineColor(sf::Color(214, 87, 159));
        botonCargar.setOutlineThickness(3);
        botonCargar.setOutlineColor(sf::Color(214, 87, 159));
        botonLimpiar.setOutlineThickness(3);
        botonLimpiar.setOutlineColor(sf::Color(214, 87, 159));
    }

    void VistaPrincipal::configurarMensajes() {
        mensajeError.setFont(fuente);
        mensajeError.setCharacterSize(15);
        mensajeError.setFillColor(sf::Color(145, 16, 33)); 
        mensajeError.setPosition(100, 555);

        mensajeVictoria.setFont(fuente);
        mensajeVictoria.setCharacterSize(15);
        mensajeVictoria.setFillColor(sf::Color(71, 111, 64)); 
        mensajeVictoria.setPosition(115, 555);
    }

    //Actualizar
    void VistaPrincipal::actualizarBotones() {
        sf::Vector2f posicionMouse(static_cast<float>(sf::Mouse::getPosition(ventana).x),
            static_cast<float>(sf::Mouse::getPosition(ventana).y));
        bool clicado = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        botonNuevo.actualizar(posicionMouse, clicado);
        botonReintentar.actualizar(posicionMouse, clicado);
        botonResolver.actualizar(posicionMouse, clicado);
        botonGuardar.actualizar(posicionMouse, clicado);
        botonCargar.actualizar(posicionMouse, clicado);
        botonLimpiar.actualizar(posicionMouse, clicado);
    }

    void VistaPrincipal::actualizarSeleccion() {
        sf::Vector2f posicionMouse(static_cast<float>(sf::Mouse::getPosition(ventana).x),
            static_cast<float>(sf::Mouse::getPosition(ventana).y));

        if (modoConfiguracion && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int fila = 0; fila < 9; ++fila) {
                for (int col = 0; col < 9; ++col) {
                    if (posicionMouse.x >= col * 60 && posicionMouse.x < (col + 1) * 60 &&
                        posicionMouse.y >= fila * 60 && posicionMouse.y < (fila + 1) * 60) {

                        // Verifica si la celda ya ha sido seleccionada
                        auto celdaPos = std::make_pair(fila, col);
                        if (std::find(celdasSeleccionadas.begin(), celdasSeleccionadas.end(), celdaPos) == celdasSeleccionadas.end()) {
                            celdasSeleccionadas.push_back(celdaPos);
                        }
                    }
                }
            }
        }
    }

    void VistaPrincipal::ejecutar() {
        errores = 0; 

        while (ventana.isOpen()) {
            sf::Event evento;
            while (ventana.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed)
                    ventana.close();

                manejarEventos(evento, errores);
          
            }
            actualizarBotones();
            manejarEventoBotones();

            ventana.clear(sf::Color(255, 248, 252));
            dibujarTablero();
            dibujarBotones();

            if (mostrarMensajeError) {
                ventana.draw(mensajeError);
            }
            if (mostrarMensajeVictoria) {
                ventana.draw(mensajeVictoria);
            }
            ventana.display(); 
        }
    }
    //Manejar eventos
    void VistaPrincipal::manejarEventos(const sf::Event& evento, int& errores) {
        if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f posicionMouse(static_cast<float>(evento.mouseButton.x), static_cast<float>(evento.mouseButton.y));
            int col = static_cast<int>(posicionMouse.x / 60);
            int fila = static_cast<int>(posicionMouse.y / 60);

            if (fila >= 0 && fila < 9 && col >= 0 && col < 9) {
                celdaSeleccionada = { fila, col };
                if (modoConfiguracion) {
                    Celda& celda = tablero.getCelda(fila, col);
                    almacenarCeldas.push_back(&celda);
                }
            }
        }

        if (evento.type == sf::Event::TextEntered) {
            manejarEntradaTexto(evento, errores);
            verificarGanador();
        }
    }

    void VistaPrincipal::manejarEntradaTexto(const sf::Event& evento, int& errores) {
        if (estadoJuego == EstadoJuego::EnCurso) {
            if (evento.text.unicode < 128) {
                char input = static_cast<char>(evento.text.unicode);
                if (isdigit(input)) {
                    int numeroIngresado = input - '0';
                    auto [fila, col] = celdaSeleccionada;
                    validarNumeroIngresado(fila, col, numeroIngresado, errores);
                }
            }
        }
    }
    void VistaPrincipal::validarNumeroIngresado(int fila, int col, int numeroIngresado, int& errores) {
        if (tablero.getCelda(fila, col).esEditable()) {
            if (tablero.esNumeroValido(fila, col, numeroIngresado)) {
                if (numeroIngresado == tablero.getSolucion(fila, col)) {
                    tablero.setCelda(fila, col, numeroIngresado);
                    verificarGanador();
                    mostrarMensajeVictoria = false;
                }
            }
            else {
                errores++;
                std::cout << "Número incorrecto. Errores: " << errores << std::endl;
                if (errores >= 3) {
                    estadoJuego = EstadoJuego::Perdido;
                    mostrarMensajeError = true;
                    mensajeError.setString("¡Has perdido! Demasiados errores.");
                }
            }
        }
        else {
            std::cout << "No puedes editar esta celda." << std::endl;
        }
    }

    void VistaPrincipal::manejarEventoBotones() {
        if (botonNuevo.estaClicado()) {;
            tablero.generarTablero();  
            celdaSeleccionada = { -1, -1 }; 
            estadoJuego = EstadoJuego::EnCurso;
            tableroLimpiado = false;
            mostrarMensajeVictoria = false;
            mostrarMensajeError = false;
        }
        else if (botonReintentar.estaClicado()) {
            if (!tableroLimpiado) {
                tablero.reiniciarTablero(); 
                errores = 0; 
                celdaSeleccionada = { -1, -1 }; 
                estadoJuego = EstadoJuego::EnCurso;
                tableroLimpiado = false;
                mostrarMensajeVictoria = false;
                mostrarMensajeError = false;
            }
        }
        else if (botonResolver.estaClicado()) {
            if (!tableroLimpiado) { 
                for (int fila = 0; fila < 9; ++fila) {
                    for (int col = 0; col < 9; ++col) {
                        tablero.setCelda(fila, col, tablero.getSolucion(fila, col));
                    }
                }
                errores = 0;
                celdaSeleccionada = { -1, -1 };
                mostrarMensajeVictoria = false;
                mostrarMensajeError = false;
            }
         }

        else if (botonGuardar.estaClicado()) {
            if (estadoJuego == EstadoJuego::Configuracion) {
                modoConfiguracion = false;
                tablero.generarTableroConCeldasFijas(almacenarCeldas);
                estadoJuego = EstadoJuego::EnCurso; 
                tableroLimpiado = false;
                almacenarCeldas.clear();
                errores = 0;
            }
        }
        else if (botonCargar.estaClicado()) {
            tablero.limpiarTablero();
            estadoJuego = EstadoJuego::Configuracion;
            celdaSeleccionada = { -1, -1 }; 
            celdasSeleccionadas.clear();
           modoConfiguracion = true;
           mostrarMensajeVictoria = false;
           mostrarMensajeError = false;
        }
        else if (botonLimpiar.estaClicado()) {
             celdaSeleccionada = { -1, -1 }; 
            tablero.limpiarTablero(); 
            tableroLimpiado = true;
            errores = 0;
            mostrarMensajeVictoria = false;
            mostrarMensajeError = false;
        }
    }

    bool VistaPrincipal::verificarGanador() {
        for (int fila = 0; fila < 9; ++fila) {
            for (int col = 0; col < 9; ++col) {
                if (tablero.getCelda(fila, col).getValor() != tablero.getSolucion(fila, col)) {
                    return false;
                }
            }
        }
        estadoJuego = EstadoJuego::Ganado;
        mostrarMensajeVictoria = true;
        mensajeVictoria.setString("¡Felicidades, has ganado!");
        return true;
    }

    //Dibujar
    void VistaPrincipal::dibujarLineasSeparadoras() {
        for (int i = 1; i <= 2; ++i) {
     
            sf::Vertex verticalLine[] = {
                sf::Vertex(sf::Vector2f(i * 3 * 60, 0), sf::Color::Black),
                sf::Vertex(sf::Vector2f(i * 3 * 60, 540), sf::Color::Black) 
            };
            ventana.draw(verticalLine, 2, sf::PrimitiveType::Lines);

            sf::Vertex horizontalLine[] = {
                sf::Vertex(sf::Vector2f(0, i * 3 * 60), sf::Color::Black),
                sf::Vertex(sf::Vector2f(540, i * 3 * 60), sf::Color::Black) 
            };
            ventana.draw(horizontalLine, 2, sf::PrimitiveType::Lines);
        }

        for (int i = 1; i <= 2; ++i) {
          
            sf::RectangleShape lineaVertical(sf::Vector2f(3, 540));
            lineaVertical.setPosition(i * 3 * 60, 0);
            lineaVertical.setFillColor(sf::Color::Black);
            ventana.draw(lineaVertical);

            sf::RectangleShape lineaHorizontal(sf::Vector2f(540, 3));
            lineaHorizontal.setPosition(0, i * 3 * 60);
            lineaHorizontal.setFillColor(sf::Color::Black);
            ventana.draw(lineaHorizontal);
        }
    }

    void VistaPrincipal::dibujarCelda(int fila, int col) {
        sf::RectangleShape celda(sf::Vector2f(60, 60));
        celda.setPosition(col * 60, fila * 60);
        celda.setOutlineColor(sf::Color::Black);
        celda.setOutlineThickness(1.0f);

        if (tablero.getCelda(fila, col).esEditable()) {
            celda.setFillColor(sf::Color(252, 235, 245));
        }
        else {
            celda.setFillColor(sf::Color(200, 200, 200));
        }

        if (celdaSeleccionada.first == fila && celdaSeleccionada.second == col) {
            celda.setFillColor(sf::Color(173, 216, 230));
        }

        ventana.draw(celda);
    }

    void VistaPrincipal::dibujarTextoEnCelda(int fila, int col) {
        if (tablero.getCelda(fila, col).esEditable()) {
            int valorJuego = tablero.getCelda(fila, col).getValor();
            if (valorJuego != 0) {
                sf::Text texto;
                texto.setFont(fuente);
                texto.setCharacterSize(24);
                texto.setFillColor(sf::Color::Black);
                texto.setString(std::to_string(valorJuego));
                texto.setPosition(col * 60 + 20, fila * 60 + 20);
                ventana.draw(texto);
            }
        }
    }

    void VistaPrincipal::dibujarTablero() {
        for (int fila = 0; fila < 9; ++fila) {
            for (int col = 0; col < 9; ++col) {
                dibujarCelda(fila, col);
                dibujarTextoEnCelda(fila, col);
            }
        }
        dibujarLineasSeparadoras();
    }


    void VistaPrincipal::dibujarBotones() {
        botonNuevo.dibujar(ventana);
        botonReintentar.dibujar(ventana);
        botonResolver.dibujar(ventana);
        botonGuardar.dibujar(ventana);
        botonCargar.dibujar(ventana);
        botonLimpiar.dibujar(ventana);
    }
    
 