#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Lista ligada
	// Node
	typedef struct node Node;
	struct node {
		Data *data;
		Node *proximo;
	};

	// Root
	typedef struct root {
		Node *primeiro;
	} Root;

//Constantes importantes
	
	//Define cores UwU
	#define KMAG "\x1B[32m"
	#define RESET "\033[0m"
  
  //Definem os numeros para menus
	enum {
		SAIR,
		CRIAR_DATA,
		LIBERAR_DATA,
		SOMAR,
		SUBTRAIR,
		ATRIBUIR,
		DIA,
		MES,
		ANO,
		BISSEXTO,
		COMPARAR,
		ENTRE_DIAS,
		IMPRIMIR,
		MENU_INICIAL
	};

//Variáveis globais
	unsigned int procedimento; //Variavel para escolha de menu 
	unsigned int contadorData = 0;
	int i;
	Root root = {.primeiro=NULL};
	Node **futuroNode = &root.primeiro;

// Declaração de Funções
  //Funções auxiliares
    void limparBufferDeEntrada();//Limpa o buffer de entrada
    void limparSaida();//Limpa a saída (semelhante ao system(clear))
    void colocaData(Data *data);
    void tiraData();
		Data *achaData(unsigned int indice);
    void imprimirTodasDatas(); //Imprime a lista de datas
    void pausar();
  //Funções menu 
    void menuInicial(); //chama o menu inicial
    void criaDataMenu(); //chama o menu de criação de data
    void liberaDataMenu(); //chama o menu de liberação de data
    void somaDataMenu(); //chamda o menu de soma de dias
    void subtrairDataMenu(); //chama o menu de subtração de dias
    void atribuirDataMenu(); //chma o menu de atribuição de data
    void obtemDiaMenu(); //chama o menu de obtenção de dia
    void obtemMesMenu(); //chama o menu de obtenção de mes 
    void obtemAnoMenu(); //chama o menu de obtenção de ano
    void bissextoMenu(); //chama o menu de verificador de data bissexta
    void compararMenu(); //chama o menu de compração de datas
    void entreDiasMenu(); //chama o menu de calcular dias entre datas 
    void imprimirMenu(); //chama o menu de impressão de uma data 

int main(int argc, char *argv[])
{
	// Procedimento inicial
	procedimento = MENU_INICIAL;

	// Loop principal
	while(1){
		limparSaida(); //Limpa a saída para o menu inicial

		switch(procedimento){
			case MENU_INICIAL: menuInicial(); break;
			case CRIAR_DATA: criaDataMenu(); break;
			case LIBERAR_DATA: liberaDataMenu(); break;
			case SOMAR: somaDataMenu(); break;
			case SUBTRAIR: subtrairDataMenu(); break;
			case ATRIBUIR: atribuirDataMenu(); break;
			case DIA: obtemDiaMenu(); break;
			case MES: obtemMesMenu(); break;
			case ANO: obtemAnoMenu(); break;
			case BISSEXTO: bissextoMenu(); break;
			case COMPARAR: compararMenu(); break;
			case ENTRE_DIAS: entreDiasMenu(); break;
			case IMPRIMIR: imprimirMenu(); break;
			case SAIR: return 0; // Fecha o programa
			default: procedimento = MENU_INICIAL;
		}
	} 
}

