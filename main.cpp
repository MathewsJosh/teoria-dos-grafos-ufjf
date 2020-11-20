/** 
 * @file  main.cpp
 * @brief Arquivo principal do projeto
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
#include <time.h>

#include "grafo.h"

using namespace std;

/*******************************************************************
*   IMPLEMENTACAO
*******************************************************************/

/** 
 * @brief Função responsável pela execução das opções selecionada pelo usuário.
 * Cada opção exibirá os resultados de acordo com grafo da instancia que está sendo analisada (passada como parâmetro)
 * 
 * @param op opcao selecionada pelo usuario
 * @param g é o ponteiro para o grafo gerado
 * @param f é o vetor que retorna a frequencia relativa
 */
void menu(int op, Grafo *g, vector<freq> f)
{
    switch (op)
    {
    case 0:
        cout << endl
             << "Numero de vertices do grafo: " << g->getNumVertices() << endl;
        break;

    case 1:
        cout << endl
             << "Numero de arestas do grafo: " << g->numArestas() << endl;
        break;

    case 2:
        cout << endl
             << "Grau medio do grafo: " << g->grauMedioGrafo() << endl;
        break;

    case 3:
        cout << endl
             << "Frequencia relativa: " << endl;

        for (int i = 0; i < f.size(); i++)
            cout << "F(" << f.at(i).grau << ") = " << f.at(i).frequencia << endl;

        break;

    case 4:

        cout << endl
             << "Insira em seguida o vertice desejado para se iniciar a busca em largura (o no deve estar contido na instancia): ";
        int l;
        cin >> l;
        g->buscaLargura(l);
        cout << endl;
        break;

    case 5:

        cout << endl
             << "Insira em seguida o vertice desejado para se iniciar a busca em profundidade (o no deve estar contido na instancia): ";
        int p;
        cin >> p;
        g->buscaProfundidade(p);
        cout << endl;
        break;

    case 6:

        cout << endl
             << "Insira em seguida o vertice desejado para se iniciar a distancia minima utilizando Dijkstra (o no deve estar contido na instancia): ";
        int d;
        cin >> d;
        g->dijkstra(d);
        break;

    case 7:

        g->floyd();
        break;

    case 8:

        g->prim();
        break;

    case 9:

        g->kruskal();
        break;

    case 10:
        int piorSolucao;
        int melhorSolucao;
        int qualidadeGuloso;
        float rdi = 0;

        float alfas[5] = {0.1, 0.2, 0.3, 0.5, 0.7};
        int qualidade[6] = {0, 0, 0, 0, 0, 0};
        float tempo[6] = {0, 0, 0, 0, 0, 0};

        clock_t tempoInicial = clock();
        qualidadeGuloso = g->guloso();
        float tempoGuloso = 1000 * (clock() - tempoInicial) / CLOCKS_PER_SEC; // Tempo em milissegundos

        qualidade[0] = qualidadeGuloso;
        tempo[0] = tempoGuloso;

        piorSolucao = qualidade[0];
        melhorSolucao = qualidade[0];

        float mediaTempoRandomizado = 0;
        float mediaQualidade = 0;

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 10; i++)
            {
                tempoInicial = clock();
                mediaQualidade += g->gulosoRandomizado(alfas[j], i);
                mediaTempoRandomizado += (clock() - tempoInicial) / CLOCKS_PER_SEC;
            }

            mediaQualidade /= 10;        // Media da melhor solução (Randomizado).
            mediaTempoRandomizado /= 10; // Media do tempo de execução de cada guloso.

            qualidade[j + 1] = mediaQualidade;
            tempo[j + 1] = mediaTempoRandomizado;
        }

        for (int k = 0; k < 6; k++)
        {
            if (piorSolucao < qualidade[k])
                piorSolucao = qualidade[k];

            if (melhorSolucao > qualidade[k])
                melhorSolucao = qualidade[k];
        }

        for (int l = 0, m = 0; l < 6; l++)
        {
            rdi = (float)(qualidade[l] - melhorSolucao) / (piorSolucao - melhorSolucao);

            if (l == 0)
            {
                cout << endl
                     << "---------------------------------------------------------" << endl
                     << "Guloso" << endl
                     << "RDI: " << rdi << endl
                     << "Qualidade da solucao: " << qualidade[l] << endl
                     << "Tempo medio: " << tempo[l] << " milissegundos" << endl;
            }
            else
            {
                cout << endl
                     << "---------------------------------------------------------" << endl
                     << "Guloso Randomizado - Alfa " << alfas[m] << endl
                     << "RDI: " << rdi << endl
                     << "Qualidade da solucao: " << qualidade[l] << endl
                     << "Tempo medio: " << tempo[l] << " segundos" << endl;

                m++;
            }

            cout << endl
                 << "---------------------------------------------------------" << endl
                 << "Melhor media: " << melhorSolucao << endl;
        }

        break;
    }
}
/** 
 * @brief Função Principal do programa que recebe como argumentos argc e argv. 
 * A partir daqui iremos controlar todas as outras classes criadas no projeto;
 * Observação: Para que o programa execute, precisamos usar a seguinte linha de codigo no terminal:
 * g++ -c *.cpp;g++ -o main -O3 *.o;./main <arquivoEntrada> <arquivoSaida>
 * 
 * @param argc tamanho do vetor de argv
 * @param argv vetor que armazena argumentos de entrada (ex: main, "saida.txt", etc) 
 * @return int 
 */
