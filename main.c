#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.c"
#include "abp.h"
#include "avl.c"
#include "avl.h"
#define ROW_SIZE 100

/* Exemplo de uso dos argumentos para main
O programa l� um arquivo texto como entrada e gera um arquivo como sa�da com o conte�do do arquivo de entrada convertido para letras min�sculas
Para chamar, digite "exemplo entrada.txt saida.txt" */


int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end; //para contar o tempo decorrido

    FILE * entrada_dados;
    FILE * entrada_usuario;
    FILE * saida;

    // Cria árvores
    NodoAVL* raiz_avl = inicializaAVL(raiz_avl);
    NodoAVL* achado_avl = inicializaAVL(achado_avl);

    NodoABP* raiz_abp = inicializaABP(raiz_abp);
    NodoABP* achado_abp = inicializaABP(achado_abp);

    // Variável de controle da inserção da AVL e contador de rotações

    int ok = 0,rot = 0;

    char *titulo_jogo, *jogo, linha[ROW_SIZE]; // linhas a serem lidas do arquivo
    float horas = 0;
    float soma_abp = 0, soma_avl = 0;
    char *separador = ",";

    //comentario

    if (argc!=4)  //o numero de parametros esperado 4: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("Numero incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_csv> <arq_txt> <arq_saida>\n");
        return 1;
    }

    else
    {

        entrada_dados = fopen (argv[1], "r"); // abre o arquivo csv para leitura -- argv[1] é o primeiro arquivo para leitura
        entrada_usuario = fopen (argv[2], "r");

        if (entrada_dados == NULL || entrada_usuario == NULL) //se não conseguiu abrir o arquivo
        {
            if (entrada_dados == NULL)
                printf ("Erro ao abrir o arquivo %s",argv[1]);
            else
                printf ("Erro ao abrir o arquivo %s",argv[2]);
            return 1;
        }

        else // arquivo de entrada OK
        {

            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.

            start = clock(); //inicia a contagem do tempo

            

            //percorre todo o arquivo lendo linha por linha
            while (fgets(linha,ROW_SIZE,entrada_dados))
            {
                
                titulo_jogo = strtok (linha, separador); // lê o arquivo csv separando por virgulas
                horas = atof(strtok (NULL, separador));

                // Escrever aqui o código que popula a árvore
                raiz_avl = InsereAVL(raiz_avl, titulo_jogo, horas, &ok, &rot);
                raiz_abp = InsereArvore(raiz_abp, titulo_jogo, horas);

            }

            printf("Numero de rotacoes: %d\n", rot);

            //percorre todo o arquivo lendo linha por linha
            while(fgets(linha,ROW_SIZE,entrada_usuario))
            {
                achado_abp = consultaABP(raiz_abp, linha);
                achado_avl = consultaAVL(raiz_avl, linha);
                
                soma_abp += achado_abp->horas;
                soma_avl += achado_avl->horas;
               
                // Aqui não é necessário usar o strtok, porque cada nome do jogo vai estar em uma nova linha
                // Escrever aqui o código que procura um jogo em determinada árvore
                // Note que o nome do jogo vai estar salvo na variável 'linha'

                
            }

            printf("Total de comparações ABP: %d\n", comp1);
            printf("Total de comparações AVL: %d\n", comp2);

            if(soma_abp == soma_avl)
                printf("A soma das horas é: %.2f\n", soma_abp);

            printf("\nArquivo %s gerado com sucesso.\n",argv[3]);

            end = clock(); // finaliza contagem do tempo
            float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
            printf("Tempo: %.5f ms\n",miliseconds);
        }
        fclose (entrada_dados); //fecha os arquivos
        fclose (entrada_usuario); 
        fclose (saida);
        return 0;
    }
}

//mudei algumas coisas como tinhamos falado naquele dia. fica a vontade pra testar se quiser. 
//ainda não faz nada com o arquivo que só vai ter jogos
//ja ta mais certo lidando com o outro e ja existe as variaveis, inicialização e etc do arquivo q nn tinha