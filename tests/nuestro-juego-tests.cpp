#include "gtest-1.8.1/gtest.h"
#include "../src/juego.h"

TEST(nuestroJuegoTest, jugarYganar){

    set<Coordenada> parNivel3 = {{0,0},{0,1},{0,2}};
    set<Coordenada> depNivel3 = {{1,1}};
    set<Coordenada> cajNivel3 = {{1,0}};
    mapa m3 = mapa();
    for(Coordenada c : parNivel3){
        m3.agPared_M(c);
    }
    for(Coordenada c : depNivel3){
        m3.agDeposito_M(c);
    }
    nivel n3 = nivel(m3, {0,-1}, cajNivel3, 3);

    set<Coordenada> parNivel4 = {{1,0},{1,1},{1,2}};
    set<Coordenada> depNivel4 = {{2,1}};
    set<Coordenada> cajNivel4 = {{2,0}};
    mapa m4 = mapa();
    for(Coordenada c : parNivel4){
        m4.agPared_M(c);
    }
    for(Coordenada c : depNivel4){
        m4.agDeposito_M(c);
    }
    nivel n4 = nivel(m4, {1,-1}, cajNivel4, 2);

    juego j = juego({n3,n4});

    j.tirarBomba_J();
    EXPECT_FALSE(j.mover_J(Este));
    EXPECT_FALSE(j.mover_J(Este));
    EXPECT_FALSE(j.mover_J(Este));
    j.deshacer_J();
    j.deshacer_J();
    EXPECT_TRUE(j.mover_J(Norte));

    EXPECT_TRUE(j.nivelesPendientes_J().empty());

    EXPECT_FALSE(j.mover_J(Este));
    EXPECT_TRUE(j.mover_J(Norte));


}
