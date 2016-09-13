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
    char  nomeDesc[tamstr];
}Descritor;

typedef struct
{
    char  nomeDist[tamstr];
    float distancia;
}DistEucli;

Descritor formaBuscada;
Descritor formasBase[num-1];
DistEucli DistVet[num+1];
char Nomebuscado[tamstr];
char Tabela[num+1][num+1];
float bigVetBase[2*tamDesc];
float bigVetBuscado[2*tamDesc];

FILE *descBuscado, *descBase, *resultado;

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

/*Ordenacao*/
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

void DaResultado(int indice)
{
    int i;
    char resStr[tamstr];
    strcpy(resStr,"Distancias_");
    strcat(resStr,Nomebuscado);
    resultado = fopen(resStr,"w");
    for(i=0;i<indice;i++)
    {
    //   if(strcmp(DistVet[i].nomeDist,"Buscado" ) != 0)
          fprintf(resultado,"%d %s %f\n",i,DistVet[i].nomeDist, DistVet[i].distancia);
    }
    fclose(resultado);
}

/*Monta o vetor ordenado em relacao a menor distancia Euclidiana da amostra*/
int Classifica()
{
  int i,j,indice = 0;
  MontaBigVet(formaBuscada,bigVetBuscado);
  for (i = 0; i < num; i++)
  {
    if(strcmp(formasBase[i].nomeDesc,"Buscado") != 0)
    {
      printf("Indice %d, i %d\n",indice,i );
      MontaBigVet(formasBase[i],bigVetBase);
      DistVet[indice].distancia = DistEuclidiana();
      strcpy(DistVet[indice].nomeDist,formasBase[i].nomeDesc);
      indice++;
    }
  }
  quicksort(DistVet,0,indice-1);
  return indice-1;
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

/*Salva o resto dos descritores e corresponde o indice do buscado na Tabela*/
int FormaVetoresBase()
{
    int i = 0,j;
    for(i=0;i<num;i++)
    {
      if(strcmp(formaBuscada.nomeDesc,Tabela[i+1]) !=0)
      {
          descBase = fopen(Tabela[i+1],"r");
          if(descBase == NULL)
          {
              printf("Erro ao abrir o arquivo %s\n",Tabela[i+1]);
              return -1;
          }
          ArqToVetor(descBase,&formasBase[i]);
          strcpy(formasBase[i].nomeDesc,Tabela[i+1]);
          fclose(descBase);
      }
      else
      {
        strcpy(formasBase[i].nomeDesc,"Buscado");
      }
    }
    return 1;
}

/*Escolhe o arquivo do descritor a ser usando como amostra e salva ele no descritor formaBuscada*/
int EscolheBuscado()
{
    int i;
    printf("Nome do Descritor Buscado: ");
    scanf("%s",&Nomebuscado);
    descBuscado = fopen(Nomebuscado,"r");
    if(descBuscado == NULL)
    {
      printf("Erro na abertura do Arquivo\n");
      return -1;
    }
    ArqToVetor(descBuscado,&formaBuscada);
    strcpy(formaBuscada.nomeDesc,Nomebuscado);
    fclose(descBuscado);
    return 1;
}


void MostraTabela(){
  int i;
  for(i=1;i<=num;i++)
  {
    printf("%s %d\n",Tabela[i],i);
  }
}

/*Monta uma tabela de correspondencia para decritor e indice*/
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
        strcat(base, ".txt");
        strcpy(Tabela[count],base);
        count++;
     }
   }
}

int main()
{
  int indice;
  MontaTabela();
  while(1)
  {
    if(EscolheBuscado() != -1)
    {
        if(FormaVetoresBase() != -1)
        {
          indice = Classifica();
          DaResultado(indice);
        }
    }
   printf("ok\n");
  }



  getchar();
  return 0;
}
