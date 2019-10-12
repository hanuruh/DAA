#include <stdio.h>

void printArr(int arr[],int size){
	int i;
	for(i=0; i<size;i++){
		printf("%d\n", arr[i]);
	}
	//printf("\n");
}

int main(int argc, char **argv)
{
	int caminho[10000],i=0,local;
	scanf("%d",&local);
	
	while(local!=0){
		caminho[i]=local;
		scanf("%d",&local);
		i++;
	}
	//printArr(caminho,i);
	
	int caminhoIdeal[100],j,z,count=0;
	
	for(j=0;j<i;j++){
		caminhoIdeal[count]=caminho[j];
		for(z=j;z<i;z++){
			if(caminho[z]==caminhoIdeal[count])
				j=z;
		}
		count++;
	}
	
	printArr(caminhoIdeal,count);
	
	return 0;
}
