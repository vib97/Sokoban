#include "gtest-1.8.1/gtest.h"
#include "../src/nivel.h"

/**Tests de clase Nivel**/

TEST(nivel_test, nivel) {
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

    EXPECT_EQ(n.mapa_N().depositos_M(), m.depositos_M());
    EXPECT_EQ(n.mapa_N().hayPared_M({-1, 3}), m.hayPared_M({-1, 3}));
    EXPECT_EQ(n.mapa_N().hayPared_M({1, 2}), m.hayPared_M({1, 2}));
    EXPECT_EQ(n.mapa_N().hayPared_M({0, -2}), m.hayPared_M({0, -2}));
    EXPECT_EQ(n.persona_N(), p);
    EXPECT_EQ(n.cajas_N(), cajas);
    EXPECT_EQ(n.cantBombas_N(), 3);

}
