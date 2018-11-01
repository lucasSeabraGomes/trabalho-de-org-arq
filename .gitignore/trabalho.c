#include <stdio.h>
#include <stdlib.h>
void CriaIndiceParaArq(char[]);
void unir(char[],char[]);
void excluir(char[]);
struct elementos
{
    char curso[2];
    char nome[40];
    char matricula[6];
    char escolha[2];
    char turma;
};
struct indiceSec
{
    char campo[10];
    char indice[60][30];
};
int main()
{
    char nomeArq[15];
    char nomeArq2[15];
    int escolha=-1;
    while(escolha!=0)
    {
        printf("digite 0 caso sair;\n");
        printf("digite 1 caso deseje criar um indice;\n");
        printf("digite 2 caso deseje unir duas listas;\n");
        printf("digite 3 excluir um registro;\n");
        scanf("%d",&escolha);
        getchar();
        if(escolha==1)
        {
            //abre a função de criar arquivo com nome digitado com parametro
            //observação o arquivo deve estar na mesma pasta do binario
            printf("\nescreva o nome do arquivo para criar um indice\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            CriaIndiceParaArq(nomeArq);
        }
        if(escolha==2)
        {
            //abre a função de criar arquivo com nome digitado com parametro
            //observação o arquivo deve estar na mesma pasta do binario
            printf("\nescreva o nome dos arquivos para uni-los\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            scanf("%s",nomeArq2);
            unir(nomeArq,nomeArq2);
        }
        if(escolha==3)
        {
            //abre a função de criar arquivo com nome digitado com parametro
            //observação o arquivo deve estar na mesma pasta do binario
            printf("\nescreva o nome do arquivo de onde será excluido o regitro\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            excluir(nomeArq);
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
    getchar();
    printf("digite 1 se voce deseja um indice de chaves primarias ou 2 para secundarias");
    scanf("%d",&tipo);
    if(tipo==1)
    {
        int p;
        int i=0;
        int j;
        char chavePrimaria[60][30];
        //abre pu cria um arquivo de indice primario para escrita
        FILE *fs;
        fs = fopen (index, "ab+");
        chavePrimaria[i][30]='\0';
        fread(chavePrimaria[i],sizeof(char),30,fp);
        //este  loop garante que todos os elementos da lista original estarão na lista de chaves
        //loop que coloca apenas um numero x de elementos na memoria ram no caso o numero foi 60 mas pode ser aumentado de acordo com a disponibilidade de ram no computador
        while(i<60&&(feof(fp) == 0))
        {
            fseek(fp,(33*sizeof(char)),SEEK_CUR);
            fread(chavePrimaria[i],sizeof(char),30,fp);
            chavePrimaria[i][30]='\0';
            i++;
        }
        //este loop escreve todos as chaves da string e suas respectivas posições no arquivo de indices.
            for(j=0;j<=i;j++)
            {
                printf("\nchave:");
                for(p=0;p<30;p++)
                {
                    printf("%c",chavePrimaria[j][p]);
                    fprintf(fs,"%c",chavePrimaria[j][p]);
                }
                printf(" posicao do primeiro char%d",j*63);
                fprintf(fs,"%d",j*63);
            }
        system("PAUSE");
    }
    //neste if serão criados indices de chaves secundarias
    else if(tipo==2)
    {
        int p;
        char aux[30];
        char aux2[10];
        int i=0;
        int cont;
        int j;
        int z;
        char index2[33];
        char indiceSecArqBase[37];
        //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
        while(index[i]!='\0')
        {
            indiceSecArqBase[i]=index[i];
            index2[i]=index[i];
            i++;
            if(index[i]=='\0')
            {
                indiceSecArqBase[i]='S';
                indiceSecArqBase[i+1]='e';
                indiceSecArqBase[i+2]='c';
                index2[i]='S';
                index2[i+1]='e';
                index2[i+2]='c';
                index2[i+3]='\0';
            }

        }
        indiceSecArqBase[i+3]='B';
        indiceSecArqBase[i+4]='a';
        indiceSecArqBase[i+5]='s';
        indiceSecArqBase[i+6]='e';
        indiceSecArqBase[i+7]='\0';
        //cria o arquivo de indice
        FILE *fs;
        fs = fopen (index2, "ab+");
        FILE *fsb;
        fsb = fopen (indiceSecArqBase, "ab+");
        struct indiceSec colocar[10];
        //loop para inicializae a estrutura do indice como \0 na coluna de curso
        while(i<10)
        {
            for(j=0;j<10;j++)
            {
                colocar[i].campo[j]='\0';
                for(p=0;p<60;p++)
                {
                    colocar[i].indice[p][0]='\0';
                }
            }
            i++;
        }
        //adiciona o primeiro elemento ao vetor de estruturas chaves secundarias.
        fread(colocar[0].indice[0],sizeof(char),30,fp);
        colocar[0].indice[0][30]='\0';
        fseek(fp,(22*sizeof(char)),SEEK_CUR);
        fscanf(fp,"%s",colocar[0].campo);
        //loop para pegar do arquivo os elementos para colocar na estrutura de indices secundarios
        while(feof(fp) == 0)
        {
            i=0;
            //neste ponto pega os dados do arquivo e coloca em strings auxiliares
            fseek(fp,(9*sizeof(char)),SEEK_CUR);
            fread(aux,sizeof(char),30,fp);
            aux[30]='\0';
            fseek(fp,(22*sizeof(char)),SEEK_CUR);
            fscanf(fp,"%s",aux2);
            for(i=0;colocar[i].campo[0]!='\0';i++)
            {
                cont=0;
                for(j=0;colocar[i].campo[j]!='\0';j++)
                {
                    if(colocar[i].campo[j]!=aux2[j])
                    {
                        cont++;
                    }
                }
                if(cont==0)
                {
                    //este loop coloca no ultimo elemento do array de indices
                    p=0;
                    while(colocar[i].indice[p][0]!=0)
                    {
                        p++;
                    }
                    z=0;//
                    while(z<30){
                        colocar[i].indice[p][z]=aux[z];
                        z++;
                    }
                    colocar[i].indice[p][30]='\0';
                    break;
                }
            }
            //caso de não existir nenhum membro do array de indices secundarios com o campo lido
            if(cont!=0)
            {
                j=0;
                while(aux2[j]!='\0')
                {
                    colocar[i].campo[j]=aux2[j];
                    j++;
                }
                colocar[i].campo[j+1]='\0';
                for(j=0;j<30;j++)
                {
                    colocar[i].indice[0][j]=aux[j];
                }
            }
        }
        int auxiliar1=0;
        i=0;

        while(colocar[i].campo[0]!='\0')
        {
            j=0;
            fprintf(fsb,"%s ",colocar[i].campo);
            fprintf(fsb,"%d\n",auxiliar1);
                while (colocar[i].indice[j][0]!='\0')
                {
                    fseek(fs,auxiliar1*sizeof(char),SEEK_SET);
                    z=0;
                    auxiliar1=auxiliar1+30;
                    while(z<30)
                    {
                        fprintf(fs,"%c",colocar[i].indice[j][z]);
                        z++;
                    }
                    if(colocar[i].indice[j+1][0]!='\0')
                    {
                         fprintf(fs," %d ",auxiliar1);
                    }
                    else
                    {
                        fprintf(fs," %d ",-1);
                    }
                }
                i++;
        }
    }
    //caso de digitarm um valor invalido no menu
    else
    {
        printf("pedido invalido");
        return;
    }
};
void unir(char arq[],char arq2[])
{
    int z=0;
    int n=0;
    int i=0;
    char indiceArq[27]="index";
    char indiceSecArq[30];
    for(z=0;indiceArq[z]!='\0';z++){};
    for(n=0;arq[n]!='\0';n++)
    {
        indiceArq[z+n]=arq[n];
    }
    indiceArq[z+n+1]='\0';
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(indiceArq[i]!='\0')
    {

        indiceSecArq[i]=indiceArq[i];
        i++;
        if(indiceArq[i]=='\0')
        {
            indiceSecArq[i]='S';
            indiceSecArq[i+1]='e';
            indiceSecArq[i+2]='c';
            indiceSecArq[i+3]='\0';
        }
    }
    //verifica se o arquivo existe
    FILE *fp1;
    fp1 = fopen (arq, "r");
    if (fp1 == NULL)
    {
       printf ("Houve um erro ao abrir o %s\n",arq);
       system("PAUSE");
       return;
    }
    FILE *fc1;
    fc1 = fopen (indiceArq, "r");
    while (fc1 == NULL)
    {
       printf ("Houve um erro ao abrir o indice de chaves primarias do arquivo %s\nvoce sera recirecionado para a criação de indices para criar um indice de chaves primarias.",arq);
       CriaIndiceParaArq(arq);
        fc1 = fopen (indiceArq, "r");
    }
    FILE *fs1;
    fs1 = fopen (indiceArq, "r");
    while (fs1 == NULL)
    {
       printf ("Houve um erro ao abrir o indice de chaves secundarias do arquivo %s\nvoce sera recirecionado para a criação de indices para criar um indice de chaves secundarias.",arq);
       CriaIndiceParaArq(arq);
        fs1 = fopen (indiceSecArq, "r");
    }
    z=0;
    n=0;
    i=0;
    char indiceArq2[27]="index";
    char indiceSecArq2[30];
    for(z=0;indiceArq2[z]!='\0';z++){};
    for(n=0;arq2[n]!='\0';n++)
    {
        indiceArq2[z+n]=arq2[n];
    }
    indiceArq2[z+n+1]='\0';
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(indiceArq2[i]!='\0')
    {

        indiceSecArq2[i]=indiceArq2[i];
        i++;
        if(indiceArq2[i]=='\0')
        {
            indiceSecArq2[i]='S';
            indiceSecArq2[i+1]='e';
            indiceSecArq2[i+2]='c';
            indiceSecArq2[i+3]='\0';
        }
    }
    FILE *fc2;
    fc2 = fopen (indiceArq, "r");
    while (fc2 == NULL)
    {
       printf ("Houve um erro ao abrir o indice de chaves primarias do arquivo %s\nvoce sera recirecionado para a criação de indices para criar um indice de chaves primarias.",arq2);
       CriaIndiceParaArq(arq2);
        fc2 = fopen (indiceArq2, "r");
    }
    FILE *fs2;
    fs2 = fopen (indiceArq2, "r");
    while (fs2 == NULL)
    {
       printf ("Houve um erro ao abrir o indice de chaves secundarias do arquivo %s\nvoce sera recirecionado para a criação de indices para criar um indice de chaves secundarias.",arq2);
       CriaIndiceParaArq(arq2);
        fs2 = fopen (indiceSecArq2, "r");
    }
    char uniao[20];
    printf("\ndigite o nome desejado para o novo arquivo de uniao\n obs:tamanho maximo 20 caracters\n obs2:nao usar espaços, acentos ou cedilha\n");
    scanf("%s",uniao);
    char indiceUniao[27]="index";
    char indiceSecUniao[30];
    //gera uma string chamada index que vai conter o nome do indice primario da lista
    z=0;
    n=0;
    i=0;
    for(z=0;indiceUniao[z]!='\0';z++){};
    for(n=0;uniao[n]!='\0';n++)
    {
        indiceUniao[z+n]=uniao[n];
    }
    indiceUniao[z+n+1]='\0';
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(indiceUniao[i]!='\0')
    {

        indiceSecUniao[i]=indiceUniao[i];
        i++;
        if(indiceUniao[i]=='\0')
        {
            indiceSecUniao[i]='S';
            indiceSecUniao[i+1]='e';
            indiceSecUniao[i+2]='c';
            indiceSecUniao[i+3]='\0';
        }
    }
};
void excluir(char arq[])
{
    int z=0;
    int n=0;
    int i=0;
    int escolha;
    char indiceArq[27]="index";
    char indiceSecArq[30];
    for(z=0;indiceArq[z]!='\0';z++){};
    for(n=0;arq[n]!='\0';n++)
    {
        indiceArq[z+n]=arq[n];
    }
    indiceArq[z+n+1]='\0';
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(indiceArq[i]!='\0')
    {

        indiceSecArq[i]=indiceArq[i];
        i++;
        if(indiceArq[i]=='\0')
        {
            indiceSecArq[i]='S';
            indiceSecArq[i+1]='e';
            indiceSecArq[i+2]='c';
            indiceSecArq[i+3]='\0';
        }
    }
    //verifica se o arquivo existe
    FILE *fp1;
    fp1 = fopen (arq, "r");
    if (fp1 == NULL)
    {
       printf ("Houve um erro ao abrir o %s\n",arq);
       system("PAUSE");
       return;
    }
    FILE *fc1;
    fc1 = fopen (indiceArq, "r");
    while (fc1 == NULL)
    {
       printf ("Houve um erro ao abrir o indice de chaves primarias do arquivo %s\nvoce sera recirecionado para a criação de indices para criar um indice de chaves primarias.",arq);
       CriaIndiceParaArq(arq);
        fc1 = fopen (indiceArq, "r");
    }
    FILE *fs1;
    fs1 = fopen (indiceArq, "r");
    while (fs1 == NULL)
    {
       printf ("Houve um erro ao abrir o indice de chaves secundarias do arquivo %s\nvoce sera recirecionado para a criação de indices para criar um indice de chaves secundarias.",arq);
       CriaIndiceParaArq(arq);
        fs1 = fopen (indiceSecArq, "r");
    }
    printf("digite 1 para excluir baseado na matricula\ndigite 2 para excluir baseado no nome");
    if(escolha==1)
    {

    }
    if(escolha==2)
    {

    }
};
