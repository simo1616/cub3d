#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    int width;
    int height;
    char **grid;
    int player_x;
    int player_y;
    char player_dir;
} Map;

char* strtrim(const char *s) {
    if (s == NULL)
    {
        return NULL;
    }
    while (isspace((unsigned char)*s))
    {
        s++;
    }
    size_t len;
    len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1]))
    {
        len--;
    }
    char *trimmed;
    trimmed = malloc(len + 1);
    if (!trimmed)
    {
        return NULL;
    }
    memcpy(trimmed, s, len);
    trimmed[len] = '\0';
    return trimmed;
}

bool is_config_line(const char *line) {
    if (strncmp(line, "NO ", 3) == 0)
    {
        return true;
    }
    if (strncmp(line, "SO ", 3) == 0)
    {
        return true;
    }
    if (strncmp(line, "WE ", 3) == 0)
    {
        return true;
    }
    if (strncmp(line, "EA ", 3) == 0)
    {
        return true;
    }
    if (strncmp(line, "F ", 2) == 0)
    {
        return true;
    }
    if (strncmp(line, "C ", 2) == 0)
    {
        return true;
    }
    return false;
}

char** read_file_lines(const char *filename, int *out_count) {
    FILE *f;
    f = fopen(filename, "r");
    if (!f)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    char **lines;
    lines = NULL;
    size_t capacity;
    capacity = 0;
    int count;
    count = 0;
    char *line;
    line = NULL;
    size_t len;
    len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, f)) != -1)
    {
        if (nread > 0 && line[nread - 1] == '\n')
        {
            line[nread - 1] = '\0';
            nread--;
        }
        char *line_copy;
        line_copy = strdup(line);
        if (!line_copy)
        {
            perror("Erreur d'allocation de mémoire");
            fclose(f);
            free(line);
            int i;
            i = 0;
            while (i < count)
            {
                free(lines[i]);
                i++;
            }
            free(lines);
            return NULL;
        }
        if (count >= (int)capacity)
        {
            size_t new_capacity;
            new_capacity = (capacity == 0) ? 16 : capacity * 2;
            char **new_lines;
            new_lines = realloc(lines, new_capacity * sizeof(char*));
            if (!new_lines)
            {
                perror("Erreur d'allocation de mémoire");
                fclose(f);
                free(line);
                int j;
                j = 0;
                while (j < count)
                {
                    free(lines[j]);
                    j++;
                }
                free(lines);
                free(line_copy);
                return NULL;
            }
            lines = new_lines;
            capacity = new_capacity;
        }
        lines[count] = line_copy;
        count++;
    }
    free(line);
    fclose(f);
    *out_count = count;
    return lines;
}

int find_map_start(char **lines, int line_count) {
    bool in_config_section;
    in_config_section = true;
    int i;
    i = 0;
    while (i < line_count)
    {
        char *trimmed;
        trimmed = strtrim(lines[i]);
        if (!trimmed)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            return -1;
        }
        if (in_config_section)
        {
            if (*trimmed == '\0')
            {
                free(trimmed);
                i++;
                continue;
            }
            else if (is_config_line(trimmed))
            {
                free(trimmed);
                i++;
                continue;
            }
            else
            {
                free(trimmed);
                return i;
            }
        }
        else
        {
            free(trimmed);
            return i;
        }
        i++;
    }
    return -1;
}

bool parse_map(char **lines, int start_index, int line_count, Map *map) {
    int map_start;
    map_start = start_index;
    while (map_start < line_count)
    {
        char *trim;
        trim = strtrim(lines[map_start]);
        if (!trim)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            return false;
        }
        bool empty;
        empty = (*trim == '\0');
        free(trim);
        if (!empty)
        {
            break;
        }
        map_start++;
    }
    if (map_start >= line_count)
    {
        fprintf(stderr, "Erreur: Pas de carte trouvée dans le fichier\n");
        return false;
    }
    int count;
    count = 0;
    int i;
    i = map_start;
    while (i < line_count)
    {
        char *trim;
        trim = strtrim(lines[i]);
        if (!trim)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            return false;
        }
        bool empty;
        empty = (*trim == '\0');
        free(trim);
        if (empty)
        {
            break;
        }
        count++;
        i++;
    }
    if (count == 0)
    {
        fprintf(stderr, "Erreur: Pas de carte trouvée dans le fichier\n");
        return false;
    }
    map->height = count;
    int max_width;
    max_width = 0;
    i = map_start;
    while (i < map_start + count)
    {
        int length;
        length = strlen(lines[i]);
        if (length > max_width)
        {
            max_width = length;
        }
        i++;
    }
    map->width = max_width;
    map->grid = malloc(map->height * sizeof(char*));
    if (!map->grid)
    {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        return false;
    }
    map->player_x = -1;
    map->player_y = -1;
    map->player_dir = '\0';
    int player_count;
    player_count = 0;
    int row;
    row = 0;
    while (row < map->height)
    {
        map->grid[row] = lines[map_start + row];
        lines[map_start + row] = NULL;
        int col;
        col = 0;
        while (map->grid[row][col] != '\0')
        {
            char c;
            c = map->grid[row][col];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                map->player_x = col;
                map->player_y = row;
                map->player_dir = c;
                player_count++;
            }
            if (c != ' ' && c != '0' && c != '1' &&
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
            {
                fprintf(stderr, "Erreur: Caractère invalide '%c' dans la carte (ligne %d)\n", c, row);
                return false;
            }
            col++;
        }
        row++;
    }
    if (player_count != 1)
    {
        if (player_count == 0)
        {
            fprintf(stderr, "Erreur: Aucune position de départ du joueur dans la carte\n");
        }
        else
        {
            fprintf(stderr, "Erreur: Positions de départ multiples trouvées (%d)\n", player_count);
        }
        return false;
    }
    return true;
}

