#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define tamMax 125
#define k 3
#define num 162
#define complemento 54
#define nClasse 18
#define qFormas 12

typedef struct
{
      float distancia;
      char  nomeDist[50];
}EstruturaDist;

typedef struct
{
  float valor[tamMax];
  char nomeDesc[50];
}EstruturaDesc;

FILE *descritorT, *descritorB, *DisKnn;
EstruturaDesc DescTeste, DescBase[tamMax];
EstruturaDist DistEucli[num];
char TabelaBase[num+1][num+1], TabelaTeste[num+1][num+1];
int conjunto;

/*Monta uma TabelaBase de correspondencia para decritor e indice*/
void MontaTabelaBase(int classeA, int classeB, int classeC)
{
   int i,j,count = 1;
   char base[50];
   char numero[3];
   for(j=1;j<=qFormas;j++)
   {
      for(i=1;i<=nClasse;i++)
      {
         if(j != classeA && j != classeB && j != classeC)
         {
            strcpy(base,"Desc_RFFT-pontos-");
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
    char base[50];
    char numero[3];

    for (i = 1; i <= nClasse ; i++)
    {
      for (j =classeA ; j < classeA+3; j++)
      {
        strcpy(base,"Desc_RFFT-pontos-");
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
   switch (conjunto)
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


float DistEuclidiana(int n)
{
  int i;
  float soma=0, dist=0, sub =0;
  for (i = 0; i <tamMax; i++)
  {
    sub = DescBase[n].valor[i] - DescTeste.valor[i];
    soma += pow(sub,2);
  }
  dist = sqrt(soma);
  return dist;
}

void quicksort(EstruturaDist arr[],int low,int high)
{
   int j,i,pivot;
   EstruturaDist temp;
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

void Classifica()
{
    int i;
    float Daux;
    for (i = 0; i < num; i++)
    {
        Daux= DistEuclidiana(i);
        DistEucli[i].distancia = Daux;
        strcpy(DistEucli[i].nomeDist,DescBase[i].nomeDesc);
    }
    quicksort(DistEucli,0,num-1);
}

void ArqToVetor(FILE *arq, EstruturaDesc *D)
{
    int i = 0;
    float vAux;
    while (fscanf(arq,"%f",&vAux) != EOF)
    {
      (*D).valor[i] = vAux;
      i++;
    }
}

void AbreTeste(int n)
{
    int i,j;
    descritorT = fopen(TabelaTeste[n],"r");
    if(descritorT == NULL)
    {
        printf("Erro na abertura do %s\n",TabelaTeste[n]);
    }
    else
    {
        ArqToVetor(descritorT,&DescTeste);
        strcpy(DescTeste.nomeDesc,TabelaTeste[n]);
    }
    fclose(descritorT);
}

void AbreBase()
{
    int i,j;
    for (i = 0; i < num; i++)
    {
       descritorB = fopen(TabelaBase[i+1],"r");
       if(descritorB == NULL)
       {
          printf("Erro na abertura do %s\n",TabelaBase[1]);
       }
       else
       {
          ArqToVetor(descritorB,&DescBase[i]);
          strcpy(DescBase[i].nomeDesc,TabelaBase[i+1]);
       }
       fclose(descritorB);
    }
}

void ArqResultado(int n)
{
  int i;
  char base[50];
  strcpy(base,"Knn_RFFT-");
  strcat(base,TabelaTeste[n]);
  DisKnn = fopen(base,"w");
  if(DisKnn == NULL)
  {
    printf("Erro na abertura do %s\n",base);
  }
  else
  {
    for (i = 0; i < k; i++)
    {
      fprintf(DisKnn, "%s %.4f\n",DistEucli[i].nomeDist, DistEucli[i].distancia);
    }
  }
  fclose(DisKnn);
}

int main()
{
  int i,j;
  printf("Conjunto: \n");
  scanf("%d",&conjunto);
  DesterminaTesteTreino();
  AbreBase();
  for (i = 0; i < complemento; i++)
  {
    AbreTeste(i+1);
    Classifica();
    ArqResultado(i+1);
  }
  printf("oooook\n");
  return 0;
}
