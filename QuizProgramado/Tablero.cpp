#include "Tablero.h"
   
Tablero::Tablero(): tableroLimpiado(false) {
    celdas.resize(9, std::vector<Celda>(9));
    solucion.resize(9, std::vector<int>(9));
    inicializarCeldas();
}

void Tablero::inicializarCeldas() {
    for (int fila = 0; fila < 9; ++fila) {
        for (int col = 0; col < 9; ++col) {
            celdas[fila][col] = Celda(0, true); 
        }
    }
}

void Tablero::reiniciarTablero() {
    celdas = celdasOriginal; 
}

bool Tablero::esValido(int fila, int col, int num) const {
    return esNumeroValido(fila, col, num);
}

bool Tablero::resolver() {
    for (int fila = 0; fila < 9; ++fila) {
        for (int col = 0; col < 9; ++col) {
            if (celdas[fila][col].getValor() == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (esValido(fila, col, num)) {
                        celdas[fila][col].setValor(num);
                        if (resolver()) {
                            return true;
                        }
                        celdas[fila][col].setValor(0);
                    }
                }
                return false; // Si no se puede resolver, retornar false
            }
        }
    }
    return true; // Tablero resuelto
}

void Tablero::generarTablero() {
    limpiarTablero();
    llenar(); 
    eliminarNumeros(40); 
    celdasOriginal = celdas;
}

bool Tablero::llenar() {
    for (int fila = 0; fila < 9; ++fila) {
        for (int col = 0; col < 9; ++col) {
            if (celdas[fila][col].getValor() == 0) {
                std::vector<int> numeros = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                std::shuffle(numeros.begin(), numeros.end(), std::mt19937(std::random_device()()));
                for (int num : numeros) {
                    if (esValido(fila, col, num)) {
                        celdas[fila][col].setValor(num);
                        solucion[fila][col] = num; 
                        if (llenar()) {
                            return true;
                        }
                        celdas[fila][col].setValor(0);
                        solucion[fila][col] = 0; 
                    }
                }
                return false; 
            }
        }
    }
    return true; 
}

void Tablero::limpiarTablero() {
    for (int fila = 0; fila < 9; ++fila) {
        for (int col = 0; col < 9; ++col) {
            celdas[fila][col].setValor(0);
            celdas[fila][col].hacerEditable(); 
        }
    }
    tableroLimpiado = true;
}

void Tablero::mostrarTablero() const {
    for (const auto& fila : celdas) {
        for (const auto& celda : fila) {
            std::cout << celda.getValor() << " ";
        }
        std::cout << std::endl;
    }
}

bool Tablero::esNumeroValido(int fila, int col, int num) const {
   
    for (int c = 0; c < 9; ++c) {
        if (c != col && celdas[fila][c].getValor() == num) {
            return false; 
        }
    }

    
    for (int r = 0; r < 9; ++r) {
        if (r != fila && celdas[r][col].getValor() == num) {
            return false; 
        }
    }

    int cajaInicioFila = (fila / 3) * 3;
    int cajaInicioCol = (col / 3) * 3;
    for (int r = cajaInicioFila; r < cajaInicioFila + 3; ++r) {
        for (int c = cajaInicioCol; c < cajaInicioCol + 3; ++c) {
            if (!(r == fila && c == col) && celdas[r][c].getValor() == num) {
                return false; 
            }
        }
    }

    return true; 
}

int Tablero::getSolucion(int fila, int col) const {
    return solucion[fila][col]; 
}

void Tablero::eliminarNumeros(int cantidad) {
    int eliminados = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 8);

    while (eliminados < cantidad) {
        int fila = distr(gen);
        int col = distr(gen);

        if (celdas[fila][col].getValor() != 0) {
            int valorBackup = celdas[fila][col].getValor();
            celdas[fila][col].setValor(0); 

            eliminados++;
        }
    }
}

Celda& Tablero::getCelda(int fila, int col) {
    return celdas[fila][col]; 
}

void Tablero::setCelda(int fila, int col, int valor) {
    celdas[fila][col].setValor(valor); 
}

bool Tablero::compararConSolucion() const {
    for (int fila = 0; fila < 9; ++fila) {
        for (int col = 0; col < 9; ++col) {
            if (celdas[fila][col].getValor() != solucion[fila][col]) {
                return false; 
            }
        }
    }
    return true; 
}

void Tablero::reiniciarEstado() {
    tableroLimpiado = false; 
}

void Tablero::generarTableroConCeldasFijas(const std::vector<Celda*>& celdasFijas) {
    limpiarTablero();
    llenar();

    for (Celda* celda : celdasFijas) {
        if (celda != nullptr) {;
            celda->hacerEditable();
        }
    }
    eliminarNumerosConFijas(30, celdasFijas);
    celdasOriginal = celdas;
}

void Tablero::eliminarNumerosConFijas(int cantidad, const std::vector<Celda*>& celdasFijas) {
    int eliminados = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 8);

    while (eliminados < cantidad) {
        int fila = distr(gen);
        int col = distr(gen);

        Celda& celda = celdas[fila][col];

        if (celda.getValor() != 0 && std::find(celdasFijas.begin(), celdasFijas.end(), &celda) == celdasFijas.end()) {
            celda.setValor(0);
            eliminados++;
        }
    }
}