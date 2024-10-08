#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void up(int matrix[4][4], int *score);
void left(int matrix[4][4], int *score);
void down(int matrix[4][4], int *score);
void right(int matrix[4][4], int *score);
void fim(int score, int best);
int random(int seed);
int vazios(int matrix[4][4]);
void spawn(int matrix[4][4], int seed);
int load();
void render(int matrix[4][4], int score, int best);

int main(){
    int score = 0;
    int best = load();
    int matrix[4][4] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int end = 0;

    spawn(matrix, 0); //carrega 2 ou 4 nos espacos vazios com proporcao de 85% e 15% de chance
    spawn(matrix, 1);
  
    while (end == 0){
        // printa a tela
        render(matrix, score, best);

        //testa se acabou
        if (vazios(matrix) == 0){ //se nao tem nenhum espaco vazio
            int iguais = 0;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    if ((matrix[i][j] == matrix[i][j+1]) || (matrix[i][j] == matrix[i+1][j])){ //testa se existe algum numero igual do lado um do outro
                        iguais = 1;
                        i = 3;
                        break;
                    }
                }
            }
            if (iguais == 0){//se ainda nao encontrou iguais, testa os que faltam
                for (int i = 0; i < 3; i++){
                    if (matrix[i][3] == matrix[i+1][3])
                        iguais = 1; 
                }
                for (int j = 0; j < 3; j++){
                    if (matrix[3][j] == matrix[3][j+1])
                        iguais = 1; 
                }
            }
            if (iguais == 0) //se nao encontrar nenhum igual um do lado do outro, game over
                end = 1;
        }

        char key;
        scanf("%c", &key);//le character do teclado
        fflush(stdin); //limpa o buffer

        switch (key){
            case 'w': case 'W':
                up(matrix, &score);
                break;
            case 'a': case 'A':
                left(matrix, &score);
                break;
            case 's': case 'S':
                down(matrix, &score);
                break;
            case 'd': case 'D':
                right(matrix, &score);
                break;
            default:
                break;
        }
    }
    fim(score, best);//carrega a tela de game over
}

//movimenta para cima
void up(int matrix[4][4], int *score){
    int spn = 0;
    for (int j = 0; j < 4; j++){
        for (int i = 0; i < 4; i++){
            if (matrix[i][j] != 0){
                int num = matrix[i][j]; //salva o numero original
                int k = i-1;    //posicao do de cima
                int zero = 0;   //flag para zerar ou nao depois da movimentacao
                if (k >= 0) {   //se ele nao estiver na parede
                    while (k >= 0){
                        if (matrix[k][j] != 0 && matrix[k][j] != num){ //em cima nao eh vazio e nao eh igual ao numero sendo movido
                            matrix[k+1][j] = num;   //se em cima tem um numero, o de baixo vira o numero sendo movido
                            break;
                        }
                        if (matrix[k][j] != 0 && matrix[k][j] == num){//em cima nao eh vazio mas o numero eh igual
                            matrix[k][j] = matrix[k][j] + num;  //soma os dois valores que sao iguais
                            *score = *score + (num * 2);    //adiciona os pontos no score
                            zero = 1;
                            break;
                        }
                        if (k == 0 && matrix[k][j] == 0){ //em cima eh parede, e espaco eh vazio
                            matrix[k][j] = num;
                            zero = 1;
                            break;
                        }
                        if (matrix[k][j] == 0){ // de cima eh vazio
                            k--;    //movimenta o k
                            zero = 1; //como foi movimentado, o orignial deve ser zerado
                        }
                    }
                    if (zero == 1){ //foi movimentado ou somado, entao o original deve ser zerado
                        spn = 1;
                        matrix[i][j] = 0;
                    }
                }
            }
        }
    }
    if (spn == 1)
        spawn(matrix, 2);
}

