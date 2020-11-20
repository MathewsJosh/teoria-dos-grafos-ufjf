/** 
 * @file  no.cpp
 * @brief Arquivo do objeto no do projeto
 *
 * @warning Documentar sempre que possível!
 * @todo 
 * @bug 
 * @authors João Victor - 201665528AB, Matheus Casarim 201765512AB, Mathews Edwirds 201765503AB. Grupo 19
*/

/*******************************************************************
*   Includes
*******************************************************************/
#include "no.h"


/*******************************************************************
*   IMPLEMENTAÇÃO
*******************************************************************/

/**
 * @brief Construtor do objeto No
 * 
 * @param id Identificação do no
 */
No::No(int id)
{
    this->id = id;
    this->prox = NULL;
}

/**
 * @brief Destrutor do objeto No
 * 
 */
No::~No() // Destrutor
{
    if (prox != NULL)
    {
        delete prox;
    }
}

/**
 * @brief Retorna o nó atual
 * 
 * @return int 
 */
int No::getId() // GET ID
{
    return this->id;
}

/**
 * @brief Determina o id do nó atual
 * 
 * @param id 
 */
void No::setId(int id) // SET ID
{
    this->id = id;
}

/**
 * @brief Determina o peso do nó atual
 * 
 * @param peso 
 */
void No::setPesoNo(int peso)
{
    this->pesoNo = peso;
}

/**
 * @brief Retorna o peso do nó atual
 * 
 * @return int 
 */
int No::getPesoNo()
{
    return this->pesoNo;
}

/**
 * @brief Retorna o proximo nó
 * 
 * @return Aresta* 
 */
Aresta *No::getProx() // GET PROX
{
    return this->prox;
}

/**
 * @brief Determina o proximo nó
 * 
 * @param prox Proximo nó
 */
void No::setProx(Aresta *prox) // SET PROX
{
    this->prox = prox;
}

/**
 * @brief Adiciona aresta entre os nos
 * 
 * @param n no atual
 * @param peso peso da aresta
 */
void No::adcAresta(No *n, int peso)
{
    Aresta *a = new Aresta(n, this->getProx(), peso);
    this->setProx(a);
}