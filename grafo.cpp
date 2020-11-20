/** 
 * @file  grafo.cpp
 * @brief Arquivo do objeto grafo do projeto
 *
 * @warning Documentar sempre que possível!
 * @todo 
 * @bug 
 * @authors João Victor - 201665528AB, Matheus Casarim 201765512AB, Mathews Edwirds 201765503AB. Grupo 19
*/

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
#include <climits>
#include <math.h>

#include "grafo.h"

/*******************************************************************
*   IMPLEMENTAÇÃO
*******************************************************************/

using namespace std;

/**
 * @brief Struct estado - agrupa dados diferentes como sendo do mesmo tipo estado
 * 
 */
struct estado
{
    int id;
    int custoDist;
    int idPai;
};

/**
 * @brief Struct arestasOrdenadas - agrupa dados diferentes como sendo do mesmo tipo arestasOrdenadas
 * 
 */
struct arestasOrdenadas
{
    int id;
    Aresta *a;
};

/**
 * @brief Struct candidatos - agrupa dados diferentes como sendo do mesmo tipo candidatos
 * 
 */
struct candidatos
{
    int id;
    int numVizinhos;
};

/**
 * @brief Método booleano que ordena o vetor frequencia relativa em conjunto com o metodo sort()
 * 
 * @param v1 Primeiro elemento da comparação
 * @param v2 Segundo elemento da comparação
 * @return true 
 * @return false 
 */
bool compare(int v1, int v2)
{
    return (v1 > v2);
}

/**
 * @brief Método booleano que compara e ordena os elementos de acordo com seu custo
 * 
 * @param e1 Primeiro elemento da comparação
 * @param e2 Segundo elemento da comparação
 * @return true 
 * @return false 
 */
bool compare2(estado e1, estado e2)
{
    return (e1.custoDist < e2.custoDist);
}

/**
 * @brief Método booleano que compara e ordena os elementos de acordo com seu peso
 * 
 * @param ao1 Primeiro elemento da comparação
 * @param ao2 Segundo elemento da comparação
 * @return true 
 * @return false 
 */
bool compare3(arestasOrdenadas ao1, arestasOrdenadas ao2)
{
    return (ao1.a->getPeso() > ao2.a->getPeso());
}

/**
 * @brief Método booleano que compara e ordena as arestas a partir de seu id
 * 
 * @param ao1 Primeiro elemento da comparação
 * @param ao2 Segundo elemento da comparação
 * @return true 
 * @return false 
 */
bool compare4(arestasOrdenadas ao1, arestasOrdenadas ao2)
{
    return (ao1.id < ao2.id);
}

/**
 * @brief Método booleano que compara e ordena os candidatos a partir do seu numero de vizinhos
 * 
 * @param c1 Primeiro elemento da comparação
 * @param c2 Segundo elemento da comparação
 * @return true 
 * @return false 
 */
bool compare5(candidatos c1, candidatos c2)
{
    return (c1.numVizinhos < c2.numVizinhos);
}

/**
 * @brief Função que realiza o "split" ou quebra de cada linha lida do grafo, separando os nós e ponderamentos de cada aresta entre os mesmos
 * 
 * @param str Vetor de string a ser particionado
 * @param delimiter O limitador para o particionamento
 * @return vector<string> 
 */
vector<string> Grafo::split(string str, char delimiter)
{
    vector<string> s;
    stringstream ss(str);
    string part;
    while (getline(ss, part, delimiter))
    {
        s.push_back(part);
    }

    return s;
}

/**
 * @brief Retorna o numero de vertices do grafo
 * 
 * @return int 
 */
int Grafo::getNumVertices()
{
    return n_vertices;
}

/**
 * @brief Imprime o grafo na tela.
 * 
 */
void Grafo::printGrafo()
{

    for (int i = 0; i < n_vertices; i++)
    {
        cout << grafo[i]->getId() << " - ";
        Aresta *aux = grafo[i]->getProx();
        while (aux != NULL)
        {
            cout << aux->getNo()->getId() << " - ";
            aux = aux->getProx();
        }

        cout << endl;
    }
}

