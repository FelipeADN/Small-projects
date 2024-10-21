#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;  //valor do no
    struct no *esq, *dir, *pai; //ponteiros conectados a este no
} no_t;

no_t *criaNo (int chave){
    no_t *no = malloc (sizeof (no_t)); //aloca espaco do no(valor e ponteiros)

    //atribui os valores
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
    return no;
}

//calcula a altura
int altura(no_t *no){
    if (no != NULL){
        //percorre a arvore
        int esquerda = altura(no->esq);
        int direita = altura(no->dir);

        //retorna quem tem a maior altura
        if (esquerda>direita){
            return 1 + esquerda;
        }
        return 1 + direita;
    }
    return -1; //quando achar um nulo, sua altura eh -1
}

int fatorBalanceamento(no_t *no){
    if (no != NULL){
        int esquerda = altura(no->esq);//altura na esq
        int direita = altura(no->dir);//altura na dir
        return (esquerda-direita); //fator de balanceamento eh a diferenca das alturas
    }
    return 0;//fator de um no nulo eh 0
}

no_t *rotEsquerda(no_t *p){
    no_t *q = p->dir; //guarda o filho da direita
    p->dir = q->esq; //nova direita do p, é a esquerda do filho da direita(q)
    q->pai = p->pai; //o filho da direita(q) substitui a posicao do no original(p)
    if (q->pai != NULL){ //arruma o pai de q
        if (q->chave < q->pai->chave) //se q eh filho da esquerda
            q->pai->esq = q;
        else            //se q eh filho da direita
            q->pai->dir = q;  
    }
    p->pai = q; //pai do original(p) é o antigo filho da direita(q)
    if (q->esq != NULL) //se tem alguem na esquerda do filho da direita(q), ele passa a ser o filho da direita de p
        q->esq->pai = p;
    
    q->esq = p; //esquerda do antigo filho da direita(q), passa a ser o original(p)
    return q;
}

no_t *rotDireita(no_t *p){
    no_t *q = p->esq; //guarda o filho da esquerda
    p->esq = q->dir; //nova esquerda do p, é a direita do filho da esquerda(q)
    q->pai = p->pai; //o filho da esquerda(q) substitui a posicao do no original(p)
    if (q->pai != NULL){ //arruma o pai de q
        if (q->chave < q->pai->chave) //se q eh filho da esquerda
            q->pai->esq = q;
        else            //se q eh filho da direita
            q->pai->dir = q;  
    }
    p->pai = q; //pai do original(p) é o antigo filho da esquerda(q)
    if (q->dir != NULL) //se tem alguem na direita do filho da esquerda(q), ele passa a ser o filho da esquerda de p
        q->dir->pai = p;
    
    q->dir = p; //direita do antigo filho da esquerda(q), passa a ser o original(p)
    return q;
}

no_t *rot2Direita(no_t *p){//rotaciona filho pra esquerda, depois chama rotacao normal pra direita
    no_t *p1 = p->esq; //filho da esquerda
    no_t *q = p1->dir; //guarda o filho da direita
    p1->dir = q->esq; //nova direita do p, é a esquerda do filho da direita(q)
    q->pai = p1->pai; //o filho da direita(q) substitui a posicao do no original(p)
    if (q->pai != NULL){ //arruma o pai de q
        if (q->chave < q->pai->chave) //se q eh filho da esquerda
            q->pai->esq = q;
        else            //se q eh filho da direita
            q->pai->dir = q;  
    }
    p1->pai = q; //pai do original(p) é o antigo filho da direita(q)
    if (q->esq != NULL) //se tem alguem na esquerda do filho da direita(q), ele passa a ser o filho da direita de p
        q->esq->pai = p1;
    q->esq = p1; //esquerda do antigo filho da direita(q), passa a ser o original(p)
    rotDireita(p);
}

