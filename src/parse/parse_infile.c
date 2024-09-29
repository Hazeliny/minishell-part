/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:02:43 by linyao            #+#    #+#             */
/*   Updated: 2024/09/25 17:13:13 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

void	delete_file_element(char ***av, char **fl)
{
	int	i;

	i = 0;
	if (!*av || !fl || !*fl)
		return ;
	while (fl[i])
	{
		del_array_em(find_index_array(*av, fl[i]), av);
		i++;
	}
}

//add the absolute path of the infile (including "<" or "<<")
//into two-dimensional array "res"
static void	assign_infile(char ***av, char ***res, int *i)
{
	if (ft_strcmp((*av)[(*i)], LESS_S) == 0)
	{
		add_array(res, LESS_S);
		if ((*av)[(*i) + 1])
		{
			add_array(res, (*av)[(*i) + 1]);
			(*i)++;
		}
	}
	else if (ft_strcmp((*av)[(*i)], DOUBLE_LESS) == 0)
	{
		add_array(res, DOUBLE_LESS);
		if ((*av)[(*i) + 1])
		{
			add_array(res, (*av)[(*i) + 1]);
			(*i)++;
		}
	}
}

// extract the infile part from the two-dimensional array
// remove the element about infile from the array
char	**get_infile_path(char ***av)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	if (!*av || !**av)
		return (NULL);
	while ((*av)[i])
	{
		assign_infile(av, &res, &i);
		i++;
	}
	delete_file_element(av, res);
	return (res);
}

//To deal with the cases in which multiple "<" and/or "<<" are included
//only keep one "<" with one infile
//only keep one "<" with one infile and one "<<" with one delimiter
static char	**cut_inf(char **inf, int len)
{
	if (ft_strcmp(inf[len - 2], inf[len - 4]) == 0)
	{
		while (count_arrays(inf) != 2)
			del_array_em(0, &inf);
		return (inf);
	}
	else
	{
		while (count_arrays(inf) != 4)
			del_array_em(0, &inf);
		return (inf);
	}
}

//To deal with multiple infiles
char	**validate_inf(char **inf)
{
	int	len;

	if (!inf || !*inf)
		return (NULL);
	len = count_arrays(inf);
	if (ft_strcmp(inf[len - 1], DOUBLE_LESS) == 0)
	{
		while (count_arrays(inf) != 1)
			del_array_em(0, &inf);
		return (inf);
	}
	if (len >= 4)
		return (cut_inf(inf, len));
	return (inf);
}
