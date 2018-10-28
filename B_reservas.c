#include <stdio.h>
#include <stdlib.h>
#include "grafos2.h"


void analise(GRAFO *g, int nligacoes, int nnos){
    //x: primeiro valor
    //y:segundo valor
    //d: lugares disponíveis
    //p: preco da sequencia
    int x,y,d,p; //scan do primeiro valor, segundo valor, lugares disponiveis, preço
    while(nligacoes>0){
        printf("Ligacao: ");
        scanf("%d %d %d %d",&x, &y, &d, &p);
         if(find_arc(x,y,g)== NULL && x<=nnos && y<=nnos)
            insert_new_arc(x,y,d,p,g);//criar grafo com as direções
        nligacoes--;
    }
    //k:nº de lugares necessários
    //nosreserva: nº de nós do percurso
    //VALOR1_ARCO: lugares disponiveis
    //VALOR2_ARCO: preço dessa ligação
    ARCO *a;
    int nreservas, k, nosreserva, preco, count1, count2, v[1000], i;
    scanf("%d", &nreservas);
    while(nreservas>0){
        preco=0;
        i=0;
        scanf("%d %d %d", &k, &nosreserva, &x);
        v[i]= x; i++;
        while(nosreserva>1){
            scanf("%d",&y);
            v[i]=y;
            if((a = find_arc(x,y,g))== NULL){
                    printf("(%d,%d) inexistente\n", x,y);
                    break;
            }
            else if(k>VALOR1_ARCO(a)){
                printf("Sem lugares em (%d,%d)\n", x,y);
                break;
            }
            else if(k<=VALOR1_ARCO(a) && (a = find_arc(x,y,g))!= NULL){ //numero de lugares vs lugares disponiveis
                    preco+= k*VALOR2_ARCO(a);
                    count2++;
            }
        x=y;
        nosreserva--;
        i++;
        }
        if(nosreserva==1){
            int z=0;
            while((i-1)>0){ //retirar os lugares que estão agora ocupados
                  a= find_arc(v[z],v[z+1], g);
                  VALOR1_ARCO(a)-=k;
                  z++;
                  i--;
            }
            printf("Total a pagar: %d\n", preco);
        }
        nreservas--;
    }
}

int main()
{
    int nnos, nligacoes;
    scanf("%d %d", &nnos, &nligacoes);
    GRAFO *g = new_graph(nligacoes);
    analise(g,nligacoes, nnos);
    
    return 0;
}
