#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float pontosX[10];
float pontosY[10];
float Arestas[10][10];

void Coordenadas()
{
  int i;
  printf("Insira as coordenadas do contorno da forma 2D:\n");
  for(i=0;i<10;i++)
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
    for(i=0;i<10;i++)
    {
        for(j=i+1;j<10;j++)
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
  for(i=0;i< 10;i++)
  {
    for(j=i+1;j< 10; j++)
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
