#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define tamP 900
#define num 216
#define nClasse 18
#define qFormas 12
#define maxPontos 128

int qtepontos;
char TabelaArq[num+1][num+1];
float SelpontosY[tamP], SelpontosX[tamP],pontosY[tamP], pontosX[tamP];
float mediaX, mediaY;
float Distancia[tamP], X[tamP], FD[tamP];
FILE *forma2D, *resultado;

/****************************************************************************
* rfft(float X[],int N)                                                     *
*     A real-valued, in-place, split-radix FFT program                      *
*     Decimation-in-time, cos/sin in second loop                            *
*     Input: float X[1]...X[N] (NB Fortran style: 1st pt X[1] not X[0]!)    *
*     Length is N=2**M (i.e. N must be power of 2--no error checking)       *
*     Output in X[1]...X[N], in order:                                      *
*           [Re(0), Re(1),..., Re(N/2), Im(N/2-1),..., Im(1)]               *
*                                                                           *
* Original Fortran code by Sorensen; published in H.V. Sorensen, D.L. Jones,*
* M.T. Heideman, C.S. Burrus (1987) Real-valued fast fourier transform      *
* algorithms.  IEEE Trans on Acoustics, Speech, & Signal Processing, 35,    *
* 849-863.  Adapted to C by Bill Simpson, 1995  wsimpson@uwinnipeg.ca       *
****************************************************************************/

void rfft(float X[],int N)
{
  int I,I0,I1,I2,I3,I4,I5,I6,I7,I8, IS,ID;
  int J,K,M,N2,N4,N8;
  float A,A3,CC1,SS1,CC3,SS3,E,R1,XT;
  float T1,T2,T3,T4,T5,T6;

  M=(int)(log(N)/log(2.0));               /* N=2^M */
  /* ----Digit reverse counter--------------------------------------------- */
  J = 1;
  for(I=1;I<N;I++)
  {
      if (I<J)
      {
        XT    = X[J];
        X[J]  = X[I];
        X[I]  = XT;
      }
      K = N/2;
      while(K<J)
      {
        J -= K;
        K /= 2;
      }
      J += K;
  }
  /* ----Length two butterflies--------------------------------------------- */
  IS = 1;
  ID = 4;
  do
          {
          for(I0 = IS;I0<=N;I0+=ID)
                  {
                  I1    = I0 + 1;
                  R1    = X[I0];
                  X[I0] = R1 + X[I1];
                  X[I1] = R1 - X[I1];
                  }
          IS = 2 * ID - 1;
          ID = 4 * ID;
          }while(IS<N);
  /* ----L shaped butterflies----------------------------------------------- */
  N2 = 2;
  for(K=2;K<=M;K++)
          {
          N2    = N2 * 2;
          N4    = N2/4;
          N8    = N2/8;
          E     = (float) 6.2831853071719586f/N2;
          IS    = 0;
          ID    = N2 * 2;
          do
                  {
                  for(I=IS;I<N;I+=ID)
                          {
                          I1 = I + 1;
                          I2 = I1 + N4;
                          I3 = I2 + N4;
                          I4 = I3 + N4;
                          T1 = X[I4] +X[I3];
                          X[I4] = X[I4] - X[I3];
                          X[I3] = X[I1] - T1;
                          X[I1] = X[I1] + T1;
                          if(N4!=1)
                                  {
                                  I1 += N8;
                                  I2 += N8;
                                  I3 += N8;
                                  I4 += N8;
                                  T1 = (X[I3] + X[I4])*.7071067811865475244f;
                                  T2 = (X[I3] - X[I4])*.7071067811865475244f;
                                  X[I4] = X[I2] - T1;
                                  X[I3] = -X[I2] - T1;
                                  X[I2] = X[I1] - T2;
                                  X[I1] = X[I1] + T2;
                                  }
                          }
                          IS = 2 * ID - N2;
                          ID = 4 * ID;
                  }while(IS<N);
          A = E;
          for(J= 2;J<=N8;J++)
                  {
                  A3 = 3.0 * A;
                  CC1   = cos(A);
                  SS1   = sin(A);  /*typo A3--really A?*/
                  CC3   = cos(A3); /*typo 3--really A3?*/
                  SS3   = sin(A3);
                  A = (float)J * E;
                  IS = 0;
                  ID = 2 * N2;
                  do
                          {
                          for(I=IS;I<N;I+=ID)
                                  {
                                  I1 = I + J;
                                  I2 = I1 + N4;
                                  I3 = I2 + N4;
                                  I4 = I3 + N4;
                                  I5 = I + N4 - J + 2;
                                  I6 = I5 + N4;
                                  I7 = I6 + N4;
                                  I8 = I7 + N4;
                                  T1 = X[I3] * CC1 + X[I7] * SS1;
                                  T2 = X[I7] * CC1 - X[I3] * SS1;
                                  T3 = X[I4] * CC3 + X[I8] * SS3;
                                  T4 = X[I8] * CC3 - X[I4] * SS3;
                                  T5 = T1 + T3;
                                  T6 = T2 + T4;
                                  T3 = T1 - T3;
                                  T4 = T2 - T4;
                                  T2 = X[I6] + T6;
                                  X[I3] = T6 - X[I6];
                                  X[I8] = T2;
                                  T2    = X[I2] - T3;
                                  X[I7] = -X[I2] - T3;
                                  X[I4] = T2;
                                  T1    = X[I1] + T5;
                                  X[I6] = X[I1] - T5;
                                  X[I1] = T1;
                                  T1    = X[I5] + T4;
                                  X[I5] = X[I5] - T4;
                                  X[I2] = T1;
                                  }
                          IS = 2 * ID - N2;
                          ID = 4 * ID;
                          }while(IS<N);
                  }
          }
  return;
}

