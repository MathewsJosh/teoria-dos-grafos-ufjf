/** 
 * @file  grafo.h
 * @brief Arquivo da classe grafo do projeto
 *
 * @warning Documentar sempre que possível!
 * @todo 
 * @bug 
 * @authors João Victor - 201665528AB, Matheus Casarim 201765512AB, Mathews Edwirds 201765503AB. Grupo 19
*/

/*******************************************************************
*   Defines
*******************************************************************/
#ifndef GRAFO_H
#define GRAFO_H

/*******************************************************************
*   Includes
*******************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

#include "no.h"

/*******************************************************************
*   DECLARAÇÕES DOS METODOS
*******************************************************************/

using namespace std;

typedef struct
{
    int grau;
    float frequencia;
} freq;

/**
 * @brief Definição da classe Grafo
 * 
 */
class Grafo
{

private:
    void leArquivo(string caminho);
    void leArquivo2(string caminho);
    vector<string> split(string str, char delimiter);
    No **grafo;     // Vetor de vetores, do tipo No.
    int n_vertices; // Variável responsável por alocar o número de vértices de cada grafo.
    vector<int> sequenciaGrau;
    bool verificaSolucao (bool *nos);

public:
    Grafo(string caminho);
    ~Grafo();
    void printGrafo();
    int numArestas();
    int numArestasTotal();
    float grauMedioGrafo();
    bool verificaAresta(int id1, int id2);
    vector<freq> frequenciaRelativa(); // Capta a sequencia de graus de cada nó e armazena em vetor.
    int getNumVertices();
    void buscaLargura(int origem);
    void buscaProfundidade(int origem);
    void dijkstra(int origem);
    void floyd();
    void prim();
    void kruskal();
    int guloso(); // Conjunto Dominante Mínimo
    int gulosoRandomizado(float alfa, int semente);
};

#endif