#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <stdlib.h>
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
   do {
    printf("Numero de generos (1 a %d): ", MAX_GENEROS);
    scanf("%d", &f.numGenres);
    limparBuffer();

    if (f.numGenres < 1 || f.numGenres > MAX_GENEROS) {
        printf("Erro: o numero de generos deve estar entre 1 e %d.\n", MAX_GENEROS);
    }
} while (f.numGenres < 1 || f.numGenres > MAX_GENEROS);


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
   do {
    printf("Numero de atores (1 a %d): ", MAX_ACTORES);
    scanf("%d", &f.numActors); 
    limparBuffer();

    if (f.numActors < 1 || f.numActors > MAX_ACTORES) {
        printf("Erro: o numero de atores deve estar entre 1 e %d.\n", MAX_ACTORES);
    }
} while (f.numActors < 1 || f.numActors > MAX_ACTORES);


    // Inserir atores
    for (int i = 0; i < f.numActors; i++) {
        printf("Ator %d: ", i + 1);
        fgets(f.actors[i], MAX_STR, stdin);
        f.actors[i][strcspn(f.actors[i], "\n")] = 0;
    }

    // Ano (>0) e apenas numeros 
    int anoOK = 0;
    do {
            printf("Ano: "); 
        if (scanf("%d", &f.year) != 1) {
            printf("Erro: insira apenas numeros!\n");
        while (getchar() != '\n'); // limpa buffer
        } else if (f.year <= 0) {
            printf("Erro: o ano tem de ser maior que 0!\n");
        } else {
            anoOK = 1;
            getchar(); // consome '\n' restante
        }
    } while (!anoOK);



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

    
   // Favoritos (apenas número)
    int favOK = 0;
    do {
        printf("Favoritos (apenas numero): ");
        if (scanf("%d", &f.favorite) != 1) {
            printf("Erro: insira apenas numeros!\n");
            while (getchar() != '\n'); // limpa buffer
        } else {
            favOK = 1;
            getchar(); // consome '\n'
        }
    } while (!favOK);


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

// -----------------------------Parte do Adam----------------------------------------------
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
// --------------------- alterar filme existente
void alterarFIlme(Filme filmes[], int totalFilmes) {
    int code;
    printf("Digite o codigo do filme a alterar: ");
    scanf("%d", &code);
    limparBuffer();
    printf (" quer alterar o que no filme %d? \n", code);
    printf ("1 - Titulo \n");
    printf ("2 - Generos \n");
    printf ("3 - Ano \n");
    printf ("4 - Duracao \n");
    printf ("5 - Rating \n");
    printf ("6 - Favoritos \n");
    printf ("7 - Receita \n");
    int opcao;
    scanf ("%d", &opcao);
    limparBuffer();
    for (int i = 0; i < totalFilmes; i++) {
        if (filmes[i].code == code) {
            switch (opcao) {
                case 1: // ---------titulo
                do {
                    printf("Novo Titulo: ");
                    fgets(filmes[i].title, MAX_STR, stdin);
                    filmes[i].title[strcspn(filmes[i].title, "\n")] = 0;
                } while (strlen(filmes[i].title) == 0);
                break;
                case 2: // --------generos
                    printf("Numero de generos (max %d): ", MAX_GENEROS);
                    do {
                        scanf("%d", &filmes[i].numGenres); limparBuffer();
                        if (filmes[i].numGenres < 1) {
                            printf("Erro: deve haver pelo menos 1 genero. Tente novamente: ");
                        } else if (filmes[i].numGenres > MAX_GENEROS) {
                            filmes[i].numGenres = MAX_GENEROS;
                        }
                    } while (filmes[i].numGenres < 1);

                    // Seleção de géneros
                    for (int j = 0; j < filmes[i].numGenres; j++) {
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

                        filmes[i].genres[j] = (genero)g;
                    }
                    break;
                case 3: // -------ano
                    do {
                        printf("Novo Ano: ");
                        scanf("%d", &filmes[i].year); 
                        limparBuffer();
                        if (filmes[i].year <= 1888 || filmes[i].year > 2026) {
                            printf("Erro: o ano tem de ser maior que 1888!\n");
                        }
                    } while (filmes[i].year <= 1888 || filmes[i].year > 2026); //ano valido
                    break;
                case 4: // -------duracao
                    do {
                        printf("Nova Duracao (minutos > 0): ");
                        scanf("%d", &filmes[i].duration); 
                        limparBuffer();
                        if (filmes[i].duration <= 0) {
                            printf("Erro: a duracao tem de ser maior que 0.\n");
                        }
                    } while (filmes[i].duration <= 0);
                    break;
                case 5: // --------rating
                    do {
                        printf("Novo Rating (0-10): ");
                        scanf("%f", &filmes[i].rating); 
                        limparBuffer();
                        if (filmes[i].rating < 0.0 || filmes[i].rating > 10.0) {
                            printf("Erro: o rating tem de estar entre 0.0 e 10.0.\n");
                        }
                    } while (filmes[i].rating < 0.0 || filmes[i].rating > 10.0);
                    break;
                case 6:  // --------favoritos
                    do {
                        printf("Novo Favorito (0 = nao | 1 = sim): ");
                        scanf("%d", &filmes[i].favorite);
                        limparBuffer();
                    } while (filmes[i].favorite < 0 || filmes[i].favorite > 1);
                    break;
                
                case 7:   // -------receita
                    do {
                        printf("Nova Receita (milhoes): ");
                        scanf("%f", &filmes[i].revenue); 
                        limparBuffer();
                        if (filmes[i].revenue < 0.0) {
                            printf("Erro: a receita nao pode ser negativa.\n");
                        }
                    } while (filmes[i].revenue < 0.0);
                default:
                    printf("Opcao invalida!\n");
            }
            printf("Filme alterado com sucesso!\n");
            return;
        }
    }
}
// --------------------- eliminar filme existente
void eliminarFilme(Filme filmes[], int *totalFilmes, int code){
    printf("\n o filme com codigo %d foi encontrado! \n", code);
    printf("A eliminar o filme com codigo %d...\n", code);
    for (int i = 0; i < *totalFilmes; i++) {
        if (filmes[i].code == code) {
            // Move todos os filmes após o filme a ser eliminado uma posição para trás
            for (int j = i; j < *totalFilmes - 1; j++) {
                filmes[j] = filmes[j + 1];
            }
            char op;
            printf("Tem a certeza que deseja eliminar o filme com codigo %d? (s/n): ", code);
            scanf(" %c", &op);
            limparBuffer();
            if (op == 'N' || op == 'n') {
                printf("Eliminacao cancelada.\n");
                return;
            }
            else {
                (*totalFilmes)--; // Decrementa o total de filmes
                printf("Filme com codigo %d eliminado com sucesso!\n", code);
                return;
            }
        }
    }
    printf("Filme com codigo %d nao encontrado!\n", code);
}

