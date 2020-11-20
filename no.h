/** 
 * @file  no.h
 * @brief Arquivo da classe no do projeto
 *
 * @warning Documentar sempre que possível!
 * @todo 
 * @bug 
 * @authors João Victor - 201665528AB, Matheus Casarim 201765512AB, Mathews Edwirds 201765503AB. Grupo 19
*/

/*******************************************************************
*   Defines
*******************************************************************/
#ifndef NO_H
#define NO_H

/*******************************************************************
*   Includes
*******************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "aresta.h"

/*******************************************************************
*   DECLARAÇÕES DOS METODOS
*******************************************************************/

using namespace std;

class Aresta;
/**
 * @brief Definição da classe no
 * 
 */
class No
{

private:
    int id;       // Valor contido em um nó.
    Aresta *prox; // Aresta que liga o nó atual aos seus adjacentes.
    int pesoNo;

public:
    No(int id);                 // Construtor da classe Nó.
    ~No();                      // Destrutor da classe Nó.
    int getId();                // Retorna o ID do nó (função GET).
    void setId(int id);         // Altera o ID do nó (função SET).
    int getPesoNo();
    void setPesoNo(int peso);
    Aresta *getProx();          // Retorna o ponteiro da aresta que liga o nó ao adjacente.
    void setProx(Aresta *prox); // Altera o nó adjacente.
    void adcAresta(No *n, int peso);
};

#endif