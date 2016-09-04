//Compara um dercritor com os demais a partir da Distancia Euclidiana classificando uma lista da menor para a maior distancia
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define num 216
#define tamstr 50
#define tamDesc 13
#define nClasse 18
#define qFormas 12

typedef struct
{
    float kmedio[tamDesc];
    float kmax[tamDesc];
}Descritor;

Descritor formaBuscada;
Descritor formasBase[num-1];
char Nomebuscado[tamstr];

char Tabela[num+1][num+1];

FILE *descBuscado, *descBase;

/*void MostraVet()
{
    int i;
    for(i=0;i<tamDesc;i++)
    {
        printf("Medio: %.4f Max: %.4f\n",formaBuscada.kmedio[i],formaBuscada.kmax[i]);
    }
}*/

/*void MostraBase()
{
    int i,j;
    for(j=0;j<num;j++)
    {
      printf("Desc %d\n",j);
      for(i=0;i<tamDesc;i++)
      {
          printf("Medio: %.4f Max: %.4f\n",formasBase[j].kmedio[i],formasBase[j].kmax[i]);
      }
    }
}*/

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

int FormaVetoresBase()
{
    int i;
    char nomeD[tamstr];
    for(i=0;i<num;i++)
    {
      strcpy(nomeD,Tabela[i+1]);
      strcat(nomeD,".txt");
      if(strcmp(nomeD,Nomebuscado) != 0)
      {
          descBase = fopen(nomeD,"r");
          if(descBase == NULL)
          {
              printf("Erro ao abrir o arquivo %s\n",nomeD);
              return -1;
          }
          ArqToVetor(descBase,&formasBase[i]);
          fclose(descBase);
      }
    }
    return 1;
}

int EscolheBuscado()
{

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


/*void MostraTabela(){
  int i;
  for(i=1;i<=num;i++)
  {
    printf("%s %d\n",Tabela[i],i);
  }
}*/

void MontaTabela()
{
   int i,j,count = 1;
   char base[tamstr];
   char numero[3];

   for(j=1;j<=nClasse;j++)
   {
     for(i=1;i<=qFormas;i++)
     {
        strcpy(base,"Descritor_");
        itoa(j,numero,10);
        strcat(base,numero);
        strcpy(numero,"");
        strcat(base,"-");
        itoa(i,numero,10);
        strcat(base,numero);
        strcpy(Tabela[count],base);
        count++;
     }
   }
}

int main()
{
  MontaTabela();
  if(EscolheBuscado() != -1)
  {
      if(FormaVetoresBase() != -1)
        //printf("ok\n");
        MostraBase();
  }
  getchar();
  return 0;
}