void Coordenadas(int k)
{
  int i;
  forma2D = fopen(TabelaArq[k],"r");
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
      qtepontos = i;
  }
  fclose(forma2D);
}

void PrintaTeste()
{
    int i;
    for(i=0; i< maxPontos;i++)
    {
        printf("%d - %f %f\n",i,SelpontosX[i],SelpontosY[i]);
    }
}

void NormalizaPontos()
{
    int  i,j = 0;
    float d;
    d = (int)qtepontos/maxPontos;
    for (i = 0; i < 128; i++)
    {
      SelpontosY[i] = pontosY[j];
      SelpontosX[i] = pontosX[j];
      j+=d;
    }
}

void CalculaMedia()
{
  int i;
  mediaX = 0;
  mediaY = 0;
  for  (i = 0; i < maxPontos; i++)
  {
    mediaX += SelpontosX[i];
    mediaY += SelpontosY[i];
  }
  mediaX = mediaX/qtepontos;
  mediaY = mediaY/qtepontos;
}

void DistanciaEuclidiana()
{
  int i;
  float d, maiordistancia = 0;
  for(i=0;i< maxPontos;i++)
  {
    d = pow((SelpontosX[i] - mediaX),2) + pow((SelpontosY[i] - mediaY),2);
    Distancia[i] = sqrt(d);
  }
}

void CopiaDistancia()
{
  int i;
  for (i = 1; i <=maxPontos; i++)
  {
      X[i] = Distancia[i-1];
  }
}

void PrePross()
{
  NormalizaPontos();
  CalculaMedia();
  DistanciaEuclidiana();
  CopiaDistancia();
}

void MostraTabelaArq()
{
  int i;
  for (i = 1; i <=num; i++) {
      printf("%s\n",TabelaArq[i]);
  }
}

void DefineNomeArq()
{
  int i,j,count = 1;
  char base[50];
  char numero[3];

  for(j=1;j<=nClasse;j++)
  {
    for(i=1;i<=qFormas;i++)
    {
       strcpy(base,"pontos-");
       itoa(j,numero,10);
       strcat(base,numero);
       strcpy(numero,"");
       strcat(base,"-");
       itoa(i,numero,10);
       strcat(base,numero);
       strcat(base, ".txt");
       strcpy(TabelaArq[count],base);
       count++;
    }
  }
}

void PosPross()
{
   int i;
   for (i=3; i <= maxPontos; i++)
   {
      FD[i-3] = fabs(X[i]/X[2]);
   }
}


void MontaDescritor(int k)
{
  int i;
  char base[50];
  strcpy(base,"Desc_RFFT-");
  strcat(base,TabelaArq[k]);
  resultado = fopen(base,"w");
  if(resultado == NULL)
  {
      printf("Erro na abertura do Arq %s\n",base);
  }
  else
  {
      for (i = 0; i < maxPontos-3; i++)
      {
          fprintf(resultado, "%.4f\n",FD[i]);
      }
      fclose(resultado);
  }
}

void LimpaVariaveis()
{
  int i;
  for (i = 0; i < maxPontos; i++)
  {
    X[i] = -1;
    FD[i] = -1;
    SelpontosY[i] = -1;
    SelpontosX[i] = -1;
    Distancia[i] = -1;
  }
  for ( i = 0; i < qtepontos; i++) {
    pontosY[i] = -1;
    pontosX[i] = -1;
  }
}

int main()
{
      int i;
      DefineNomeArq();
      for (i = 0; i < num; i++)
      {
          Coordenadas(i+1);
          PrePross();
          rfft(X,maxPontos);
          PosPross();
          MontaDescritor(i+1);
          LimpaVariaveis();
      }
      printf("ok\n");
      return 0;
}
