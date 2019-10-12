#include <stdio.h>
void printArr(int arr[],int size){
	int i;
	for(i=0; i<size;i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int countCadeirasL(int arr[],int size){
	int i,sum=0;
	for(i=1;i<size;i+=2){
		sum+=arr[i];
	}
	
	return sum;
}

//retirar uma cadeira de um tipo
//se não houver retornar flag 
int retirarCadeira(int opcao, int arr[],int size){
	int i,flag=0;
	for(i=0;i<size;i+=2){
		if(arr[i]==opcao){
			if(arr[i+1]==0)
				flag=1;
			else
				arr[i+1]--;
			break;
		}
	}
	
	return flag;
}

int main(int argc, char **argv)
{
	int n;
	scanf("%d", &n);
	
	int i,tipo,tipoQ,cadeirasArr[200];
	
	for(i=0;i<n*2;i+=2){//fazer array das cadeiras
		scanf("%d",&tipo);
		cadeirasArr[i]=tipo;
		scanf("%d",&tipoQ);
		cadeirasArr[i+1]=tipoQ;
	}
	//printArr(cadeirasArr,n*2);
	
	int habitantes,opcoes,opcaoT,j,habitantePe=0,flag;
	
	scanf("%d",&habitantes);
	for(i=0;i<habitantes;i++){//percorrer cada habitante
		flag=0;
		scanf("%d",&opcoes);
		//percorrer opcoes do habitante, retirando-se uma cadeira de cada opcao
		//habitante fica em pe se das suas opcoes, nenhuma ter já alguma cadeira
		//flag serve para mostrar que ja encontramos cadeira e nao precisamos retirar mais
		for(j=0;j<opcoes;j++){
			scanf("%d",&opcaoT);
			if(flag==0){
				if(retirarCadeira(opcaoT,cadeirasArr,n*2)!=1)
					flag=1;//encontrou cadeira
			}
		}
		if(flag==0)
			habitantePe++;
		//printArr(cadeirasArr,n*2);
	}
	
	printf("%d\n%d\n",habitantePe,countCadeirasL(cadeirasArr,n*2));
	
	return 0;
}