/**
 * @brief Construtor do objeto grafo
 * 
 * @param caminho 
 */
Grafo::Grafo(string caminho)
{
    string tipo = caminho;
    string aux;
    char c = tipo[0];
    int cont = 1;

    while (c != '.')
    {
        c = tipo[cont];
        cont++;
    }

    for (int i = 0; i < 3; i++)
    {
        aux += tipo[cont + i];
    }

    if (aux == "txt")
        leArquivo(caminho);

    else
        leArquivo2(caminho);
}

/**
 * @brief Destrutor do objeto grafo
 * 
 */
Grafo::~Grafo()
{
    for (int i = 0; i < n_vertices; i++)
    {
        delete grafo[i];
    }

    delete[] grafo;
}

/**
 * @brief Realiza a leitura do arquivo .txt fornecido no parametro para a fase 1
 * 
 * @param caminho Caminho referente ao arquivo instancia
 */
void Grafo::leArquivo(string caminho)
{

    ifstream arquivo(caminho);

    if (!arquivo.is_open())
    {
        cout << "Arquivo nao encontrado.";
        return;
    }

    else
    {

        string linha;
        getline(arquivo, linha);

        // Converte a primeira linha do arquivo de string para inteiro (número de vértices).
        n_vertices = stoi(linha);

        // Instancia o vetor de vetores com o número de vértices.
        grafo = new No *[n_vertices];

        for (int i = 0; i < n_vertices; i++)
        {
            // Preenche o vetor de nós.
            grafo[i] = new No(i);
        }

        // Enquanto a linha do aruivo for diferente de NULL.
        while (getline(arquivo, linha))
        {
            // Realiza o "split" linha após linha, obtendo os nós e o peso das arestas.
            vector<string> vet = split(linha, ' ');

            // Conversão dos valores obtidos em cada linha.
            int no1 = stoi(vet[0]);
            int no2 = stoi(vet[1]);
            int peso = stoi(vet[2]);

            if (verificaAresta(no1, no2))
            {
                // Conecta ao nó as arestas que o ligam aos seus adjacentes.
                grafo[no1]->adcAresta(grafo[no2], peso);

                // Realiza o mesmo processo com o nó adjacente.
                grafo[no2]->adcAresta(grafo[no1], peso);
            }
        }

        arquivo.close();
    }
}

/**
 * @brief Realiza a leitura do arquivo de instâncias fornecido no parametro para a fase 2
 * 
 * @param caminho Caminho referente ao arquivo instancia
 */
void Grafo::leArquivo2(string caminho)
{
    ifstream arquivo(caminho);

    if (!arquivo.is_open())
    {
        cout << "Arquivo nao encontrado.";
        return;
    }

    else
    {
        string linha;
        getline(arquivo, linha);
        getline(arquivo, linha);

        n_vertices = stoi(linha);

        grafo = new No *[n_vertices];

        for (int i = 0; i < n_vertices; i++)
        {
            // Preenche o vetor de nós.
            grafo[i] = new No(i);
        }

        for (int i = 0; i < n_vertices + 2; i++)
        {
            getline(arquivo, linha);
        }

        for (int i = 0; i < n_vertices; i++)
        {
            getline(arquivo, linha);
            grafo[i]->setPesoNo(stoi(linha));
        }

        getline(arquivo, linha);

        for (int i = 0; i < n_vertices; i++)
        {
            getline(arquivo, linha);
            vector<string> vet = split(linha, ' ');

            for (int j = 0; j < n_vertices; j++)
            {
                if (verificaAresta(i, j))
                {
                    if (stoi(vet[j]) == 1)
                        grafo[i]->adcAresta(grafo[j], 0);
                }
            }
        }

        arquivo.close();
    }
}

/**
 * @brief Calcula e retorna o numero total de arestas ao dobro (x2)
 * 
 * @return int 
 */
