#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define tamN 1000
#define tamT 13

typedef struct
{
      float kmax;
      float kmedio;
}Desct;

int   qtepontos;
float pontosX[tamN];
float pontosY[tamN];
float Arestas[tamN][tamN];
int   Rede[tamN][tamN];
int   grauVertices[tamN];
float limiaresT[tamT] = {0.0250,0.1000,0.1750,0.2500,0.3250,0.4000,0.4750,0.5500,0.6250,0.7000,0.7250,0.8500,0.9250};
Desct descritor[tamT];
FILE *forma2D, *Descritor;

void Coordenadas()
{
  int i,j;
  char nomeIma[20];
  printf("Quantidade de Pontos\n",&qtepontos);
  scanf("%d",&qtepontos);
  qtepontos = qtepontos - 2;
  printf("Nome do Arquivo da Base: ");
  scanf("%s",&nomeIma);
  printf("%s\n",nomeIma);
  forma2D = fopen(nomeIma,"r");
  if(forma2D == NULL)
  {
      printf("Erro na Abertura do Arquivo\n");
  }
  else
  {
      i = 0;
      while (fscanf(forma2D,"%f %f\n",&pontosX[i], &pontosY[i]) != EOF)
      {
          i++;
      }
  }
  fclose(forma2D);
}

void PrintaTeste()
{
    int i;
    for(i=0; i<= qtepontos;i++)
    {
        printf("%d - %f %f\n",i,pontosX[i],pontosY[i]);
    }
}

void NormalizaDistancia(float Wmax)
{
    int i,j;
    for(i=0;i<qtepontos;i++)
    {
        for(j=i+1;j<qtepontos;j++)
        {
          Arestas[i][j] = Arestas[i][j]/Wmax;
        //  printf("[%d,%d] = %.2f\n",i,j,Arestas[i][j]);
        }
    }
}

void DistanciaEuclidiana()
{
  int i,j;
  float d, maiordistancia = 0;
  for(i=0;i< qtepontos;i++)
  {
    for(j=i+1;j< qtepontos; j++)
    {
      d = pow((pontosX[i] - pontosX[j]),2) + pow((pontosY[i] - pontosY[j]),2);
      Arestas[i][j] = sqrt(d);
      if(Arestas[i][j] > maiordistancia)
        maiordistancia = Arestas[i][j];
    }
  }
  NormalizaDistancia(maiordistancia);
}

void IniciagrauVet()
{
    int i;
    for(i= 0;i<qtepontos;i++)
    {
        grauVertices[i] = 0;
    }
}

//Calcula os graus dos vertices para depois calcular o Médio e o Maximo
void DeterminaGrau()
{
  int i,j;
  IniciagrauVet();
  for (i=0; i<qtepontos; i++)
  {
    for(j=0; j<qtepontos; j++)
    {
        if(Rede[i][j] == 1 || Rede[j][i] == 1)
          grauVertices[i]++;
    }
  }
}

void CalculaGrauMaximo(Desct *d)
{
    int i,j, valormax = 0;
    for(i=0;i<qtepontos;i++)
    {
      if(grauVertices[i] > (*d).kmax)
        (*d).kmax = grauVertices[i];
    }
}

void CalculaGrauMedio(Desct *d)
{
    int i,soma = 0;
    for(i=0;i<qtepontos;i++)
    {
        soma += grauVertices[i];
    }
    (*d).kmedio = soma/qtepontos;
}

void MostraDescritores()
{
  int i;
  Descritor = fopen("Descritor.txt","w");
  for(i=0;i<tamT;i++)
  {
    fprintf(Descritor,"%4f %.4f\n",descritor[i].kmedio,descritor[i].kmax);
  }
  printf("\nDescritores Formados;\n");
}

void SelecionaArestas(float t)
{
  int j,k;
  for (j=0; j<qtepontos;j++)
  {
    for (k = j+1; k < qtepontos; k++)
    {
      if(Arestas[j][k] <= t)
        Rede[j][k] = 1;
    }
  }
}

void TranformacaoRede()
{
   int i,j,k;
   for(i = 0;i< tamT;i++)
   {
        SelecionaArestas(limiaresT[i]);
        DeterminaGrau();
        CalculaGrauMaximo(&descritor[i]);
        CalculaGrauMedio(&descritor[i]);
   }
     MostraDescritores();
}

void IniciaMatrizes()
{
    int i,j;
    for(i=0;i<qtepontos;i++)
    {
        descritor[i].kmax = 0;
        descritor[i].kmedio = 0;
        for(j=0;j<qtepontos;j++)
        {
          Arestas[i][j] = 0;
          Rede[i][j] = 0;
        }
    }
}

int main()
{
  while(1)
  {
    IniciaMatrizes();
    Coordenadas();
    //PrintaTeste();
    DistanciaEuclidiana();
    TranformacaoRede();
    fclose(Descritor);
    getchar();
  }
  return 0;
}
