#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ordenaVetorIndices(char[][30],int[]);
void swap(char [][30], int , int,int[]);
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
//função de ordenar vetore  se strings
void ordenaVetorIndices(char v[][30],int* indices)
{
    int len = 0;
    int j;
    while(v[len][0]!='\0')
    {
        len++;
    }
    while(len>0)
    {
        for(j=0;j<len;j++)
        {
            if(compara(v[j],v[j+1])==1)
            {
                swap(v,j,j+1,indices);
            }
        }
        len--;
    }
}
int compara(char prim[30],char seg[30])
{
    int i=0;
    while(prim[i]==seg[i]&&i<30)
    {
        i++;
    }
    if(prim[i]>seg[i])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void swap(char v[][30], int j, int aposJ,int*indices)
{
    char aux[30];
    int aux2;
    int i=0;
    aux2=indices[j];
    indices[j]=indices[aposJ];
    indices[aposJ]=aux2;
    while(i<30)
    {
        aux[i]=v[j][i];
        v[j][i] = v[aposJ][i];
        v[aposJ][i] = aux[i];
        i++;
    }
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
        int aux[60];
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
            for(j=0;j<=i;j++)
            {
                aux[j]=j*63;
            }
            ordenaVetorIndices(chavePrimaria,aux);
        //este loop escreve todos as chaves da string e suas respectivas posições no arquivo de indices.
        printf("posicao do fim do arquivo:%i",aux[0]);
        fprintf(fs,"%d ",aux[0]);
            for(j=1;j<=i;j++)
            {
                printf("\nchave:");
                for(p=0;p<30;p++)
                {
                    printf("%c",chavePrimaria[j][p]);
                    fprintf(fs,"%c",chavePrimaria[j][p]);
                }
                printf(" posicao do primeiro char%d",aux[j]);
                fprintf(fs,"%d",aux[j]);
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
void unir(char arq1[],char arq2[])
{
    char uniao[30];
    printf("\ndigite o nome do arquivo gerado pela união:\nobs:sem caracteres especiais como acentos e espacos\n");
    scanf("%s",uniao);
    FILE *fp1;
    fp1 = fopen (arq1, "r");
    if (fp1 == NULL)
    {
       printf ("Houve um erro ao abrir o arquivo %s.\n",arq1);
       system("PAUSE");
       return;
    }
    char index1[30]="index";
    int z=0;
    int n=0;
    for(z=0;index1[z]!='\0';z++){};
    for(n=0;arq1[n]!='\0';n++)
    {
        index1[z+n]=arq1[n];
    }
    index1[z+n+1]='\0';
    int i=0;
    char index2[33];
    char indiceSecArq1Base[37];
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(index1[i]!='\0')
    {
        indiceSecArq1Base[i]=index1[i];
        index2[i]=index1[i];
        i++;
        if(index1[i]=='\0')
        {
            indiceSecArq1Base[i]='S';
            indiceSecArq1Base[i+1]='e';
            indiceSecArq1Base[i+2]='c';
            index2[i]='S';
            index2[i+1]='e';
            index2[i+2]='c';
            index2[i+3]='\0';
        }
    }
    indiceSecArq1Base[i+3]='B';
    indiceSecArq1Base[i+4]='a';
    indiceSecArq1Base[i+5]='s';
    indiceSecArq1Base[i+6]='e';
    indiceSecArq1Base[i+7]='\0';
    //cria o arquivo de indice
    FILE *fs1;
    fs1 = fopen (index2, "r");
    while(fs1==NULL)
    {
        printf("o arquivo %s não possui indice secundario\n voce sera redirecionado para fazer um arquivo de indices secundarios\n",arq1);
        CriaIndiceParaArq(arq1);
    }
    FILE *fsb1;
    fsb1 = fopen (indiceSecArq1Base, "r");
    FILE *fip1;
    fip1 = fopen (index2, "r");
    while(fip1==NULL)
    {
        printf("o arquivo %s não possui indice primario\n voce sera redirecionado para fazer um arquivo de indices primarios\n",arq1);
        CriaIndiceParaArq(arq1);
    }

    FILE *fp2;
    fp2 = fopen (arq2, "r");
    if (fp2 == NULL)
    {
       printf ("Houve um erro ao abrir o arquivo %s.\n",arq2);
       system("PAUSE");
       return;
    }
    char index12[30]="index";
    z=0;
    n=0;
    for(z=0;index12[z]!='\0';z++){};
    for(n=0;arq2[n]!='\0';n++)
    {
        index12[z+n]=arq2[n];
    }
    index12[z+n+1]='\0';
    i=0;
    char index22[33];
    char indiceSecArq2Base[37];
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(index12[i]!='\0')
    {
        indiceSecArq2Base[i]=index12[i];
        index22[i]=index12[i];
        i++;
        if(index12[i]=='\0')
        {
            indiceSecArq2Base[i]='S';
            indiceSecArq2Base[i+1]='e';
            indiceSecArq2Base[i+2]='c';
            index22[i]='S';
            index22[i+1]='e';
            index22[i+2]='c';
            index22[i+3]='\0';
        }
    }
    indiceSecArq2Base[i+3]='B';
    indiceSecArq2Base[i+4]='a';
    indiceSecArq2Base[i+5]='s';
    indiceSecArq2Base[i+6]='e';
    indiceSecArq2Base[i+7]='\0';
    //cria o arquivo de indice
    FILE *fs2;
    fs2 = fopen (index22, "r");
    while(fs2==NULL)
    {
        printf("o arquivo %s não possui indice secundario\n voce sera redirecionado para fazer um arquivo de indices secundarios\n",arq2);
        CriaIndiceParaArq(arq2);
    }
    FILE *fsb2;
    fsb2 = fopen (indiceSecArq2Base, "r");
    FILE *fip2;
    fip2 = fopen (index22, "r");
    while(fip2==NULL)
    {
        printf("o arquivo %s não possui indice primario\n voce sera redirecionado para fazer um arquivo de indices primarios\n",arq2);
        CriaIndiceParaArq(arq2);
    }

    FILE *fpu;
    fpu= fopen (uniao, "w");
    char indexu[30]="index";
    z=0;
    n=0;
    for(z=0;indexu[z]!='\0';z++){};
    for(n=0;uniao[n]!='\0';n++)
    {
        indexu[z+n]=uniao[n];
    }
    indexu[z+n+1]='\0';
    i=0;
    char indexu2[33];
    char indiceSecUniaoBase[37];
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(indexu[i]!='\0')
    {
        indiceSecUniaoBase[i]=indexu[i];
        indexu2[i]=indexu[i];
        i++;
        if(indexu[i]=='\0')
        {
            indiceSecUniaoBase[i]='S';
            indiceSecUniaoBase[i+1]='e';
            indiceSecUniaoBase[i+2]='c';
            indexu2[i]='S';
            indexu2[i+1]='e';
            indexu2[i+2]='c';
            indexu2[i+3]='\0';
        }
    }
    indiceSecUniaoBase[i+3]='B';
    indiceSecUniaoBase[i+4]='a';
    indiceSecUniaoBase[i+5]='s';
    indiceSecUniaoBase[i+6]='e';
    indiceSecUniaoBase[i+7]='\0';
    //cria o arquivo de indice
    FILE *fsu;
    fsu = fopen (indexu2, "w");
    FILE *fsbu;
    fsbu = fopen (indiceSecUniaoBase, "w");
    FILE *fipu;
    fipu = fopen (indexu2, "w");

};
void excluir(char arq1[])
{
    int escolha;
    FILE *fp1;
    fp1 = fopen (arq1, "r");
    if (fp1 == NULL)
    {
       printf ("Houve um erro ao abrir o arquivo %s.\n",arq1);
       system("PAUSE");
       return;
    }
    char index1[30]="index";
    int z=0;
    int n=0;
    for(z=0;index1[z]!='\0';z++){};
    for(n=0;arq1[n]!='\0';n++)
    {
        index1[z+n]=arq1[n];
    }
    index1[z+n+1]='\0';
    int i=0;
    char index2[33];
    char indiceSecArq1Base[37];
    //gera um indice secundario de nome "index"+(nome do arquivo)+"sec" onde o + representa concatenação de strings
    while(index1[i]!='\0')
    {
        indiceSecArq1Base[i]=index1[i];
        index2[i]=index1[i];
        i++;
        if(index1[i]=='\0')
        {
            indiceSecArq1Base[i]='S';
            indiceSecArq1Base[i+1]='e';
            indiceSecArq1Base[i+2]='c';
            index2[i]='S';
            index2[i+1]='e';
            index2[i+2]='c';
            index2[i+3]='\0';
        }
    }
    indiceSecArq1Base[i+3]='B';
    indiceSecArq1Base[i+4]='a';
    indiceSecArq1Base[i+5]='s';
    indiceSecArq1Base[i+6]='e';
    indiceSecArq1Base[i+7]='\0';
    //cria o arquivo de indice
    FILE *fs1;
    fs1 = fopen (index2, "r");
    while(fs1==NULL)
    {
        printf("o arquivo %s não possui indice secundario\n voce sera redirecionado para fazer um arquivo de indices secundarios\n",arq1);
        CriaIndiceParaArq(arq1);
    }
    FILE *fsb1;
    fsb1 = fopen (indiceSecArq1Base, "r");
    FILE *fip1;
    fip1 = fopen (index2, "r");
    while(fip1==NULL)
    {
        printf("o arquivo %s não possui indice primario\n voce sera redirecionado para fazer um arquivo de indices primarios\n",arq1);
        CriaIndiceParaArq(arq1);
    }
    printf("digite 1 para excluir baseado na matricula\ndigite 2 para excluir baseado no nome");
    scanf("%i",&escolha);
    if(escolha==1)
    {

    }
    if(escolha==2)
    {

    }
};
