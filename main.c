#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "abp.h"
#include "abp.c"
#include "avl.c"
#include "avl.h"
#define ROW_SIZE 100

/* O programa le dois arquivos como entrada e gera um arquivo texto como saida 
com o conteudo especificado no enunciado do trabalho. */

int main(int argc, char *argv[]) //argc conta o numero de parametros e argv armazena as strings correspondentes aos paramentros digitados
{

    clock_t start, end; //para contar o tempo decorrido

    //declaracao de ponteiros para arquivos
    FILE * entrada_dados;
    FILE * entrada_usuario;
    FILE * saida;

    

    // Cria árvores e nodos para busca
    NodoAVL* raiz_avl = inicializaAVL(raiz_avl);
    NodoAVL* achado_avl = inicializaAVL(achado_avl);

    NodoABP* raiz_abp = inicializaABP(raiz_abp);
    NodoABP* achado_abp = inicializaABP(achado_abp);

    // Variável de controle da inserção da AVL e contador de rotações

    int ok = 0, rot = 0, i = 0;

    char *titulo_jogo, *jogo, linha[ROW_SIZE]; // linhas a serem lidas do arquivo
    float horas = 0;
    float soma_abp = 0, soma_avl = 0;
    char *separador = ",";

    if (argc!=4)  
    //o numero de parametros esperado 4: nome do programa (argv[0]), 
    //nome do arq de entrada que tem os jogos e as horas(argv[1]), 
    //nome do arquivo de entrada com os jogos que o usuario escolheu(argv[1]),
    //nome do arq de saida(argv[3])
    {
        printf ("Numero incorreto de parâmetros.\n Para chamar o programa digite: exemplo <arq_csv> <arq_txt> <arq_saida>\n");
        return 1;
    }

    else
    {

        entrada_dados = fopen (argv[1], "r"); // abre o arquivo csv para leitura -- argv[1] eh o primeiro arquivo para leitura
        entrada_usuario = fopen (argv[2], "r");//abre o arquivo txt para leitura -- argv[2] eh o segundo arquivo para leitura

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

            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[3] eh o arquivo para escrita

            start = clock(); //inicia a contagem do tempo
            
            //percorre todo o arquivo lendo linha por linha
            while (fgets(linha,ROW_SIZE,entrada_dados))
            {
                
                titulo_jogo = strtok (linha, separador); // lê o arquivo csv separando por virgulas

                horas = strtof(strtok (NULL, separador), NULL);

                raiz_avl = InsereAVL(raiz_avl, titulo_jogo, horas, &ok, &rot);

                raiz_abp = InsereArvore(raiz_abp, titulo_jogo, horas);

            }

            //printf("Numero de rotacoes: %d\n", rot);  -- teste de rotacoes

            //percorre todo o arquivo lendo linha por linha
            while(fgets(linha,ROW_SIZE,entrada_usuario))
            {

                if(linha[strlen(linha)-1] == '\n')
                    linha[strlen(linha)-1] = '\0';

                achado_abp = consultaABP(raiz_abp, linha);

                if(achado_abp)
                {
                    soma_abp += achado_abp->horas;
                }


                achado_avl = consultaAVL(raiz_avl, linha);

                if(achado_avl)
                {
                    soma_avl += achado_avl->horas;
                }
                
            }

            //printf("Soma ABP: %.2f\n", soma_abp); - teste soma de horas abp
            //printf("Soma AVL: %.2f\n", soma_avl); - teste soma de horas avl
            
            //verifica se as somas das horas estao iguais
            if(soma_abp == soma_avl) 
            {
                //imprime no arquivo de saida as informacoes solicitadas
                fprintf(saida,"Tempo total estimado: %.2f horas\n\n", soma_abp);

                fprintf(saida,"================ ESTATÍSTICAS ABP ================== \n");
                fprintf(saida,"Número de nodos: %d\n", ContaNodosABP(raiz_abp));
                fprintf(saida,"Altura: %d\n",AlturaABP(raiz_abp));
                fprintf(saida,"Rotações: 0\n");
                fprintf(saida,"Comparações: %d\n\n", comp1);
                
                fprintf(saida,"================ ESTATÍSTICAS AVL ================== \n");
                fprintf(saida,"Número de nodos: %d\n", ContaNodosAVL(raiz_avl));
                fprintf(saida,"Altura: %d\n",AlturaAVL(raiz_avl));
                fprintf(saida,"Rotações: %d\n", rot);
                fprintf(saida,"Comparações: %d\n", comp2);

            }
                
            printf("\nArquivo %s gerado com sucesso.\n",argv[3]); //mensagem de sucesso

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