// Eliminar todos os filmes
void eliminarTodosFilmes(Filme filmes[], int *totalFilmes){
    char op;
    printf("Tem a certeza que deseja eliminar todos os filmes? (s/n): ");
    scanf(" %c", &op);
    limparBuffer();
    if (op == 'N' || op == 'n') {
        printf("Eliminacao cancelada.\n");
        return;
    }
    else {
        *totalFilmes = 0; // Define o total de filmes para 0
        printf("Todos os filmes foram eliminados com sucesso!\n");
    }
}
// -----------------Verifica se um filme existe pelo código

// converte string para uppercase
void toUpper(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
}

// troca ',' por '.' (decimais)
void corrigirDecimal(char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] == ',')
            str[i] = '.';
}

// converte nome do género para enum
int generoFromString(char *g) {
    toUpper(g);
    for (int i = 0; i < 20; i++)
        if (strcmp(g, generoNomes[i]) == 0)
            return i;
    return -1;
}

int importarFilmesCSV(Filme filmes[], int *totalFilmes) {
    FILE *f = fopen("movies_all.csv", "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro CSV!\n");
        return 0;
    }

    char linha[2048];
    fgets(linha, sizeof(linha), f); // ignora cabeçalho

    while (fgets(linha, sizeof(linha), f)) {
        if (*totalFilmes >= MAX_FILMES) break;

        Filme fme;
        char genresStr[MAX_STR], actorsStr[500];
        char ratingStr[20], revenueStr[20];

        linha[strcspn(linha, "\n")] = 0;

        sscanf(linha,
            "%d,%199[^,],%199[^,],%199[^,],%199[^,],%499[^,],%d,%d,%19[^,],%d,%19[^,\n]",
            &fme.code,
            fme.title,
            genresStr,
            fme.description,
            fme.director,
            actorsStr,
            &fme.year,
            &fme.duration,
            ratingStr,
            &fme.favorite,
            revenueStr
        );

        // -------- géneros
        fme.numGenres = 0;
        char *tok = strtok(genresStr, "|");
        while (tok && fme.numGenres < MAX_GENEROS) {
            int g = generoFromString(tok);
            if (g != -1)
                fme.genres[fme.numGenres++] = g;
            tok = strtok(NULL, "|");
        }

        // -------- atores
        fme.numActors = 0;
        tok = strtok(actorsStr, "|");
        while (tok && fme.numActors < MAX_ACTORES) {
            strcpy(fme.actors[fme.numActors++], tok);
            tok = strtok(NULL, "|");
        }

        // -------- números
        corrigirDecimal(ratingStr);
        corrigirDecimal(revenueStr);
        fme.rating = atof(ratingStr);
        fme.revenue = atof(revenueStr);

        filmes[*totalFilmes] = fme;
        (*totalFilmes)++;
    }

    fclose(f);
    printf("Importacao concluida! Filmes carregados: %d\n", *totalFilmes);
    return 1;
}

// ---------------exportar filmes pro ficheiro cvs

int exportarFilmesCSV(Filme filmes[], int *totalFilmes) {
    FILE *f = fopen("movies_export.csv", "w");

    if (!f) {
        printf("Erro ao criar o ficheiro CSV!\n");
        return 0;
    }

    // cabeçalho
    fprintf(f,
        "code,title,genres,description,director,actors,year,duration,rating,favorite,revenue\n"
    );

    for (int i = 0; i < *totalFilmes; i++) {
        Filme fm = filmes[i];

        // ---- escrever géneros
        char genresStr[200] = "";
        for (int g = 0; g < fm.numGenres; g++) {
            strcat(genresStr, generoNomes[fm.genres[g]]);
            if (g < fm.numGenres - 1)
                strcat(genresStr, "|");
        }

        // ---- escrever atores
        char actorsStr[400] = "";
        for (int a = 0; a < fm.numActors; a++) {
            strcat(actorsStr, fm.actors[a]);
            if (a < fm.numActors - 1)
                strcat(actorsStr, "|");
        }

        // ---- escrever linha CSV
        fprintf(f,
            "%d,%s,%s,%s,%s,%s,%d,%d,%.1f,%d,%.1f\n",
            fm.code,
            fm.title,
            genresStr,
            fm.description,
            fm.director,
            actorsStr,
            fm.year,
            fm.duration,
            fm.rating,
            fm.favorite,
            fm.revenue
        );
    }

    fclose(f);
    printf("Filmes exportados com sucesso para movies_export.csv\n");
    return -1;
}