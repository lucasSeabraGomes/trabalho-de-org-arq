#include <stdio.h>
#include <stdlib.h>
void CriaIndiceParaArq(char[]);
int main()
{
    char nomeArq[15];
    int escolha=-1;
    while(escolha!=0)
    {
        printf("digite 0 caso sair:");
        printf("digite 1 caso deseje criar um indice:");
        scanf("%d",&escolha);
        if(escolha==1)
        {
            //abre a função de criar arquivo com nome digitado com parametro
            //observação o arquivo deve estar na mesma pasta do binario
            printf("\nescreva o nome do arquivo para criar um indice\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            CriaIndiceParaArq(nomeArq);
        }
    }
    return 0;
}
//função que cria um indice a partir de um arqivo txt formatado de acordo com as especificações de trabalho
//ou seja tamanho fixo para todos os campos
void CriaIndiceParaArq(char nomeArq[])
{
    //abre o arquivo para leitura ou mostra um erro se não conseguir abri-lo
    FILE *fp;
    fp = fopen (nomeArq, "r");
    if (fp == NULL) {
       printf ("Houve um erro ao abrir o arquivo solicitado.\n");
       system("PAUSE");
       return;
    }
    //gera uma string chamada index que vai conter o nome do indice primario da lista
    char index[30]="index";
    int z=0;
    int n=0;
    for(z=0;index[z]!='\0';z++){};
    for(n=0;nomeArq[n]!='\0';n++)
    {
        index[z+n]=nomeArq[n];
    }
    index[z+n+1]='\0';
    //verifica o tipo de indice desejado
    int tipo;
    printf("digite 1 se voce deseja um indice de chaves primarias ou 2 para secundarias");
    scanf("%d",&tipo);
    if(tipo==1)
    {
        int i=0;
        int j;
        char chavePrimaria[30][30];
        //abre pu cria um arquivo de indice primario para escrita
        FILE *fs;
        fs = fopen (index, "ab+");
        chavePrimaria[i][30]='\0';
        fread(chavePrimaria[i],sizeof(char),30,fp);
        //este  loop garante que todos os elementos da lista original estarão na lista de chaves
        //loop que coloca apenas um numero x de elementos na memoria ram no caso o numero foi 30 mas pode ser aumentado de acordo com a disponibilidade de ram no computador
        while(i<30&&(feof(fp) == 0))
        {
            fseek(fp,(33*sizeof(char)),SEEK_CUR);
            fread(chavePrimaria[i],sizeof(char),30,fp);
            chavePrimaria[i][30]='\0';
            printf("\nchave:%s \nPosiçao do 1 caracter no arquivo:%d\n",chavePrimaria[i],i*63);
            if(i==29||(feof(fp) != 0))
            {
                //este loop escreve todos as chaves da string e suas respectivas posições no arquivo de indices.
                for(j=0;j<=i;j++)
                {
                    fprintf(fs,"%s %d ",chavePrimaria[j],j*63);
                }
            }
            i++;
        }
        system("PAUSE");
    }
    //neste if serão criados indices de chaves secundarias
    else if(tipo==2)
    {
        int i=0;
        char index2[33];
        //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
        while(index[i]!='\0')
        {
            index2[i]=index[i];
            i++;
            if(index[i]=='\0')
            {
                index2[i]='S';
                index2[i+1]='e';
                index2[i+2]='c';
                index2[i+3]='\0';
            }

        }
        //cria o arquivo de indice
        FILE *fs;
        fs = fopen (index2, "ab+");

    }
    else
    {
        printf("pedido invalido");
        return;
    }
};