int Grafo::numArestasTotal()
{
    int cont = 0;
    Aresta *aux;

    for (int i = 0; i < n_vertices; i++)
    {
        aux = grafo[i]->getProx();

        while (aux != NULL)
        {
            cont++;

            aux = aux->getProx();
        }
    }

    return cont;
}

/**
 * @brief Calcula e retorna o numero total de arestas do grafo
 * 
 * @return int 
 */
int Grafo::numArestas()
{
    int total = this->numArestasTotal() / 2;

    return total;
}

/**
 * @brief Calcula e retorna o grau medio dos nós do grafo
 * 
 * @return float 
 */
float Grafo::grauMedioGrafo()
{
    float total = (float)this->numArestasTotal() / n_vertices;

    return total;
}

/**
 * @brief Verifica o grafo eliminando self-loops e multiarestas. O padrão de inserção de arestas se dá pela ordem de aparição das mesmas no arquivo <entrada.txt>
 * 
 * @param id1 É a identificação do no 1 a ser verificado
 * @param id2 É a identificação do no 2 a ser verificado
 * @return true 
 * @return false 
 */
bool Grafo::verificaAresta(int id1, int id2)
{
    if (id1 == id2)
        return false;

    Aresta *aux = this->grafo[id1]->getProx();

    if (aux != NULL)
    {
        while (aux != NULL)
        {
            if (aux->getNo()->getId() == id2)
                return false;

            aux = aux->getProx();
        }

        return true;
    }
    else
    {
        return true;
    }
}

/**
 * @brief É o vector do tipo <freq> (struct) que armazena em ordem decrescente as frequencias relativas do grafo 
 * 
 * @return vector<freq> 
 */
vector<freq> Grafo::frequenciaRelativa()
{
    Aresta *aux;
    int cont;

    freq auxF;
    vector<freq> f;

    for (int i = 0; i < n_vertices; i++)
    {
        aux = grafo[i]->getProx();
        int cont = 0;

        while (aux != NULL)
        {
            cont++;
            aux = aux->getProx();
        }

        sequenciaGrau.push_back(cont);
        cont = 0;
    }

    int maiorGrau = sequenciaGrau.at(0);
    int menorGrau = sequenciaGrau.at(0);

    for (int i = 1; i < n_vertices; i++)
    {
        if (sequenciaGrau.at(i) > maiorGrau)
            maiorGrau = sequenciaGrau.at(i);

        if (sequenciaGrau.at(i) < menorGrau)
            menorGrau = sequenciaGrau.at(i);
    }

    int j;
    int contadorOcorrencia;

    vector<int> ordenado = sequenciaGrau;
    sort(ordenado.begin(), ordenado.end(), compare);

    while (ordenado.size() != 0)
    {
        j = 1;
        contadorOcorrencia = 1;

        while (j < ordenado.size())
        {
            if ((ordenado.at(0) == ordenado.at(j)))
            {
                ordenado.erase(ordenado.begin() + j);
                contadorOcorrencia++;
                j--;
            }

            j++;
        }

        auxF.grau = ordenado.at(0);
        auxF.frequencia = contadorOcorrencia / (float)this->n_vertices;
        f.push_back(auxF);

        ordenado.erase(ordenado.begin());
    }

    return f;
}

/**
 * @brief Faz a busca em largura no grafo, marcando as posições a cada visita 
 * 
 * @param origem posição inicial onde começa a busca
 */
