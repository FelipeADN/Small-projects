#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pixel{
    unsigned char R, G, B;
    int passou;
};

struct posicao{
    int i;
    int j;
};

struct node{
    struct posicao *pos;
    struct node *prox;
};

//compara dois pixels
int comparaPixel(struct pixel p1, struct pixel p2){
    if (p1.R == p2.R)
        if (p1.G == p2.G)
            if (p1.B == p2.B)
                return 1; //eh igual
    return 0;//eh diferente
}

//abre arquivo e testa se eh ppm
FILE* abrePPM(char* nome){
    //le o arquivo
    FILE* arquivo = fopen(nome, "rb");
    if (arquivo == NULL){
        printf("Erro ao ler arquivo");
        return NULL;
    }

    //testa se eh ppm
    char tipo[3];
    char teste[] = "P6";
    fscanf(arquivo, "%s", tipo);
    if (strcmp(tipo, teste) != 0){
        printf("Arquivo deve ser de tipo ppm");
        return NULL;
    }
    return arquivo;
}

//le a imagem
void lerImagem(FILE* arquivo, int *x, int *y, struct pixel imagem[*x][*y]){
    fscanf(arquivo,"%*d %*d");

    unsigned char *buffer = malloc(*x * *y * 3);//aloca espaco para a imagem
    if (buffer == NULL){
        printf("ERRO NO MALLOC");
        exit(0);
    }

    if (fread(buffer, 1, (*x) * (*y) * 3, arquivo) != (*x) * (*y) * 3){//le a imagem para o buffer
        printf("ERRO NO FREAD");
        exit(0);
    }

    fclose(arquivo);

    //coloca os valores do buffer na estrutura de pixels
    int cont = 0;
    for (int i = 0; i < *x; i++){
        for (int j = 0; j < *y; j++){
            imagem[i][j].R = buffer[cont];
            cont++;
            imagem[i][j].G = buffer[cont];
            cont++;
            imagem[i][j].B = buffer[cont];
            cont++;
            imagem[i][j].passou = 0;
        }
    }

    free(buffer);
}

//Remove o valor do topo da lista e retorna o novo topo
struct posicao *pop(struct node **lista){
    if ((*lista)->prox != NULL){ //remocao normal do topo da lista
        struct node *temp = *lista;
        (*lista) = (*lista)->prox;
        free(temp->pos);
        free(temp);
        return (*lista)->pos;
    }
    else{//ultima remocao
        struct node *temp = *lista;
        (*lista) = NULL;
        free(temp->pos);
        free(temp);
        return NULL;
    }
}

//Adiciona um valor no topo da lista
void push(struct node **lista, int i, int j){
    if (*lista == NULL){//primeira adicao na lista
        struct node *novoNode = malloc(sizeof(struct node)); //aloca espaco para o novo node
        struct posicao *novoPos = malloc(sizeof(struct posicao)); //aloca espaco para a posicao
        if (novoNode == NULL || novoPos == NULL){
            printf("\nERRO NO MALLOC\n");
            exit(0);
        }
        novoPos->i = i;
        novoPos->j = j;
        novoNode->pos = novoPos;
        novoNode->prox = NULL;
        *lista = novoNode;
    }
    else{//adicao normal a lista
        struct node *novoNode = malloc(sizeof(struct node));
        struct posicao *novoPos = malloc(sizeof(struct posicao));
        if (novoNode == NULL || novoPos == NULL){
            printf("\nERRO NO MALLOC\n");
            exit(0);
        }
        novoPos->i = i;
        novoPos->j = j;
        novoNode->pos = novoPos;
        novoNode->prox = *lista;
        *lista = novoNode;
    }
}