//movimenta para a esquerda
void left(int matrix[4][4], int *score){
    int spn = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (matrix[i][j] != 0){
                int num = matrix[i][j]; //salva o numero original
                int k = j-1;    //posicao do da esquerda
                int zero = 0;   //flag para zerar ou nao depois da movimentacao
                if (k >= 0) {   //se ele nao estiver na parede
                    while (k >= 0){
                        if (matrix[i][k] != 0 && matrix[i][k] != num){ //na esquerda nao eh vazio e nao eh igual ao numero sendo movido
                            matrix[i][k+1] = num;   //na esquerda tem um numero, o da direita dele vira o numero sendo movido
                            break;
                        }
                        if (matrix[i][k] != 0 && matrix[i][k] == num){//na esquerda nao eh vazio mas o numero eh igual
                            matrix[i][k] = matrix[i][k] + num;  //soma os dois valores que sao iguais
                            *score = *score + (num * 2);    //adiciona os pontos no score
                            zero = 1;
                            break;
                        }
                        if (k == 0 && matrix[i][k] == 0){ //na esquerda eh parede, e espaco eh vazio
                            matrix[i][k] = num;
                            zero = 1;
                            break;
                        }
                        if (matrix[i][k] == 0){ // na esquerda eh vazio
                            k--;    //movimenta o k
                            zero = 1; //como foi movimentado, o orignial deve ser zerado
                        }
                    }
                    if (zero == 1){ //foi movimentado ou somado, entao o original deve ser zerado
                        spn = 1;
                        matrix[i][j] = 0;
                    }
                }
            }
        }
    }
    if (spn == 1)
        spawn(matrix, 2);
}

//movimenta para baixo
void down(int matrix[4][4], int *score){
    int spn = 0;
    for (int j = 0; j < 4; j++){
        for (int i = 3; i >= 0; i--){
            if (matrix[i][j] != 0){
                int num = matrix[i][j]; //salva o numero original
                int k = i+1;    //posicao do de baixo
                int zero = 0;   //flag para zerar ou nao depois da movimentacao
                if (k <= 3) {   //se ele nao estiver na parede
                    while (k <= 3){
                        if (matrix[k][j] != 0 && matrix[k][j] != num){ //em baixo nao eh vazio e nao eh igual ao numero sendo movido
                            matrix[k-1][j] = num;   //se em baixo tem um numero, o de cima vira o numero sendo movido
                            break;
                        }
                        if (matrix[k][j] != 0 && matrix[k][j] == num){//em baixo nao eh vazio mas o numero eh igual
                            matrix[k][j] = matrix[k][j] + num;  //soma os dois valores que sao iguais
                            *score = *score + (num * 2);    //adiciona os pontos no score
                            zero = 1;
                            break;
                        }
                        if (k == 3 && matrix[k][j] == 0){ //em baixo eh parede, e espaco eh vazio
                            matrix[k][j] = num;
                            zero = 1;
                            break;
                        }
                        if (matrix[k][j] == 0){ // de baixo eh vazio
                            k++;    //movimenta o k
                            zero = 1; //como foi movimentado, o orignial deve ser zerado
                        }
                    }
                    if (zero == 1){ //foi movimentado ou somado, entao o original deve ser zerado
                        spn = 1;
                        matrix[i][j] = 0;
                    }
                }
            }
        }
    }
    if (spn == 1)
        spawn(matrix, 2);
}

//movimenta para a direita
void right(int matrix[4][4], int *score){
    int spn = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 3; j >= 0; j--){
            if (matrix[i][j] != 0){
                int num = matrix[i][j]; //salva o numero original
                int k = j+1;    //posicao do da direita
                int zero = 0;   //flag para zerar ou nao depois da movimentacao
                if (k <= 3) {   //se ele nao estiver na parede
                    while (k <= 3){
                        if (matrix[i][k] != 0 && matrix[i][k] != num){ //na direita nao eh vazio e nao eh igual ao numero sendo movido
                            matrix[i][k-1] = num;   //se na direita tem um numero, o da direita vira o numero sendo movido
                            break;
                        }
                        if (matrix[i][k] != 0 && matrix[i][k] == num){//na direita nao eh vazio mas o numero eh igual
                            matrix[i][k] = matrix[i][k] + num;  //soma os dois valores que sao iguais
                            *score = *score + (num * 2);    //adiciona os pontos no score
                            zero = 1;
                            break;
                        }
                        if (k == 3 && matrix[i][k] == 0){ //na direita eh parede, e espaco eh vazio
                            matrix[i][k] = num;
                            zero = 1;
                            break;
                        }
                        if (matrix[i][k] == 0){ // na direita eh vazio
                            k++;    //movimenta o k
                            zero = 1; //como foi movimentado, o orignial deve ser zerado
                        }
                    }
                    if (zero == 1){ //foi movimentado ou somado, entao o original deve ser zerado
                        spn = 1;
                        matrix[i][j] = 0;
                    }
                }
            }
        }
    }
    if (spn == 1)
        spawn(matrix, 2);
}

