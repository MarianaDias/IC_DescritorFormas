#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float pontosX[10];
float pontosY[10];

void Coordenadas()
{
  int i;
  printf("Insira as coordenadas do contorno da forma 2D:\n");
  for(i=0;i<10;i++)
  {
      printf("x %d: ",i);
      scanf("%d",&pontosX[i]);
      printf("y %d: ",i);
      scanf("%d",&pontosY[i]);
  }
}

int main()
{
  Coordenadas();
  return 0;
}
