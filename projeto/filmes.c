#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "filmes.h"

// ======================================================
// ADICIONAR FILME
// ======================================================
void adicionarFilme(Filme filmes[], int *totalFilmes) {
    Filme f;
    f.code = *totalFilmes + 1;

    printf("\n=== Adicionar Filme ===\n");

    printf("Título: ");
    fgets(f.title, MAX_STR, stdin);
    f.title[strcspn(f.title, "\n")] = 0;

    printf("Número de géneros: ");
    scanf("%d", &f.numGenres); getchar();

    for (int i = 0; i < f.numGenres; i++) {
        int g;
        printf("Digite o número do género (0-19): ");
        scanf("%d", &g); getchar();
        f.genres[i] = (genero)g;
    }

    printf("Descrição: ");
    fgets(f.description, MAX_STR, stdin);
    f.description[strcspn(f.description, "\n")] = 0;

    printf("Realizador: ");
    fgets(f.director, MAX_STR, stdin);
    f.director[strcspn(f.director, "\n")] = 0;

    printf("Número de atores: ");
    scanf("%d", &f.numActors); getchar();

    for (int i = 0; i < f.numActors; i++) {
        printf("Ator %d: ", i + 1);
        fgets(f.actors[i], MAX_STR, stdin);
        f.actors[i][strcspn(f.actors[i], "\n")] = 0;
    }

    printf("Ano: ");
    scanf("%d", &f.year);

    printf("Duração: ");
    scanf("%d", &f.duration);

    printf("Rating (0-10): ");
    scanf("%f", &f.rating);

    printf("Favoritos: ");
    scanf("%d", &f.favorite);

    printf("Receita (milhões): ");
    scanf("%f", &f.revenue);
    getchar();

    filmes[*totalFilmes] = f;
    (*totalFilmes)++;

    printf("Filme adicionado com sucesso! Código: %d\n", f.code);
}

// ======================================================
// PESQUISAS POR ORDEM / CRITÉRIO
// ======================================================
void pesquisarPorCodigo(Filme filmes[], int totalFilmes) {
    printf("\n=== PESQUISAR POR CÓDIGO ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        Filme f = filmes[i];
        printf("%d | %s | Rating %.1f | Ano %d\n",
               f.code, f.title, f.rating, f.year);
    }
}

void pesquisarPorRating(Filme filmes[], int totalFilmes) {
    // ordenação decrescente
    for (int i = 0; i < totalFilmes - 1; i++)
        for (int j = i + 1; j < totalFilmes; j++)
            if (filmes[j].rating > filmes[i].rating) {
                Filme t = filmes[i];
                filmes[i] = filmes[j];
                filmes[j] = t;
            }

    printf("\n=== PESQUISAR POR RATING ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        Filme f = filmes[i];
        printf("%d | %s | %.1f\n", f.code, f.title, f.rating);
    }
}

void pesquisarPorTituloAlfabetico(Filme filmes[], int totalFilmes) {
    for (int i = 0; i < totalFilmes - 1; i++)
        for (int j = i + 1; j < totalFilmes; j++)
            if (strcmp(filmes[j].title, filmes[i].title) < 0) {
                Filme t = filmes[i];
                filmes[i] = filmes[j];
                filmes[j] = t;
            }

    printf("\n=== PESQUISAR POR TÍTULO (A-Z) ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        Filme f = filmes[i];
        printf("%d | %s\n", f.code, f.title);
    }
}

// ======================================================
// PESQUISAS POR STRING / CRITÉRIO
// ======================================================
void pesquisarPorTitulo(Filme filmes[], int totalFilmes) {
    char termo[MAX_STR];
    printf("Parte do título: ");
    fgets(termo, MAX_STR, stdin);
    termo[strcspn(termo, "\n")] = 0;

    printf("\n=== RESULTADOS ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        if (strstr(filmes[i].title, termo) != NULL) {
            Filme f = filmes[i];
            printf("%d | %s | %.1f\n", f.code, f.title, f.rating);
        }
    }
}

void pesquisarPorGenero(Filme filmes[], int totalFilmes) {
    int g;
    printf("Digite o número do género (0-19): ");
    scanf("%d", &g); getchar();

    printf("\n=== RESULTADOS ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        for (int j = 0; j < filmes[i].numGenres; j++) {
            if (filmes[i].genres[j] == g) {
                Filme f = filmes[i];
                printf("%d | %s | %.1f\n", f.code, f.title, f.rating);
            }
        }
    }
}

void pesquisarPorRealizador(Filme filmes[], int totalFilmes) {
    char dir[MAX_STR];
    printf("Realizador: ");
    fgets(dir, MAX_STR, stdin);
    dir[strcspn(dir, "\n")] = 0;

    printf("\n=== RESULTADOS ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        if (strcasecmp(filmes[i].director, dir) == 0) {
            Filme f = filmes[i];
            printf("%d | %s | %s\n", f.code, f.title, f.director);
        }
    }
}

void pesquisarPorAtor(Filme filmes[], int totalFilmes) {
    char nome[MAX_STR];
    printf("Ator: ");
    fgets(nome, MAX_STR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("\n=== RESULTADOS ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        for (int j = 0; j < filmes[i].numActors; j++) {
            if (strcasecmp(filmes[i].actors[j], nome) == 0) {
                Filme f = filmes[i];
                printf("%d | %s | %s\n", f.code, f.title, filmes[i].actors[j]);
            }
        }
    }
}

// ======================================================
// CONSULTAR DETALHES
// ======================================================
void consultarFilme(Filme filmes[], int totalFilmes, int code) {
    for (int i = 0; i < totalFilmes; i++) {
        if (filmes[i].code == code) {
            Filme f = filmes[i];
            printf("\n=== DETALHES DO FILME ===\n");
            printf("Código: %d\n", f.code);
            printf("Título: %s\n", f.title);

            printf("Géneros: ");
            for (int j = 0; j < f.numGenres; j++)
                printf("%d ", f.genres[j]);
            printf("\n");

            printf("Descrição: %s\n", f.description);
            printf("Realizador: %s\n", f.director);

            printf("Atores: ");
            for (int j = 0; j < f.numActors; j++)
                printf("%s; ", f.actors[j]);
            printf("\n");

            printf("Ano: %d\n", f.year);
            printf("Duração: %d\n", f.duration);
            printf("Rating: %.1f\n", f.rating);
            printf("Favoritos: %d\n", f.favorite);
            printf("Receita: %.1f milhões\n", f.revenue);
            return;
        }
    }
    printf("Filme não encontrado!\n");
}
