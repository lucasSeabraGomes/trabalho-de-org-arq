#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ordenaVetorIndices(char[][30],int[]);
int compara(char[],char[]);
void swap(char [][30], int , int,int[]);
void CriaIndiceParaArq(char[]);
void unir(char[],char[]);
void excluir(char[],char[6]);
void incluir(char[],char[]);
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
        printf("digite 4 incluir um registro;\n");
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
            printf("\nescreva o nome dos arquivos para uni-los\n no formato arq1 \"espaco\"arq2\nou arq1\"enter\"arq2\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            scanf("%s",nomeArq2);
            unir(nomeArq,nomeArq2);
        }
        if(escolha==3)
        {
            char matricula[6];
            //abre a função de criar arquivo com nome digitado com parametro
            //observação o arquivo deve estar na mesma pasta do binario
            printf("\nescreva o nome do arquivo de onde será excluido o regitro\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            printf("\ndigite a matricula:\n");
            scanf("%s",matricula);
            excluir(nomeArq,matricula);
        }
        if(escolha==4)
        {
            char elemento[64];
            char aux [40];
            int i;
            int j;
            printf("\ndigite a matricula:\nobs deve ter 6 caractere numericos\n");
            scanf("%s",aux);
            getchar();
            for(i=0;i<6;i++)
            {
                elemento[i]=aux[i];
            }
            elemento[i]=' ';
            i++;
            printf("\ndigite o nome do aluno:\nobs deve ter no maximo 40 caracteres\n");
            scanf("%[^\n]s",aux);
            getchar();
            for(j=0;aux[j]!='\0';j++)
            {
                elemento[i+j]=aux[j];
            }
            while(j<41)
            {
                elemento[i+j]=' ';
                j++;
            }
            i=i+j;
            printf("\ndigite a opcao do aluno:\nobs deve ter exatamente 2 caracteres numericos\n");
            scanf("%s",aux);
            elemento[i]=aux[0];
            i++;
            elemento[i]=aux[1];
            i++;
            elemento[i]=' ';
            i++;
            elemento[i]=' ';
            i++;
            printf("\ndigite o curso do aluno:\nobs deve ter exatamente 2 caracteres\n");
            scanf("%s",aux);
            elemento[i]=aux[0];
            i++;
            elemento[i]=aux[1];
            i++;
            for(j=0;j<7;j++)
            {
                elemento[i]=' ';
                i=i+1;
            }
            printf("\ndigite a turma do aluno:\nobs deve ter exatamente 1 caracter\n");
            scanf("%s",aux);
            elemento[i]=aux[0];
            i++;
            elemento[i]='\n';
            printf("\nescreva o nome do arquivo de onde será excluido o regitro\nobs:arquivos de texto sempre terminam em .txt mesmo nao explicito\n");
            scanf("%s",nomeArq);
            incluir(nomeArq,elemento);
            CriaIndicePrimario(nomeArq);
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
int compara(char prim[],char seg[])
{
    int i=0;
    while(prim[i]==seg[i] && prim[i]!='\0' && seg[i]!='\0')
    {
        i++;
    }
    if(prim[i]>seg[i])
    {
        return 1;
    }
    if(seg[i]>prim[i])
    {
        return -1;
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
    char index[30]="index\0";
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
        fs = fopen (index, "w+b");
        fread(chavePrimaria[0],sizeof(char),30,fp);
        chavePrimaria[0][30]='\0';
        i=1;
        //este  loop garante que todos os elementos da lista original estarão na lista de chaves
        //loop que coloca apenas um numero x de elementos na memoria ram no caso o numero foi 60 mas pode ser aumentado de acordo com a disponibilidade de ram no computador
        while(feof(fp) == 0)
        {
            fseek(fp,(34*sizeof(char)),SEEK_CUR);
            fread(chavePrimaria[i],sizeof(char),30,fp);
            chavePrimaria[i][30]='\0';
            i++;
        }
        for(j=0;j<=i;j++)
        {
            aux[j]=j*64;
        }
        chavePrimaria[j-2][0]='\0';
        ordenaVetorIndices(chavePrimaria,aux);
        //este loop escreve todos as chaves da string e suas respectivas posições no arquivo de indices.
        printf("posicao do fim do arquivo:%i",aux[j-2]);

        fwrite(&aux[j-1],sizeof(int),1,fs);
            for(j=1;j<=i-1;j++)
            {
                printf("\nchave:");
                for(p=0;p<30;p++)
                {
                    printf("%c",chavePrimaria[j][p]);
                    fwrite(&chavePrimaria[j][p],sizeof(char),1,fs);
                }
                printf(" posicao do primeiro char%d\n",aux[j]);
                fwrite(&aux[j],sizeof(char),4,fs);
            }
        system("PAUSE");
        fclose(fs);
        fclose(fp);
    }
    //neste if serão criados indices de chaves secundarias
    else if(tipo==2)
    {
        int p;
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
        fs = fopen (index2, "w+b");
        FILE *fsb;
        fsb = fopen (indiceSecArqBase, "w+b");
        struct indiceSec colocar[10];
        //loop para inicializae a estrutura do indice como \0 na coluna de curso
        while(i<10)
        {
            j=0;
            colocar[i].campo[0]='\0';
            colocar[i].campo[2]='\0';
            while(j<60)
            {
                for(p=0;p<60;p++)
                {
                    colocar[i].indice[p][0]='\0';
                    colocar[i].indice[p][30]='\0';
                }
                j++;
            }
            i++;
        }
        //adiciona o primeiro elemento ao vetor de estruturas chaves secundarias.
        fread(colocar[0].indice[0],sizeof(char),30,fp);
        colocar[0].indice[0][30]='\0';
        fseek(fp,sizeof(char)*22,SEEK_CUR);
        fread(colocar[0].campo,sizeof(char),2,fp);
        colocar[0].campo[2]='\0';
        char novo[30];
        while((feof(fp) == 0))
        {
            fseek(fp,sizeof(char)*10,SEEK_CUR);
            fread(novo,sizeof(char),30,fp);
            novo[30]='\0';
            fseek(fp,sizeof(char)*22,SEEK_CUR);
            fread(aux2,sizeof(char),2,fp);
            aux2[2]='\0';
            z=0;
            while(colocar[z].campo[0]!='\0')
            {
                cont=0;
                j=0;
                while(aux2[j]!='\0')
                {
                    if(aux2[j]!=colocar[z].campo[j])
                    {
                        cont++;
                    }
                    j++;
                }
                if(cont==0)
                {
                    j=0;
                    while(colocar[z].indice[j][0]!='\0')
                    {
                        j++;
                    }
                    i=0;
                    while(i<30)
                    {
                        colocar[z].indice[j][i]=novo[i];
                        i++;
                    }
                    break;
                }
                z++;
            }
            if(cont!=0)
            {
                j=0;
                while(j<3)
                {
                    colocar[z].campo[j]=aux2[j];
                    j++;
                }
                i=0;
                while(i<30)
                {
                    colocar[z].indice[0][i]=novo[i];
                    i++;
                }
            }
        }
        i=0;
        cont=0;
        while(colocar[i].campo[0]!='\0')
        {
            z=0;
            printf("\nCurso\n");
            while(z<2)
            {
                fwrite(&colocar[i].campo[z],sizeof(char),1,fsb);
                printf("%c",colocar[i].campo[z]);
                z++;
            }
            printf("\nalunos\n");
            z=0;
            while(z<30)
            {
                fwrite(&colocar[i].indice[0][z],sizeof(char),1,fsb);
                printf("%c",colocar[i].indice[0][z]);
                z++;
            }
            if(colocar[i].indice[1][0]!=0)
            {
                fwrite(&cont,sizeof(char),4,fsb);
                printf("posicao do proximo no arquivo:%i\n",cont);
            }
            else
            {
                p=-1;
                fwrite(&p,sizeof(char),4,fsb);
                printf("nao existem mais alunos deste curso");
            }
            j=1;
            while(colocar[i].indice[j][0]!=0)
            {
                z=0;
                while(z<30)
                {
                    fwrite(&colocar[i].indice[j][z],sizeof(char),1,fs);
                    printf("%c",colocar[i].indice[j][z]);
                    z++;
                }
                cont=cont+34;
                if(colocar[i].indice[j+1][0]!=0)
                {
                    fwrite(&cont,sizeof(char),4,fs);
                    printf("posicao do proximo no arquivo:%i\n",cont);
                }
                else
                {
                    p=-1;
                    fwrite(&p,sizeof(char),4,fs);
                    printf("nao existem mais alunos deste curso");
                }
                j++;
            }
            i++;
        }
        fclose(fsb);
        fclose(fs);
        fclose(fp);
    }

    //caso de digitarm um valor invalido no menu
    else
    {
        printf("pedido invalido");
        return;
    }
};
void unir(char nomeArq[],char nomeArq2[])
{
    char nomeArk12[30];
    printf("\ndigite o nome do arquivo gerado pela união:\nobs:sem caracteres especiais como acentos e espacos\n");
    scanf("%s",nomeArk12);
    FILE *fp;
    fp = fopen (nomeArq, "r");
    if (fp == NULL) {
       printf ("Houve um erro ao abrir o arquivo solicitado.\n");
       system("PAUSE");
       return;
    }
    //gera uma string chamada index que vai conter o nome do indice primario da lista
    char index[30]="index\0";
    int z=0;
    int n=0;
    for(z=0;index[z]!='\0';z++){};
    for(n=0;nomeArq[n]!='\0';n++)
    {
        index[z+n]=nomeArq[n];
    }
    index[z+n+1]='\0';
    FILE *fs;
    fs = fopen (index, "r+b");
    FILE *fp2;
    fp2 = fopen (nomeArq, "r");
    if (fp2 == NULL) {
       printf ("Houve um erro ao abrir o arquivo solicitado.\n");
       system("PAUSE");
       return;
    }
    //gera uma string chamada index que vai conter o nome do indice primario da lista
    char index2[30]="index\0";
    z=0;
    n=0;
    for(z=0;index2[z]!='\0';z++){};
    for(n=0;nomeArq2[n]!='\0';n++)
    {
        index2[z+n]=nomeArq2[n];
    }
    index[z+n+1]='\0';
    FILE *fs2;
    fs2 = fopen (index2, "r+b");
    char chave[60][30];
    int indice[60];
    char chave2[60][30];
    int indice2[60];
    for(z=0;z<60;z++)
    {
        chave[z][0]='\0';
        chave2[z][0]='\0';
    }
    z=0;
    fseek(fs,sizeof(char)*4,SEEK_SET);
    while(feof(fs) == 0)
    {
        fread(chave[z],sizeof(char),30,fs);
        chave[z][30]='\0';
        fread(&indice[z],sizeof(char),4,fs);
        z++;
    }
    z=0;
    fseek(fs2,sizeof(char)*4,SEEK_SET);
    while(feof(fs2) == 0)
    {
        fread(chave2[z],sizeof(char),30,fs2);
        chave2[z][30]='\0';
        fread(&indice2[z],sizeof(char),4,fs2);
        z++;
    }
    n=0;
    z=0;
    char aux[64];
    FILE *fu;
    fu = fopen (nomeArk12, "w");
    printf("Arquivo gerado");
    while(z<60||n<60)
    {
        /*o primeiro caacter de um indice neste programa sempre é parte de uma matricula que por sua vez sempre é um numerico a menos que o indice tenha sido excluido ou corrompido assim são ignorados estes casos com estes 2 loops*/
        while(chave[n][0]!='1'&&chave[n][0]!='2'&&chave[n][0]!='3'&&chave[n][0]!='4'&&chave[n][0]!='5'&&chave[n][0]!='6'&&chave[n][0]!='7'&&chave[n][0]!='8'&&chave[n][0]!='9'&&chave[n][0]!='0'&&n<60)
        {
            n++;
        }
        while(chave2[z][0]!='1'&&chave2[z][0]!='2'&&chave2[z][0]!='3'&&chave2[z][0]!='4'&&chave2[z][0]!='5'&&chave2[z][0]!='6'&&chave2[z][0]!='7'&&chave2[z][0]!='8'&&chave2[z][0]!='9'&&chave2[z][0]!='0'&&z<60)
        {
            z++;
        }
        if(compara(chave[n],chave2[z])==1)
        {
            fseek(fp,sizeof(char)*indice[n],SEEK_SET);
            fread(aux,sizeof(char),64,fp);
            aux[64]='\0';
            printf("\n%s\n",aux);
            fwrite(aux,sizeof(char),63,fu);
            n++;
        }
        else if(compara(chave[n],chave2[z])==-1)
        {
            fseek(fp2,sizeof(char)*indice2[z],SEEK_SET);
            fread(aux,sizeof(char),64,fp2);
            aux[64]='\0';
            printf("\n%s\n",aux);
            fwrite(aux,sizeof(char),63,fu);
            z++;
        }
        else if(compara(chave[n],chave2[z])==0)
        {
            fseek(fp,sizeof(char)*indice[n],SEEK_SET);
            fread(aux,sizeof(char),64,fp);
            aux[64]='\0';
            printf("\n%s\n",aux);
            fwrite(aux,sizeof(char),63,fu);
            n++;
            z++;
        }
    }
    fclose(fu);
};
void excluir(char arq1[],char matricula[6])
{
    FILE *fp1;
    fp1=fopen(arq1,"r");
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
    fs1 = fopen (index2, "r+b");
    while(fs1==NULL)
    {
        printf("o arquivo %s não possui indice secundario\n voce sera redirecionado para fazer um arquivo de indices secundarios\n",arq1);
        CriaIndiceParaArq(arq1);
        fs1 = fopen (index2, "r+b");
    }
    FILE *fsb1;
    fsb1 = fopen (indiceSecArq1Base, "r+b");
    FILE *fip1;
    fip1 = fopen (index1, "r+b");
    while(fip1==NULL)
    {
        printf("o arquivo %s não possui indice primario\n voce sera redirecionado para fazer um arquivo de indices primarios\n",arq1);
        CriaIndiceParaArq(arq1);
        fip1 = fopen (index1, "r+b");
    }
        char aux[7];
        int aux2;
        int aux3=0;
        int cont=1;
        fread(&aux2,sizeof(int),1,fip1);
        //aux 2 é o numero de elementos no arquivo de indices
        aux2=(int)(aux2/64);
        while(aux3!=aux2&&cont!=0)
        {
            cont=0;
            aux3++;
            fseek(fip1,(sizeof(char)*4)*(aux3)+(sizeof(char)*30*(aux3-1)),SEEK_SET);
            fread(aux,sizeof(char),6,fip1);
            aux[6]='\0';
            for(i=0;i<6;i++)
            {
                if(aux[i]!=matricula[i])
                {
                    cont++;
                }
            }
        }
        if(compara(matricula,aux)==0)
        {
            fseek(fip1,(sizeof(char)*4)*(aux3)+(sizeof(char)*30*(aux3-1)),SEEK_SET);
            fread(aux,sizeof(char),6,fip1);
            aux[6]='\0';
            int lugar;
            fseek(fip1,(sizeof(char)*4)*(aux3)+(sizeof(char)*30*(aux3)),SEEK_SET);
            fread(&lugar,sizeof(char),4,fip1);
            fseek(fp1,sizeof(char)*(lugar),SEEK_SET);
            char elem[64];
            fread(elem,sizeof(char),64,fp1);
            elem[64]='\0';
            printf("realmente deseja excluir o registro:%s\ndigite 1 para sim",elem);
            scanf("%d",&i);
            if(i==1)
            {
                int cont=1;
                char curso[2];
                int tenta;
                char teste[6];
                while(feof(fsb1)==0&&cont!=0)
                {
                    cont=0;
                    fread(curso,sizeof(char),2,fsb1);
                    fseek(fsb1,30,SEEK_CUR);
                    fread(&tenta,sizeof(char),4,fsb1);
                    for(i=0;i<2;i++)
                    {
                        if(curso[i]!=elem[i+52])
                        {
                            cont++;
                        }
                    }
                }
                fseek(fsb1,-34*sizeof(char),SEEK_CUR);
                fread(teste,sizeof(char),6,fsb1);
                for(i=0;i<6;i++)
                {
                    if(curso[i]!=matricula[i])
                    {
                        cont++;
                    }
                }
                if(cont==0)
                {
                    fseek(fsb1,-6*sizeof(char),SEEK_CUR);
                    char t=' ';
                    for(i=0;i<30;i++)
                    {

                    }
                }
            }
            system("PAUSE");
        }
        else
        {
            printf("nao existe registro com esta matricula");
            system("PAUSE");
        }
};
void atualizar(char arq1[],char matricula[6])
{
}
void incluir(char arq1[],char elemento[64])
{
    FILE *fp;
    fp = fopen (arq1, "r+b");
    fseek(fp,0,SEEK_END);
    fwrite(elemento,sizeof(char),64,fp);
    printf("novo indice de chaves primarias:");
    fclose(fp);
}
void CriaIndicePrimario(char nomeArq[])
{
    FILE *fp;
    fp = fopen (nomeArq, "r");
    if (fp == NULL) {
       printf ("Houve um erro ao abrir o arquivo solicitado.\n");
       system("PAUSE");
       return;
    }
    //gera uma string chamada index que vai conter o nome do indice primario da lista
    char index[30]="index\0";
    int z=0;
    int n=0;
    for(z=0;index[z]!='\0';z++){};
    for(n=0;nomeArq[n]!='\0';n++)
    {
        index[z+n]=nomeArq[n];
    }
    index[z+n+1]='\0';
    int p;
        int i=0;
        int j;
        int aux[60];
        char chavePrimaria[60][30];
        //abre pu cria um arquivo de indice primario para escrita
        FILE *fs;
        fs = fopen (index, "w+b");
        fread(chavePrimaria[0],sizeof(char),30,fp);
        chavePrimaria[0][30]='\0';
        i=1;
        //este  loop garante que todos os elementos da lista original estarão na lista de chaves
        //loop que coloca apenas um numero x de elementos na memoria ram no caso o numero foi 60 mas pode ser aumentado de acordo com a disponibilidade de ram no computador
        while(feof(fp) == 0)
        {
            fseek(fp,(34*sizeof(char)),SEEK_CUR);
            fread(chavePrimaria[i],sizeof(char),30,fp);
            chavePrimaria[i][30]='\0';
            i++;
        }
        for(j=0;j<=i;j++)
        {
            aux[j]=j*64;
        }
        chavePrimaria[j-2][0]='\0';
        ordenaVetorIndices(chavePrimaria,aux);
        //este loop escreve todos as chaves da string e suas respectivas posições no arquivo de indices.
        printf("posicao do fim do arquivo:%i",aux[j-2]);

        fwrite(&aux[j-1],sizeof(int),1,fs);
            for(j=1;j<=i-1;j++)
            {
                printf("\nchave:");
                for(p=0;p<30;p++)
                {
                    printf("%c",chavePrimaria[j][p]);
                    fwrite(&chavePrimaria[j][p],sizeof(char),1,fs);
                }
                printf(" posicao do primeiro char%d\n",aux[j]);
                fwrite(&aux[j],sizeof(char),4,fs);
            }
        system("PAUSE");
        fclose(fs);
        fclose(fp);
}