//tela de fim
void fim(int score, int best){
    printf("\n\033[0;31;1m"); //vermelho bold
    printf("        GAME\n        OVER\n");
    if (score > best){ //caso tenha batido o record
        printf("\n\033[0;33;1m"); //amarelo bold
        printf("Parabens, voce atingiu um novo recorde!\n");
        best = score;
        FILE *file = fopen("record.txt", "w"); //abre para escrita
        fprintf(file,"%d", score); //salva o novo high score
        fclose(file); //fecha o arquivo
    }
    //resume os resultados
    printf("\n\033[0;32m");
    printf("Score: %d   ", score);
    printf("\033[0;36m");
    printf("Best: %d\n\n", best);
}

//retorna um numero pseudoaleatorio de 0-99
int random(int seed){
    srand(time(NULL)+seed); //a seed eh o tempo
    int random[10]; //gera uma matrix de 10 numeros de 0 a 99
    for (int i = 0; i < 10; i++)
        random[i] = rand() % 100;
    return random[random[0]%10]; //o primeiro numero determina qual dos 10 numeros retornar
}

//conta e retorna a quantidade de espacos vazios
int vazios(int matrix[4][4]){
    int zeros = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (matrix[i][j] == 0)
                zeros++;
        }
    }
    return zeros;
}

//carrega um numero 2 ou 4 nos espacos vazios da matriz
void spawn(int matrix[4][4], int seed){
    int zeros = vazios(matrix); // espacos vazios

    //calcula um espaco aleatorio dentre os espacos vazios
    int r = random(seed)%zeros;

    //vai ate o local aleatorio vazio e coloca um 2 ou 4 com proporcao de 85% e 15% de chance respectivamente
    int cont = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (matrix[i][j] != 0)
                r++;
            if (i*4+j == r){
                int odds = random(seed);
                if (odds >= 85) 
                    matrix[i][j] = 4;
                else 
                    matrix[i][j] = 2;
                i = 4;
                break;
            }
            cont++;
        }
    }
}

//carrega e retorna o recorde
int load(){
    FILE *file = fopen("record.txt", "r");//abre para leitura
    if (file == NULL){  //se o arquivo nao existir
        FILE *new = fopen("record.txt", "w"); //cria um novo arquivo
        fprintf(new,"%d", 0);// coloca 0 no arquivo
        fclose(new); //fecha o arquivo
    }

    int record;
    fscanf(file,"%d",&record); //carrega o numero salvo no arquivo para a variavel record
    fclose(file); //fecha o arquivo
    return record;
}

//printa no console a matriz do jogo
void render(int matrix[4][4], int score, int best){
    printf("\n\033[0;32m");//verde
    printf("Score: %d   ", score);
    printf("\033[0;36m");//ciano
    printf("Best: %d\n\n", best);
    for (int i = 0; i < 4; i++){//carrega o tabuleira, e configura as cores de acordo com os numeros
        for (int j = 0; j < 4; j++){
            if (matrix[i][j] == 0) 
                printf("\033[0;30m");//cinza
            if (matrix[i][j] == 2 || matrix[i][j] == 4)
                printf("\033[0;37;1m");//branco bold
            if (matrix[i][j] == 8)
                printf("\033[0;37m"); //branco
            if (matrix[i][j] == 16)
                printf("\033[0;33m"); //amarelo
            if (matrix[i][j] == 32)
                printf("\033[0;31m"); //vermelho
            if (matrix[i][j] == 64)
                printf("\033[0;31;1m"); //vermelho bold
            if (matrix[i][j] > 64 && matrix[i][j] < 4096)
                printf("\033[0;33;1m"); //amarelo bold
            if (matrix[i][j] >= 4096)
                printf("\033[0;35;1m"); //magenta
            printf("%-7d", matrix[i][j]);
        }
        printf("\n");
        printf("\033[0;30m");//volta para o cinza
    }
    printf("comando:");
}