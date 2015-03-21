#include <stdlib.h>
#include <stdio.h>
#include <cgraph.h>
#include "grafo.h"

//------------------------------------------------------------------------------
// estrutura de dados para representar um grafo simples
//
// o grafo pode ser
// - direcionado ou não
// - com pesos nas arestas ou não
//
// além dos vértices e arestas, o grafo tem um nome
//
// os vértices do grafo também tem nome
//
// os nomes do grafo e dos vértices são strings quaisquer
//
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
//
// o peso default de uma aresta é 0.0

struct grafo {
  int grafo_direcionado;
  char *grafo_nome;
  struct vertice *grafo_vertices;
  struct aresta *grafo_arestas;
};

//------------------------------------------------------------------------------
// estrutura de dados para representar um vértice

struct vertice {
  char *vertice_nome;
  struct vertice *vertice_proximo;
};

//------------------------------------------------------------------------------
// estrutura de dados para representar uma aresta

struct aresta {
  double aresta_peso;
  struct vertice *aresta_origem, *aresta_destino;
  struct aresta *aresta_proximo;
};

//------------------------------------------------------------------------------
// Encontra um vertice a partir do seu nome

struct vertice *encontra_vertice(struct vertice *vertices, const char *nome) {
  struct vertice *v;

  for(v = vertices; v != NULL; v = v->vertice_proximo) {
    if(strcmp(v->vertice_nome, nome) == 0) {
      return v;
    }
  }

  return NULL;
}

//------------------------------------------------------------------------------
// Encontra uma aresta dados seus vertices em uma lista de arestas

struct aresta *encontra_aresta(struct aresta *arestas, int tamanho, struct vertice *cauda, struct vertice *cabeca) {
  struct aresta *a;
  int i;

  for(i = 0, a = arestas; i < tamanho; ++i, a = a->aresta_proximo) {
    if(a->aresta_origem == cauda && a->aresta_destino == cabeca) {
      return a;
    }
  }

  return NULL;
}

//------------------------------------------------------------------------------
// Carrega os vertices de um grafo do tipo Agraph_t para um grafo do tipo
// da estrutura implementada

struct vertice *obter_vertices(Agraph_t *grafo) {
  Agnode_t *v;
  struct vertice *vertices = NULL;
  int n_vertices, i;

  n_vertices = agnnodes(grafo);

  if(n_vertices > 0) {
    vertices = (struct vertice *) malloc(sizeof(struct vertice) * n_vertices);

    if(vertices != NULL) {
      for(i = 0, v = agfstnode(grafo); i < n_vertices; ++i, v = agnxtnode(grafo, v)) {
        vertices[i].vertice_nome = strdup(agnameof(v));
        vertices[i].vertice_proximo = (i + 1 < n_vertices) ? vertices + (i + 1) : (struct vertice *) NULL;
      }
    }
  }

  return vertices;
}

//------------------------------------------------------------------------------
// Carrega as arestas de um grafo do tipo Agraph_t para um grafo do tipo
// da estrutura implementada

struct aresta *obter_arestas(Agraph_t *grafo, struct vertice *lista_vertices) {
  Agedge_t *a;
  Agnode_t *v;
  struct aresta *arestas = NULL;
  struct vertice *cauda, *cabeca;
  char *peso;
  int n_arestas, contador = 0;

  n_arestas = agnedges(grafo);

  if(n_arestas > 0) {
    arestas = (struct aresta *) malloc(sizeof(struct aresta) * n_arestas);

    if(arestas != NULL) {
      for(v = agfstnode(grafo); v != NULL; v = agnxtnode(grafo, v)) {
        for(a = agfstedge(grafo, v); a != NULL && contador < n_arestas; a = agnxtedge(grafo, a, v)) {
          cauda = encontra_vertice(lista_vertices, agnameof(agtail(a)));
          cabeca = encontra_vertice(lista_vertices, agnameof(aghead(a)));

          if(encontra_aresta(arestas, contador, cauda, cabeca) == NULL) {
            peso = agget(a, "peso");

            arestas[contador].aresta_origem = cauda;
            arestas[contador].aresta_destino = cabeca;
            arestas[contador].aresta_peso = (peso != NULL && *peso != '\0') ? atof(peso) : 0.0;
            arestas[contador].aresta_proximo = (contador + 1 < n_arestas) ? arestas + (contador + 1) : (struct aresta *) NULL;

            ++contador;
          }
        }
      }
    }
  }

  return arestas;
}

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input, usando as rotinas de libcgraph
//
// desconsidera todos os atributos do grafo lido
// exceto o atributo "peso" nas arestas onde ocorra
//
// num grafo com pesos nas arestas todas as arestas tem peso, que é um double
//
// o peso default de uma aresta num grafo com pesos é 0.0
//
// devolve o grafo lido ou
//         NULL em caso de erro

grafo le_grafo(FILE *input) {
  Agraph_t *g;
  struct grafo *grafo_lido;

  grafo_lido = (struct grafo *) malloc(sizeof(struct grafo));
  grafo_lido->grafo_nome = (char *) NULL;
  grafo_lido->grafo_vertices = (struct vertice *) NULL;
  grafo_lido->grafo_arestas = (struct aresta *) NULL;

  if(grafo_lido != NULL) {
    if((g = agread(input, NULL)) == NULL) {
      destroi_grafo(grafo_lido);
      return NULL;
    }

    if((grafo_lido->grafo_vertices = obter_vertices(g)) == NULL) {
      free(g);
      destroi_grafo(grafo_lido);
      return NULL;
    }

    if((grafo_lido->grafo_arestas = obter_arestas(g, grafo_lido->grafo_vertices)) == NULL) {
      free(g);
      destroi_grafo(grafo_lido);
      return NULL;
    }

    grafo_lido->grafo_direcionado = agisdirected(g);
    grafo_lido->grafo_nome = strdup(agnameof(g));
  }

  return grafo_lido;
}
//------------------------------------------------------------------------------
// desaloca toda a memória utilizada em g
//
// devolve 1 em caso de sucesso ou
//         0 em caso de erro

int destroi_grafo(grafo g) {

}
//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot, de forma que
//
// 1. todos os vértices são escritos antes de todas as arestas/arcos
// 2. se uma aresta tem peso, este deve ser escrito como um atributo
//
// devolve o grafo escrito ou
//         NULL em caso de erro

grafo escreve_grafo(FILE *output, grafo g) {

}
