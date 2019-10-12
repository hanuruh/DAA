#include <stdio.h>

int maxArr(int arr[],int size){
	int max=arr[0],i;
	for(i=1;i<size;i++){
		if(arr[i]>max)
			max=arr[i];
	}
	return max;
}

int getIndex(int val, int arr[],int size){
	int i;
	for(i=1;i<= size; i++){
		if(arr[i]==val)
			return i;
	}
	return 0;
}

void printArrStora(int arr[],int size){
	int i, maxIndex = getIndex(maxArr(arr,size),arr,size);
	printf("%d",size);
	for(i=maxIndex; i>=0;i--){
		printf("% d", arr[i]);
	}
    for(i=(size-1);i>maxIndex;i--)
		printf("% d", arr[i]);
	printf("\n");
}

int getFirst(int arr[], int size){
	int i;
	for(i=1;i<= size; i++){
		if(arr[i]!=0)
			return arr[i];
	}
	return 0;
}

int main(int argc, char **argv)
{
	int nPessoas,id,sequencia[1000], i,sozinho=0;
	
	scanf("%d", &nPessoas);
	
	for(i=1; i<=nPessoas;i++){
		scanf("%d", &id);
		sequencia[i]=id;
		
	}
	
	//printArr(sequencia,nPessoas);
	int counter, allSeen=0;
	
	while(allSeen!=nPessoas){
		int auxArr[1000];
		counter=0;
		i = getFirst(sequencia,nPessoas);
		auxArr[counter]= i; counter++;
		i = getIndex(i,sequencia,nPessoas);
		sequencia[i]=0;
		
		while(i!=auxArr[0]){
			auxArr[counter]=i; counter++;
			i = getIndex(i,sequencia,nPessoas);
			sequencia[i]=0;
		}	
		if(counter>=3) printArrStora(auxArr,counter); else sozinho+=counter;
		allSeen+=counter;
	}
	
	
	printf("%d\n",sozinho);
	
	
	
	
	return 0;
}
