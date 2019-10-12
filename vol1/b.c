#include <stdio.h>

void printArr(int arr[],int size){
	int i;
	for(i=0; i<=size;i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void inserirMoeda(int moeda, int maquina[]){
	switch (moeda){ 
		case 2:
			maquina[0]++;
			break;
		case 1:
			maquina[1]++;
			break;
		case 50:
			maquina[2]++;
			break;
		case 20:
			maquina[3]++;
			break;
		case 10:
			maquina[4]++;
			break;
		case 5:
			maquina[5]++;
			break;
	}
}

int moedaConvert(int moeda){
		switch (moeda){ 
		case 2:
			return 200;
		case 1:
			return 100;
		default:
			return moeda;
	}
	return 0;
}

int transacao(int euro,int cent, int mMaquina[], float quantiClient){
	int pagamento = euro*100 + cent;
	int troco = quantiClient - pagamento;
	int money[6]={200,100,50,20,10,5};
	//printf("%d %d\n",pagamento,troco);
	
	int i;
	for(i=0;i<=5;i++){
		while(money[i]<=troco && mMaquina[i]!=0){
			//printf("%f\n",money[i]);
			troco-=money[i];
			mMaquina[i]--;
		}
	}
	
	//printf("%d \n",troco);
	return troco;
}

int main(int argc, char **argv)
{
	int mMaquina[6],i;
	
	for(i=0;i<=5;i++){
		scanf("%d", &mMaquina[i]);  
	}
	
	//printArr(mMaquina,5);
	
	int euro,cent,moeda,countT=0,countR=0;;
	int retido=0,quantiClient,resultado;
	
	scanf("%d %d", &euro,&cent);
	
	while(euro != 0 || cent != 0){
		quantiClient = 0;
		scanf("%d", &moeda);
		quantiClient+=moedaConvert(moeda);
		while(moeda != 0){
			inserirMoeda(moeda,mMaquina);
			scanf("%d", &moeda);
			quantiClient+=moedaConvert(moeda);
		}
		
		resultado=transacao(euro,cent,mMaquina,quantiClient);
		if(resultado>0){
			//rintf("%d\n",resultado);
			retido+=resultado;
			countR++;
		}
		countT++;
		scanf("%d %d", &euro,&cent);
		
	}
	int novoE=retido/100;
	int novoC=(retido%100);
	printf("%d %d\n%d/%d\n",novoE,novoC,countR,countT);
	
	return 0;
}
