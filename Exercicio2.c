#include <stdio.h>
#include <stdlib.h>

void entradaTemp(int *v, int size)
{
  printf("Temperaturas medidas (em graus Celsius):\n\n");
  
  int *ponte = v;
  int verificador = -101;
  int i;

  for (i = 0; i < size; i++) {
    do { 
        printf("Dia %d: ", i+1);
        scanf("%d", &verificador);
    printf("\n");
     
    if (verificador < -100 || verificador > 100) {
      printf("Temperatura deve ser maior ou igual a -100 graus e menor ou igual a 100 graus\n\n");
      }
    } while (verificador < -100 || verificador > 100);
    
    *(ponte) = verificador;

    ponte++;
  }
}

int encontrarTemp(int *vetor, int size)
{
  int maiorTemp = vetor[0];
  int i;

  for (i = 1; i<size; i++) {
    if (maiorTemp < vetor[i]) {
      maiorTemp = vetor[i];
    }
  }
  return maiorTemp;
}

int nDias(int *vetor, int size, int maiorTemp){
  int quantidade = 0;
  int i;

  for (i = 0; i < size; i++) {
    if(vetor[i] == maiorTemp) {
      quantidade++;
    }
  }
  return quantidade;
}

void diaMaisQuente(int *vetor, int size, int maiorTemp, int *maiorDias){
  int contador = 0;
  int i;

  for (i = 0; i<size; i++) {
    if (vetor[i] == maiorTemp) {
      maiorDias[contador] = i+1;
      contador++;
    } 
  }
}

void imprimir(int *vetor, int size) {
  int i;

  for (i = 0; i < size; i++) {
    printf(" %d", vetor[i]);
  }
}

float calcMedia(int *vetor, int size){
  float media;
  float soma = 0;
  int i;
    
  for (i = 0; i < size; i++) {
    soma = soma + vetor[i];
  }
  media = soma / size;
  
  return media;
}

int main(int argc, char *argv[])
{

  int ano = 0;
  int mes = 0;
  int numDias;



  printf("Entre com o ano da medicao das temperaturas: ");
    scanf("%d", &ano);
  printf("\n");


  if (ano <= 2000 || ano>2023){
    printf("Ano deve ser maior ou igual a 2000 e menor ou igual a 2024\n\n");
    printf("Entre com o ano da medicao das temperaturas: ");
      scanf("%d", &ano);
    printf("\n");
    }


  printf("Entre com o mes da medicao das temperaturas: ");
    scanf("%d", &mes);
printf("\n");
    

  if (mes <= 0 || mes > 12){
    printf("Mes deve ser maior do que zero e menor ou igual a 12\n\n");
      printf("Entre com o mes da medicao das temperaturas: ");
    scanf("%d", &mes);
    printf("\n");
    }

   
  if(mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)
  {
      numDias = 31;
  }
  
  if(mes==4 || mes==6 || mes==9 || mes==11)
  {
      numDias = 30;
  }
  
  if(mes==2)
  {
      if((ano % 4 == 0 && ano % 100 != 0)|| (ano % 400 == 0))
      {
          numDias = 29;
      }
      
      else
      {
        numDias  = 28;
      }
  
  }
  
  

  int *temperaturas = malloc(numDias * sizeof(int));

  entradaTemp(temperaturas, numDias);
  int maiorTemperatura = encontrarTemp(temperaturas, numDias);

  int numMaiorDias = nDias(temperaturas, numDias, maiorTemperatura);

  int *maioresDias = malloc(numMaiorDias * sizeof(int));
  
  diaMaisQuente(temperaturas, numDias, maiorTemperatura, maioresDias);
 
  
  printf("A maior temperatura maxima do mes foi de %d e aconteceu nos dias: ", maiorTemperatura);
  imprimir(maioresDias,numMaiorDias);
  printf("\n\n");

  printf("A temperatura maxima media no mes foi de: %.1f graus Celsius", calcMedia(temperaturas, numDias));

  
  free(temperaturas);
  free(maioresDias);

  return 0;
}