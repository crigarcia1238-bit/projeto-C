

typedef enum {
    ACTION, ADVENTURE, ANIMATION, BIOGRAPHY, COMEDY, CRIME, DRAMA, FAMILY,
    FANTASY, HISTORY, HORROR, MUSIC, MUSICAL, MYSTERY, ROMANCE, SCI_FI,
    SPORT, THRILLER, WAR, WESTERN, GENRE_COUNT
} Genero;

typedef struct {
    int code;
    char title[100];
    Genero genres[5];
    int genre_count;
    char description[500];
    char director[50];
    char actors[200];
    int year;
    int duration; 
    float rating; 
    int favorite;
    float revenue; 
} Filme;


void listar_filmes(Filme filmes[], int n, int criterio);
void pesquisar_por_titulo(Filme filmes[], int n, const char* str);
void pesquisar_por_genero(Filme filmes[], int n, Genero g);
void pesquisar_por_diretor(Filme filmes[], int n, const char* diretor);
void pesquisar_por_ator(Filme filmes[], int n, const char* ator);
void consultar_filme(Filme filmes[], int n, int codigo);
int adicionar_filme(Filme filmes[], int* n, int* prox_codigo);

const char* get_genre_name(Genero g);

