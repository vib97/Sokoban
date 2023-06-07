#include "gtest-1.8.1/gtest.h"
#include "../src/sokoban.h"


/** Tests de clase Sokoban **/

TEST(sokoban_test, constructor_vacio){
    sokoban s = sokoban();
    for(int x = -10; x <= 10; x++){
        for(int y = -10; y <= 10; y++){
            EXPECT_FALSE(s.mapa_S().hayPared_M({x,y}));
            EXPECT_FALSE(s.mapa_S().hayDeposito_M({x,y}));
            EXPECT_FALSE(s.hayCaja_S({x,y}));
        }
    }
    EXPECT_EQ(s.cantidadBombas_S(), 0);
}

TEST(sokoban_test, mover){
    mapa m;
    m.agPared_M({-1, 3});
    m.agPared_M({1, 2});
    m.agPared_M({0, -2});
    m.agDeposito_M({0, 3});
    m.agDeposito_M({3, 3});
    set<Coordenada> cajas;
    Coordenada p = {0, 0};
    cajas.insert({-2, 1});
    cajas.insert({1, -2});
    nivel n = nivel(m, p, cajas, 3);

    sokoban s = sokoban(n);

    EXPECT_TRUE(s.puedeMover_S(Norte));

    s.mover_S(Este); //(1, 0)
    s.mover_S(Norte); //(1, 1)

    EXPECT_FALSE(s.puedeMover_S(Norte));

}

TEST(sokoban_test, persona){
    mapa m;
    m.agPared_M({-1, 3});
    m.agPared_M({1, 2});
    m.agPared_M({0, -2});
    m.agDeposito_M({0, 3});
    m.agDeposito_M({3, 3});
    set<Coordenada> cajas;
    Coordenada p = {0, 0};
    cajas.insert({-2, 1});
    cajas.insert({1, -2});
    nivel n = nivel(m, p, cajas, 3);

    sokoban s = sokoban(n);

    EXPECT_EQ(s.persona_S(), p);

    s.mover_S(Este);

    Coordenada q = {1, 0};

    EXPECT_EQ(s.persona_S(), q);
}

TEST(sokoban_test, paredes_y_cajas){
    mapa m;
    m.agPared_M({-1, 3});
    m.agPared_M({1, 2});
    m.agPared_M({0, -2});
    m.agDeposito_M({0, 3});
    m.agDeposito_M({3, 3});
    set<Coordenada> cajas;
    Coordenada p = {0, 0};
    cajas.insert({-2, 1});
    cajas.insert({1, -2});
    nivel n = nivel(m, p, cajas, 3);

    sokoban s = sokoban(n);

    EXPECT_TRUE(s.hayCaja_S({1, -2}));
    EXPECT_TRUE(s.noHayParedNiCaja_S({0, 1}));
    EXPECT_TRUE(s.hayCajas_S({{-2, 1}, {1, -2}}));
}

TEST(sokoban_test, bombas){
    mapa m;
    m.agPared_M({-1, 3});
    m.agPared_M({1, 2});
    m.agPared_M({0, -2});
    m.agDeposito_M({0, 3});
    m.agDeposito_M({3, 3});
    set<Coordenada> cajas;
    Coordenada p = {0, 0};
    cajas.insert({-2, 1});
    cajas.insert({1, -2});
    nivel n = nivel(m, p, cajas, 3);

    sokoban s = sokoban(n);

    EXPECT_EQ(s.cantidadBombas_S(), 3);

    s.tirarBomba_S();

    EXPECT_EQ(s.cantidadBombas_S(), 2);
    EXPECT_TRUE(s.noHayParedNiCaja_S({0, -2}));

    s.tirarBomba_S();

    EXPECT_EQ(s.cantidadBombas_S(), 1);

}

TEST(sokoban_test, deshacer){
    mapa m;
    m.agPared_M({0, 1});
    m.agDeposito_M({0, 3});
    m.agDeposito_M({3, 3});
    set<Coordenada> cajas;
    Coordenada p = {0, 0};
    cajas.insert({1, 0});

    nivel n = nivel(m, p, cajas, 3);

    sokoban s = sokoban(n);

    s.mover_S(Este);
    EXPECT_TRUE(s.hayCaja_S({2, 0}));
    s.deshacer_S();
    EXPECT_FALSE(s.hayCaja_S({2, 0}));
    EXPECT_TRUE(s.hayCaja_S({1, 0}));

    s.tirarBomba_S();
    EXPECT_TRUE(s.noHayParedNiCaja_S({0, 1}));
    s.deshacer_S();
    EXPECT_FALSE(s.noHayParedNiCaja_S({0, 1}));
}

TEST(sokoban_test, gano){
    mapa m;
    m.agDeposito_M({0, 3});
    m.agDeposito_M({3, 3});
    set<Coordenada> cajas;
    Coordenada p = {0, 1};
    cajas.insert({3, 3});
    cajas.insert({0, 2});
    nivel n = nivel(m, p, cajas, 3);

    sokoban s = sokoban(n);

    s.mover_S(Norte);
    EXPECT_TRUE(s.gano_S());

}

