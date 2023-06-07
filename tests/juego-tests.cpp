#include "gtest-1.8.1/gtest.h"
#include "../src/aed2_Juego.h"

class JuegoTest : public testing::Test {
protected:
    Coordenada pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos6O, pos7, pos8, pos8S, pos9, posN, posE, posS, posO;
    set<Coordenada> posiciones123, posiciones456, posiciones0456, posiciones789, posiciones5789;
    aed2_Nivel n1, n2;

    void SetUp() {
        pos0 = {1, 0};
        posN = {1, 1};
        posE = {2, 0};
        posS = {1, -1};
        posO = {0, 0};
        pos1 = {2, 1};
        pos2 = {-1, 1};
        pos3 = {0, -1};
        pos4 = {3, -1};
        pos5 = {3, -2};
        pos6 = {0, 2};
        pos6O = {-1, 2};
        pos7 = {2, -1};
        pos8 = {2, -2};
        pos8S = {2, -3};
        pos9 = {0, 1};
        posiciones123 = {pos1, pos2, pos3};
        posiciones456 = {pos4, pos5, pos6};
        posiciones0456 = {pos0, pos4, pos5, pos6};
        posiciones789 = {pos7, pos8, pos9};
        posiciones5789 = {pos5, pos7, pos8, pos9};
        n1 = {posiciones123, posiciones456, posiciones789, pos0, 2};
        // Nivel n1:
        //
        // -D---
        // PC-P-
        // --I--
        // -P-CD
        // ---CD
        n2 = {posiciones123, posiciones0456, posiciones5789, pos0, 0};
    }
};

TEST_F(JuegoTest, empezar_juego) {
    aed2_Juego j({n1});

    EXPECT_TRUE(j.hayPared(pos1));
    EXPECT_TRUE(j.hayPared(pos2));
    EXPECT_TRUE(j.hayPared(pos3));
    EXPECT_TRUE(j.hayDeposito(pos4));
    EXPECT_TRUE(j.hayDeposito(pos5));
    EXPECT_TRUE(j.hayDeposito(pos6));
    EXPECT_TRUE(j.hayCaja(pos7));
    EXPECT_TRUE(j.hayCaja(pos8));
    EXPECT_TRUE(j.hayCaja(pos9));
    EXPECT_EQ(j.posicionActual(), pos0);
    EXPECT_EQ(j.cantidadBombas(), 2);
}

TEST_F(JuegoTest, empezar_juego_con_solapamientos) {
    aed2_Juego j({n2});

    EXPECT_TRUE(j.hayPared(pos1));
    EXPECT_TRUE(j.hayPared(pos2));
    EXPECT_TRUE(j.hayPared(pos3));
    EXPECT_TRUE(j.hayDeposito(pos0));
    EXPECT_TRUE(j.hayDeposito(pos4));
    EXPECT_TRUE(j.hayDeposito(pos5));
    EXPECT_TRUE(j.hayDeposito(pos6));
    EXPECT_TRUE(j.hayCaja(pos5));
    EXPECT_TRUE(j.hayCaja(pos7));
    EXPECT_TRUE(j.hayCaja(pos8));
    EXPECT_TRUE(j.hayCaja(pos9));
    EXPECT_EQ(j.posicionActual(), pos0);
    EXPECT_EQ(j.cantidadBombas(), 0);
}

TEST_F(JuegoTest, se_puede_mover) {
    aed2_Juego j({n1});

    EXPECT_TRUE(j.sePuedeMover(Norte));
    EXPECT_TRUE(j.sePuedeMover(Este));
    EXPECT_TRUE(j.sePuedeMover(Sur));
    EXPECT_TRUE(j.sePuedeMover(Oeste));
}

TEST_F(JuegoTest, mover_al_norte) {
    aed2_Juego j({n1});

    EXPECT_FALSE(j.mover(Norte));
    EXPECT_EQ(j.posicionActual(), posN);
}

TEST_F(JuegoTest, mover_al_este) {
    aed2_Juego j({n1});

    EXPECT_FALSE(j.mover(Este));
    EXPECT_EQ(j.posicionActual(), posE);
}

TEST_F(JuegoTest, mover_al_sur) {
    aed2_Juego j({n1});

    EXPECT_FALSE(j.mover(Sur));
    EXPECT_EQ(j.posicionActual(), posS);
}

TEST_F(JuegoTest, mover_al_oeste) {
    aed2_Juego j({n1});

    EXPECT_FALSE(j.mover(Oeste));
    EXPECT_EQ(j.posicionActual(), posO);
}

TEST_F(JuegoTest, no_se_puede_mover_NS) {
    aed2_Juego j({n1});
    j.mover(Este);

    EXPECT_FALSE(j.sePuedeMover(Norte));
    EXPECT_FALSE(j.sePuedeMover(Sur));
}

