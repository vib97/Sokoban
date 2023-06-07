#ifndef MAPAGRAFICO_H
#define MAPAGRAFICO_H

#include <vector>
#include "../src/aed2_Juego.h"

enum TipoPosicion {
    Nada, Deposito, Pared, Caja, Personaje, DepositoCaja, DepositoPersonaje, Bomba, Explosion
};

using CoordenadaGrafica = pair<int, int>;

class MapaGrafico {
public:

    MapaGrafico(aed2_Juego j);

    void escanearAlrededores();

    TipoPosicion tipoPosicion(int x, int y) const;

    CoordenadaGrafica posicionActual() const;

    Nat cantidadBombas() const;

    bool sePuedeMover(PuntoCardinal pc) const;

    bool mover(PuntoCardinal pc);

    bool sePuedeTirarBomba() const;

    void tirarBomba();

    void deshacer();

    void desplazarCentro();

private:

    aed2_Juego _juego;
    vector<vector<TipoPosicion> > _mapaGrafico;
    int _centroX;
    int _centroY;

};

#endif // MAPAGRAFICO_H