//Funções de Menu - Definição 
	void menuInicial(){
		puts(KMAG "BIBLIOTECA DATAS        //   FERNANDO MALTEZ BEZERRA\n\n" RESET);
		puts("1 - Função Criar Data");
		puts("2 - Função Liberar Data");
		puts("3 - Função Somar dias a Data");
		puts("4 - Função Subtrair dias a Data");
		puts("5 - Função Atribuir uma nova data a Data");
		puts("6 - Função Obter o dia de uma data");
		puts("7 - Função Obter o mes de uma data");
		puts("8 - Função Obter o ano de uma data");
		puts("9 - Função Verificar se a data pertence a ano bissexto");
		puts("10 - Função Comparar 2 datas");
		puts("11 - Função Pegar o numero de dias entre 2 datas");
		puts("12 - Função Imprimir uma data");
		puts("0 - Sair do programa");
		scanf("%d", &procedimento);
	}

	void criaDataMenu() {
		unsigned int dia, mes, ano;
	  int validade = 1;	

    while (validade == 1) {
    
			fputs("Digite o dia, mês e ano separados por espaço: ", stdout);
			scanf("%d %d %d", &dia, &mes, &ano);
			limparBufferDeEntrada();

			//Verificação de validade de data 
			validade = validaData(dia, mes, ano);
    }

    limparSaida();
		colocaData(criaData(dia, mes, ano));
    printf("Data criada com sucesso\n");

    procedimento = MENU_INICIAL;
	}

	void liberaDataMenu() {
		unsigned int indice;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);
		limparBufferDeEntrada();
		indice--; // A indexagem do usuário começa em 1 e a implementado em código começa em zero

		if (indice < contadorData) {
			tiraData(indice);
		} else {
			puts("Índice inválido");
		}
		procedimento = MENU_INICIAL;
	}

	 void somaDataMenu() {
	 	unsigned int indice;
	 	imprimirTodasDatas();
	 	fputs("Digite o índice para selecionar a data: ", stdout);
	 	scanf("%d", &indice);
		limparBufferDeEntrada();
		indice--; // A indexagem do usuário começa em 1 e a implementado em código começa em zero
	
	 	if (indice < contadorData) {
			unsigned int dias;
	 		printf("Digite a quantidade de dias que deseja somar à data %s:", imprimeData(*(achaData(indice)), "ddmmaaaa"));	
			scanf("%d", &dias);
			limparBufferDeEntrada();
			colocaData(somaDiasData(*(achaData(indice)), dias));
	 	} else {
	 		puts("Índice inválido");
	 	}
	 	
	 	printf("Nova data: %s\n", imprimeData(*(achaData(contadorData)), "ddmmaaaa"));
	 	pausar();
	 	
    procedimento = MENU_INICIAL;
	 }

	 void subtrairDataMenu() {
		unsigned int indice;
	 	imprimirTodasDatas();
	 	fputs("Digite o índice para selecionar a data: ", stdout);
	 	scanf("%d", &indice);
		limparBufferDeEntrada();
	
	 /* 	if (indice < contadorData) { */
			unsigned int dias;
	 		printf("Digite a quantidade de dias que deseja subtrair da data %s:", imprimeData(*(achaData(indice)), "ddmmaaaa"));	
			scanf("%d", &dias);
			limparBufferDeEntrada();
			colocaData(subtrairDiasData(*(achaData(indice)), dias));
	 	// } else {
	 	// 	puts("Índice inválido");
	 	// }
	
	 	printf("%s\n", imprimeData(*(achaData(contadorData)), "ddmmaaaa"));
	 	pausar();
	 	
    procedimento = MENU_INICIAL;
	 }
	
	 void atribuirDataMenu() {
		unsigned int indice, dia, mes, ano;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);

		fputs("Digite o dia, mês e ano separados por espaço: ", stdout);
		scanf("%d %d %d", &dia, &mes, &ano);
		
		atribuirData(achaData(indice), dia, mes, ano);

    printf("Nova data: %s\n",  imprimeData(*(achaData(indice)), "ddmmaaaa"));
    pausar();
    procedimento = MENU_INICIAL;
	 }
	
	 void obtemDiaMenu() {
	 	unsigned int indice;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);

		printf("Dia da data selecionada: %d\n", achaData(indice)->dia);
    pausar();
    procedimento = MENU_INICIAL;
	 }
	
	 void obtemMesMenu() {
	 	unsigned int indice;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);

		printf("Mes da data selecionada: %d\n", achaData(indice)->mes);
    pausar();
    procedimento = MENU_INICIAL;
	 }
	
	 void obtemAnoMenu() {
	 	unsigned int indice;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);

		printf("Ano da data selecionada: %d\n", achaData(indice)->ano);
    pausar();
    procedimento = MENU_INICIAL;
	 }
	
	 void bissextoMenu() {
		unsigned int indice;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);

		if(bissextoData(*(achaData(indice)))) {
			puts("O ano é bissexto");
      pausar();
		} else {
			puts("O ano não é bissexto");
      pausar();
		}
    procedimento = MENU_INICIAL;
	 }
	
	 void compararMenu() {
		unsigned int indice, indice2;
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar uma data: ", stdout);
		scanf("%d", &indice);
		limparSaida();
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar outra data: ", stdout);
		scanf("%d", &indice2);

		short resultado = comparaData(*(achaData(indice)), *(achaData(indice2)));
  
		switch(resultado) {
			case 1:
				printf("A data %d é maior que a data %d\n", indice, indice2);
        pausar();
				break;
			case 0:
				printf("A data %d é igual à data %d\n", indice, indice2);
        pausar();
				break;
			case -1:
				printf("A data %d é menor que a data %d\n", indice, indice2);
        pausar();
				break;
		}
    procedimento = MENU_INICIAL;
	 }
	
	 void entreDiasMenu() {
    unsigned int indice1, indice2;  
    imprimirTodasDatas();
    fputs("Digite o índice para selecionar uma data: ", stdout);
    scanf("%d", &indice1);
    fputs("Digite o índice para selecionar outra data: ", stdout);
    scanf("%d", &indice2);
      printf("O numero de dias entre as datas é: %d\n", numeroDiasData(*achaData(indice1), *achaData(indice2)));
    limparBufferDeEntrada();
    pausar();
    
    procedimento = MENU_INICIAL;
	 }
	
	 void imprimirMenu() {
		unsigned int indice;
    unsigned short tam = 9;
		char formato[tam];
		imprimirTodasDatas();
		fputs("Digite o índice para selecionar a data: ", stdout);
		scanf("%d", &indice);

		fputs("Digite a formatação da data: ", stdout);
		limparBufferDeEntrada();
		fgets(formato, tam, stdin);
		formato[strcspn(formato, "\n")] = '\0'; 
    

		printf("Data nessa formatação: %s\n", imprimeData(*(achaData(indice)), formato));
    pausar();
    procedimento = MENU_INICIAL;
	 }