void Grafo::buscaLargura(int origem)
{
    if (origem >= 0 && origem < this->getNumVertices())
    {
        bool *vetor_visitas = new bool[this->getNumVertices()]; // Vetor de posições visitadas

        for (int i = 0; i < this->getNumVertices(); i++)
            vetor_visitas[i] = false; // Inicializa todas as posições como não visitadas.

        queue<int> fila;

        vetor_visitas[origem] = true;
        fila.push(origem);

        Aresta *iterador = grafo[origem]->getProx();

        while (!fila.empty())
        {

            cout << fila.front() << " - ";

            for (; iterador != NULL; iterador = iterador->getProx())
            {
                if (!vetor_visitas[iterador->getNo()->getId()])
                {
                    vetor_visitas[iterador->getNo()->getId()] = true;
                    fila.push(iterador->getNo()->getId());
                }
            }

            fila.pop();

            if (!fila.empty())
                iterador = grafo[fila.front()]->getProx();
        }

        cout << endl;

        delete[] vetor_visitas;
    }

    else
    {
        cout << endl
             << "O no fornecido nao consta na instancia analisada!" << endl;
        return;
    }
}

/**
 * @brief Faz a busca em profundidade marcando as posições assim que é feita a visita
 * 
 * @param origem posição inicial onde começa a busca
 */
void Grafo::buscaProfundidade(int origem)
{

    if (origem >= 0 && origem < this->getNumVertices())
    {
        bool *vetor_visitas = new bool[this->getNumVertices()]; // Vetor de posições visitadas

        for (int i = 0; i < this->getNumVertices(); i++)
            vetor_visitas[i] = false; // Inicializa todas as posições como não visitadas.

        stack<int> pilha;

        vetor_visitas[origem] = true;
        pilha.push(origem);

        Aresta *iterador = grafo[origem]->getProx();

        while (!pilha.empty())
        {

            cout << pilha.top() << " - ";

            pilha.pop();

            for (; iterador != NULL; iterador = iterador->getProx())
            {
                if (!vetor_visitas[iterador->getNo()->getId()])
                {
                    vetor_visitas[iterador->getNo()->getId()] = true;
                    pilha.push(iterador->getNo()->getId());
                }
            }

            if (!pilha.empty())
                iterador = grafo[pilha.top()]->getProx();
        }

        cout << endl;

        delete[] vetor_visitas;
    }

    else
    {
        cout << endl
             << "O no fornecido nao consta na instancia analisada!" << endl;
        return;
    }
}

/**
 * @brief implementa o caminhamento dijkstra para encontrar o caminho mais curto
 * 
 * @param origem posição inicial onde começa a busca
 */
void Grafo::dijkstra(int origem)
{
    if (origem >= 0 && origem < this->getNumVertices())
    {
        vector<estado> fila;
        vector<int> distanciaMin;

        for (int i = 0; i < this->getNumVertices(); i++)
        {
            if (i == origem)
                distanciaMin.push_back(0);
            else
                distanciaMin.push_back(INT_MAX);
        }

        estado inicio;
        inicio.id = origem;
        inicio.custoDist = 0;
        inicio.idPai = -1;

        fila.push_back(inicio);

        while (!fila.empty())
        {
            if (distanciaMin[fila.back().id] >= fila.back().custoDist)
            {
                Aresta *aux = grafo[fila.back().id]->getProx();

                estado atual;
                atual.custoDist = fila.back().custoDist;
                atual.id = fila.back().id;
                atual.idPai = fila.back().idPai;
                fila.pop_back();

                for (; aux != NULL; aux = aux->getProx())
                {
                    estado e;
                    e.id = aux->getNo()->getId();
                    e.custoDist = atual.custoDist + 1;
                    e.idPai = atual.id;

                    if (atual.idPai != e.id)
                    {
                        if (distanciaMin[e.id] > e.custoDist)
                        {
                            distanciaMin[e.id] = e.custoDist;
                            fila.push_back(e);
                        }
                    }
                }

                sort(fila.begin(), fila.end(), compare2);
            }
            else
                fila.pop_back();
        }

        for (int i = 0; i < distanciaMin.size(); i++)
        {
            cout << "Distancia No " << i << ": " << distanciaMin[i] << endl;
        }
    }

    else
    {
        cout << "O no fornecido nao consta na instancia analisada!" << endl;
    }
}

/**
 * @brief implementa o caminhamento floyd para encontrar o caminho mais curto a partir de uma matriz de adjacencia
 * 
 */
