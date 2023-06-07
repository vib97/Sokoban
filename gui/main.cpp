#include <SDL2/SDL.h>
#include "InterfazGrafica.h"
#include "LectorDeNiveles.h"

int main(int argc, char *args[]) {
    // Inicializar SDL y crear la ventana
    if (!iniciar()) {
        printf("Fallo al inicializar\n");
    } else {
        // Cargar las imagenes
        if (!cargarArchivos()) {
            printf("Fallo al cargar las imagenes\n");
        } else {
            bool quit = false;

            // Manejador de eventos
            SDL_Event e;

            // Limpiar la pantalla
            SDL_SetRenderDrawColor(renderizador, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderizador);

            // Inicializar variables para mostrar el mapa
            aed2_Juego j = crearJuego();
            MapaGrafico mg(j);
            RenderizadorMapaGrafico mgr(mg);

            // Imprimir el estado inicial
            mgr.renderizarMapaCompleto();

            // Mientras el programa esta corriendo
            while (!quit) {
                // Manejo de eventos en la cola
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        // El usuario cierra el programa
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        // El usuario apreta una letra
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                            case SDLK_w:
                                mgr.mover(Norte);
                                break;

                            case SDLK_RIGHT:
                            case SDLK_d:
                                mgr.mover(Este);
                                break;

                            case SDLK_DOWN:
                            case SDLK_s:
                                mgr.mover(Sur);
                                break;

                            case SDLK_LEFT:
                            case SDLK_a:
                                mgr.mover(Oeste);
                                break;

                            case SDLK_SPACE:
                            case SDLK_b:
                                mgr.tirarBomba();
                                break;

                            case SDLK_BACKSPACE:
                            case SDLK_r:
                                mgr.deshacer();
                                break;

                            default:
                                break;
                        }
                    }
                }
            }
        }
    }

    // Liberar los recursos y cerrar SDL
    cerrar();

    return 0;
}
