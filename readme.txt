Trabalho de Implementação 1 de Algoritmos e Teoria dos Grafos (CI065)
Rafael Ravedutti Lucio Machado - rafaelm - GRR20135958

--------------------------------------------------------------------------

Informações sobre o trabalho:

No trabalho foram implementadas três estruturas: grafo, vertice e aresta.

O grafo possui uma variável que diz se ele é um grafo direcionado, um nome,
um ponteiro para a base de uma lista ligada de vértices e outro ponteiro
para a base de uma lista ligada de arestas. Os vértices possuem o nome
e um ponteiro para o próximo vértice. E por fim, as arestas possuem o peso,
a origem (ou cauda), o destino (ou cabeça) e o ponteiro para a próxima aresta
da lista.

A principio (por questões de desempenho) todos os vértices e arestas são
alocados no mesmo momento e na mesma região de memória e por isto só é
necessário liberar a memória uma vez (na função destroi_grafo). Futuramente,
caso seja necessário desenvolver uma função para adicionar grafos e arestas,
será necessário desenvolver métodos para tratar disto.

Não fora encontrado nenhum bug durante os testes, portanto não há o
conhecimento prévio de nenhum.
