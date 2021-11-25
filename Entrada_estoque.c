#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arquivoPRO "produto.dat"
#define PRATELEIRA 10
#define ARMARIO 2

typedef struct
{
    int armario,prateleira;
    
} Endereco;

typedef struct
{
    int tamanho, quantidade, codigo;
    char cor[10], marca[10], modelo[20];
    Endereco end_estoque;
} Produto;

void entrada_produtos(void);
void verifica_estoque(void); //verificar se a prateleira está cheia ou não

int main()
{
    int opcao;

    do{
    printf("\n\n\t-------------------------------------------------\n"); // Barra t da um tipo de espaçamento como se estivesse apertando o TAB
    printf("\t|  Bem-Vindo ao sistema de controle do estoque  |\n");
    printf("\t-------------------------------------------------\n");
    printf("\n\t1- Cadastrar Produto\n");
    printf("\n\t0- Sair do programa\n\n");
    printf("\tDigite o numero correspondente a funcao desejada: ");
    scanf("%d", &opcao);

    
        switch (opcao)
        {
        case 1:                 // Usuario escolhe 1
            entrada_produtos(); // Chama a função de cadastrar novos produtos
            break;
        case 0:            // Usuario escolhe 0 que sai do programa
            break;
        default:
            printf("\n\tOpcao invalida! Digite uma opcao valida!: ");
            scanf("%d", &opcao);
            break;
        }
    } while (opcao != 0); // Enquanto o usuario não digitar 0, o programa continua executando.

    return 0;
}

void entrada_produtos(void)
{
    FILE *arq;
    Produto x; // Referência da struct Produto
    char data[9];
    int num=0, i;

        do{
        if ((arq = fopen(arquivoPRO, "ab")) == NULL) // se arq for null, deu algum erro na criação do arquivo
        {
            fprintf(stderr, "\n\tImpossivel abrir o arquivo %s!\n", arquivoPRO); // o erro sai em uma memsgaem de erro pelo stder
        }

        fseek(arq, 0, SEEK_END); // Função para escolher de onde começará a leitura ou escrita no arquivo, no caso será possível escrever a partir do final

        x.codigo = ftell(arq) / sizeof(Produto) + 1; // Retorna a posição dentro do arquivo, divide essa posição pelo tamanho do arquivo(por isso o sizeof)
                                                     // e soma mais um, definindo o código do novo produto do estoque.

        system("cls"); // Limpa o terminal
        printf("\n\n\t     Cadastro de novos Produtos \n\n");
        
        printf("\nPara cadastrar novos produtos, basta preencher as informacoes solicitadas! \n\n");
        printf("Codigo: %d", x.codigo); // Como o numero do código é feito automaticamente, então só precisamos imprimir ele
        _strdate(data); // Função para puxar a data atual
        printf("\nData de cadastro: %s", data);
        //printf("\nEndereco no estoque: A%d-P%d", x.end_estoque.armario,x.end_estoque.prateleira);
        printf("\nModelo: ");
        fflush(stdin);         // Limpa o buffer para ler string sem erros
        scanf("%s", x.modelo); // Recebe a string e armazena no modelo do produto
        printf("\nMarca: ");
        fflush(stdin);
        scanf("%s", x.marca); // Recebe a string e armazena na marca do produto
        printf("\nCor: ");
        fflush(stdin);
        scanf("%s", x.cor); // Recebe a string e armazena na cor do produto
        printf("\nTamanho: ");
        scanf("%d", &x.tamanho); // Recebe o inteiro e armazena o tamanho produto
        printf("\nQuantidade: ");
        scanf("%d", &x.quantidade);
        /*printf("\nEnderecamento: ");
        printf("\nRua: ");
        scanf("%d", &x.end_estoque.rua); // Recebe o inteiro e armazena a quantidade a entrar no estoque
        printf("\nArmario: ");
        scanf("%d", &x.end_estoque.armario);
        printf("\nPrateleira: ");
        scanf("%d", &x.end_estoque.prateleira);*/
        verifica_estoque();
        system("pause");
        fwrite(&x, sizeof(Produto), 1, arq); // Escreve as informações armazenada na struct do produto dentro do arquivo
        system("cls");                       // Limpa o terminal
        printf("\n\n\tProduto Cadastrado Com Sucesso!\n\n");
        fclose(arq);

        printf("\n\tDeseja Cadastrar outro produto ?\n\n\t1- Sim\n\n\t2- Nao\n\n ");
        scanf("%d", &num);
        while (num < 0 || num > 2)
        {
            system("cls");
            printf("\n\tOpcao Invalida!!\n\n\tDigite novamente:\n\n\t\t1-Sim\n\n\t\t2- Nao\n");
            scanf("%d", &num);
            system("cls");
        }
    }while(num==1);
}

void verifica_estoque(void){

    int j,i,aux,aux2,soma; //cont's
    Produto z;
    int estoque[PRATELEIRA][ARMARIO];


    for ( i = 1; i < ARMARIO; i++) //Percorre a Armario
    {
        for (j = 1; j < PRATELEIRA; j++) // Percorre a pratileira
        {
            estoque[j][i] = 0; //Zera a matriz
               
        }
    }

    for ( i = 1; i < ARMARIO; i++) //Percorre a Armario
    {
        for (j = 1; j < PRATELEIRA; j++) // Percorre a pratileira
        {
            if(estoque[j][i] == 0){
                estoque[j][i] = z.codigo;
                printf("\nEnderecamento: ");
                printf("A%d-P%d", i, j); 
                break;
            }
        }
    }
    
}
/*aux = z.end_estoque.armario + 1;
aux2 = z.end_estoque.prateleira + 1;*/