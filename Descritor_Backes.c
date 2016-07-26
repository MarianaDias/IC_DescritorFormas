#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define tamN 10
#define tamT 13

typedef struct Caracteristicas
{
      int kmax;
      int kmedio;
};

float pontosX[tamN];
float pontosY[tamN];
float Arestas[tamN][tamN];
int   Rede[tamN][tamN];
float limiaresT[tamT] = {0.0250,0.0100,0.1750,0.2500,0.3250,0.4000,0.4750,0.5500,0.6250,0.7000,0.7250,0.8500,0.9250};
Caracteristicas descritor[tamT];

void Coordenadas()
{
  int i;
  printf("Insira as coordenadas do contorno da forma 2D:\n");
  for(i=0;i<tamN;i++)
  {
      printf("x %d: ",i);
      scanf("%f",&pontosX[i]);
      printf("y %d: ",i);
      scanf("%f",&pontosY[i]);
  }
}

void NormalizaDistancia(float Wmax)
{
    int i,j;
    for(i=0;i<tamN;i++)
    {
        for(j=i+1;j<tamN;j++)
        {
          Arestas[i][j] = Arestas[i][j]/Wmax;
          printf("[%d,%d] = %.2f\n",i,j,Arestas[i][j]);
        }
    }
}

void DistanciaEuclidiana()
{
  int i,j;
  float d, maiordistancia = 0;
  for(i=0;i< tamN;i++)
  {
    for(j=i+1;j< tamN; j++)
    {
      d = pow((pontosX[i] - pontosX[j]),2) + pow((pontosY[i] - pontosY[j]),2);
      Arestas[i][j] = sqrt(d);
      if(Arestas[i][j] > maiordistancia)
        maiordistancia = Arestas[i][j];
      printf("[%d,%d] = %.2f\n",i,j,Arestas[i][j]);
    }
  }
  printf("\n-------- Calculou ------ \n");
  NormalizaDistancia(maiordistancia);
}
void IniciacontaAresta(int countAresta[])
{
    int i;
    for(int = 0;j<tamN;i++)
    {
        countAresta[i] = 0;
    }
}

void CalculaGrauMaximo()
{
    int i,j, countAresta[tamN], valormax = 0;
    IniciacontaAresta();
    for (i=0; i<tamN; i++)
    {
      for(j=0; j<tamN; j++)
      {
          if(Rede[i][j] == 1 || Rede[j][i] == 1)
            countAresta[i]++;
      }
    }
    for(i=0;i<tamN;i++)
    {
      if(countAresta[i] > valormax)
        descritor.kmax = i;
    }
}

void CalculaGrauMedio()
{

}

void MontaDescritor()
{

}

void SelecionaArestas(float t)
{
  for (j=0; j<tamN;j++)
  {
    for (k = j+1; k < tamN; k++)
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
    }
}

void IniciaMatrizes()
{
    int i,j;
    for(i=0;i<tamN;i++)
    {
        for(j=0;i<tamN;j++)
        {
          Arestas[i][j] = 0;
          Rede[i][j] = 0;
        }
    }
}

int main()
{
  IniciaMatrizes();
  Coordenadas();
  DistanciaEuclidiana();
  return 0;
}
