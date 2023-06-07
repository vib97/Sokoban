#include "InterfazGrafica.h"

SDL_Window *ventana = nullptr;

bool iniciar() {
    bool success = true;

    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        success = false;
    } else {
        // Setear filtrado de texturas a lineal
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Advertencia: No se pudo habilitar el fitrado de texturas lineal\n");
        }

        // Crear ventana
        ventana = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, VENTANA_ANCHO,
                                   VENTANA_ALTO, SDL_WINDOW_SHOWN);
        if (ventana == nullptr) {
            printf("Error al crear la ventana: %s\n", SDL_GetError());
            success = false;
        } else {
            // Crear renderizador para la ventana
            renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
            if (renderizador == nullptr) {
                printf("Error al crear el renderizador: %s\n", SDL_GetError());
                success = false;
            } else {
                // Inicializar color de renderizador
                SDL_SetRenderDrawColor(renderizador, 0xFF, 0xFF, 0xFF, 0xFF);

                // Inicializar cargador de PNG
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("Error al inicializar SDL_image: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool cargarArchivos() {
    bool success = true;

    // Cargar los sprites desde la imagen
    if (!texturaSprites.cargarDesdeArchivo("../gui/imagenes/sprites.png", renderizador)) {
        printf("Fallo al cargar los sprites\n");
        success = false;
    } else {
        int i = 0;
        for (int y = 0; y < 96; y += 32) {
            for (int x = 0; x < 96; x += 32) {
                sprites[i].x = x;
                sprites[i].y = y;
                sprites[i].w = 32;
                sprites[i].h = 32;
                ++i;
            }
        }
    }

    // Cargar los numeros desde la imagen
    if (!texturaNumeros.cargarDesdeArchivo("../gui/imagenes/numeros.png", renderizador)) {
        printf("Fallo al cargar los numeros\n");
        success = false;
    } else {
        int i = 0;
        for (int x = 0; x < 280; x += 28) {
            numeros[i].x = x;
            numeros[i].y = 0;
            numeros[i].w = 28;
            numeros[i].h = 32;
            ++i;
        }
    }

    // Cargar el fondo desde la imagen
    if (!texturaFondo.cargarDesdeArchivo("../gui/imagenes/fondo.png", renderizador)) {
        printf("Fallo al cargar el fondo\n");
        success = false;
    } else {
        fondo.x = 0;
        fondo.y = 0;
        fondo.w = 800;
        fondo.h = 600;
    }

    return success;
}

void cerrar() {
    // Liberar las imagenes cargadas
    texturaSprites.liberar();
    texturaNumeros.liberar();
    texturaFondo.liberar();

    // Destruir la ventana
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    ventana = nullptr;
    renderizador = nullptr;

    // Salir de los subsistemas de SDL
    IMG_Quit();
    SDL_Quit();
}
