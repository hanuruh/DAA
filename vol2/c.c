#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXVERTS 50000
// numero maximo de vertices (alterar se necessario)


typedef struct arco {
  int no_final;
  int valor;
  struct arco *prox;
} ARCO;

typedef struct no {
  //int label;
  ARCO *adjs;
} NO;

typedef struct graph {
  NO verts[MAXVERTS+1];  // nós implicitamente numerados de 1 a nvs
  int nvs, narcos;
} GRAFO;

//--- protótipos das funções disponíveis----------------------------
//    ATENÇÃO AOS TIPOS DE ARGUMENTOS E DE RESULTADO


GRAFO *new_graph(int nverts);
/* cria um grafo com nverts vertices e sem arcos */
void destroy_graph(GRAFO *g);
/* liberta o espaço reservado na criação do grafo */
void insert_new_arc(int i, int j, int valor_ij, GRAFO *g);
/* insere arco (i,j) no grafo, bem como o seu peso; não evita repetições */
void remove_arc(ARCO *arco, int i, GRAFO *g);
/* retira adjacente arco da lista de adjacentes de i */
ARCO *find_arc(int i, int j, GRAFO *g);
/* retorna um apontador para o arco (i,j) ou NULL se não existir */

//--- macros de acesso aos campos da estrutura --------------------------

#define NUM_VERTICES(g) ( (g) -> nvs )
// numero de vertices
#define NUM_ARCOS(g) ( (g) -> narcos )
// numero de arcos
#define ADJS_NO(i,g) ( (g) -> verts[i].adjs )
// primeiro arco da lista de adjacentes do nó i
#define PROX_ADJ(arco) ((arco) -> prox)
// proximo adjacente 
#define ADJ_VALIDO(arco) (((arco) != NULL))
// se arco é válido
#define EXTREMO_FINAL(arco) ((arco) -> no_final)
// qual o extremo final de arco
#define VALOR_ARCO(arco) ((arco) -> valor)
// qual o valor do arco

//======  protótipos de funções auxiliares (privadas) ======
static ARCO* cria_arco(int, int valor_ij);
static void free_arcs(ARCO *);


//======  Implementação (definição das funções) ========================

// para criar um grafo com nverts vertices e sem ramos
GRAFO *new_graph(int nverts)
{
  if (nverts > MAXVERTS) {
    fprintf(stderr,"Erro: %d > MAXVERTS\n",nverts);
    exit(EXIT_FAILURE);
  }
  GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
  if (g == NULL) { 
    fprintf(stderr,"Erro: falta memoria\n");
    exit(EXIT_FAILURE);
  }

  NUM_VERTICES(g) = nverts;  
  NUM_ARCOS(g) = 0;
  while (nverts) {
    ADJS_NO(nverts,g) = NULL;
    nverts--;
  }
  return g;
}


// para destruir um grafo criado
void destroy_graph(GRAFO *g)
{ int i;
  if (g != NULL) {
    for (i=1; i<= NUM_VERTICES(g); i++) 
      free_arcs(ADJS_NO(i,g));
    free(g);
  }
}

// para inserir um novo arco num grafo
void insert_new_arc(int i, int j, int valor_ij, GRAFO *g)
{ /* insere arco (i,j) no grafo g, bem como o seu label  */

  ARCO *arco = cria_arco(j,valor_ij);
  PROX_ADJ(arco) = ADJS_NO(i,g);
  ADJS_NO(i,g) = arco;  // novo adjacente fica à cabeça da lista
  NUM_ARCOS(g)++;
}

// para remover um arco de um grafo (se existir na lista de adjs[i])
void remove_arc(ARCO *arco, int i, GRAFO *g)
{ 
  if (arco != NULL) {
    ARCO *aux = ADJS_NO(i,g), *prev = NULL;
    while (aux != arco && ADJ_VALIDO(aux)) {
      prev = aux;
      aux = PROX_ADJ(aux);
    }
    if (aux == arco) {
      if (prev == NULL) {
	ADJS_NO(i,g)  = PROX_ADJ(arco);
      } else PROX_ADJ(prev) = PROX_ADJ(arco);
      free(arco);
      NUM_ARCOS(g)--;
    }
  }
}

