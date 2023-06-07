#include "juego.h"


juego::juego(vector<nivel> ns) : _nivelActual(sokoban()) {
    if(ns.size() == 0){
        _nivelActual = sokoban();
        _nivelesPendientes = {};
    } else {
        _nivelActual = sokoban(ns[0]);
        _nivelesPendientes = {};
        int tam_ns = ns.size();
        for (int i = 1; i < tam_ns; i++) {
            _nivelesPendientes.push_back(ns[i]);
        }
    }
}

bool juego::mover_J(PuntoCardinal pc){
    _nivelActual.mover_S(pc);
    bool res = _nivelActual.gano_S();
    if(res && _nivelesPendientes.size() != 0){
        _nivelActual = sokoban(_nivelesPendientes.front());
        _nivelesPendientes.pop_front();
    }
    return res;
}

void juego::tirarBomba_J(){
    _nivelActual.tirarBomba_S();
}

void juego::deshacer_J(){
    _nivelActual.deshacer_S();
}

sokoban juego::nivelActual_J() const {
    return _nivelActual;
}

list<nivel> juego::nivelesPendientes_J() {
    return _nivelesPendientes;
}
