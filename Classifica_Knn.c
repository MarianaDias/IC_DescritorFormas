/*Calcula a distancia Euclidiana entre um Teste e uma base de treino para Teste k-nn*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define k 5
#define num 162
#define nClasse 18
#define qFormas 12
#define tamstr 50
#define tamDesc 13

typedef struct
{
    float kmedio[tamDesc];
    float kmax[tamDesc];
    char  nomeDesc[tamstr];
}Descritor;

typedef struct
{
    char  nomeDist[tamstr];
    float distancia;
}DistEucli;

int conjuntoTeste;
Descritor formaBuscada;
Descritor formasBase[num-1];
DistEucli DistVet[num+1];
float bigVetBase[26];
float bigVetBuscado[26];
char TabelaBase[num+1][num+1];
char TabelaTeste[55][55];

FILE *descBuscado, *descBase, *resultado;

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

/*Escolhe o arquivo do descritor a ser usando como amostra e salva ele no descritor formaBuscada*/
int EscolheBuscado(int n)
{
    descBuscado = fopen(TabelaTeste[n],"r");
    if(descBuscado == NULL)
    {
      printf("Erro na abertura do Arquivo\n");
      return -1;
    }
    ArqToVetor(descBuscado,&formaBuscada);
    strcpy(formaBuscada.nomeDesc,TabelaTeste[n]);
    fclose(descBuscado);
    return 1;
}


int FormaVetoresBase()
{
    int i = 0,j;
    for(i=0;i<num;i++)
    {
      descBase = fopen(TabelaBase[i+1],"r");
      if(descBase == NULL)
      {
          printf("Erro ao abrir o arquivo %s\n",TabelaBase[i+1]);
          return -1;
      }
      ArqToVetor(descBase,&formasBase[i]);
      strcpy(formasBase[i].nomeDesc,TabelaBase[i+1]);
      fclose(descBase);
    }
    return 1;
}

/*Coloca o descritor em um vetor unico [kmedio,kmax,...kmedio,kmax]*/
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

int Classifica()
{
  int i,j,indice = 0;
  MontaBigVet(formaBuscada,bigVetBuscado);
  for (i = 0; i < num; i++)
  {
    if(strcmp(formasBase[i].nomeDesc,"Buscado") != 0)
    {
      MontaBigVet(formasBase[i],bigVetBase);
      DistVet[indice].distancia = DistEuclidiana();
      strcpy(DistVet[indice].nomeDist,formasBase[i].nomeDesc);
      indice++;
    }
  }
  quicksort(DistVet,0,indice-1);
  return indice;
}

/*Monta uma TabelaBase de correspondencia para decritor e indice*/
void MontaTabelaBase(int classeA, int classeB, int classeC)
{
   int i,j,count = 1;
   char base[tamstr];
   char numero[3];

   for(j=1;j<=qFormas;j++)
   {
      for(i=1;i<=nClasse;i++)
      {
         if(j != classeA && j != classeB && j != classeC)
         {
            strcpy(base,"Descritor_");
            itoa(i,numero,10);
            strcat(base,numero);
            strcpy(numero,"");
            strcat(base,"-");
            itoa(j,numero,10);
            strcat(base,numero);
            strcat(base, ".txt");
            strcpy(TabelaBase[count],base);
            count++;
         }
       }
    }
}

void  MontaTabelaTeste(int classeA)
{
    int i,j, count = 1;
    char base[tamstr];
    char numero[3];

    for (i = 1; i <= nClasse ; i++)
    {
      for (j =classeA ; j < classeA+3; j++)
      {
        strcpy(base,"Descritor_");
        itoa(i,numero,10);
        strcat(base,numero);
        strcpy(numero,"");
        strcat(base,"-");
        itoa(j,numero,10);
        strcat(base,numero);
        strcat(base, ".txt");
        strcpy(TabelaTeste[count],base);
        count++;
      }
    }
}

void DesterminaTesteTreino()
{
   switch (conjuntoTeste)
   {
     case 1: MontaTabelaBase(1,2,3);
             MontaTabelaTeste(1);
             break;
     case 2: MontaTabelaBase(4,5,6);
             MontaTabelaTeste(4);
             break;
     case 3: MontaTabelaBase(7,8,9);
             MontaTabelaTeste(7);
             break;
     case 4: MontaTabelaBase(10,11,12);
             MontaTabelaTeste(10);
             break;
   }
}

void MostraTabela(){
  int i;
  for(i=1;i<=54;i++)
  {
    printf("%s %d\n",TabelaTeste[i],i);
  }
}

void LimpaVariaveis()
{
    int i;
    for (i = 0; i < num+1; i++)
    {
      DistVet[i].distancia = 0;
      strcpy(  DistVet[i].nomeDist," ");
    }
}

void DaResultado(int indice, int iTT)
{
    int i;
    char resStr[tamstr];
    strcpy(resStr,"Distancias_");
    strcat(resStr,TabelaTeste[iTT]);
    resultado = fopen(resStr,"w");
    for(i=0;i<k;i++)
    {
          fprintf(resultado,"%d %s %f\n",i,DistVet[i].nomeDist, DistVet[i].distancia);
    }
    fclose(resultado);
}


int main()
{
    int i, indice;
    printf("Numero do conjunto Teste: \n");
    scanf("%d",&conjuntoTeste);
    DesterminaTesteTreino();
  //  MostraTabela();
    if(  FormaVetoresBase() != -1)
    {
      for (i = 1; i <= 54; i++)
      {
          if(EscolheBuscado(i) != -1)
          {
            LimpaVariaveis();
            indice = Classifica();
            DaResultado(indice, i);
          }
      }
    }
    printf("ok\n");
    getchar();
    return 0;
}
