#include <stdio.h>
#include <stdlib.h>
#include "grafos.c"

void analise_percurso(GRAFO *g, int nadjs[]){
    //x: primeiro valor
    //y:segundo valor
    int n,x,y;
    scanf("%d %d", &n, &x); //scan do nº de nos do trajeto e o primeiro valor
    while(n>1){
        scanf("%d", &y); //scan do segundo valor
        if(find_arc(x,y,g)== NULL){ //se este percurso (x,y) n existir, adicionar ao arco
            insert_new_arc(x,y,n,g);
            nadjs[x]++; //aumentar o nº de nós adjacentes a x
        }
        x=y; //o segundo elemento é agora o primeiro
        n--;
    }
}


int main()
{
    //nvs: nós da redee
    //nps:número de trajetos a analisar
    int nvs, nps, i;
    scanf("%d %d", &nvs, &nps);
    int nadjs[nvs + 1]; //vetor com o numero de nós adjacentes de cada um
    GRAFO *g = new_graph(nvs);
    for(i=1; i<= nvs; i++)
        nadjs[i]=0; //meter tds valores do vetor igual a 0
    while(nps>0){//cada ciclo analisa um percurso, modificando vetor dos nºs adjacentes
        analise_percurso(g,nadjs);
        nps--;
    }
    for(i=1;i<=nvs;i++)
        printf("%d\n", nadjs[i]); //OUTPUT




    return 0;
}

