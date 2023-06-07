#ifndef MAPAGRAFICORENDERIZADOR_H
#define MAPAGRAFICORENDERIZADOR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MapaGrafico.h"
#include "Textura.h"

const int COMIENZO_MAPA_X = 228;
const int COMIENZO_MAPA_Y = 28;
const int COMIENZO_CONTADOR_BOMBAS_X = 44;
const int COMIENZO_CONTADOR_BOMBAS_Y = 550;

// Renderizador de la ventana
extern SDL_Renderer *renderizador;

extern SDL_Rect sprites[9];
extern SDL_Rect numeros[10];
extern SDL_Rect fondo;
extern Textura texturaSprites;
extern Textura texturaNumeros;
extern Textura texturaFondo;

class RenderizadorMapaGrafico {
public:

    RenderizadorMapaGrafico(MapaGrafico mg);

    void renderizarCantidadBombas();

    void renderizarPosicion(int x, int y, TipoPosicion tp);

    void renderizarMapaCompleto();

    void renderizarBomba(int xB, int yB);

    void renderizarExplosion(int xB, int yB);

    void renderizarMovimientoGanador(CoordenadaGrafica posicionAnterior, PuntoCardinal pc);

    void mover(PuntoCardinal pc);

    void tirarBomba();

    void deshacer();

private:

    MapaGrafico _mapaGrafico;

};

#endif // MAPAGRAFICORENDERIZADOR_H
