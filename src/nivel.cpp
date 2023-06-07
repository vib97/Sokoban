#include "nivel.h"

nivel::nivel(mapa m, Coordenada p, set<Coordenada> sc, Nat b) {
	_mapa = m;
    _per = p;
    _setCajas = sc;
    _b = b;
}

mapa nivel::mapa_N() const {
	return _mapa;
}

Coordenada nivel::persona_N() const {
	return _per;
}

set<Coordenada> nivel::cajas_N() const {
	return _setCajas;
}

Nat nivel::cantBombas_N() const {
	return _b;
}