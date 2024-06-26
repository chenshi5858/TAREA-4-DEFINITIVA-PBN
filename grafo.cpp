#include "grafo.h"
#include <queue>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

Grafo::Grafo(int n){
    n_nodos = n;
    for (int i=1; i<=n; i++){ //no se puede ahi segun Fernanda, Chen no sabe
        nodos.push_back(i);
    }
}

int Grafo::add_nodo(){
    n_nodos+=1;
    nodos.push_back(n_nodos);
    //lista_a_matriz();
    if (matriz.size()!=0){
        if (verificar_matriz_a_lista()){
            matriz_a_lista();
        }
    }
    return n_nodos;
}

void Grafo::add_arco(int d, int h){
    if(lista_adyacencias.size()!=0 || (lista_adyacencias.size()==0 && matriz.size()==0)) lista_adyacencias.push_back({d, h});
    else matriz[d-1][h-1]=1;
    n_arcos+=1;
    if (verificar_lista_a_matriz()){
        lista_a_matriz();
    }

};


bool Grafo::hay_arco(int d, int h) {
    if (lista_adyacencias.size()!=0){
        for (const auto& arco : lista_adyacencias) {
            if (arco[0] == d && arco[1] == h) {
                return true;
            }
        }
    }else{
        if (matriz[d-1][h-1]==1) return true;
    }
    return false;
}



bool Grafo::hay_camino(int d, int h) {
    if(matriz.size()==0){
        //std::cout<<verificar_lista_a_matriz()<<std::endl;
        std::queue<int> cola;
        std::vector<bool> visitado(n_nodos + 1, false); // Vector para marcar nodos visitados
        cola.push(d);
        visitado[d] = true;

        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();

            // Verificar si hemos llegado al nodo destino h
            if (actual == h) {
                return true;
            }

            // Explorar los nodos adyacentes a 'actual'
            for (const auto& arco : lista_adyacencias) {
                if (arco[0] == actual && !visitado[arco[1]]) {
                    cola.push(arco[1]);
                    visitado[arco[1]] = true;
                }
            }
        }

        // Si terminamos la búsqueda y no encontramos el nodo h
        return false;
    }else{
        std::cout<<"wemooooooooo"<<std::endl;
        std::vector<int> caminos_actuales = {d}, caminos_proximos={};
        bool encontrado = false;
        while(!encontrado){
            for (unsigned i=0; i<caminos_actuales.size(); i++){
                for (unsigned j=0; j<matriz[caminos_actuales[i]-1].size(); j++){
                    if (matriz[caminos_actuales[i]-1][j]==1){
                        caminos_proximos.push_back(j+1);
                    }
                }
            }
            auto it = std::find(caminos_proximos.begin(), caminos_proximos.end(), h);
            if (it !=caminos_proximos.end()){
                encontrado = true;
            }
            caminos_actuales=caminos_proximos;
            caminos_proximos={};
        }
        return encontrado;
    }

}



void Grafo::mostrar_atributos(){
    std::cout<<"n_nodos: "<<n_nodos<<std::endl;

    std::cout<<"lista_adyacencias";
    std::cout<<"{";
    for(unsigned i=0; i<lista_adyacencias.size();i++){
        std::cout<<"{";
        for(unsigned j=0; j<lista_adyacencias[i].size();j++){
            std::cout<<lista_adyacencias[i][j]<<" ";
        }
        std::cout<<"}";
    }
    std::cout<<"}";
    std::cout<<std::endl;

    std::cout<<"nodos: ";
    std::cout<<"{";
    for (unsigned i=0; i<nodos.size(); i++){
        std::cout<<nodos[i]<<",";
    }
    std::cout<<"}";
    std::cout<<std::endl;

    std::cout<<"matriz_adyacencias";
    std::cout<<"{";

    for (unsigned i=0; i<matriz.size(); i++){
        std::cout<<"{";
        for (unsigned j=0; j<matriz[i].size();j++){
            std::cout<<matriz[i][j]<<" ";
        }
        std::cout<<"}"<<std::endl;
    }
    std::cout<<"}";
    std::cout<<std::endl;

}

bool Grafo::verificar_lista_a_matriz(){ //true: pasa a matriz , false: no pasa a matriz
    return n_arcos>(n_nodos*log2(n_nodos));
}

bool Grafo::verificar_matriz_a_lista(){ //true: lista , false: matriz
    return n_arcos<=(n_nodos*log2(n_nodos))/2;
}


void Grafo::lista_a_matriz(){
    matriz={};
    std::vector<int> fila;
    for(int i=0; i<n_nodos; i++){
        for(int j=0; j<n_nodos; j++){
            if (hay_arco(i+1,j+1)){
                fila.push_back(1);
            }else fila.push_back(0);
        }
        matriz.push_back(fila);
        fila={};
    }
    lista_adyacencias={};
}

void Grafo::matriz_a_lista(){

    for (int i=0; i<matriz.size(); i++){
        for (int j=0; j<matriz[i].size();j++){
            if (matriz[i][j]==1){
                lista_adyacencias.push_back({i+1,j+1});
            }
        }
    }
    matriz={};
}