void Grafo::floyd()
{
    if (this->getNumVertices() > 0)
    {
        int **matrizAdj = new int *[this->getNumVertices()];

        // Instanciando a matriz de distâncias.
        for (int i = 0; i < this->getNumVertices(); i++)
            matrizAdj[i] = new int[this->getNumVertices()];

        // Inicialização da matriz.
        for (int i = 0; i < this->getNumVertices(); i++)
        {
            for (int j = 0; j < this->getNumVertices(); j++)
            {
                if (i == j)
                    matrizAdj[i][j] = 0;
                else
                    matrizAdj[i][j] = INT_MAX;
            }
        }

        No *auxNo;
        Aresta *auxAresta;

        for (int i = 0; i < this->getNumVertices(); i++)
        {
            auxNo = grafo[i];
            auxAresta = auxNo->getProx();

            while (auxAresta != NULL)
            {
                matrizAdj[i][auxAresta->getNo()->getId()] = 1;

                auxAresta = auxAresta->getProx();
            }
        }

        for (int i = 0; i < this->getNumVertices(); i++)
        {
            for (int j = 0; j < this->getNumVertices(); j++)
            {
                for (int k = 0; k < this->getNumVertices(); k++)
                {
                    if (matrizAdj[j][i] != INT_MAX && matrizAdj[i][k] != INT_MAX)
                    {
                        if (matrizAdj[j][k] > (matrizAdj[j][i] + matrizAdj[i][k]))
                            matrizAdj[j][k] = matrizAdj[j][i] + matrizAdj[i][k];
                    }
                }
            }
        }

        for (int i = 0; i < this->getNumVertices(); i++)
        {
            for (int j = i; j < this->getNumVertices(); j++)
                cout << "Distancia de " << i << " ate " << j << ": " << matrizAdj[i][j] << endl;
        }

        // Destrutor da matriz
        for (int i = 0; i < this->getNumVertices(); i++)
        {
            delete[] matrizAdj[i];
        }

        delete[] matrizAdj;
    }
    else
        cout << "Nao foi possivel retornar o caminhamento utilizando o algoritmo de Prim, vertices insuficientes." << endl;
}

/**
 * @brief Algoritmo Guloso - Prim - usado para encontrar uma arvore geradora minima (AGM)
 * 
 */
void Grafo::prim()
{
    vector<Aresta *> franja; // Arestas candidatas
    vector<int> inclusos;    // Nos inclusos na AGM
    vector<Aresta *> inclusas;
    vector<int> ordemGerada;
    vector<int> origemArestas;

    int custo = 0;
    int indiceMenorPeso;

    inclusos.push_back(0);
    int j;

    do
    {
        int menorPeso = INT_MAX;
        franja.clear();
        origemArestas.clear();

        for (int i = 0; i < inclusos.size(); i++)
        {
            for (Aresta *aux = grafo[inclusos[i]]->getProx(); aux != NULL; aux = aux->getProx())
            {
                for (j = 0; j < inclusos.size(); j++)
                {
                    if (aux->getNo()->getId() == inclusos[j])
                        break;
                }

                if (j == inclusos.size())
                {
                    franja.push_back(aux);
                    origemArestas.push_back(inclusos[i]);
                }
            }
        }

        indiceMenorPeso = -1;

        for (int i = 0; i < franja.size(); i++)
        {
            if (franja[i]->getPeso() < menorPeso)
            {
                menorPeso = franja[i]->getPeso();
                indiceMenorPeso = i;
            }
        }

        if (indiceMenorPeso != -1)
        {
            inclusos.push_back(franja[indiceMenorPeso]->getNo()->getId());
            ordemGerada.push_back(origemArestas[indiceMenorPeso]);
            inclusas.push_back(franja[indiceMenorPeso]);
        }

    } while (!franja.empty());

    for (int i = 0; i < inclusas.size(); i++)
    {
        cout << ordemGerada[i] << " - " << inclusas[i]->getNo()->getId() << endl;
    }

    cout << endl
         << "Numero de arestas: " << inclusas.size() << endl;
    cout << "Numero de nos: " << inclusos.size() << endl;
}

