#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define arquivoPRO "produto.dat"
#define ENDERECOPRO "endereco.dat"
#define ARMARIO 100
#define ESTOQUE 200
typedef struct
{
    int armario, box;

} Endereco;

typedef struct
{
    int tamanho, quantidade, codigo;
    char cor[10], marca[10], modelo[20], data[9];
    Endereco end_estoque;
} Produto;

void Ler(void);
void entrada_produtos(void);
void verifica_estoque(void); // verificar se a prateleira está cheia ou não

int main()
{
    int opcao;

    do
    {
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
        case 0: // Usuario escolhe 0 que sai do programa
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
    int num = 0, i;

    do
    {
        if ((arq = fopen(arquivoPRO, "ab")) == NULL) // se arq for null, deu algum erro na criação do arquivo
        {
            fprintf(stderr, "\n\tImpossivel abrir o arquivo %s!\n", arquivoPRO); // o erro sai em uma mensagem de erro pelo stder
        }

        fseek(arq, 0, SEEK_END); // Função para escolher de onde começará a leitura ou escrita no arquivo, no caso será possível escrever a partir do final

        if (ftell(arq) / sizeof(Produto) >= ESTOQUE)
        {

            system("cls");
            printf("\n\tEstoque cheio, impossivel cadastrar!");
            break;
        }
        else
        {
            x.codigo = ftell(arq) / sizeof(Produto) + 1; // A ftell dimensiona o tamanho do arquivo em byte, o sizeof faz o mesmo porém com o Produto
                                                         // Ao realizar a divisão consigo ter o número de produtos que tem dentro do arquivo, com esse valor
                                                         //somado a um eu tenho o código do próximo produto.
            x.end_estoque.box = ftell(arq) / sizeof(Produto) + 1;
            if (x.end_estoque.box > ARMARIO)
            {
                x.end_estoque.armario = 2;
            }
            else
            {
                x.end_estoque.armario = 1;
            }
            system("cls");
            printf("\n\n\t-------------------------------------------------\n"); // Barra t da um tipo de espaçamento como se estivesse apertando o TAB
            printf("\t|           Cadastro de novos Produtos          |\n");
            printf("\t-------------------------------------------------\n");
            printf("\n\tPara cadastrar novos produtos, basta preencher as informacoes solicitadas! \n\n");
            printf("\n\tCodigo: %d", x.codigo); // Como o numero do código é gerado automaticamente, então basta imprimir 
            printf("\n\tEndereco: A%d-B%d", x.end_estoque.armario, x.end_estoque.box); // Como o endereçamento é gerado automaticamente, então basta imprimir 
            _strdate(x.data); // Função para puxar a data atual do sistema
            printf("\n\tData de cadastro: %s", x.data);
            printf("\n\tModelo: ");
            fflush(stdin);         // Limpa o buffer para ler string sem erros
            scanf("%s", x.modelo); // Recebe a string e armazena no modelo do produto
            printf("\tMarca: ");
            fflush(stdin);
            scanf("%s", x.marca); // Recebe a string e armazena na marca do produto
            printf("\tCor: ");
            fflush(stdin);
            scanf("%s", x.cor); // Recebe a string e armazena na cor do produto
            printf("\tTamanho: ");
            scanf("%d", &x.tamanho);             // Recebe o inteiro e armazena o tamanho produto
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
        }
    } while (num == 1);
    system("cls");
}
