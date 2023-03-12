#include <unistd.h>
#include <stdlib.h>
// out put functions -start
void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str++, 1);
	}
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_atoi(char *str)
{
	int				i;
	unsigned int	nbr;
	int				sign;

	i = 0;
	nbr = 0;
	sign = 0;
	while (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign++;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	if (sign % 2 == 1)
		return (nbr * -1);
	return (nbr);
}

void ft_putnbr(int nb)
{
	unsigned int nbr;

    if (nb < 0)
    {
        ft_putchar('-');
        nbr = nb * -1;
    }
    else
    	nbr = nb;
    if (nbr / 10 != 0)
    	ft_putnbr(nbr / 10);
    ft_putchar(nbr % 10 + 48);
}

//output functions -end

//check user input
int check_arguments(int argc, char *argv[])
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (argc != 2)
		return (1);
	str = argv[0];
	/* check if the partern is correct */
	if (ft_strlen(argv[1]) != 31)
		return (1);
	while (str[i] != '\0')
	{
		/* for each char at index i check if it is a valid digit */
		if (str[i] >= '0' && str[i] <= '9')
		{
			j = ft_atoi(str + i);
			if (j < 0 || j > 4)
				return (0);
		}
		i++;
	}
	return (0);
}

//convert the input into array

int *convert_pattern(char *str)
{
	int *tab;
	int i;
	int j;

	i = 0;
	j = 0;
	
	if (!(tab = malloc(sizeof(int) * 16)))
		return (0);
	while (str[i] != '\0')
	{
		/* for each char at index i convert it to `int` */
		if (str[i] >= '0' && str[i] <= '9')
			tab[j++] = ft_atoi(str + i);
		i++;
	}
	return (tab);
}


void print_puzzle_grid(int grid[4][4])
{
	int	i;
	int	j;

	i = 0;
	/* loop inside rows and columns */
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			/* display each cell */
			ft_putnbr(grid[i][j]);
			if (j < 3)
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int check_col_up(int grid[4][4], int gap, int pattern[16])
{
	int i;
	int max;
	int count;

	i = 0;
	max = 0;
	count = 0;
	/* check if the current gap represent the good column  */
	if (gap / 4 == 3)
	{
		/* start from i = 0 to go from top to bottom */
		while (i < 4)
		{
			/* for each cell of the column get max and count */
			if (grid[i][gap % 4] > max)
			{
				/* change max value to new max */
				max = grid[i][gap % 4];
				count++;
			}
			i++;
		}
		/* compare if the result is as expected */
		if (pattern[gap % 4] != count)
			return (1);
	}
	return (0);
}

int check_row_right(int grid[4][4], int gap, int pattern[16])
{
	int i;
	int max_size;
	int visible_towers;

	i = 4;
	max_size = 0;
	visible_towers = 0;
	/* check if the current gap represent the good row */
	if (gap % 4 == 3)
	{
		/* start from i = 4 to go from right to left */
		while (--i >= 0)
		{
			/* for each cell of the row get max and count */
			if (grid[gap / 4][i] > max_size)
			{
				/* change max value to new max */
				max_size = grid[gap / 4][i];
				visible_towers++;
			}
		}
		/* compare if the result is as expected */
		if (pattern[12 + gap / 4] != visible_towers)
			return (1);
	}
	return (0);
}

int check_col_down(int grid[4][4], int gap, int pattern[16])
{
	int i;
	int max;
	int count;

	i = 3;
	max = 0;
	count = 0;
	/* check if the current gap represent the good column */
	if (gap / 4 == 3)
	{
		/* start from i = 3 to go from bottom to top */
		while (i >= 0)
		{
			/* for each cell of the column get max and count */
			if (grid[i][gap % 4] > max)
			{
				/* change max value to new max */
				max = grid[i][gap % 4];
				count++;
			}
			i--;
		}
		/* compare if the result is as expected */
		if (pattern[4 + gap % 4] != count)
			return (1);
	}
	return (0);
}

int check_row_left(int grid[4][4], int gap, int pattern[16])
{
	int i;
	int max;
	int count;

	i = 0;
	max = 0;
	count = 0;
	/* check if the current gap represent the good row */
	if (gap % 4 == 3)
	{
		/* start from i = 0 to go from left to right */
		while (i < 4)
		{
			/* for each cell of the row get max and count */
			if (grid[gap / 4][i] > max)
			{
				/* change max value to new max */
				max = grid[gap / 4][i];
				count++;
			}
			i++;
		}
		/* compare if the result is as expected */
		if (pattern[8 + gap / 4] != count)
			return (1);
	}
	return (0);
}

int check_cell(int grid[4][4], int gap, int pattern[16])
{
	/* test for all possibilities if current case if good */
	if (check_row_left(grid, gap, pattern) == 1)
		return (1);
	if (check_row_right(grid, gap, pattern) == 1)
		return (1);
	if (check_col_down(grid, gap, pattern) == 1)
		return (1);
	if (check_col_up(grid, gap, pattern) == 1)
		return (1);
	return (0);
}


int check_adjacent_cell(int grid[4][4], int gap, int num)
{
	int i;

	i = 0;
	/* for each columns of the grid */
	while (i < gap / 4)
	{
		/* test if the value of `num` is present */
		if (grid[i][gap % 4] == num)
			return (1);
		i++;
	}
	i = 0;
	/* for each rows of the grid */
	while (i < gap % 4)
	{
		/* test if the value of `num` is present */
		if (grid[gap / 4][i] == num)
			return (1);
		i++;
	}
	return (0);
}

int puzzle_solver(int grid[4][4], int pattern[16], int gap)
{
	int num;

	/* if solver reaches end, it returns that the grid is solved */
	if (gap == 16)
		return (1);
	num = 0;
	while (++num <= 4)
	{
		/* check if the new supposed nul is already in */
		if (check_adjacent_cell(grid, gap, num) == 0)
		{
			/* put new supposed value in the grid */
			grid[gap / 4][gap % 4] = num;
			/* check if new number is correct */
			if (check_cell(grid, gap, pattern) == 0)
			{
				/* go to next cell */
				if (puzzle_solver(grid, pattern, gap + 1) == 1)
					return (1);
			}
			/* if not remove it */
			else
			{
				grid[gap / 4][gap % 4] = 0;
			}
		}
	}
	/* if any solution can be find return that the grid cannot be solved */
	return (0);
}

int main(int argc, char *argv[])
{
	int grid[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	};
	int *pattern;

	/* if incorrect arguments in the user entries end the program */
	if (check_arguments(argc, argv) == 1)
	{
		ft_putstr("Error\n");
		return (0);
	}
	/* convert the string pattern as an array of `int` */
	pattern = convert_pattern(argv[1]);
	if (!pattern)
		return (1);
	/* call main program function */
	if (puzzle_solver(grid, pattern, 0) == 1)
	{
		/* if a solution is found display it */
		print_puzzle_grid(grid);
	}
	/* otherwise display error */
	else
	{
		ft_putstr("Error\n");
	}
	return (0);
}