/**
 * @brief Algoritmo guloso para encontrar uma AGM (arvore gerado minima) num grafo com pesos
 * 
 */
void Grafo::kruskal()
{
    vector<arestasOrdenadas> l; // Lista contendo todas as arestas.
    vector<arestasOrdenadas> f; // Lista contendo arestas da solução.
    vector<int> t;              // Vetor contendo as "V" subárvores com cada uma, um nó isolado.
    Aresta *aux;
    int contador = 0; // Contador que retornará o número de componentes conexas (árvores).
    arestasOrdenadas ao;

    for (int i = 0; i < this->getNumVertices(); i++)
    {
        aux = grafo[i]->getProx();

        t.push_back(i);

        while (aux != NULL)
        {
            ao.id = i;
            ao.a = aux;

            l.push_back(ao);

            aux = aux->getProx();
        }
    }

    sort(l.begin(), l.end(), compare3); // Ordenação do vetor de arestas com base no peso.

    while ((contador < t.size() - 1) && (!l.empty()))
    {
        ao = l.back();
        l.pop_back();

        if (t[ao.id] != t[ao.a->getNo()->getId()])
        {
            f.push_back(ao);
            t[ao.a->getNo()->getId()] = t[ao.id];
            contador++;
        }
    }

    int conexas = t.size() - contador;

    sort(f.begin(), f.end(), compare4);

    cout << f[0].id << " - " << f[0].a->getNo()->getId();

    for (int i = 1; i < f.size(); i++)
    {
        if (f[i - 1].id == f[i].id || f[i - 1].id == f[i].a->getNo()->getId())
            cout << " - " << f[i].a->getNo()->getId();
        else
            cout << endl
                 << f[i].id << " - " << f[i].a->getNo()->getId();
    }

    cout << endl
         << endl
         << "Componentes conexas do grafo: " << conexas << endl;
}

/**
 * @brief Verifica se todos os nós já foram dominados
 * 
 * @param nos nós do grafo que serão verificados
 * @return true 
 * @return false 
 */
bool Grafo::verificaSolucao(bool *nos)
{
    for (int i = 0; i < this->getNumVertices(); i++)
    {
        if (!nos[i])
            return false; // Se qualquer nó se quer, não estiver contido no conjunto de dominados, então ainda não atingimos a solução.
    }

    return true;
}

/**
 * @brief Método responsável por realizar o algoritmo guloso simples no grafo
 * 
 * @return int tamanho do grafo encontrado
 */
int Grafo::guloso()
{
    vector<candidatos> c;
    vector<int> solucao;
    candidatos aux;
    Aresta *auxAresta;
    bool *dominados = new bool[this->getNumVertices()];

    for (int i = 0; i < this->getNumVertices(); i++)
    {
        int cont = 0;
        aux.id = i;
        auxAresta = grafo[i]->getProx();
        dominados[i] = false;

        while (auxAresta != NULL)
        {
            auxAresta = auxAresta->getProx();
            cont++;
        }

        aux.numVizinhos = cont;
        c.push_back(aux);
    }

    while (!verificaSolucao(dominados))
    {
        sort(c.begin(), c.end(), compare5);

        solucao.push_back(c.back().id);
        dominados[c.back().id] = true;

        auxAresta = grafo[c.back().id]->getProx();
        while (auxAresta != NULL)
        {
            dominados[auxAresta->getNo()->getId()] = true;
            auxAresta = auxAresta->getProx();
        }

        c.pop_back();

        for (int i = 0; i < c.size(); i++)
        {
            auxAresta = grafo[c[i].id]->getProx();

            int cont = 0;

            while (auxAresta != NULL)
            {
                if (!dominados[auxAresta->getNo()->getId()])
                    cont++;

                auxAresta = auxAresta->getProx();
            }

            c[i].numVizinhos = cont;
        }
    }

    cout << endl
         << "Conjunto Dominante: ";

    for (int i = 0; i < solucao.size(); i++)
    {
        if (i == solucao.size() - 1)
        {
            cout << solucao[i] << endl;
            break;
        }

        cout << solucao[i] << " - ";
    }

    cout << endl
         << "Qualidade da solucao: " << solucao.size() << endl;

    delete[] dominados;

    return solucao.size();
}

