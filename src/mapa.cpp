#include "mapa.h"

mapa::mapa() {
	_paredes = {};
	_depositos = {};
	_bombas = {};
}

void mapa::agPared_M(Coordenada c) {
	int n = _paredes.size();
	Coordenada aux = c;
	for(int i = 0; i < n; i++){
		if(aux.first < _paredes[i].first || 
		  (aux.first == _paredes[i].first && aux.second < _paredes[i].second)){
			Coordenada auxParaSwap = aux;
			aux = _paredes[i];
			_paredes[i] = auxParaSwap;
		}
	}
	_paredes.push_back(aux);
}

void mapa::agDeposito_M(Coordenada c) {
	int n = _depositos.size();
	Coordenada aux = c;
	for(int i = 0; i < n; i++){
		if(aux.first < _depositos[i].first || 
		  (aux.first == _depositos[i].first && aux.second < _depositos[i].second)){
			Coordenada auxParaSwap = aux;
			aux = _depositos[i];
			_depositos[i] = auxParaSwap;
		}
	}
	_depositos.push_back(aux);
}

bool mapa::hayPared_M(Coordenada c) const {
	bool esta = false;
	int inf = 0;
	int sup = _paredes.size()-1;
	int med = 0;
	while(!esta && inf <= sup){
		med = (inf + sup)/2;
		if(c == _paredes[med]){
			esta = true;
		} else if(c.first < _paredes[med].first || 
		         (c.first == _paredes[med].first && c.second < _paredes[med].second)){
			sup = med-1;
		} else {
			inf = med+1;
		}
	}
	if(esta){
		for(Coordenada p : _bombas){
			if(c.first == p.first || c.second == p.second){
				return false;
			}
		}
	}
	return esta;
}

bool mapa::hayDeposito_M(Coordenada c) const {
	bool esta = false;
	int inf = 0;
	int sup = _depositos.size()-1;
	int med = 0;
	while(!esta && inf <= sup){
		med = (inf + sup)/2;
		if(c == _depositos[med]){
			esta = true;
		} else if(c.first < _depositos[med].first || 
		         (c.first == _depositos[med].first && c.second < _depositos[med].second)){
			sup = med-1;
		} else {
			inf = med+1;
		}
	}
	return esta;
}

void mapa::tirarBomba_M(Coordenada c) {
	_bombas.push_back(c);
}

void mapa::deshacerBomba_M() {
	_bombas.pop_back();
}

set<Coordenada> mapa::depositos_M() {
	set<Coordenada> depos = {};
	for(int i = 0; i < _depositos.size(); i++){
		depos.insert(_depositos[i]);
	}
	return depos;
}