no_t *rot2Esquerda(no_t *p){//rotaciona filho pra direita, depois chama rotacao normal pra esquerda
    no_t *p1 = p->esq; //filho da direita
    no_t *q = p->esq; //guarda o filho da esquerda
    p->esq = q->dir; //nova esquerda do p, é a direita do filho da esquerda(q)
    q->pai = p->pai; //o filho da esquerda(q) substitui a posicao do no original(p)
    if (q->pai != NULL){ //arruma o pai de q
        if (q->chave < q->pai->chave) //se q eh filho da esquerda
            q->pai->esq = q;
        else            //se q eh filho da direita
            q->pai->dir = q;  
    }
    p->pai = q; //pai do original(p) é o antigo filho da esquerda(q)
    if (q->dir != NULL) //se tem alguem na direita do filho da esquerda(q), ele passa a ser o filho da esquerda de p
        q->dir->pai = p;
    
    q->dir = p; //direita do antigo filho da esquerda(q), passa a ser o original(p)
    return q;
    rotEsquerda(p);
}

void balancearAux(no_t *no){
        int fatorPai = fatorBalanceamento(no->pai);//calcula o fator para saber se tem que balancear
    if (fatorPai == 2 && fatorBalanceamento(no->pai->esq) == -1){//se o pai tem fator 2 e a esquerda -1, tem que rotacionar o filho pra esquerda, depois a raiz pra direita
        rot2Direita(no->pai);
    }
    else if (fatorPai == -2 && fatorBalanceamento(no->pai->dir) == 1){//rotaciona filho pra direita, depois raiz pra esquerda
        rot2Esquerda(no->pai);
    }
    else if (fatorPai == -2){//pai tem fator -2, rotacao para a esquerda
        rotEsquerda(no->pai);
    }
    else if (fatorPai == 2){//pai tem fator 2, rotacao para a direita
        rotDireita(no->pai);
    }
    else if(fatorBalanceamento(no->dir) == 2 || fatorBalanceamento(no->esq) == 2){//no tem o fator 2, rotacao para a direita no filho
        rotDireita(no);
    }
    else if(fatorBalanceamento(no->dir) == -2 || fatorBalanceamento(no->esq) == -2){//no tem o fator -2, rotacao para a esquerda no filho
        rotEsquerda(no);
    }
}

no_t *balancear(no_t *no){//garante que vai balancear ate a raiz, e que vai retornar o node da raiz
    if (no->pai != NULL){
        while (no->pai != NULL){
            balancearAux(no);
            if (no->pai != NULL){
                no = no->pai;
            }
        }
    }
    return no;
}

no_t *incluiAux (no_t *no, int c, no_t **local){
    if (no == NULL){ //se o no atual é nulo, cria o no com valor c
        *local = criaNo(c);
        return *local;
    }
    if(c < no->chave){ //se for menor que o atual
        no->esq = incluiAux(no->esq, c, local); //desce um para a esquerda
        no->esq->pai = no; //depois de chegar no final atribui o pai dos nos
    }
    else{
        no->dir = incluiAux(no->dir, c, local); //desce para a direita por ser maior ou igual
        no->dir->pai = no;
    }
    return no;
}

no_t *inclui(no_t *no, int c){
    no_t **local = malloc (sizeof(local)); //ponteiro que guarda a localizacao onde vai ocorrer o balanceamento
    incluiAux(no, c, local); //inclui
    no = balancear((*local)->pai); //balanceia, e retorna a raiz
    free (local);
    return no;
}

no_t *busca(no_t *no, int chave){
    if (no == NULL) //nao encontrado retorna null
        return NULL;
    if (no->chave == chave) //encontrou, retorna o no
        return no;
    if (chave < no->chave) //menor vai para a esquerda
        return busca(no->esq, chave);
    else                    //maior ou igual vai para a direita
        return busca(no->dir, chave);
}

no_t *min(no_t *no){
    if (no->esq == NULL)//nao tem mais esquerda, retorna o no atual
        return no;
    else
        return min(no->esq);//se nao, desce mais para a esquerda ate o fim
}

no_t *max(no_t *no){
    if (no->dir == NULL)//nao tem mais direita, retorna o no atual
        return no;
    else
        return max(no->dir);//se nao, desce mais para a direita ate o fim
}

