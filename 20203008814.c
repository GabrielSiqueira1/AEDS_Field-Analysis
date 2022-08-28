/****

LAED1 - Projeto (Parte III) - Proximidade dos obstáculos

Aluno: Gabriel Siqueira Silva

Data: 26/08/2021

****/

#include <stdio.h> // Necessario para compilar o programa
#include <string.h> // Necessario para operar com as strings do arquivo
#include <stdlib.h> // Necessario para realizar funções nao existentes na biblioteca padrao

// Funcoes de lista, fonte: Ziviane - Estrutura de Dados Básicas (Usando Arranjo)
#define INICIOARRANJO   1
#define MAXTAM          1000

typedef int TipoChave;

typedef int TipoApontador;

typedef char TipoResultado; // Adicao propria

typedef struct {
    TipoChave Chave;
    TipoResultado Resultado[50]; // Adicao propria
} TipoItem;

typedef struct {
    TipoItem Item[MAXTAM];
    TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================== */

void FLVazia(TipoLista *Lista){ // Ha uma igualdade entre a posicao do primeiro e ultimo item de uma lista tornando-a vazia
    Lista -> Primeiro = INICIOARRANJO;
    Lista -> Ultimo = Lista -> Primeiro; 
}

int Vazia(TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista){
    if (Lista -> Ultimo > MAXTAM)
        printf("Lista esta cheia\n");
    else {
        Lista -> Item[Lista -> Ultimo - 1] = x; // Adiciona-se x a posicao de ultimo - 1 porque o arranjo comeca em zero
        Lista -> Ultimo++; // Adiciona-se uma nova posicao
    }
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item){
    int Aux;
    if (Vazia(*Lista) || p >= Lista -> Ultimo){
        printf(" Erro   Posicao nao existe\n");
        return;
    }
    *Item = Lista -> Item[p - 1];
    Lista -> Ultimo--;
    for (Aux = p; Aux < Lista -> Ultimo; Aux++)
        Lista -> Item[Aux - 1] = Lista -> Item[Aux];
}

void Imprime(TipoLista Lista){
    int Aux;

    for (Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++){
        printf("%d %s\n", Lista.Item[Aux].Chave, Lista.Item[Aux].Resultado);
    }
}
/* ========================================================================== */
int main() {
    FILE *fp;
    TipoLista lista; // E uma lista com MAXTAM itens
    TipoItem item;
    FLVazia(&lista); // Cria a lista vazia

    // Contadores
    int erro = 0; // Contador que verifica se há interrupcao na estrada
    int n; // Item para criacao de um vetor ajustavel
    int m; // Item para criacao de um vetor ajustavel
    int i = 0; // Utilizado para preencher o vetor que armazena os dados provenientes do arquivo (vetor)
    int z = 0; // Utilizado para preencher o vetor que recebe a separação de itens do vetor anterior (receptor)
    int q = 0; // Contador generico
    int e = 0; // Contador generico
    int disp = 0; // Assume o valor da quantidade de dados
    int conversor; // Recebe a string convertida em int
    int temp = 0; // Necessario para todas as posicoes que tem a quantidade de dados
    int linhas = 0; // Quantidade de conjunto de dados contidos no documento
    int string1 = 0; // Contador de comparacao com as strings de resposta
    int string2 = 0;
    int string3 = 0;

    // String com as respostas possiveis para cada item
    char resposta1[] = "Pista normal.";
    char resposta2[] = "Pista impedida.";
	char resposta3[] = "Padrao nao identificado.";

    char nomeArquivo[300];
    printf("Digite o nome do arquivo: ");
    scanf("%s",nomeArquivo);
    fp = fopen(nomeArquivo,"r"); // Abre arquivo texto para leitura
    if(!fp) {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    }

    // Reajuste da incializacao de vetores, agora com vetores de tamanhos variaveis
    fscanf(fp,"%d",&n);
    fscanf(fp,"%d",&m);
    char c[n*m+n+1]; // E a quantidade de faixas, n, e a quantidade de termos em cada faixa m
    char* vetor[n*m+n+1];
    char* receptor[n*m+n+1];

    while(fgets(c, sizeof c, fp) != NULL){ // Enquanto nao chegar ao final do arquivo
        vetor[i] = strdup(c); // A funcao duplica o valor e o armazena no vetor
        i++;
    }
    for (int j = 0; j < i; j++){
        char *token = strtok(vetor[j], " ");
        while(token != NULL) {
            receptor[z] = token;
            token = strtok(NULL, " "); // Utilizado para separar os numeros a partir do espaço entre eles, unico problema e que a quebra de linha tambem esta sendo armazenada
            z++;
        }
    }
    linhas = n;
    int vetorInteiro[m][linhas];
    int vetorCrescente[m][linhas];
	// Sistema de separacao de dados, por exemplo, se sao 950 dados, serao separados x conjuntos de 950 dados
    for (int x = 1; x<z-1; x++){
        conversor = atoi(receptor[x]);
        if (temp == 1){
            disp = conversor;
            temp--;
        }
        else{
            vetorInteiro[e][q] = conversor; // Nao é mais armazenada a quebra de linha
            vetorCrescente[e][q] = conversor;
            e++;
            if (e == m){
                temp++;
                q++;
                e=0;
            }
        }
    }
    int tent = 0;
    for(tent = 0; tent < linhas; tent++){
        int tamanho = 1;
        // A logica de definir o tamanho foi alterada por uma mais simples
        for (int x = 0; x<disp; x++){
            if((vetorInteiro[x][tent] != vetorInteiro[x+1][tent]) && x != disp-1){
                tamanho++;
            }
        }
        // Ordenador do vetor, para torna-lo crescente
        int armazenador = 0;
        int matrizCrescente[disp+2][2];
        int matrizCrescenteUnitaria[disp+2][2];
        int matrizFinal[2][disp+2];
        for (int x = 0; x<disp; x++){
            for (int y=x+1; y<disp; y++){
                if(vetorCrescente[x][tent]>vetorCrescente[y][tent]){
                    armazenador = vetorCrescente[x][tent];
                    vetorCrescente[x][tent] = vetorCrescente[y][tent];
                    vetorCrescente[y][tent] = armazenador;
                }
            }
        }
        // A matriz crescente serve para armazenar o vetor crescente em uma coluna e na coluna seguinte a ordem deles, se e 1, 2, 3 ou qualquer outro valor de associacao
        int t=0; // Ajuste da matriz
        int r=1; // O numero associado ao crescimento
        matrizCrescente[t][0] = vetorCrescente[0][tent];
        matrizCrescente[t][1] = r;
        t++;
        for (int x = 0; x<disp; x++){
            if(vetorCrescente[x][tent]!=vetorCrescente[x+1][tent]){
                matrizCrescente[t][0] = vetorCrescente[x][tent];
                matrizCrescente[t][1] = r;
                r++;
                t++;
            }
            else{
                matrizCrescente[t][0] = vetorCrescente[x][tent];
                matrizCrescente[t][1] = r;
                t++;
            }
        }
        t = 0;
        // Nessa parte, a repeticao dos numeros e retirada, por exemplo, na ordenacao tem 000, este termo sera subsituido por 0
        matrizCrescenteUnitaria[0][0] = matrizCrescente[0][0];
        matrizCrescenteUnitaria[0][1] = matrizCrescente[0][1];
        for(int x = 0; x<disp; x++){
            if(matrizCrescenteUnitaria[t][0] != matrizCrescente[x][0]){
                t++;
                matrizCrescenteUnitaria[t][0] = matrizCrescente[x][0];
                matrizCrescenteUnitaria[t][1] = matrizCrescente[x][1];
            }
        }

        // Nesse for, podemos realizar a separação das matrizes e organizar o resultado final
        // A Matriz final organiza de acordo com o vetor retirado do documento orginal
        /*
        Ex: 			0 0 0 128 128 0 0 255 255 255 255
        Matriz Final
                        1 1 1  2   2  1 1  3   3   3   3 -> Essa linha deve conservar os itens iguais
                        1 1 1  1   1  1 1  1   1   1   1 -> Essa linha tem que somar os 1's ate que o item de cima se diferencie
        */
        int contador = 0;
        for(int x = 0; x<disp; x++){
            for(int y = 0; y<=t; y++){
                if(vetorInteiro[x][tent] == matrizCrescenteUnitaria[y][0]){
                    matrizFinal[0][x] = matrizCrescenteUnitaria[y][1];
                    contador++;
                }
            }
            matrizFinal[1][x] = contador;
            contador=0;
        }


        // Esse for realiza a soma da segunda linha da Matriz Final (1 1 1  1   1  1 1  1   1   1   1)
        int matrizFinalFinal[2][disp+2];
        int soma = 0;
        int k = 0;
        for(int x = 0; x<2; x++){
            for(int y = 0; y<disp; y++){
                if(matrizFinal[0][y] != matrizFinal[0][y+1]){
                    soma = soma + matrizFinal[1][y];
                    matrizFinalFinal [1][k] = soma;
                    soma = 0;
                    k++;
                }
                else{
                    soma = soma + matrizFinal[1][y];
                }
            }
        }

        // Esse for realiza a conservação da primeira linha da Matriz Final (1 1 1  2   2  1 1  3   3   3   3)
        k=0;
        for(int x = 0; x<2; x++){
            for(int y = 0; y<disp; y++){
                if(matrizFinal[0][y] != matrizFinal[0][y+1]){
                    matrizFinalFinal[0][k] = matrizFinal[0][y];
                    k++;
                }
            }
        }

        //Alteração do código passado a partir deste ponto
        int matrizReajuste[2][disp+2];
        for(int x = 0; x<2; x++){
            for(int y = 0; y<tamanho; y++){
                matrizReajuste[x][y] = matrizFinalFinal[x][y];
            }
        }
	contador = 0;
	int contadorSecundario = 0;
	k = 0;
	int vetor2[5] = {1,3,2,3,1};
	// Sistema de comparacao de dois vetores
	for(int y = 0; y<tamanho; y++){
		if(matrizReajuste[0][y] == vetor2[k]){
			contador++;
        // Para essa condicao e necessario pensar que a interrupcao da via tambem e considerada padrao encontrado
			if ((contador == 3 && matrizReajuste[0][y+2] == vetor2[k]) || contador==5) {
				contadorSecundario = 1;
			}
			k++;
		}
		else{
			if(contador != 0){ // Evita loop e saltos quando o if não e satisfeito
				y--;
			}
			contador = 0;
			k = 0;
		}
	}
	if(contadorSecundario != 0){ // Apenas padroes encontrados poderao ser classificados em pista impedida ou pista normal
		contador = 0;
		int contadorTerciario = 0;
		k = 0;
		int vetor1[2] = {3,2};
		// Sistema de comparacao de dois vetores
		for(int y = 0; y<tamanho; y++){
			if(matrizReajuste[0][y] == vetor1[k]){
				contador++;
				if (contador == 2 && matrizReajuste[0][y+2] == 2 && matrizReajuste[0][y+3] == 3){ // Sempre que o vetor for igual em uma sequencia de 5
					contadorTerciario = 1;
				}
				k++;
			}
			else{
				if(contador != 0){ // Evita loop e saltos quando o if não e satisfeito
					y--;
				}
				contador = 0;
				k = 0;
			}
		}
		if(contadorTerciario != 0){ // Verifica se a pista está impedida em algum ponto
			for(i = 0; i<strlen(resposta2); i++){
				item.Resultado[i] = resposta2[i];
				erro++;
			}
			contadorTerciario = 0;
		}
		else{
			for(i = 0; i<strlen(resposta1); i++){
				item.Resultado[i] = resposta1[i];
			}
		}

	}
	else{
		for(i = 0; i<strlen(resposta3); i++){
			item.Resultado[i] = resposta3[i];
		}
	}
	int p = 0;
	for(p = 0; p<i; p++){
    		item.Resultado[i] = '\0'; // Limpa a string
	}
	item.Chave = tent+1;
	Insere(item, &lista);
    }
    // Abaixo tem a analise do que sera escrito no prompt de comando. Veja que a string3 ira alterar quando erro for igual zero representando nenhum impedimento na pista e caso tenha o impedimento e necessario entender em qual ponto da curva ele esta. Para isso, no else a string 1 ou 2 vai ter seu valor alterado para representar onde esta o impedimento.
    if (erro == 0){
        string3++;
    }
    else{
        for(i = 0; i<disp; i++){
            if(i<5 && strcmp(lista.Item[i].Resultado, resposta2) == 0){
                string1++;
            }
            else if(i>=5 && strcmp(lista.Item[i].Resultado, resposta2) == 0){
                string2++;
            }
        }
    }
    if(string1 != 0){
        printf("Resultado: Pista com impedimento distante.\n");
    }
    else if(string2 != 0){
        printf("Resultado: Pista com impedimento proximo.\n");
    }
    else if(string3 != 0){
        printf("Resultado: Pista sem impedimento.\n");
    }
    else{ // Caso esteja fora da pista
        printf("Resultado: Padrao nao encontrado.\n");
    }
    fclose(fp);
    return 0;
}
