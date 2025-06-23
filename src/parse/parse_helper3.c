#include "cub3d.h"

// Détecte si la ligne commence par un identifiant de texture
bool is_texture_attempt(char *line)
{
    return (ft_strncmp(line, "NO", 2) == 0 || 
            ft_strncmp(line, "SO", 2) == 0 ||
            ft_strncmp(line, "WE", 2) == 0 || 
            ft_strncmp(line, "EA", 2) == 0);
}

// Vérifie le format correct d'une texture (identifiant + espace + chemin)
bool is_valid_texture_format(char *line)
{
    if (ft_strlen(line) < 4)
        return false;
        
    // Vérifier que le 3ème caractère est un espace
    if ((ft_strncmp(line, "NO ", 3) == 0) ||
        (ft_strncmp(line, "SO ", 3) == 0) ||
        (ft_strncmp(line, "WE ", 3) == 0) ||
        (ft_strncmp(line, "EA ", 3) == 0))
    {
        // Vérifier qu'il y a quelque chose après l'espace
        char *path = ft_strtrim(line + 3, " \t");
        if (path && ft_strlen(path) > 0)
        {
            free(path);
            return true;
        }
        if (path)
            free(path);
    }
    return false;
}

// Détecte si la ligne commence par un identifiant de couleur
bool is_color_attempt(char *line)
{
    return (line[0] == 'F' || line[0] == 'C');
}

// Vérifie le format correct d'une couleur
bool is_valid_color_format(char *line)
{
    if (ft_strlen(line) < 3)
        return false;
        
    // Vérifier que le 2ème caractère est un espace
    if ((ft_strncmp(line, "F ", 2) == 0) ||
        (ft_strncmp(line, "C ", 2) == 0))
    {
        // Vérifier qu'il y a quelque chose après l'espace
        char *values = ft_strtrim(line + 2, " \t");
        if (values && ft_strlen(values) > 0)
        {
            free(values);
            return true;
        }
        if (values)
            free(values);
    }
    return false;
}

// Détecte si une ligne ressemble à une ligne de map
bool is_map_line(char *line)
{
    int i = 0;
    
    // Ignorer les espaces au début
    while (line[i] == ' ' || line[i] == '\t')
        i++;
        
    // Vérifier si la ligne contient des caractères de map valides
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && 
            line[i] != '\t' && line[i] != 'N' && line[i] != 'S' && 
            line[i] != 'E' && line[i] != 'W')
            return false;
        i++;
    }
    return (i > 0); // Au moins un caractère trouvé
}
