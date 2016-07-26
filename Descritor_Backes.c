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

void DistanciaEuclidiana()
{
  int i,j;
  float d;
  for(i=0;i< 10;i++)
  {
    for(j=i+1;j< 10; j++)
    {
      d = pow((pontosX[i] - pontosX[j]),2) + pow((pontosY[i] - pontosY[j]),2);
      Arestas[i][j] = sqrt(d);
      printf("[%d,%d] = %.2f\n",i,j,Arestas[i][j]);
    }
  }
  printf("\n-------- Calculou ------ \n");
}

int main()
{
  Coordenadas();
  DistanciaEuclidiana();
  return 0;
}
