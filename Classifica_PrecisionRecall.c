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
    int numdescritor;
}Descritor;

typedef struct
{
    int indice;
    float distancia;
}DistEucli;

Descritor formaBuscada;
Descritor formasBase[num-1];
DistEucli DistVet[num-1];
char Nomebuscado[tamstr];
char Tabela[num+1][num+1];
float bigVetBase[2*tamDesc];
float bigVetBuscado[2*tamDesc];

FILE *descBuscado, *descBase, *resultado;

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

void MontaBigVet(Descritor d, float bigVet[])
{
   int i = 0,j;
   for(j=0;j<tamDesc;j++)
   {
      bigVet[i] = d.kmedio[j];
      bigVet[i+1] = d.kmax[j];
      i = i+2;
   }
}

float DistEuclidiana()
{
  int i;
  float soma=0, dist=0, sub =0;
  for (i = 0; i <tamDesc; i++)
  {
    sub = bigVetBase[i] - bigVetBuscado[i];
    soma += pow(sub,2);
  }
  dist = sqrt(soma);
  printf("%f\n",dist);
  return dist;
}

void quicksort(DistEucli arr[],int low,int high)
{
 int j,i,pivot;
 DistEucli temp;
 if(low < high)
 {
  pivot = low;
  i = low;
  j = high;

  while(i<j)
  {
   while((arr[i].distancia<=arr[pivot].distancia)&&(i<high))
   {
    i++;
   }

   while(arr[j].distancia>arr[pivot].distancia)
   {
    j--;
   }

   if(i<j)
   {
    temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
   }
  }

  temp=arr[pivot];
  arr[pivot]=arr[j];
  arr[j]=temp;
  quicksort(arr,low,j-1);
  quicksort(arr,j+1,high);
 }
}

void DaResultado()
{
    int i;
    char resStr[tamstr];
    strcpy(resStr,"Distancias_");
    strcat(resStr,Nomebuscado);
    resultado = fopen(resStr,"w");
    for(i =0;i<num-1;i++)
    {
        printf("%s %.4f\n",Tabela[DistVet[i].indice],DistVet[i].distancia);
      //  fprintf(resultado, "%d\n",DistVet[i].indice);
    }
    fclose(resultado);
}


void Classifica()
{
  int i;
  float distancia[num-1];
  MontaBigVet(formaBuscada,bigVetBuscado);
  for (i = 0; i < num; i++)
  {
      MontaBigVet(formasBase[i],bigVetBase);
      DistVet[i].distancia = DistEuclidiana();
      DistVet[i].indice = formasBase[i].numdescritor;
  }
  quicksort(DistVet,0,num-1);
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
          formasBase[i].numdescritor = i;
          fclose(descBase);
      }
      else
      {
        formaBuscada.numdescritor = i;
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
      {
        Classifica();
        printf("haha\n" );
        DaResultado();
      }

  }
 printf("ok\n");

  getchar();
  return 0;
}
