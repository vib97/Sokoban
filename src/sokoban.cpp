#include "sokoban.h"

sokoban::sokoban() {
    _mapa = mapa();
    _cantB = 0;
    _trayectoria = {};
    _cajas = {};
}

sokoban::sokoban(nivel n) {
    _mapa = n.mapa_N();
    _cantB = n.cantBombas_N();
    pair<Coordenada,Nat> par;
    par.first = n.persona_N();
    par.second = n.cajas_N().size();
    _trayectoria = {par};
    set<Coordenada> cajasDelNivel = n.cajas_N();
    for(Coordenada caja : n.cajas_N()){
        _cajas.push_back(caja);
    }
}

void sokoban::mover_S(PuntoCardinal pc) {
    Coordenada p = persona_S();
    if(pc == Norte) {
        p.second = p.second + 1;
    } else if(pc == Sur) {
        p.second = p.second - 1;
    } else if(pc == Oeste) {
        p.first = p.first - 1;
    } else if(pc == Este) {
        p.first = p.first + 1;
    }
    int c = _cajas.size();
    int i = 0;
    while (i < c && _cajas[i] != p){
        i++;
    }
    pair<Coordenada, int> tup = make_pair(p,i);
    _trayectoria.push_back(tup);
    if (i < c){
        if(pc == Norte) {
            p.second = p.second + 1;
        } else if(pc == Sur) {
            p.second = p.second - 1;
        } else if(pc == Oeste) {
            p.first = p.first - 1;
        } else if(pc == Este) {
            p.first = p.first + 1;
        }
        _cajas[i] = p;
    }
}

void sokoban::tirarBomba_S() {
    _mapa.tirarBomba_M(persona_S());
    _cantB--;
    pair<Coordenada,Nat> par;
    par.first = persona_S();
    par.second = _cajas.size();
    _trayectoria.push_back(par);
}

mapa sokoban::mapa_S() {
    return _mapa;
}

Coordenada sokoban::persona_S() {
    return _trayectoria[_trayectoria.size()-1].first;
}

bool sokoban::hayCaja_S(Coordenada c) {
    int n = _cajas.size();
    for(int i = 0; i < n; i++){
        if(_cajas[i] == c){
            return true;
        }
    }
    return false;
}

Nat sokoban::cantidadBombas_S() {
    return _cantB;
}

void sokoban::deshacer_S() {
    int n = _trayectoria.size()-1;
    if(n > 0){
        if(_trayectoria[n].first == _trayectoria[n-1].first){
            _mapa.deshacerBomba_M();
            _cantB++;
            _trayectoria.pop_back();
        } else if(_trayectoria[n].second == _cajas.size()){
            _trayectoria.pop_back();
        } else {
            _cajas[_trayectoria[n].second] = _trayectoria[n].first;
            _trayectoria.pop_back();
        }
    }
}

bool sokoban::noHayParedNiCaja_S(Coordenada c) {
    return (!_mapa.hayPared_M(c) && !hayCaja_S(c));
}

bool sokoban::puedeMover_S(PuntoCardinal pc) {
    Coordenada p = persona_S();
    if(pc == Norte) {
        p.second = p.second + 1;
    } else if(pc == Sur) {
        p.second = p.second - 1;
    } else if(pc == Oeste) {
        p.first = p.first - 1;
    } else if(pc == Este) {
        p.first = p.first + 1;
    }
    bool pnc = noHayParedNiCaja_S(p);
    bool c = hayCaja_S(p);
    if(pc == Norte) {
        p.second = p.second + 1;
    } else if(pc == Sur) {
        p.second = p.second - 1;
    } else if(pc == Oeste) {
        p.first = p.first - 1;
    } else if(pc == Este) {
        p.first = p.first + 1;
    }
    bool m = noHayParedNiCaja_S(p);
    return pnc || (c && m);
}

bool sokoban::gano_S() {
 return hayCajas_S(_mapa.depositos_M());
}

bool sokoban::hayCajas_S(set<Coordenada> sc) {
    for(Coordenada caja : sc){
        if(!hayCaja_S(caja)){
            return false;
        }
    }
    return true;
}