#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define tamN 10
#define tamT 13

typedef struct
{
      float kmax;
      float kmedio;
}Desct;

float pontosX[tamN];
float pontosY[tamN];
float Arestas[tamN][tamN];
int   Rede[tamN][tamN];
int   grauVertices[tamN];
float limiaresT[tamT] = {0.0250,0.0100,0.1750,0.2500,0.3250,0.4000,0.4750,0.5500,0.6250,0.7000,0.7250,0.8500,0.9250};
Desct descritor[tamT];

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
        //  printf("[%d,%d] = %.2f\n",i,j,Arestas[i][j]);
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
      //printf("[%d,%d] = %.2f\n",i,j,Arestas[i][j]);
    }
  }
  NormalizaDistancia(maiordistancia);
}

void IniciagrauVet()
{
    int i;
    for(i= 0;i<tamN;i++)
    {
        grauVertices[i] = 0;
    }
}

void DeterminaGrau()
{
  int i,j;
  IniciagrauVet();
  for (i=0; i<tamN; i++)
  {
    for(j=0; j<tamN; j++)
    {
        if(Rede[i][j] == 1 || Rede[j][i] == 1)
          grauVertices[i]++;
    }
  }
}

void CalculaGrauMaximo(Desct *d)
{
    int i,j, valormax = 0;
    for(i=0;i<tamN;i++)
    {
      if(grauVertices[i] > (*d).kmax)
        (*d).kmax = grauVertices[i];
    }
    //printf("Grau Maximo %d\n",(*d).kmax);
}

void CalculaGrauMedio(Desct *d)
{
    int i,soma = 0;
    for(i=0;i<tamN;i++)
    {
        soma += grauVertices[i];
    }
    (*d).kmedio = soma/tamN;
}

void MostraDescritores()
{
  int i;
  printf("\nDescritores Formados;\n");
  for(i=0;i<tamN;i++)
  {
    printf("\nDescritor: %d\n",i);
    printf("Grau Maximo: %.4f\n",descritor[i].kmax);
    printf("Grau Medio: %.4f\n",descritor[i].kmedio);
  }
}

void SelecionaArestas(float t)
{
  int j,k;
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
        //printf("%.4f\n",limiaresT[12]);
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
    for(i=0;i<tamN;i++)
    {
        descritor[i].kmax = 0;
        descritor[i].kmedio = 0;
        for(j=0;j<tamN;j++)
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
  TranformacaoRede();
  return 0;
}