void ajustaNoPai(no_t *no, no_t *novo){
    if (no->pai != NULL) { // se no pai eh nulo
        if (no->pai->esq == no) //se no eh o filho da esquerda
            no->pai->esq = novo; //no passa a ser o novo
        else                      //eh o filho da direita
            no->pai->dir = novo; //no passa a ser o novo
        if (novo != NULL) //se novo existe
            novo->pai = no->pai; //o no, e o novo tem o mesmo pai
    }
}   

no_t *sucessor(no_t *no){
    return min(no->dir); //menor valor da direita do no
}

no_t *antecessor(no_t *no){
    return max(no->esq); //maior valor da esquerda do no
}

no_t *exclui (no_t *no, no_t *raiz) {
    no_t *antecess, *local, *novaRaiz = raiz;
    if (no->esq == NULL){ //esquerda null
        local = no->pai;
        ajustaNoPai(no, no->dir); //apaga o no substituindo pelo filho da direita
        free (no); //libera o espaco
    } 
    else {
        if (no->dir == NULL){//se a direita eh null
            local = no->pai;
            ajustaNoPai(no, no->esq); //apaga substituindo pelo filho da esquerda
            free(no); //libera o espaco
        }
        else {
            antecess = antecessor (no);//antecessor (menor valor da direita)
            if (antecess->pai != no)
                local = antecess->pai;
            else
                local = antecess;
            ajustaNoPai(antecess, antecess->esq);//apaga o antecessor, que esta na ponta
            antecess->esq = no->esq;//antecessor e no passam a ter mesmos vizinhos
            antecess->dir = no->dir;
            antecess->pai = no->pai;
            ajustaNoPai(no, antecess);//apaga o no, substituindo ele pelo seu antecessor
            if (no == raiz) //se o no era a raiz, guarda seu valor
                novaRaiz = antecess;
            if (antecess->dir != NULL)
                antecess->dir->pai = antecess;
            if (antecess->esq != NULL)
                antecess->esq->pai = antecess;
            free(no);//libera o espaco
        }
    }
    return balancear(local);
}

int nivel(no_t *valor, no_t *raizOriginal){ //calcula o nivel de um node
        no_t *raiz = raizOriginal;
        int cont = 0;
        while (raiz->chave != valor->chave){ //conta nivel da raiz ate o valor
            if (raiz->chave < valor->chave){
                raiz = raiz->dir;
                cont += 1;
            }
            else{
                raiz = raiz->esq;
                cont += 1;
            }
        }
        return cont; //retorna o nivel
    }

void printNivelAux(no_t *node, no_t *raiz){//print EmOrdem, mostrando o nivel
    if (node != NULL){
        printNivelAux(node->esq, raiz);
        printf("%d,%d\n", node->chave, nivel(node, raiz));
        printNivelAux(node->dir, raiz);
    }
    free(node);
}
void printNivel(no_t *raiz){
    no_t *raizCopia = malloc(sizeof(no_t));
    *raizCopia = *raiz;
    printNivelAux(raizCopia, raiz);
}

int main(){
    char tipo = 0;
    int entrada;

    while(tipo != 'i'){ //primeira entrada deve ser insercao, para poder criar raiz da arvore
        scanf("%c %d", &tipo, &entrada);
        fflush(stdin);//limpa o buffer para ler novamente
    }
    no_t *raiz = criaNo(entrada);

    while((tipo = getchar()) != EOF && tipo != 'q'){//enquanto nao chegar no fim do arquivo, ou nao for um q
        scanf("%d", &entrada);//le o valor'
        no_t *no = busca(raiz, entrada);
        switch (tipo){
        case 'i'://caso seja um i, insere
            if (no == NULL)
                raiz = inclui(raiz, entrada);
            break;
        case 'r'://se for um r, remove
            raiz = exclui(no, raiz);
            break;
        }
        fflush(stdin);//limpa o buffer para ler novamente
    }

    //saida, print em ordem mostrnado os niveis dos nodes e liberando a memória
    printNivel(raiz);
    free(raiz);
}