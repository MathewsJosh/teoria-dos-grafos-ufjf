/** 
 * @file  aresta.cpp
 * @brief Arquivo do objeto aresta do projeto
 *
 * @warning Documentar sempre que possível!
 * @todo 
 * @bug 
 * @authors João Victor - 201665528AB, Matheus Casarim 201765512AB, Mathews Edwirds 201765503AB. Grupo 19
*/

/*******************************************************************
*   Includes
*******************************************************************/
#include "aresta.h"

/*******************************************************************
*   IMPLEMENTACAO
*******************************************************************/

/**
 * @brief Construtor do objeto aresta
 * 
 * @param no Ponteiro para o vertice
 * @param prox Ponteiro que indica o vertice adjacente
 * @param peso Peso da aresta
 */
Aresta::Aresta(No *no, Aresta *prox, int peso)
{
    this->no = no;
    this->prox = prox;
    this->peso = peso;
}

/**
 * @brief Destrutor da aresta
 * 
 */
Aresta::~Aresta()
{
    if (prox != NULL)
    {
        delete prox;
    }
}

/**
 * @brief Retorna o nó atual
 * 
 * @return No* Retorna o nó atual
 */
No *Aresta::getNo()
{
    return this->no;
}

/**
 * @brief Determina o nó atual
 * 
 * @param no Nó atual
 */
void Aresta::setNo(No *no)
{
    this->no = no;
}

/**
 * @brief Retorna o proximo nó
 * 
 * @return Aresta* Proximo nó
 */
Aresta *Aresta::getProx()
{
    return this->prox;
}

/**
 * @brief Determina o proximo nó
 * 
 * @param prox Proximo nó
 */
void Aresta::setProx(Aresta *prox)
{
    this->prox = prox;
}

/**
 * @brief Retorna o peso da aresta
 * 
 * @return int Peso da aresta
 */
int Aresta::getPeso()
{
    return this->peso;
}

/**
 * @brief Determina o peso da aresta
 * 
 * @param peso peso da aresta
 */
void Aresta::setPeso(int peso)
{
    this->peso = peso;
}