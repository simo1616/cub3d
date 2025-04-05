#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


static int	check_valid_char(char c)
{
	return(c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'F');
}


void	check_validate_map(char **map)
{
	int i;
	int j;
	int len_i;
	int len_j;

	i = 0;
	
	while(map[i])
	{
		
		j = 0;
		if (map[i][j] )
		{
			while(map[i][j] && map[i][j] == ' ')
				j++;
			if(map[i][j] != '1')
			{
				printf("La map ne respecte pas les murs\n");
				exit(1);
			}
		}
		while(map[i][j])
		{
			if(!check_valid_char(map[i][j]))
			{
				printf("Le char %c, est non autorisé.\n", map[i][j]);
				exit(1);
			}
			j++;
		}
		len_j = j - 1;
		if (map[i][len_j] != '1')
		{
			printf("La map ne respecte pas les murs\n");
			exit(1);
		}
		printf("%s\n", map[i]);
		i++;
	}
	len_i = i - 1;
	j = 0;
	while(map[0][j])
	{
		if(map[0][j] != '1')
		{
			printf("La map ne respecte pas les murs\n");
			exit(1);
		}
		j++;
	}
	j = 0;
	while(map[len_i][j])
	{
		if(map[len_i][j] != '1')
		{
			printf("La map ne respecte pas les murs\n");
			exit(1);
		}
		j++;
	}
}

int main(void)
{

    char *map[] = {
		"                 1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"111101111110101101111010001",
		"11111111111111111111111111",
	};

    check_validate_map(map);
    return 0;
}