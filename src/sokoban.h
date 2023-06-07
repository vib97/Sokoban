#ifndef SOKOBAN_H
#define SOKOBAN_H

#include "nivel.h"

class sokoban {
public:

    sokoban();

    sokoban(nivel n);

    void mover_S(PuntoCardinal pc);

    void tirarBomba_S();

    mapa mapa_S();

    Coordenada persona_S();

    bool hayCaja_S(Coordenada c);

    Nat cantidadBombas_S();

    void deshacer_S();

    bool noHayParedNiCaja_S(Coordenada c);

    bool puedeMover_S(PuntoCardinal pc);

    bool gano_S();

    bool hayCajas_S(set<Coordenada> sc);

private:

    mapa _mapa;

    Nat _cantB = 0;

    vector<pair<Coordenada,Nat>> _trayectoria = {};

    vector<Coordenada> _cajas = {};

};

#endif // SOKOBAN_H
