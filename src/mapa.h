#ifndef MAPA_H
#define MAPA_H

#include "Tipos.h"

class mapa {
public:

    mapa();

    void agPared_M(Coordenada c);

    void agDeposito_M(Coordenada c);

    bool hayPared_M(Coordenada c) const;

    bool hayDeposito_M(Coordenada c) const;

    void tirarBomba_M(Coordenada c);

    void deshacerBomba_M();

    set<Coordenada> depositos_M();

private:

    vector<Coordenada> _paredes;

    vector<Coordenada> _depositos;

    list<Coordenada> _bombas;

};

#endif // MAPA_H
