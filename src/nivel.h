#ifndef NIVEL_H
#define NIVEL_H

#include "mapa.h"

class nivel {
public:

    nivel(mapa m, Coordenada p, set<Coordenada> sc, Nat b);

    mapa mapa_N() const;

    Coordenada persona_N() const;

    set<Coordenada> cajas_N() const;

    Nat cantBombas_N() const;

private:

    mapa _mapa;

    Coordenada _per;

    set<Coordenada> _setCajas;

    Nat _b;

};

#endif // NIVEL_H
