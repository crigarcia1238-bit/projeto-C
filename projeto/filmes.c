#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "filmes.h"

// Array com nomes dos géneros
const char *generoNomes[20] = {
    "ACTION", "ADVENTURE", "ANIMATION", "BIOGRAPHY", "COMEDY",
    "CRIME", "DRAMA", "FAMILY", "FANTASY", "HISTORY",
    "HORROR", "MUSIC", "MUSICAL", "MYSTERY", "ROMANCE",
    "SCI-FI", "SPORT", "THRILLER", "WAR", "WESTERN"
};

// Limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --------------------- adicionar um filme

void adicionarFilme(Filme filmes[], int *totalFilmes) {
    if (*totalFilmes >= MAX_FILMES) {
        printf("Limite de filmes atingido!\n");
        return;
    }

    Filme f;
    f.code = *totalFilmes + 1;

    printf("\n=== Adicionar Filme ===\n");

    // Título
    printf("Titulo: ");
    fgets(f.title, MAX_STR, stdin);
    f.title[strcspn(f.title, "\n")] = 0;

    // Número de géneros
    printf("Numero de generos (max %d): ", MAX_GENEROS);
    do {
        scanf("%d", &f.numGenres); limparBuffer();
        if (f.numGenres < 1) {
            printf("Erro: deve haver pelo menos 1 genero. Tente novamente: ");
        } else if (f.numGenres > MAX_GENEROS) {
            f.numGenres = MAX_GENEROS;
        }
    } while (f.numGenres < 1);

    // Seleção de géneros
    for (int i = 0; i < f.numGenres; i++) {
        int g;
        do {
            printf("Digite o numero do genero (0-19): ");
            scanf("%d", &g); limparBuffer();

            if (g < 0 || g > 19) {
                printf("Genero invalido! Tente novamente.\n");
            } else {
                printf("Genero selecionado: %s\n", generoNomes[g]);
            }
        } while (g < 0 || g > 19);

        f.genres[i] = (genero)g;
    }

    // Descrição
    printf("Descricao: ");
    fgets(f.description, MAX_STR, stdin);
    f.description[strcspn(f.description, "\n")] = 0;

    // Realizador
    printf("Realizador: ");
    fgets(f.director, MAX_STR, stdin);
    f.director[strcspn(f.director, "\n")] = 0;

    // Número de atores
    printf("Numero de atores (max %d): ", MAX_ACTORES);
    do {
        scanf("%d", &f.numActors); limparBuffer();
        if (f.numActors < 0) {
            printf("Erro: o numero de atores nao pode ser negativo. Tente novamente: ");
        } else if (f.numActors > MAX_ACTORES) {
            f.numActors = MAX_ACTORES;
        }
    } while (f.numActors < 0);

    // Inserir atores
    for (int i = 0; i < f.numActors; i++) {
        printf("Ator %d: ", i + 1);
        fgets(f.actors[i], MAX_STR, stdin);
        f.actors[i][strcspn(f.actors[i], "\n")] = 0;
    }

    // Ano
    printf("Ano: ");
    scanf("%d", &f.year); limparBuffer();

    // Duração (>0)
    do {
        printf("Duracao (minutos > 0): ");
        scanf("%d", &f.duration); limparBuffer();
        if (f.duration <= 0) {
            printf("Erro: a duracao tem de ser maior que 0.\n");
        }
    } while (f.duration <= 0);

    // Rating (0-10)
    do {
        printf("Rating (0-10): ");
        scanf("%f", &f.rating); limparBuffer();
        if (f.rating < 0.0 || f.rating > 10.0) {
            printf("Erro: o rating tem de estar entre 0 e 10.\n");
        }
    } while (f.rating < 0.0 || f.rating > 10.0);

    // Favoritos
    printf("Favoritos: ");
    scanf("%d", &f.favorite); limparBuffer();

    // Receita
    printf("Receita (milhoes): ");
    scanf("%f", &f.revenue); limparBuffer();

    // Adicionar ao array de filmes
    filmes[*totalFilmes] = f;
    (*totalFilmes)++;

    printf("Filme adicionado com sucesso! Codigo: %d\n", f.code);
}




//--------------------- listagem de todos os filmes

void pesquisarPorCodigo(Filme filmes[], int totalFilmes) {
    printf("\n=== Listagem por codigo ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        Filme f = filmes[i];
        printf("%d | %s | Rating %.1f | Ano %d\n",
               f.code, f.title, f.rating, f.year);
    }
}

void pesquisarPorRating(Filme filmes[], int totalFilmes) {
    static Filme temp[MAX_FILMES]; // array temporário para ordenar sem alterar o original
    memcpy(temp, filmes, sizeof(Filme) * totalFilmes); // copia os filmes

     // algoritmo de ordenação (bubble sort) baseado no rating
    for (int i = 0; i < totalFilmes - 1; i++)
        for (int j = i + 1; j < totalFilmes; j++)
            if (temp[j].rating > temp[i].rating) {
                Filme t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }

            // impressão dos filmes ordenados
    printf("\n=== listar por rating ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        Filme f = temp[i];
        printf("%d | %s | %.1f\n", f.code, f.title, f.rating);
    }
}

