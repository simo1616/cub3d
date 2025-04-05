#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour gérer les positions et tailles
typedef struct s_list
{
    int x;
    int y;
} t_list;

// Vérifie si un caractère est autorisé
int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

// Algorithme flood fill récursif
void flood(char **tab, t_list size, t_list cur)
{
    if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x ||
        tab[cur.y][cur.x] == '1' || tab[cur.y][cur.x] == 'F')
        return;
    tab[cur.y][cur.x] = 'F'; // Marque la case comme visitée
    t_list left = {cur.x - 1, cur.y};
    t_list right = {cur.x + 1, cur.y};
    t_list up = {cur.x, cur.y - 1};
    t_list down = {cur.x, cur.y + 1};
    flood(tab, size, left);
    flood(tab, size, right);
    flood(tab, size, up);
    flood(tab, size, down);
}

// Lance le flood fill depuis une position
void ft_flood(char **tab, t_list size, t_list start)
{
    flood(tab, size, start);
}

// Trouve la position de départ et vérifie les caractères
t_list find_start_position(char **map, int *start_count, int max_x, int max_y)
{
    t_list start = {-1, -1};
    *start_count = 0;
    int i = 0;
    while (i < max_x)
    {
        int j = 0;
        while (j < max_y)
        {
            if (!is_valid_char(map[i][j]))
            {
                printf("Erreur : caractère non autorisé '%c' à la ligne %d, colonne %d.\n", map[i][j], i + 1, j + 1);
                exit(1);
            }
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                start.x = j;
                start.y = i;
                (*start_count)++;
            }
            j++;
        }
        i++;
    }
    return start;
}

// Valide la map
void validate_map(char **map, int max_x, int max_y)
{
    int start_count;
    t_list start = find_start_position(map, &start_count, max_x, max_y);

    // Vérifie qu'il y a exactement une position de départ
    if (start_count != 1)
    {
        printf("Erreur : il doit y avoir exactement une position de départ (trouvé : %d).\n", start_count);
        exit(1);
    }

    // Crée une copie de la map pour le flood fill
    char **map_copy = malloc(max_x * sizeof(char *));
    int i = 0;
    while (i < max_x)
    {
        map_copy[i] = malloc(max_y * sizeof(char));
        memcpy(map_copy[i], map[i], max_y);
        i++;
    }

    // Lance le flood fill depuis la position de départ
    t_list size = {max_y, max_x}; // size.x = colonnes, size.y = lignes
    ft_flood(map_copy, size, start);

    // Vérifie que toutes les cases vides sont accessibles
    i = 0;
    while (i < max_x)
    {
        int j = 0;
        while (j < max_y)
        {
            if (map[i][j] == '0' || map[i][j] == ' ')
            {
                if (map_copy[i][j] != 'F')
                {
                    printf("Erreur : zone inaccessible à la ligne %d, colonne %d.\n", i + 1, j + 1);
                    exit(1);
                }
            }
            j++;
        }
        i++;
    }

    // Libère la mémoire
    i = 0;
    while (i < max_x)
    {
        free(map_copy[i]);
        i++;
    }
    free(map_copy);

    printf("La map est valide !\n");
}

int main()
{
    // Exemple de map valide
    char *map[] = {
        "111111",
        "100101",
        "101001",
        "1100N1",
        "111111",
        NULL
    };

    // Calcule les dimensions
    int max_x = 0;
    while (map[max_x])
        max_x++;
    int max_y = strlen(map[0]); // Suppose que toutes les lignes ont la même longueur

    // Crée une copie de la map
    char **map_rect = malloc(max_x * sizeof(char *));
    int i = 0;
    while (i < max_x)
    {
        map_rect[i] = malloc(max_y * sizeof(char));
        memcpy(map_rect[i], map[i], max_y);
        i++;
    }

    // Valide la map
    validate_map(map_rect, max_x, max_y);

    // Libère la mémoire
    i = 0;
    while (i < max_x)
    {
        free(map_rect[i]);
        i++;
    }
    free(map_rect);

    return 0;
}