// retorna um apontador para o arco (i,j) ou NULL se não existir 
ARCO *find_arc(int i, int j, GRAFO *g){
  ARCO *adj = ADJS_NO(i,g);

  while(adj != NULL && EXTREMO_FINAL(adj) != j)
    adj = PROX_ADJ(adj);

  return adj;
}
    

// ----  as duas funcoes abaixo sao auxiliares nao publicas ----

// reservar memoria para um novo arco e inicializa-lo
static ARCO *cria_arco(int j, int valor)
{ // cria um novo adjacente
  ARCO *arco = (ARCO *) malloc(sizeof(ARCO));
  if (arco == NULL) {
    fprintf(stderr,"ERROR: cannot create arc\n");
    exit(EXIT_FAILURE);
  }
  EXTREMO_FINAL(arco) = j;
  VALOR_ARCO(arco) = valor;
  PROX_ADJ(arco) = NULL;
  return arco;
}

// libertar uma lista de arcos 
static void free_arcs(ARCO *arco)
{ // liberta lista de adjacentes 
  if (arco == NULL) return;
  free_arcs(PROX_ADJ(arco));
  free(arco);
}


int main(int argc, char **argv)
{
	int nElementos,orig,dest;
	scanf("%d %d %d", &nElementos,&orig,&dest);
	
	int nNos,nRamos;
	scanf("%d %d", &nNos,&nRamos);
	
	GRAFO *g = new_graph(nNos);
	
	int no1,no2,problema;
	while(nRamos>0){
		scanf("%d %d %d", &no1,&no2,&problema);
		insert_new_arc(no1,no2,problema,g);
		nRamos--;
	}
	
	int nRotas,nNosR,noR1,noR2, lugaresR,foundOrig,foundDest,problemas=0,flag=1,result=0,i,finalProblemas=INT_MAX; //foundDest, 0-> n encontrado, 1-> encontrado -1->rota sem pessoas || destino atras da origem
	ARCO *arc;
	scanf("%d", &nRotas);
	
	for(i=1;i<=nRotas;i++){
		scanf("%d %d", &nNosR, &noR1);
		foundOrig=0;
		foundDest=0;
		problemas=0;

		while(nNosR>1){
			scanf("%d %d", &lugaresR,&noR2);
			arc=find_arc(noR1,noR2,g);
			
			if(arc!=NULL){
			if(foundOrig==0 || foundDest==0){
				if(noR1==orig && lugaresR>=nElementos){//destino encontrado
					foundOrig=1;
				}
						
				if(foundOrig==1 && lugaresR<nElementos)//se não houver lugar pelo caminho
					foundDest=-1;
				
				if(noR2==dest && foundOrig==0)//destino atrás da origem
					foundDest=-1;
				
				else if(noR2==dest && foundDest!=-1)//destino encontrado sem problemas
					foundDest=1;
				
				problemas+=VALOR_ARCO(arc);
			}
			}
			
			noR1=noR2;
			nNosR--;
		}
		if(foundOrig==1 && foundDest==1){
			if(problemas==0 && flag==1){//caminho sem problemas, flag para o manter
				result=i;
				flag=0;
				finalProblemas=0;
			}
			else if(problemas!=0 && flag !=0 && problemas<finalProblemas){//caminho com problemas, flag mantém-se pois queremos continuar a procurar um sem problemas
				result=i;
				finalProblemas=problemas;
			}
		}	

	}
	if(result==0)
		printf("Impossivel\n");
	else
		printf("Reserva na rota %d: %d\n",result,finalProblemas);
	return 0;
}

