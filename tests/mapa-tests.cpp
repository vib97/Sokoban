#include "gtest-1.8.1/gtest.h"
#include "../src/mapa.h"



TEST(mapa_test, test_mapa_vacio) {
    mapa m;

    for (int x = -10; x <= 10; ++x) {
        for (int y = -10; y <= 10; ++y) {
            Coordenada c = {x, y};
            EXPECT_FALSE(m.hayPared_M(c));
            EXPECT_FALSE(m.hayDeposito_M(c));
        }
    }
}

TEST(mapa_test, test_agregar_Pared) {
    mapa m;
    m.agPared_M({0,-5});

    EXPECT_FALSE(m.hayPared_M({5, 0}));
    EXPECT_FALSE(m.hayPared_M({-10, 1000}));
    EXPECT_FALSE(m.hayPared_M({6, -300}));
    EXPECT_FALSE(m.hayPared_M({0, 4}));
    EXPECT_TRUE(m.hayPared_M({0, -5}));
}

TEST(mapa_test, test_agregar_Deposito) {
    mapa m;
    m.agDeposito_M({4,5});

    EXPECT_FALSE(m.hayDeposito_M({4, 0}));
    EXPECT_FALSE(m.hayDeposito_M({4, 1000}));
    EXPECT_FALSE(m.hayDeposito_M({4, -500}));
    EXPECT_FALSE(m.hayDeposito_M({5, 4}));
    EXPECT_TRUE(m.hayDeposito_M({4,5}));
}

TEST(mapa_test, test_agregar_varios) {
    mapa m;
    m.agPared_M({0, 1});
    m.agPared_M({-1, 5});
    m.agPared_M({-2, -3});
    m.agDeposito_M({7, -4});
    m.agDeposito_M({3, -8});
    m.agDeposito_M({-7, -5});

    EXPECT_TRUE(m.hayPared_M({0, 1}));
    EXPECT_TRUE(m.hayPared_M({-1, 5}));
    EXPECT_TRUE(m.hayPared_M({-2, -3}));
    EXPECT_TRUE(m.hayDeposito_M({7, -4}));
    EXPECT_TRUE(m.hayDeposito_M({3, -8}));
    EXPECT_TRUE(m.hayDeposito_M({-7, -5}));
    EXPECT_FALSE(m.hayDeposito_M({0, 1}));
    EXPECT_FALSE(m.hayDeposito_M({-1, 5}));
    EXPECT_FALSE(m.hayPared_M({3, -8}));
    EXPECT_FALSE(m.hayPared_M({7, -4}));
}

TEST(mapa_test, test_tirar_bomba) {
    mapa m;
    m.agPared_M({0, 1});
    m.agPared_M({0, -1});
    m.agPared_M({4, -5});
    m.agPared_M({-2, -1});
    m.agDeposito_M({4, -4});
    m.agDeposito_M({3, -8});
    m.agDeposito_M({5,4});
    m.agDeposito_M({-7, -5});
    m.agDeposito_M({4,0});

    m.tirarBomba_M({4, -1});

    EXPECT_TRUE(m.hayDeposito_M({4, 0}));
    EXPECT_FALSE(m.hayPared_M({4, 1000}));
    EXPECT_FALSE(m.hayPared_M({4, -5}));
    EXPECT_FALSE(m.hayPared_M({0, -1}));
    EXPECT_TRUE(m.hayPared_M({0, 1}));
    EXPECT_TRUE(m.hayDeposito_M({5, 4}));
    EXPECT_TRUE(m.hayDeposito_M({4,-4}));
}

TEST(mapa_tests, test_deshacer_bomba){
    mapa m;

    for (int x = -10; x <= 5; ++x) {
        for (int y = -10; y <= 5; ++y) {
            Coordenada c = {x, y};
            m.agPared_M(c);
        }
    }

    for (int x = -10; x <= 5; ++x) {
        for (int y = 6; y <= 10; ++y) {
            Coordenada c = {x, y};
            m.agDeposito_M(c);
        }
    }

    m.tirarBomba_M({4, -1});

    m.deshacerBomba_M();

    EXPECT_TRUE(m.hayPared_M({4, -10}));
    EXPECT_TRUE(m.hayPared_M({4, -5}));
    EXPECT_TRUE(m.hayPared_M({0, -1}));
    EXPECT_FALSE(m.hayPared_M({0, 100}));
    EXPECT_TRUE(m.hayDeposito_M({4, 10}));
    EXPECT_TRUE(m.hayDeposito_M({4, 6}));
}

TEST(mapa_tests, test_mostrar_depositos){
    mapa m;

    for (int x = -10; x <= 10; ++x) {
        Coordenada c = {x, 0};
        m.agPared_M(c);
    }

    for (int x = -3; x <= 3; ++x) {
        Coordenada c = {x, 3};
        m.agDeposito_M(c);
    }

    set<Coordenada> conj = {{-3,3},{-2,3},{-1,3},{0,3},{1,3},{2,3},{3,3}};

    EXPECT_TRUE(m.hayPared_M({4, 0}));
    EXPECT_FALSE(m.hayPared_M({4, -5}));
    EXPECT_TRUE(m.hayPared_M({10, 0}));
    EXPECT_FALSE(m.hayPared_M({0, 100}));
    EXPECT_FALSE(m.hayDeposito_M({4, 10}));
    EXPECT_TRUE(m.hayDeposito_M({0, 3}));
    EXPECT_EQ(m.depositos_M(), conj);
}