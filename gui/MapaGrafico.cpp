#include "MapaGrafico.h"

using namespace std;

MapaGrafico::MapaGrafico(aed2_Juego j) : _juego(j) {
    _centroX = _juego.posicionActual().first;
    _centroY = _juego.posicionActual().second;
    _mapaGrafico = vector<vector<TipoPosicion> >(17, vector<TipoPosicion>(17));
    escanearAlrededores();
}

void MapaGrafico::escanearAlrededores() {
    int xReal, yReal;
    for (int y = 0; y < 17; ++y) {
        for (int x = 0; x < 17; ++x) {
            xReal = x + _centroX - 8;
            yReal = _centroY + 8 - y;
            if (_juego.hayDeposito({xReal, yReal})) {
                if (_juego.posicionActual().first == xReal and
                    _juego.posicionActual().second == yReal) {
                    _mapaGrafico[y][x] = DepositoPersonaje;
                } else if (_juego.hayCaja({xReal, yReal})) {
                    _mapaGrafico[y][x] = DepositoCaja;
                } else {
                    _mapaGrafico[y][x] = Deposito;
                }
            } else if (_juego.hayCaja({xReal, yReal})) {
                _mapaGrafico[y][x] = Caja;
            } else if (_juego.hayPared({xReal, yReal})) {
                _mapaGrafico[y][x] = Pared;
            } else if (_juego.posicionActual().first == xReal and
                       _juego.posicionActual().second == yReal) {
                _mapaGrafico[y][x] = Personaje;
            } else {
                _mapaGrafico[y][x] = Nada;
            }
        }
    }
}

TipoPosicion MapaGrafico::tipoPosicion(int x, int y) const {
    return _mapaGrafico[y][x];
}

CoordenadaGrafica MapaGrafico::posicionActual() const {
    CoordenadaGrafica posicionActual = _juego.posicionActual();
    posicionActual.first = posicionActual.first - _centroX + 8;
    posicionActual.second = -posicionActual.second + _centroY + 8;
    return posicionActual;
}

Nat MapaGrafico::cantidadBombas() const {
    return _juego.cantidadBombas();
}

bool MapaGrafico::sePuedeMover(PuntoCardinal pc) const {
    return _juego.sePuedeMover(pc);
}

bool MapaGrafico::mover(PuntoCardinal pc) {
    bool gano = _juego.mover(pc);
    if (gano) {
        _centroX = _juego.posicionActual().first;
        _centroY = _juego.posicionActual().second;
    } else {
        desplazarCentro();
    }
    escanearAlrededores();
    return gano;
}

bool MapaGrafico::sePuedeTirarBomba() const {
    return _juego.cantidadBombas() > 0;
}

void MapaGrafico::tirarBomba() {
    _juego.tirarBomba();
    escanearAlrededores();
}

void MapaGrafico::deshacer() {
    _juego.deshacer();
    desplazarCentro();
    escanearAlrededores();
}

void MapaGrafico::desplazarCentro() {
    if (posicionActual().first == 1) {
        _centroX -= 8;
    } else if (posicionActual().first == 15) {
        _centroX += 8;
    } else if (posicionActual().second == 1) {
        _centroY += 8;
    } else if (posicionActual().second == 15) {
        _centroY -= 8;
    }
}
