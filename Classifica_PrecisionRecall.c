//Compara um dercritor com os demais a partir da Distancia Euclidiana classificando uma lista da menor para a maior distancia
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define num 216
#define tamstr 50
#define tamDesc 13

typedef struct
{
    float kmedio[tamDesc];
    float kmax[tamDesc];
}Descritor;

Descritor formaBuscada;
Descritor formas[num-1];

FILE *descBuscado, *descBase;

void MostraVet()
{
    int i;
    for(i=0;i<tamDesc;i++)
    {
        printf("Medio: %.4f Max: %.4f\n",formaBuscada.kmedio[i],formaBuscada.kmax[i]);
    }
}


void ArqToVetor(FILE *Arquivo, Descritor *vet)
{
  int i = 0;
  float medio = -1, maximo = -1;
  while (fscanf(Arquivo,"%f %f",&medio, &maximo) != EOF)
  {
      (*vet).kmedio[i] = medio;
      (*vet).kmax[i] = maximo;
      i++;
  }

}

int EscolheBuscado()
{
    char Nomebuscado[tamstr];
    printf("Nome do Descritor Buscado: ");
    scanf("%s",&Nomebuscado);
    descBuscado = fopen(Nomebuscado,"r");
    if(descBuscado == NULL)
    {
      printf("Erro na abertura do Arquivo\n");
      return -1;
    }
    ArqToVetor(descBuscado,&formaBuscada);
    fclose(descBuscado);
    return 1;
}


int main()
{
    if(EscolheBuscado() != -1)
      MostraVet();
    getchar();
    return 0;
}
