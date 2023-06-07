/*
    FORMATO:
    b (Cantidad de Bombas)
    ---------------------
    -----C---------D-----
    -P-------I---------P-
    ---------------------
    ----P------2---C-----
    --------D------------
    - -> Nada
    D -> Depósito
    P -> Pared
    C -> Caja
    I -> Posición Inicial
    2 -> Depósito + Caja
    0 -> Depósito + Posición Inicial
*/

#ifndef LECTORDENIVELES_H
#define LECTORDENIVELES_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "../src/aed2_Juego.h"

using namespace std;

aed2_Nivel crearNivelDesdeArchivo(const string &rutaArchivo);

aed2_Juego crearJuego();

#endif // LECTORDENIVELES_H
