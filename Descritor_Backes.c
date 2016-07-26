#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define tamN 10
#define tamT 13

float pontosX[tamN];
float pontosY[tamN];
float Arestas[tamN][tamN];
float limiaresT[tamT] = {0.0250,0.0100,0.1750,0.2500,0.3250,0.4000,0.4750,0.5500,0.6250,0.7000,0.7250,0.8500,0.9250};

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

int main()
{
  Coordenadas();
  DistanciaEuclidiana();
  return 0;
}