//Funções Auxiliares - Definição
	void limparBufferDeEntrada(){ //Lida com buffers relacionados a char 
		char lixo;
		while((lixo = getchar()) != '\n' && lixo != EOF){continue;}
	}

	void limparSaida(){ //Limpa compleetamente a saída 
		fflush(stdout);
		puts("\e[1;1H\e[2J");
	}

	void colocaData(Data *data){
		*futuroNode = (Node *)malloc(sizeof(Node));
		if (*futuroNode != NULL){
			(*futuroNode)->data = data;
			(*futuroNode)->proximo = NULL;
			futuroNode = &((*futuroNode)->proximo);
			contadorData++;
			puts("Data adicionada com sucesso");
      pausar();
		} else {
			puts("Erro: memoria insuficiente");
      pausar();
		}
	}

	void tiraData(unsigned int indice) {
		Node *atual = root.primeiro;
		Node *anterior;

		for (i = 0; i < indice; i++) {
			anterior = atual;
			atual = atual -> proximo;
		}

		liberaData(atual->data);

		if (indice == 0) {
			root.primeiro = atual -> proximo;
			free(atual);
		}
		else if (indice <= contadorData) {
			anterior -> proximo = atual -> proximo;
			free(atual);
		} else {
			free(atual);
			anterior -> proximo = NULL;
			futuroNode = &(anterior->proximo);
		}
		contadorData--;
	}

	Data *achaData(unsigned int indice) {
		Node *atual = root.primeiro;
	 	for (i = 1; i < indice; i++) {
	 		atual = atual->proximo;
	 	}
		return atual->data;
	 }


	void imprimirTodasDatas() {
		puts("Datas criadas:");
		Node *atual = root.primeiro;
		for (i = 0; i < contadorData; i++){
			printf("%d - %s\n", i+1, imprimeData(*(atual->data), "ddmmaaaa"));
			atual = atual->proximo;
		}
	}

  void pausar() {
    printf("\nDigite 0 para voltar ao menu\n");
    int lixo;
    scanf("%d", &lixo);
}
