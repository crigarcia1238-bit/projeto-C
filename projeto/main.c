#include <stdio.h>
#include "filmes.h"

int main() {
  static Filme filmes[MAX_FILMES];
    int totalFilmes = 0;
    int opcao, sub;

    // ------------------------ menu principal -------------------------
    do {
        printf("\n===== MENU FILMES =====\n");
        printf("1 - Listar todos os filmes\n");
        printf("2 - Pesquisar filmes por criterio\n");
        printf("3 - Consultar informacao de um filme\n");
        printf("4 - Adicionar filme\n");
        printf("5 - Alterar filme\n");
        printf ("6 - Eliminar filme\n");
        printf("7 - Eliminar todos os filmes\n");
        printf("8 - Importar filmes de um arquivo CSV\n");
        printf("9- exportar filmes de um arquivo CSV\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao); getchar();

        switch (opcao) {

        case 1:
            printf("\n listar por:\n");
            printf("1 - Codigo crescente\n");
            printf("2 - Rating decrescente\n");
            printf("3 - Ordem Alfabetica (A-Z)\n");
            scanf("%d", &sub); getchar(); // o scanf le o \n do enter e o getchar limpa o buffer

            if (sub == 1) pesquisarPorCodigo(filmes, totalFilmes);
            else if (sub == 2) pesquisarPorRating(filmes, totalFilmes);
            else if (sub == 3) pesquisarPorTituloAlfabetico(filmes, totalFilmes);
            break;

        case 2:
            printf("\nPesquisar por:\n");
            printf("1 - Titulo\n");
            printf("2 - Genero\n");
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
            printf("Codigo: ");
            scanf("%d", &code); getchar();
            consultarFilme(filmes, totalFilmes, code);
            break;
        }
        
        case 4:
            adicionarFilme(filmes, &totalFilmes);
            break;
        case 5:
            alterarFIlme(filmes, totalFilmes);
            break;
        case 6: {
            int code;
            printf("Codigo do filme a eliminar: ");
            scanf("%d", &code); getchar();
            eliminarFilme(filmes, &totalFilmes, code);
            break;
        }
        case 7:
            eliminarTodosFilmes(filmes, &totalFilmes);
            break;
        case 8:
            importarFilmesCSV(filmes, &totalFilmes);
            break;
        case 9:
            exportarFilmesCSV(filmes, &totalFilmes);
            break;
        case 0:
            printf("A sair...\n");
            break;

        default:
            printf("Opção invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