bool validate_map(const Map *map) {
    int h;
    h = map->height;
    int i;
    i = 0;
    while (i < h)
    {
        int row_len;
        row_len = strlen(map->grid[i]);
        int j;
        j = 0;
        while (j < row_len)
        {
            char c;
            c = map->grid[i][j];
            if (c == ' ' || c == '1')
            {
                j++;
                continue;
            }
            if (j == 0)
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (bord gauche ouvert en %d,%d)\n", i, j);
                return false;
            }
            if (map->grid[i][j - 1] == ' ')
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (voisin gauche vide en %d,%d)\n", i, j);
                return false;
            }
            if (j == row_len - 1)
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (bord droit ouvert en %d,%d)\n", i, j);
                return false;
            }
            if (j + 1 < row_len && map->grid[i][j + 1] == ' ')
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (voisin droit vide en %d,%d)\n", i, j);
                return false;
            }
            if (i == 0)
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (bord haut ouvert en %d,%d)\n", i, j);
                return false;
            }
            int above_len;
            above_len = strlen(map->grid[i - 1]);
            if (j >= above_len || map->grid[i - 1][j] == ' ')
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (voisin du haut vide en %d,%d)\n", i, j);
                return false;
            }
            if (i == h - 1)
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (bord bas ouvert en %d,%d)\n", i, j);
                return false;
            }
            int below_len;
            below_len = strlen(map->grid[i + 1]);
            if (j >= below_len || map->grid[i + 1][j] == ' ')
            {
                fprintf(stderr, "Erreur: La carte n'est pas fermée (voisin du bas vide en %d,%d)\n", i, j);
                return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <fichier.cub>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *filename;
    filename = argv[1];
    int line_count;
    line_count = 0;
    char **lines;
    lines = read_file_lines(filename, &line_count);
    if (!lines)
    {
        return EXIT_FAILURE;
    }
    int map_start;
    map_start = find_map_start(lines, line_count);
    if (map_start < 0)
    {
        fprintf(stderr, "Erreur: Section carte introuvable dans le fichier\n");
        int i;
        i = 0;
        while (i < line_count)
        {
            free(lines[i]);
            i++;
        }
        free(lines);
        return EXIT_FAILURE;
    }
    Map map;
    map.grid = NULL;
    if (!parse_map(lines, map_start, line_count, &map))
    {
        int i;
        i = 0;
        while (i < line_count)
        {
            if (lines[i] != NULL)
            {
                free(lines[i]);
            }
            i++;
        }
        free(lines);
        if (map.grid != NULL)
        {
            int r;
            r = 0;
            while (r < map.height)
            {
                if (map.grid[r] != NULL)
                {
                    free(map.grid[r]);
                }
                r++;
            }
            free(map.grid);
        }
        return EXIT_FAILURE;
    }
    int i;
    i = 0;
    while (i < line_count)
    {
        if (lines[i] != NULL)
        {
            free(lines[i]);
        }
        i++;
    }
    free(lines);
    if (!validate_map(&map))
    {
        int r;
        r = 0;
        while (r < map.height)
        {
            free(map.grid[r]);
            r++;
        }
        free(map.grid);
        return EXIT_FAILURE;
    }
    printf("Carte valide.\n");
    printf("Dimensions: %d x %d\n", map.width, map.height);
    printf("Position initiale du joueur: (%d, %d) face %c\n", map.player_x, map.player_y, map.player_dir);
    int r;
    r = 0;
    while (r < map.height)
    {
        free(map.grid[r]);
        r++;
    }
    free(map.grid);
    return EXIT_SUCCESS;
}
