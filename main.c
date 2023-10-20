#include<stdio.h>
#include<stdlib.h>
unsigned long long layerFinder(size_t layers){//Assign a function which finds the maximum atomic number based on the number of layers
	unsigned long long answer=0;//Initialize the answer
	for(unsigned long long i=1;layers--;i++)//Find the maximum atomic number
		answer+=(i/2+1)*(i/2+1)*2;
	return answer;//Return the result
}
unsigned long long layerSum(unsigned long long* layer,unsigned long long size){//Assign a function which counts the number of electrons on a layer based on its sub-layers
	unsigned long long answer=0;//Initialize the answer
	while(size--)//Sum up the number of electrons on a layer
		answer+=layer[size];
	return answer;//Return the result
}
int main(){
	unsigned long long n,**arrangement;//Initialize variables
	size_t layers;//Initialize the number of layers
	while(1){//Run the code forever
		while(1){//Ask for the value of the atomic number and keep asking until getting a non-zero number
			printf("Atomic number: "),scanf("%u",&n);//Ask for the value of the atomic number
			if(n)//Break if the number is non-zero
				break;
			printf("\nThere is no atom with an atomic number of 0!\n");//Alert if the given number is zero
		}
		if(n>2){//Find the electorn arrangement if the atomic number is >2 (because there is a bug with finding the arrangement for electrons <1)
			layers=1;//Assign an initial number for the layers
			while(layerFinder(layers)<n)//Find the number of layers
				layers++;
			arrangement=(unsigned long long**)calloc(layers,sizeof(unsigned long long*));//Initialize the layers to the arrangement array
			for(size_t i=layers;i--;)//Initialize the sub-layers of each layer
				arrangement[i]=(unsigned long long*)calloc(i+1,sizeof(unsigned long long));
			arrangement[0][0]=2,n-=2;//Put 2 electrons on the nearest sub-layer to the core
			if(n>2)//Put 2 more electrons on the next sub-layer if the remaining electrons are more than 1
				arrangement[1][0]=2,n-=2;
			else//Put the rest of the electrons on the next sub-layer if the remaining electrons are less than 2
				arrangement[1][0]=n,n=0;
			for(unsigned long long i=3,j=0;n;i++,j=0){//Put the electrons on each sub-layer in the aufbau chemical order
				while(i-j>j+2)//Make the least n in the n+l possible by increasing the l
					j++;
				j++;//Make the l one time bigger to run it in the loop
				while(n&&j--){//Put the electrons
					if(n>j*4+2)//Put l*4+2 more electrons to the current sub-layer if the remaining electrons are more than that
						arrangement[i-j-1][j]=j*4+2,n-=j*4+2;
					else//Put the rest of the electrons in the current sub-layer if not
						arrangement[i-j-1][j]=n,n=0;
				}
			}
			for(size_t i=0;i++<layers;){//Show the layers and free the arrangement array
				printf("%u: %u",i,layerSum(arrangement[i-1],i));//Show the number of and the number of electrons in the current layer
				if(layerSum(arrangement[i-1],i)==i*i*2)//Indicate if the layer is full
					printf(" Full");
				printf("\n");//Go to the next line
				for(size_t j=0;j<i;j++){//Show the sub-layers
					printf("\t%u: %u",j,arrangement[i-1][j]);//Show the number of and the number of electrons in the current sub-layer
					if(arrangement[i-1][j]==j*4+2)//Indicate if the sub-layer is full
						printf(" Full");
					printf("\n");//Go to the next line
				}
				free(arrangement[i-1]);//Free the current layer
			}
			free(arrangement);//Free the whole array
			printf("\n");//Go to the next line
		}else//Show the electron arrangement if the atomic number is <3
			printf("1: %u%s\n\t0: %u%s\n\n",n>1?2:1,n>1?" Full":"",n>1?2:1,n>1?" Full":"");
	}
	return 0;
}
