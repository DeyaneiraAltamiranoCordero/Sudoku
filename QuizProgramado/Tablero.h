#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "Celda.h"
#include <algorithm> 
#include <random> 
#include <iostream>

class Tablero {

private:

    bool tableroLimpiado;
    std::vector<std::vector<Celda>> celdasOriginal;
    std::vector<std::vector<Celda>> celdas;
    std::vector<std::vector<int>> solucion;
    std::vector<std::pair<int, int>> celdasFijas;

public:
    Tablero();

    void inicializarCeldas();
    void reiniciarTablero();
    bool esValido(int fila, int col, int num) const;
    bool resolver();
    void generarTablero();
    void limpiarTablero();
    void mostrarTablero() const;
    void setCelda(int fila, int col, int valor);
    Celda& getCelda(int fila, int col);
    bool compararConSolucion() const;
    void reiniciarEstado();
    void generarTableroConCeldasFijas(const std::vector<Celda*>& celdasFijas);
    void eliminarNumerosConFijas(int cantidad, const std::vector<Celda*> &celdasFijas);
    bool esNumeroValido(int fila, int col, int num) const;
    int getSolucion(int fila, int col) const;
    void eliminarNumeros(int cantidad);
    bool llenar();
};
#endif // TABLERO_H