int main(int argc, char *argv[])
{

    ifstream entrada;
    ofstream saida;

    //argc recebe 3 parâmetros
    if (argc == 3)
    {

        entrada.open(argv[1], ios::in);
        saida.open(argv[2], ios::out | ios::trunc);

        // Gera um grafo a partir de um arquivo texto lido.
        Grafo *g = new Grafo(argv[1]);

        saida << g->getNumVertices() << endl;
        saida << g->numArestas() << endl;
        saida << g->grauMedioGrafo() << endl;

        vector<freq> freq = g->frequenciaRelativa();

        for (int i = 0; i < freq.size(); i++)
            saida << "F(" << freq.at(i).grau << ") = " << freq.at(i).frequencia << endl;

        saida.close();

        //g->printGrafo();

        //Menu
        cout << endl
             << "Bem vindo ao MENU!" << endl
             << "Por favor, selecione dentre as opcoes abaixo, a execucao desejada:" << endl
             << "0) Numero de vertices da instancia." << endl
             << "1) Numero de arestas da instancia." << endl
             << "2) Grau medio do grafo." << endl
             << "3) Frequencia relativa de cada grau do grafo." << endl
             << "4) Busca em largura do grafo." << endl
             << "5) Busca em profundidade do grafo." << endl
             << "6) Algoritmo de Dijkstra para distancia minima." << endl
             << "7) Algoritmo de Floyd para distancia minima." << endl
             << "8) Algoritmo de prim representando uma arvore geradora da instancia." << endl
             << "9) Algoritmo de kruskal retornando a AGM referente ao grafo fornecido." << endl
             << "10) Executa o algoritmo guloso e guloso randomizado para o conjunto dominante minimo." << endl
             << "11) Encerra a operacao." << endl
             << endl;

        int opcao;

        cin >> opcao;

        while (opcao >= 0 || opcao < 12)
        {
            if (opcao == 11)
                break;

            cout << endl
                 << "-------------------------------------------------------------------------------------------------" << endl;

            menu(opcao, g, freq);

            cout << endl
                 << "11) Para encerrar a operacao." << endl
                 << endl;

            if (opcao < 0 || opcao > 11)
                cout << "Valor invalido, por favor inserir um numero de 0 a 11, onde 11 encerra a aplicacao." << endl;

            cin >> opcao;
        }

        delete g; // Deleta a alocação em memória do grafo.
        return 0;
    }
    else
    {
        cout << "Argumentos de execucao invalidos!" << endl;
        return 0;
    }
}