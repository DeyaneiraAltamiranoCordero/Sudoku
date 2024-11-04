#ifndef CELDA_H
#define CELDA_H

class Celda {
private:
    int valor;       
    bool editable;   

public:
    Celda(int valor = 0, bool editable = true);

    int getValor() const;
    void setValor(int nuevoValor);
    void hacerEditable();
    bool esEditable() const;
    void hacerFija();
};
#endif // CELDA_H