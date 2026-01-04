#pragma once

#define MAX_STR 200
#define MAX_ACTORES 20
#define MAX_GENEROS 5
#define MAX_FILMES 2000

typedef enum {
    ACTION, ADVENTURE, ANIMATION, BIOGRAPHY, COMEDY,
    CRIME, DRAMA, FAMILY, FANTASY, HISTORY, HORROR,
    MUSIC, MUSICAL, MYSTERY, ROMANCE, SCI_FI,
    SPORT, THRILLER, WAR, WESTERN
} genero;

typedef struct {
    int code;
    char title[MAX_STR];
    genero genres[MAX_GENEROS];
    int numGenres;
    char description[MAX_STR];
    char director[MAX_STR];
    char actors[MAX_ACTORES][MAX_STR];
    int numActors;
    int year;
    int duration;
    float rating;
    int favorite;
    float revenue;
} Filme;

// Funções
void adicionarFilme(Filme filmes[], int *totalFilmes);

void pesquisarPorCodigo(Filme filmes[], int totalFilmes);
void pesquisarPorRating(Filme filmes[], int totalFilmes);
void pesquisarPorTituloAlfabetico(Filme filmes[], int totalFilmes);

void pesquisarPorTitulo(Filme filmes[], int totalFilmes);
void pesquisarPorGenero(Filme filmes[], int totalFilmes);
void pesquisarPorRealizador(Filme filmes[], int totalFilmes);
void pesquisarPorAtor(Filme filmes[], int totalFilmes);

void consultarFilme(Filme filmes[], int totalFilmes, int code);

void alterarFIlme(Filme filmes[], int totalFilmes); 
void eliminarFilme(Filme filmes[], int *totalFilmes, int code);
void eliminarTodosFilmes(Filme filmes[], int *totalFilmes);
int filmeExiste(Filme filmes[], int total, int code);

int importarFilmesCSV(Filme filmes[], int *totalFilmes);
int exportarFilmesCSV(Filme filmes[], int *totalFilmes);