TEST_F(JuegoTest, no_se_puede_mover_OE) {
    aed2_Juego j({n1});
    j.mover(Norte);

    EXPECT_FALSE(j.sePuedeMover(Oeste));
    EXPECT_FALSE(j.sePuedeMover(Este));
}

TEST_F(JuegoTest, empujar_caja_SE) {
    aed2_Juego j({n1});
    j.mover(Sur);
    j.mover(Este);
    j.mover(Sur);

    EXPECT_TRUE(j.hayCaja(pos4));
    EXPECT_TRUE(j.hayCaja(pos8S));
}

TEST_F(JuegoTest, empujar_caja_NE) {
    aed2_Juego j({n1});
    j.mover(Oeste);
    j.mover(Norte);
    j.mover(Este);
    j.mover(Norte);
    j.mover(Oeste);

    EXPECT_TRUE(j.hayCaja(pos6O));
}

TEST_F(JuegoTest, tirar_bomba_no_hace_nada) {
    aed2_Juego j({n1});
    j.tirarBomba();

    EXPECT_EQ(j.cantidadBombas(), 1);
    EXPECT_TRUE(j.hayPared(pos1));
    EXPECT_TRUE(j.hayPared(pos2));
    EXPECT_TRUE(j.hayPared(pos3));
}

TEST_F(JuegoTest, tirar_bomba_rompe_paredes) {
    aed2_Juego j({n1});
    j.mover(Norte);
    j.tirarBomba();

    EXPECT_EQ(j.cantidadBombas(), 1);
    EXPECT_FALSE(j.hayPared(pos1));
    EXPECT_FALSE(j.hayPared(pos2));
    EXPECT_TRUE(j.hayPared(pos3));
}

TEST_F(JuegoTest, deshacer_movimiento_al_norte) {
    aed2_Juego j({n1});
    j.mover(Norte);
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), pos0);
}

TEST_F(JuegoTest, deshacer_movimiento_al_este) {
    aed2_Juego j({n1});
    j.mover(Este);
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), pos0);
}

TEST_F(JuegoTest, deshacer_movimiento_al_sur) {
    aed2_Juego j({n1});
    j.mover(Sur);
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), pos0);
}

TEST_F(JuegoTest, deshacer_movimiento_al_oeste) {
    aed2_Juego j({n1});
    j.mover(Oeste);
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), pos0);
}

TEST_F(JuegoTest, deshacer_empujar_caja_SO) {
    aed2_Juego j({n1});
    j.mover(Sur);
    j.mover(Este);
    j.mover(Sur);
    j.deshacer();
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), posS);
    EXPECT_TRUE(j.hayCaja(pos7));
    EXPECT_TRUE(j.hayCaja(pos8));
}

TEST_F(JuegoTest, deshacer_empujar_caja_NE) {
    aed2_Juego j({n1});
    j.mover(Oeste);
    j.mover(Norte);
    j.mover(Este);
    j.mover(Norte);
    j.mover(Oeste);
    j.deshacer();
    j.deshacer();
    j.deshacer();
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), posO);
    EXPECT_TRUE(j.hayCaja(pos9));
}

TEST_F(JuegoTest, deshacer_tirar_bomba) {
    aed2_Juego j({n1});
    j.mover(Norte);
    j.tirarBomba();
    j.mover(Este);
    j.deshacer();
    j.deshacer();

    EXPECT_EQ(j.posicionActual(), posN);
    EXPECT_EQ(j.cantidadBombas(), 2);
    EXPECT_TRUE(j.hayPared(pos1));
    EXPECT_TRUE(j.hayPared(pos2));
    EXPECT_TRUE(j.hayPared(pos3));
}

TEST_F(JuegoTest, ganar_nivel) {
    aed2_Juego j({n1, n2});
    j.mover(Oeste);
    j.mover(Norte);
    j.mover(Este);
    j.mover(Sur);
    j.mover(Sur);
    j.mover(Este);
    j.mover(Oeste);
    j.mover(Sur);

    EXPECT_TRUE(j.mover(Este));
    EXPECT_TRUE(j.hayPared(pos1));
    EXPECT_TRUE(j.hayPared(pos2));
    EXPECT_TRUE(j.hayPared(pos3));
    EXPECT_TRUE(j.hayDeposito(pos0));
    EXPECT_TRUE(j.hayDeposito(pos4));
    EXPECT_TRUE(j.hayDeposito(pos5));
    EXPECT_TRUE(j.hayDeposito(pos6));
    EXPECT_TRUE(j.hayCaja(pos5));
    EXPECT_TRUE(j.hayCaja(pos7));
    EXPECT_TRUE(j.hayCaja(pos8));
    EXPECT_TRUE(j.hayCaja(pos9));
    EXPECT_EQ(j.posicionActual(), pos0);
    EXPECT_EQ(j.cantidadBombas(), 0);
}