// Listagem de filmes por título em ordem alfabética (A-Z)
void pesquisarPorTituloAlfabetico(Filme filmes[], int totalFilmes) {
   static Filme temp[MAX_FILMES];
    memcpy(temp, filmes, sizeof(Filme) * totalFilmes);

    for (int i = 0; i < totalFilmes - 1; i++)
        for (int j = i + 1; j < totalFilmes; j++)
            if (strcmp(temp[j].title, temp[i].title) < 0) {
                Filme t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }

            // impressão dos filmes ordenados
    printf("\n=== listar por titulo (A-Z) ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        Filme f = temp[i];
        printf("%d | %s\n", f.code, f.title);
    }
}


// --------------------- pesquisa geral

// Pesquisa filmes pelo titulo
void pesquisarPorTitulo(Filme filmes[], int totalFilmes) {
    char termo[MAX_STR];
    printf("Parte do titulo: ");
    fgets(termo, MAX_STR, stdin); // lê a string que o usuário digitou
    termo[strcspn(termo, "\n")] = 0; // remove o '\n' final

    printf("\n=== resultados ===\n");
    for (int i = 0; i < totalFilmes; i++) {
        if (strstr(filmes[i].title, termo) != NULL) {
            Filme f = filmes[i];
            printf("%d | %s | %.1f\n", f.code, f.title, f.rating);
        }
    }
}

// Pesquisa filmes por gênero
void pesquisarPorGenero(Filme filmes[], int totalFilmes) {
    int g;
    printf("Digite o numero do género (0-19): ");
    scanf("%d", &g); limparBuffer();

    if (g < 0 || g > 19) {
        printf("Genero invalido!\n");
        return;
    }

    printf("Genero selecionado: %s\n", generoNomes[g]);
    printf("\n=== resultados ===\n");
    for (int i = 0; i < totalFilmes; i++)
        for (int j = 0; j < filmes[i].numGenres; j++)
            if (filmes[i].genres[j] == g) // verifica se o filme contém o gênero
                printf("%d | %s | %.1f\n", filmes[i].code, filmes[i].title, filmes[i].rating);
}

// Pesquisa filmes por realizador
void pesquisarPorRealizador(Filme filmes[], int totalFilmes) {
    char dir[MAX_STR];
    printf("Realizador: ");
    fgets(dir, MAX_STR, stdin);
    dir[strcspn(dir, "\n")] = 0;

    printf("\n=== resultados ===\n");
    for (int i = 0; i < totalFilmes; i++)
        if (strcasecmp(filmes[i].director, dir) == 0) // compara ignorando maiúsculas/minúsculas
            printf("%d | %s | %s\n", filmes[i].code, filmes[i].title, filmes[i].director);
}

// Pesquisa filmes por ator
void pesquisarPorAtor(Filme filmes[], int totalFilmes) {
    char nome[MAX_STR];
    printf("Ator: ");
    fgets(nome, MAX_STR, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("\n=== resultados ===\n");
    for (int i = 0; i < totalFilmes; i++)
        for (int j = 0; j < filmes[i].numActors; j++)
            if (strcasecmp(filmes[i].actors[j], nome) == 0)
                printf("%d | %s | %s\n", filmes[i].code, filmes[i].title, filmes[i].actors[j]);
}


// --------------------- consultar pelo code

void consultarFilme(Filme filmes[], int totalFilmes, int code) {
    for (int i = 0; i < totalFilmes; i++)
        if (filmes[i].code == code) { // verifica se o código bate com o que o utilizador inseriu   
            Filme f = filmes[i];

            printf("\n=== detalhes do filme ===\n");
            printf("Codigo: %d\n", f.code);
            printf("Titulo: %s\n", f.title);

                // lista os gêneros
            printf("Generos: ");
            for (int j = 0; j < f.numGenres; j++)
                printf("%s ", generoNomes[f.genres[j]]);
            printf("\n");

            printf("Descricao: %s\n", f.description);
            printf("Realizador: %s\n", f.director);

            printf("Atores: ");
            for (int j = 0; j < f.numActors; j++)
                printf("%s; ", f.actors[j]);
            printf("\n");

            printf("Ano: %d\n", f.year);
            printf("Duração: %d\n", f.duration);
            printf("Rating: %.1f\n", f.rating);
            printf("Favoritos: %d\n", f.favorite);
            printf("Receita: %.1f milhoes\n", f.revenue);
            return; // filme encontrado, sai da função
        }
    printf("Filme nao encontrado!\n"); // caso não encontre
}
