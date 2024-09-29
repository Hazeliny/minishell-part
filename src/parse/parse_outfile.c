/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:27:22 by linyao            #+#    #+#             */
/*   Updated: 2024/09/27 17:50:53 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

static void	assign_outfile(char ***av, char ***res, int *i)
{
	if (ft_strcmp((*av)[(*i)], MORE_S) == 0)
	{
		add_array(res, MORE_S);
		if ((*av)[(*i) + 1])
		{
			add_array(new, (*av)[(*i) + 1]);
			(*i)++;
		}
	}
	else if (ft_strcmp((*av)[(*i)], DOUBLE_MORE) == 0)
	{
		add_array(res, DOUBLE_MORE);
		if ((*av)[(*i) + 1])
		{
			add_array(res, (*av)[(*i) + 1]);
			(*i)++;
		}
	}
}

//assign the value to outf from the two-dimensional array
char	**get_outfile_path(char ***av)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	if (!*av || !**av)
		return (NULL);
	while ((*av)[i])
	{
		assign_outfile(av, &res, &i);
		i++;
	}
	delete_file_element(av, res);
	return (res);
}
