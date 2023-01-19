/* GCC218 - Algoritmo em Grafos
 * Exercicio Avaliativo 1 - Sistema elétrico semi-automático
 * Professor: Mayron Moreira
 * Desenvolvido pelos alunos:
 *      202120910 - Enzo Velo
 *      202121025 - Francisco Afonso de Oliveira Neto
 *      201920248 - Gabriel Raimundo Pereira Barroso
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

bool ehPai (int u, vector<int> *listaAdj, vector<int> *pais, int n) {
    if (!pais[u].size()) {
        /* Se o vértice não tem pai, logo ele é pai */
        return true;
    } else {
        /* Estruturas auxiliares */
        vector<int> percorri;
        queue<int> fila;
        int aux = u;

        /* 
         * Percorri     = -1
         * Nao percorri =  0
         */
        for (int i=0; i<=n; i++) {
            percorri.push_back(0);
        }

        fila.push(aux);

        /* Vou procurar nos pais até que eu ache:
         * Um vértice que não tem pai (Retornará falso para o vertice atual ser pai)
         * Formar um ciclo:
         *      Nesse caso, todos os vértices possui um pai, caso forme apenas um ciclo, sem mais vértices, retorna Verdadeiro
         *      Caso um determinado vértice possui pai, a busca por acestral continuará até que se ache um vértice sem pai
         */
        while (!fila.empty()) {
            aux = fila.front();
            fila.pop();

            if (!pais[aux].size()) {
                return false;
            } else if (percorri[aux] == -1) {
                if (!fila.size()) {
                    return true;
                }
            } else {
                percorri[aux] = -1;
            }

            /* Adicionando os pais de aux na fila */
            for (int f : pais[aux]) {
                if (percorri[f] == 0) {
                    fila.push(f);
                }
            }
        }
    }
    return false;
}

void DFS(int u, vector<int>* listaAdj,vector<int> *pais, bool *aceso) {
    /* Como eu estou em um vértice pai, vou apagando todas as luzes a partir dele 
     * Atravéz da recursão da Busca em Profundidade
     */
    for (int i : listaAdj[u]) {
        if (aceso[i]) {
            aceso[u] = false;
            DFS(i, listaAdj, pais, aceso);
        } else {
            for (int f : listaAdj[i]) {
                if (aceso[f]) {
                    aceso[f] = false;
                    DFS (f,listaAdj,pais,aceso);
                }
            }
        } 
    }
}

int main(int agrc, char **argv) {
    int numCasos = 0, lampadas = 0, ligacoes = 0;
    int x = 0, y = 0, quant = 0;
    cin >> numCasos;
    vector<int> saidas;

    /* Quantidade de grafos */
    for (int i = 0; i < numCasos; i++) {
        cin >> lampadas >> ligacoes;

        /* Alocando estruturas */
        vector<int> *listaAdj = new vector<int>[lampadas + 1];
        vector<int> *pais = new vector<int>[lampadas + 1];
        bool *aceso = new bool[lampadas+1];
        quant = 0;
        /*
         * true = acesa
         * false = apagada
         */
        for (int j=0; j<=lampadas; j++) {
            aceso[j] = true;
        }

        /* Leitura do grafo */
        for (int f = 0; f < ligacoes; f++) {
            cin >> x >> y;
            
            /* Evitando vértices repetidos */
            if(find(listaAdj[x].begin(), listaAdj[x].end(), y) != listaAdj[x].end()) {
                continue;
            }

            listaAdj[x].push_back(y);
            pais[y].push_back(x);
        }

        /* Começo a apagar as lampadas */
        for (int z = 1; z<=lampadas; z++ ) { 
            if (aceso[z]) {
                /* Certificando que eu estou partindo de um vértice pai */
                if (ehPai (z,listaAdj,pais,lampadas)) {
                    DFS (z,listaAdj,pais,aceso);
                    quant++;
                }
                aceso[z] = false;
            }  
        }
        /* Para deixar a saida bem formatada e nao ficar número perdido no meio do codigo, coloquei em um vetor */
        saidas.push_back(quant);
        delete[]pais;
        delete[]listaAdj;
        delete[]aceso;
    }
    /* Imprimindo os resultados */
    for (int b : saidas) {
        printf("%d\n",b);
    }
    return 0;
}
