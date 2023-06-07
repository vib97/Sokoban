#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RenderizadorMapaGrafico.h"

using namespace std;

const int VENTANA_ANCHO = 800;
const int VENTANA_ALTO = 600;

// Ventana para renderizar
extern SDL_Window *ventana;

// Inicializar SDL y crear la ventana
bool iniciar();

// Cargar las imagenes
bool cargarArchivos();

// Liberar las imagenes y apagar SDL
void cerrar();

#endif // INTERFAZGRAFICA_H
