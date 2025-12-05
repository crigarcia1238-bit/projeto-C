#include <stdio.h>
#include "filmes.h"

int main() {
      printf("Programa iniciou!\n");
    Filme filmes[MAX_FILMES];
    int totalFilmes = 0;
    int opcao, sub;

    do {
        printf("\n===== MENU FILMES =====\n");
        printf("1 - Pesquisar todos os filmes\n");
        printf("2 - Pesquisar filmes por critério\n");
        printf("3 - Consultar informação de um filme\n");
        printf("4 - Adicionar filme\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao); getchar();

        switch (opcao) {

        case 1:
            printf("\nPesquisar por:\n");
            printf("1 - Código crescente\n");
            printf("2 - Rating decrescente\n");
            printf("3 - Ordem Alfabetica (A-Z)\n");
            scanf("%d", &sub); getchar();

            if (sub == 1) pesquisarPorCodigo(filmes, totalFilmes);
            else if (sub == 2) pesquisarPorRating(filmes, totalFilmes);
            else if (sub == 3) pesquisarPorTituloAlfabetico(filmes, totalFilmes);
            break;

        case 2:
            printf("\nPesquisar por:\n");
            printf("1 - Título\n");
            printf("2 - Género\n");
            printf("3 - Realizador\n");
            printf("4 - Ator\n");
            scanf("%d", &sub); getchar();

            if (sub == 1) pesquisarPorTitulo(filmes, totalFilmes);
            else if (sub == 2) pesquisarPorGenero(filmes, totalFilmes);
            else if (sub == 3) pesquisarPorRealizador(filmes, totalFilmes);
            else if (sub == 4) pesquisarPorAtor(filmes, totalFilmes);
            break;

        case 3: {
            int code;
            printf("Código: ");
            scanf("%d", &code); getchar();
            consultarFilme(filmes, totalFilmes, code);
            break;
        }

        case 4:
            adicionarFilme(filmes, &totalFilmes);
            break;

        case 0:
            printf("A sair...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
