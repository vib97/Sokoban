#include "RenderizadorMapaGrafico.h"

//The window renderer
SDL_Renderer *renderizador = nullptr;

//Scene sprites
SDL_Rect sprites[9];
SDL_Rect numeros[10];
SDL_Rect fondo;
Textura texturaSprites;
Textura texturaNumeros;
Textura texturaFondo;

RenderizadorMapaGrafico::RenderizadorMapaGrafico(MapaGrafico mg) : _mapaGrafico(mg) {}

void RenderizadorMapaGrafico::renderizarCantidadBombas() {
    Nat b = _mapaGrafico.cantidadBombas();
    if (b >= 10000) {
        for (int x = 0; x < 4; ++x) {
            texturaNumeros.renderizar(COMIENZO_CONTADOR_BOMBAS_X + 28 * x, COMIENZO_CONTADOR_BOMBAS_Y, renderizador,
                                      &numeros[9]);
        }
    } else {
        texturaNumeros.renderizar(COMIENZO_CONTADOR_BOMBAS_X + 0, COMIENZO_CONTADOR_BOMBAS_Y, renderizador,
                                  &numeros[b / 1000]);
        texturaNumeros.renderizar(COMIENZO_CONTADOR_BOMBAS_X + 28, COMIENZO_CONTADOR_BOMBAS_Y, renderizador,
                                  &numeros[b / 100 % 10]);
        texturaNumeros.renderizar(COMIENZO_CONTADOR_BOMBAS_X + 56, COMIENZO_CONTADOR_BOMBAS_Y, renderizador,
                                  &numeros[b / 10 % 10]);
        texturaNumeros.renderizar(COMIENZO_CONTADOR_BOMBAS_X + 84, COMIENZO_CONTADOR_BOMBAS_Y, renderizador,
                                  &numeros[b % 10]);
    }
}

void RenderizadorMapaGrafico::renderizarPosicion(int x, int y, TipoPosicion tp) {
    texturaSprites.renderizar(COMIENZO_MAPA_X + 32 * x, COMIENZO_MAPA_Y + 32 * y, renderizador, &sprites[tp]);
}

void RenderizadorMapaGrafico::renderizarMapaCompleto() {
    texturaFondo.renderizar(0, 0, renderizador, &fondo);
    for (int y = 0; y < 17; ++y) {
        for (int x = 0; x < 17; ++x) {
            renderizarPosicion(x, y, _mapaGrafico.tipoPosicion(x, y));
        }
    }
    renderizarCantidadBombas();
    SDL_RenderPresent(renderizador);
}

void RenderizadorMapaGrafico::renderizarBomba(int xB, int yB) {
    renderizarPosicion(xB, yB, Bomba);
    SDL_RenderPresent(renderizador);
}

void RenderizadorMapaGrafico::renderizarExplosion(int xB, int yB) {
    for (int x = 0; x < 17; ++x) {
        if (x != xB) {
            renderizarPosicion(x, yB, Explosion);
        }
    }
    for (int y = 0; y < 17; ++y) {
        if (y != yB) {
            renderizarPosicion(xB, y, Explosion);
        }
    }
    SDL_RenderPresent(renderizador);
}

void RenderizadorMapaGrafico::renderizarMovimientoGanador(CoordenadaGrafica posicionAnterior, PuntoCardinal pc) {
    int posicionAnteriorX = posicionAnterior.first;
    int posicionAnteriorY = posicionAnterior.second;
    int posicionPersonajeX = posicionAnteriorX;
    int posicionPersonajeY = posicionAnteriorY;
    int posicionDepositoCajaX = posicionPersonajeX;
    int posicionDepositoCajaY = posicionPersonajeY;
    if (pc == Norte) {
        posicionPersonajeY--;
        posicionDepositoCajaY -= 2;
    } else if (pc == Este) {
        posicionPersonajeX++;
        posicionDepositoCajaX += 2;
    } else if (pc == Sur) {
        posicionPersonajeY++;
        posicionDepositoCajaY += 2;
    } else if (pc == Oeste) {
        posicionPersonajeX--;
        posicionDepositoCajaX -= 2;
    }
    renderizarPosicion(posicionAnteriorX, posicionAnteriorY, Nada);
    renderizarPosicion(posicionPersonajeX, posicionPersonajeY, Personaje);
    renderizarPosicion(posicionDepositoCajaX, posicionDepositoCajaY, DepositoCaja);
    SDL_RenderPresent(renderizador);
}

void RenderizadorMapaGrafico::mover(PuntoCardinal pc) {
    if (_mapaGrafico.sePuedeMover(pc)) {
        CoordenadaGrafica posicionAnterior = _mapaGrafico.posicionActual();
        if (_mapaGrafico.mover(pc)) {
            renderizarMovimientoGanador(posicionAnterior, pc);
            SDL_Delay(500);
            texturaFondo.renderizar(0, 0, renderizador, &fondo);
            SDL_RenderPresent(renderizador);
            SDL_Delay(2000);
            renderizarMapaCompleto();
        } else {
            renderizarMapaCompleto();
        }
    }
}

void RenderizadorMapaGrafico::tirarBomba() {
    if (_mapaGrafico.sePuedeTirarBomba()) {
        _mapaGrafico.tirarBomba();
        Coordenada c = _mapaGrafico.posicionActual();
        int xB = c.first;
        int yB = c.second;
        renderizarBomba(xB, yB);
        SDL_Delay(1000);
        renderizarExplosion(xB, yB);
        SDL_Delay(1000);
        renderizarMapaCompleto();
    }
}

void RenderizadorMapaGrafico::deshacer() {
    _mapaGrafico.deshacer();
    renderizarMapaCompleto();
}