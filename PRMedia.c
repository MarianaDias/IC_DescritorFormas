#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define tamMax 125
#define num 216
#define nClasse 18
#define qFormas 12

char TabelaBase[num+1][num+1];
float PRmediageral[qFormas], PRmediarecall[qFormas], PRindiv[qFormas];
int classeC[num];

FILE *arq, *saida;

void ClasseCorespondente()
{
  int i;
  for (i = 1; i <= num; i++)
  {
    if(i <= 12)
        classeC[i] = 1;
    else if(i > 12 && i <= 24)
        classeC[i] = 2;
    else if(i > 24 && i <=36)
        classeC[i] = 3;
    else if(i > 36 && i <= 48)
        classeC[i] = 4;
    else if(i > 48 && i <= 60)
        classeC[i] = 5;
    else if(i > 60 && i <= 72)
        classeC[i] = 6;
    else if(i > 72 && i <= 84)
        classeC[i] = 7;
    else if(i > 84 && i <= 96)
        classeC[i] = 8;
    else if(i > 96 && i <= 108)
        classeC[i] = 9;
    else if(i > 108 && i <= 120)
        classeC[i] = 10;
    else if(i > 120 && i <= 132)
        classeC[i] = 11;
    else if(i > 132 && i <= 144)
        classeC[i] = 12;
    else if(i > 144 && i <= 156)
        classeC[i] = 13;
    else if(i > 156 && i <= 168)
        classeC[i] = 14;
    else if(i > 168 && i <= 180)
        classeC[i] = 15;
    else if(i > 180 && i <= 192)
        classeC[i] = 16;
    else if(i > 192 && i <= 204)
        classeC[i] = 17;
    else if(i > 204 && i <= 216)
        classeC[i] = 18;
  }
}


void MontaTabelaBase()
{
   int i,j,count = 1;
   char base[70];
   char numero[3];
   for(j=1;j<=nClasse;j++)
   {
      for(i=1;i<=qFormas;i++)
      {
          strcpy(base,"PR_RFFT-Desc_RFFT-pontos-");
          itoa(j,numero,10);
          strcat(base,numero);
          strcpy(numero,"");
          strcat(base,"-");
          itoa(i,numero,10);
          strcat(base,numero);
          strcat(base, ".txt");
          strcpy(TabelaBase[count],base);
          count++;
       }
    }
}

void PRindividual(int k)
{
  char linha[50], ch[3], d[20];
  int i,j,recall,classe;
  i = 0;
  recall = 0;
  PRindiv[i] = 1;
  while (fscanf(arq, "%s %s",linha,d) != EOF)
  {
    i++;
    ch[0] = linha[17];
    ch[1] = NULL;
    if(linha[18] != '-')
    {
        ch[1] = linha[18];
        ch[2] = NULL;
    }
    classe = atoi(ch);
    if(classe == classeC[k])
    {
      printf("%d %d %d\n",k,classe,classeC[k]);
      recall++;
      PRindiv[recall] = (float)recall/i;
    }
  }
}

void MediaRecall()
{
  int i;
  for (i = 0; i < qFormas; i++)
  {
    PRmediarecall[i] += PRindiv[i];
  }
}

void PRmediaGeral()
{
  int i;
  for (i = 0; i < qFormas; i++)
  {
    PRmediageral[i] = (float)PRmediarecall[i]/num;
  }
}

void AbreArquivo(int k)
{
   arq = fopen(TabelaBase[k],"r");
   if(arq == NULL)
    printf("Erro na abertura do arq %s\n",TabelaBase[k]);
   else
   {
      PRindividual(k);
      MediaRecall();
   }
   fclose(arq);
}

void Limpa() {
  int i;
  for (i = 0; i < qFormas; i++) {
    PRmediageral[i] = 0;
    PRmediarecall[i] = 0;
    PRindiv[i] = 0;
  }
}

void ImprimeMedia()
{
  int i;
  saida = fopen("PR_RFFT_media.txt","w");
  if(saida == NULL)
    printf("Erro na abertura da saida\n");
  else
  {
    for (i = 0; i < qFormas; i++)
    {
      fprintf(saida, "%.4f\n",PRmediageral[i]);
    }
  }
  fclose(saida);
}

int main()
{
  int i;
  MontaTabelaBase();
  ClasseCorespondente();
  Limpa();
  for (i = 0; i < num; i++)
  {
    AbreArquivo(i+1);
  }
  PRmediaGeral();
  ImprimeMedia();
  printf("ook\n");
  return 0;
}
