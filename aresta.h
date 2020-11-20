/** 
 * @file  aresta.h
 * @brief Arquivo da classe aresta do projeto
 *
 * @warning Documentar sempre que possível!
 * @todo 
 * @bug 
 * @authors João Victor - 201665528AB, Matheus Casarim 201765512AB, Mathews Edwirds 201765503AB. Grupo 19
*/

/*******************************************************************
*   Defines
*******************************************************************/
#ifndef ARESTA_H
#define ARESTA_H

/*******************************************************************
*   Includes
*******************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "no.h"

/*******************************************************************
*   DECLARAÇÕES DOS METODOS
*******************************************************************/

using namespace std;

class No;
/**
 * @brief Definição da classe Aresta
 * 
 */
class Aresta
{

private:
    No *no;       // Nó ao qual esta aponta (destino).
    Aresta *prox; // Próxima aresta que conecta o nó aos seus demais adjacentes.
    int peso;

public:
    Aresta(No *no, Aresta *prox, int peso);
    ~Aresta();
    No *getNo();
    void setNo(No *no);
    Aresta *getProx();
    void setProx(Aresta *prox);
    int getPeso();
    void setPeso(int peso);
};

#endif