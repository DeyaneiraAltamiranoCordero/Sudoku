#include "Celda.h"

Celda::Celda(int valor, bool editable)
    : valor(valor), editable(editable) {}

int Celda::getValor() const {
    return valor;
}

void Celda::setValor(int nuevoValor) {
    if (editable) {
        valor = nuevoValor;
    }
}

void Celda::hacerEditable() {
    editable = true;
}

bool Celda::esEditable() const {
    return editable;
}

void Celda::hacerFija() {
    editable = false;
}
