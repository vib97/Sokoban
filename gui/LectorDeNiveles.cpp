#include "LectorDeNiveles.h"

aed2_Nivel crearNivelDesdeArchivo(const string &rutaArchivo) {
    set<Coordenada> paredes;
    set<Coordenada> depositos;
    set<Coordenada> cajas;
    vector<string> mapaLeido;
    string line;
    Nat cantidadBombas;
    Coordenada posicionInicial;
    ifstream myfile(rutaArchivo);
    if (myfile.is_open()) {
        myfile >> cantidadBombas;
        while (getline(myfile, line)) {
            mapaLeido.push_back(line);
        }
        myfile.close();
    } else {
        cout << "No se pudo abrir el archivo\n";
    }
    for (int y = 0; y < mapaLeido.size(); ++y) {
        for (int x = 0; x < mapaLeido[y].size(); ++x) {
            switch (mapaLeido[y][x]) {
                case 'D':
                    depositos.insert({x, -y});
                    break;
                case 'P':
                    paredes.insert({x, -y});
                    break;
                case 'C':
                    cajas.insert({x, -y});
                    break;
                case 'I':
                    posicionInicial = {x, -y};
                    break;
                case '2':
                    depositos.insert({x, -y});
                    cajas.insert({x, -y});
                    break;
                case '0':
                    depositos.insert({x, -y});
                    posicionInicial = {x, -y};
                    break;
            }
        }
    }
    return {paredes, depositos, cajas, posicionInicial, cantidadBombas};
}

aed2_Juego crearJuego() {
    vector<aed2_Nivel> ns;
    string rutaNivel = "../gui/niveles/nivel0.txt";
    for (int i = 0; i < 10; ++i) {
        aed2_Nivel n = crearNivelDesdeArchivo(rutaNivel);
        ns.push_back(n);
        rutaNivel[20]++;
    }
    return {ns};
}
