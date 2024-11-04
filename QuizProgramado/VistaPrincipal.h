#ifndef VISTAPRINCIPAL_H
#define VISTAPRINCIPAL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Boton.h"
#include "Tablero.h"
#include <iostream>

class VistaPrincipal {
public:
    VistaPrincipal();
    void actualizarSeleccion();
    void ejecutar();
    void manejarEventos(const sf::Event& evento, int& errores);
    void manejarEntradaTexto(const sf::Event& evento, int& errores);
    void validarNumeroIngresado(int fila, int col, int numeroIngresado, int& errores);
    void manejarEventoBotones();
    void dibujarLineasSeparadoras();

private:
    void cargarFuente();
    void configurarBotones();
    void configurarMensajes();
    void actualizarBotones();
    void dibujarTablero();
    void dibujarCelda(int fila, int col);
    void dibujarTextoEnCelda(int fila, int col);
    void dibujarBotones();
    bool verificarGanador();

    int errores;
    bool modoConfiguracion = false;
    bool tableroLimpiado;
    sf::RenderWindow ventana;
    sf::Font fuente;
    Boton botonNuevo;
    Boton botonReintentar;
    Boton botonResolver;
    Boton botonGuardar;
    Boton botonCargar;
    Boton botonLimpiar;
    Tablero tablero;
    std::pair<int, int> celdaSeleccionada;
    int solucion;
    enum class EstadoJuego { EnCurso, Ganado, Perdido, Configuracion};
    std::vector<std::pair<float, float>> celdasSeleccionadas;
    std::vector<Celda*> almacenarCeldas;
    EstadoJuego estadoJuego;


    //Mensajes
    sf::Text mensajeVictoria;
    sf::Text mensajeError;
    bool mostrarMensajeError = false;
    bool mostrarMensajeVictoria = false;
};

#endif // VISTAPRINCIPAL_H