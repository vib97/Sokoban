#ifndef JUEGO_H
#define JUEGO_H

#include "sokoban.h"

class juego {
    
public:
    juego(vector<nivel> ns);

    bool mover_J(PuntoCardinal pc);

    void tirarBomba_J();

    void deshacer_J();

    sokoban nivelActual_J() const;

    list<nivel> nivelesPendientes_J();

private:

    list<nivel> _nivelesPendientes;

    sokoban _nivelActual;

};

#endif //JUEGO_H