/**
 * @brief Método responsável por realizar o algoritmo guloso randomizado no grafo
 * 
 * @param alfa coeficiente de randomização
 * @param semente coeficiente para gerar novos numeros randomicos a cada execução
 * @return int 
 */
int Grafo::gulosoRandomizado(float alfa, int semente)
{
    int random; // Randomização com base no alfa, para calcular o novo candidato a solução.
    vector<int> *melhorSolucaoObtida = nullptr;
    vector<candidatos> c;
    vector<int> *solucao;
    candidatos aux;
    Aresta *auxAresta;
    bool *dominados = new bool[this->getNumVertices()];

    srand(semente); // Define a sequência de números aleatórios a serem gerados.

    for (int j = 0; j < 30; j++)
    {
        solucao = new vector<int>;

        for (int i = 0; i < this->getNumVertices(); i++)
        {
            int cont = 0;
            aux.id = i;
            auxAresta = grafo[i]->getProx();
            dominados[i] = false;

            while (auxAresta != NULL)
            {
                auxAresta = auxAresta->getProx();
                cont++;
            }

            aux.numVizinhos = cont;
            c.push_back(aux);
        }

        while (!verificaSolucao(dominados))
        {
            sort(c.begin(), c.end(), compare5);

            int cont = 0;
            for (int l = c.size() - 1; l >= 0; l--)
            {
                if (c[l].numVizinhos >= c.back().numVizinhos - c.back().numVizinhos * alfa) // Heurística com randomização em função da qualidade.
                    cont++;
            }

            //randomização alternativa - heurística em função do tamanho do vetor de candidatos.
            //srand(semente) -> altera o valor do método rand()
            //random = rand() % (int)ceil(c.size() * alfa); // Método ceil arredonda para "cima" o float obtido.

            random = rand() % cont;

            solucao->push_back(c[c.size() - random - 1].id);
            dominados[c[c.size() - random - 1].id] = true;

            auxAresta = grafo[c[c.size() - random - 1].id]->getProx();
            while (auxAresta != NULL)
            {
                dominados[auxAresta->getNo()->getId()] = true;
                auxAresta = auxAresta->getProx();
            }

            c.erase(c.end() - random - 1);

            for (int i = 0; i < c.size(); i++)
            {
                auxAresta = grafo[c[i].id]->getProx();

                cont = 0;

                while (auxAresta != NULL)
                {
                    if (!dominados[auxAresta->getNo()->getId()])
                        cont++;

                    auxAresta = auxAresta->getProx();
                }

                c[i].numVizinhos = cont;
            }
        }

        if (melhorSolucaoObtida == nullptr)
            melhorSolucaoObtida = solucao;
        else
        {
            if (melhorSolucaoObtida->size() > solucao->size())
            {
                delete melhorSolucaoObtida;
                melhorSolucaoObtida = solucao;
            }
            else
            {
                delete solucao;
            }
        }
    }

    cout << endl
         << "Conjunto Dominante: ";

    for (int i = 0; i < melhorSolucaoObtida->size(); i++)
    {
        if (i == melhorSolucaoObtida->size() - 1)
        {
            cout << melhorSolucaoObtida->at(i) << endl;
            break;
        }

        cout << melhorSolucaoObtida->at(i) << " - ";
    }

    cout << endl
         << "Qualidade da solucao: " << melhorSolucaoObtida->size() << endl;

    int qualidade = melhorSolucaoObtida->size();

    delete melhorSolucaoObtida;
    delete[] dominados;

    return qualidade;
}