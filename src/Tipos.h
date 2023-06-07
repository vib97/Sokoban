#ifndef TIPOS_H
#define TIPOS_H

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <set>
#include <tuple>
#include <list>
#include <vector>


using namespace std;

using Nat = unsigned int;

using Coordenada = pair<int, int>;

enum PuntoCardinal {
    Norte, Este, Sur, Oeste
};

struct aed2_Nivel {
    set<Coordenada> paredes;
    set<Coordenada> depositos;
    set<Coordenada> cajas;
    Coordenada posicionInicial;
    Nat cantidadBombas;
};

#define COMPLETAR(fn)   cerr << "COMPLETAR: " << #fn << endl; exit(1); assert(false);

#endif // TIPOS_H
