#include "aed2_Juego.h"
#include "juego.h"
#include "nivel.h"

aed2_Juego::aed2_Juego(vector<aed2_Nivel> ns) : _juego(juego({})){
    vector<nivel> vs = {};
    for(int i = 0; i < ns.size(); i++){
        aed2_Nivel n = ns[i];
        mapa m = mapa();
        for(Coordenada c : n.paredes){
            m.agPared_M(c);
        }
        for(Coordenada c : n.depositos){
            m.agDeposito_M(c);
        }
        nivel niv = nivel(m,n.posicionInicial,n.cajas,n.cantidadBombas);
        vs.push_back(niv);
    }
    _juego = juego(vs);
}

bool aed2_Juego::hayPared(Coordenada c) const {
    sokoban nivAct = _juego.nivelActual_J();
    mapa map = nivAct.mapa_S();
    return map.hayPared_M(c);
}

bool aed2_Juego::hayDeposito(Coordenada c) const {
    sokoban nivAct = _juego.nivelActual_J();
    mapa map = nivAct.mapa_S();
    return map.hayDeposito_M(c);
}

bool aed2_Juego::hayCaja(Coordenada c) const {
    sokoban nivAct = _juego.nivelActual_J();
    return nivAct.hayCaja_S(c);
}

Coordenada aed2_Juego::posicionActual() const {
    sokoban nivAct = _juego.nivelActual_J();
    return nivAct.persona_S();
}

Nat aed2_Juego::cantidadBombas() const {
    sokoban nivAct = _juego.nivelActual_J();
    return nivAct.cantidadBombas_S();
}

bool aed2_Juego::sePuedeMover(PuntoCardinal pc) const {
    sokoban nivAct = _juego.nivelActual_J();
    return nivAct.puedeMover_S(pc);
}

// IMPORTANTE: Debe devolver:
// - true si al mover se completa el nivel actual
// - false en caso contrario.
bool aed2_Juego::mover(PuntoCardinal pc) {
    return _juego.mover_J(pc);
}

void aed2_Juego::tirarBomba() {
    _juego.tirarBomba_J();
}

void aed2_Juego::deshacer() {
    _juego.deshacer_J();
}

