#include <stdio.h>
#include <stdlib.h>
#include "grafos0.h"
#include "queue.h"
#define MAXQ 50000
#define MAXR 30000
#define UNDEF 0
// define pai inexistente

void maior_vetor(int v[], int size, int propriovalor){
int i=0, max=propriovalor;
    while(size>0){
    if(v[i]>max)
        max=v[i];
    i++;
    size--;
    }
    printf("%d", max);
}

int le_caminho(int v,int pai[]) {
  if (pai[v]!= UNDEF) {
    le_caminho(pai[v],pai);
  }
  return v;
}

void BFS_visit(int s,GRAFO *g, int pai[]) {
   int v, w, n = NUM_VERTICES(g);
   QUEUE *q;
   ARCO *adjs;
   BOOL visitado[n+1];

   for(v=1; v <= n; v++) {  // assume nós numerados de 1 a n
      visitado[v] = FALSE;   pai[v] = UNDEF;   // sem pai
   }

   visitado[s] = TRUE;
   q = mk_empty_queue(n);
   enqueue(s,q);

   do {
      v = dequeue(q);
      adjs = ADJS_NO(v,g);
      while (adjs != NULL) {
         w = EXTREMO_FINAL(adjs);
         if (visitado[w] == FALSE) {
            enqueue(w,q);
            visitado[w] = TRUE;
            pai[w] = v;
         }
         adjs = PROX_ADJ(adjs);
      }
   } while (queue_is_empty(q) == FALSE);
   free_queue(q);
}

void ver_max(int vec[],int q, GRAFO *g){
    int i=0, n, *pai, v, aux[MAXR],z ;
    n = NUM_VERTICES(g);
    pai = (int *) malloc(sizeof(int)*(n+1));

    while(i<q){
        printf("No %d: ", vec[i]);
        BFS_visit(vec[i],g,pai);
        z=0;
        for(v=1; v<= n; v++)
            if (pai[v] != UNDEF) {
                aux[z] = le_caminho(v,pai);
                z++;
            }
        maior_vetor(aux, z, vec[i]);
        putchar('\n');
        i++;
    }

}

void ver_questoes(GRAFO *g){
    int q, v[MAXQ], i=0,qaux;
    scanf("%d", &q);
    qaux=q;

    while(qaux>0){
        scanf("%d", &v[i]);
        i++;
        qaux--;
    }
    ver_max(v,q,g);
}

GRAFO *ler_construir_grafo(){
  int nvs, nramos, u, v;
  GRAFO *g;

  scanf("%d%d",&nvs,&nramos);

  g = new_graph(nvs);

  while(nramos > 0) {
    scanf("%d%d",&u,&v);
    insert_new_arc(u,v,g);
    insert_new_arc(v,u,g); //bidirecional
    nramos--;
  }

  return g;
}
int main()
{
    GRAFO *g = ler_construir_grafo();
    ver_questoes(g);
    return 0;
}
