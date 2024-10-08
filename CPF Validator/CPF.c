#include <stdio.h>
#include <string.h>
//calcula o primeiro digito baseado no cpf
int primeiro(int cpf[11]){
    int resultado = 0;
    int fator = 10;
    //faz a soma da multiplicação dos valores com o fator
	for (int i = 0; i < 9; i++, fator--)
        resultado += cpf[i] * fator;
    int primeiro;
    //testa se o resto da divisão é menor que 2 ou não
    if (resultado % 11 >= 2)
        primeiro = 11 - (resultado % 11);
    else primeiro = 0;
    return primeiro;
}

//calcula o segundo digito baseado no cpf
int segundo(int cpf[11]){
    int resultado = 0;
    int fator = 11;
    //faz a soma da multiplicação dos valores com o fator
	for (int i = 0; i < 10; i++, fator--)
        resultado += cpf[i] * fator;
    int segundo;
    //testa se o resto da divisão é menor que 2 ou não
    if (resultado % 11 >= 2)
        segundo = 11 - (resultado % 11);
    else segundo = 0;
    return segundo;
}

int verificar(int cpf[], int digito){
    int dig = cpf[9] * 10 + cpf[10]; //junta os ultimos 2 digitos do cpf em um unico numero
    if (digito == dig)
        return 1;
    else return 0;
}

int main(){
    //le o cpf como vetor de char
	char lercpf[11];
	printf("digite o seu cpf (apenas numeros):");
    scanf("%s", lercpf);

    //converte cpf lido como char para vetor de int
    int cpf[11];
    for (int i = 0; i < 11; i++)
        cpf[i] = lercpf[i]-48;
    
	int x = primeiro(cpf); //calcula o primeiro digito
	int y = segundo(cpf); //calcula o segundo digito
	int digito = x * 10 + y; //junta os 2 para comparar
	if (verificar(cpf, digito) == 1) //testa se o digito calculado bate com o digitado
		printf("O cpf eh valido"); 
	else (printf("O cpf eh invalido"));
}