//Passa por todo o objeto e o conta
void contaObjeto(struct node **lista, int i, int j, int x, int y, struct pixel imagem[x][y], int *cont){
    imagem[i][j].passou = *cont;
    push(lista, i, j);

    int testando = 1;
    while (testando == 1){
        while (i+1 < x && imagem[i+1][j].passou == 0 && comparaPixel(imagem[i+1][j], imagem[0][0]) != 1){//baixo
            imagem[i+1][j].passou = *cont;
            i++;
            push(lista, i, j);  
        }
        while (j+1 < y && imagem[i][j+1].passou == 0 && comparaPixel(imagem[i][j+1], imagem[0][0]) != 1){//direita
            imagem[i][j+1].passou = *cont;
            j++;
            push(lista, i, j);
        }
        while (i > 0 && imagem[i-1][j].passou == 0 && comparaPixel(imagem[i-1][j], imagem[0][0]) != 1){//cima
            imagem[i-1][j].passou = *cont;
            i--;
            push(lista, i, j);
        }
        while (j > 0 && imagem[i][j-1].passou == 0 && comparaPixel(imagem[i][j-1], imagem[0][0]) != 1){//esquerda
            imagem[i][j-1].passou = *cont;
            j--;
            push(lista, i, j);
        }
        if ((i+1 >= x || imagem[i+1][j].passou != 0 || comparaPixel(imagem[i+1][j], imagem[0][0]) == 1) && 
            (i   <= 0 || imagem[i-1][j].passou != 0 || comparaPixel(imagem[i-1][j], imagem[0][0]) == 1) &&
            (j+1 >= y || imagem[i][j+1].passou != 0 || comparaPixel(imagem[i][j+1], imagem[0][0]) == 1) &&
            (j   <= 0 || imagem[i][j-1].passou != 0 || comparaPixel(imagem[i][j-1], imagem[0][0]) == 1)){ //testa se ainda tem para onde ir
            struct posicao *pos = pop(lista); //remove topo da lista
            if (pos == NULL) //se tiver acabado a lista, finaliza essa contagem
                testando = 0;
            else{//pega o novo topo da lista para testar todos seus possiveis movimentos
                i = pos->i;
                j = pos->j;
            }
        }
    }
    *cont += 1;
}

//mostra a imagem com 0 e o numero do objeto
void mostrarImagem(struct node **lista, int *x, int *y, struct pixel imagem[*x][*y], int *cont){
    for (int i = 0; i<*x; i++){
        for (int j = 0; j<*y; j++){
            if (comparaPixel(imagem[i][j], imagem[0][0]) == 1){//pixel igual o fundo
                printf("0");
            }
            else{
                if(imagem[i][j].passou == 0){ // nao passou pelo pixel
                    contaObjeto(lista, i, j, *x, *y, imagem, cont);
                }
                printf("%d", imagem[i][j].passou);
            }
        }
        printf("\n");
    }
}

//apenas conta os objetos
void contaImagem(struct node **lista, int *x, int *y, struct pixel imagem[*x][*y], int *cont){
    for (int i = 0; i<*x; i++){
        for (int j = 0; j<*y; j++){
            if (comparaPixel(imagem[i][j], imagem[0][0]) != 1 && imagem[i][j].passou == 0)//igual o fundo ou ja passou
                contaObjeto(lista, i, j, *x, *y, imagem, cont);//conta o objeto
        }
    }
}

void main(){
    // aloca e le o nome
    char* nome = malloc(20 * sizeof(char));
    printf("Nome ou caminho do arquivo:");
    scanf("%s", nome);

    //abre e testa arquivo
    FILE* arquivo = abrePPM(nome);
    if (!arquivo)
        exit(0);
    
    free(nome); //libera a memoria do nome

    //aloca e le as coordenadas
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));
    fscanf(arquivo, "%d %d", y, x);

    struct node **lista = malloc(sizeof(struct node*));
    if (lista == NULL){
        printf("ERRO NO MALLOC");
        exit(0);
    }
    *lista = NULL;
   

    struct pixel (*imagem)[*y] = malloc(sizeof(struct pixel[*x][*y]));//aloca a matriz da imagem
    if (imagem == NULL){
        printf("ERRO NO MALLOC");
        exit(0);
    }


    lerImagem(arquivo, x, y, imagem);//le a imagem do arquivo

    int *cont = malloc(sizeof(int));
    *cont = 1;

    mostrarImagem(lista, x, y, imagem, cont);//mostra a imagem
    // contaImagem(lista, x, y, imagem, cont);

    printf("\nQuantidade de objetos = %d\n", *cont-1);

    free((*lista));
    free(imagem);
    free(lista);
    free(x);
    free(y);
    free(cont);
}