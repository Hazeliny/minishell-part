/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:19:09 by linyao            #+#    #+#             */
/*   Updated: 2024/09/29 17:19:13 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

static void	combine_cmds(char ***av, bool f)
{
	int	i;
	char	*tmp;
	char	*join;

	i = 0;
	if (!*av || !**av)
		return (NULL);
	while ((*av)[i])
	{
		if (i > 0 && (*av)[i - 1] && (*av)[i][0] == '-')
		{
			tmp = (*av)[i - 1];
			join = ft_strjoin(" ", (*av)[i]);
			(*av)[i - 1] = ft_strjoin(tmp, join);
			free(tmp);
			free(join);
			if (f)
				del_array_em(i, av);
			i--;
		}
		i++;
	}
}

//result is {"grep pattern" "|awk '{print $1}'" "| sort" "| uniq" "| wc -l"}
char    **transform_cmds(char ***av)
{
	int	i;
	char	**res;

	i = 0;
	res = NULL;
	if (!*av || !**av)
		return (NULL);
	combine_cmds(av, true);
	add_array(&res, (*av)[0]);
	while ((*av)[i])
	{
		if (ft_strcmp((*av)[i], PIPE_S) == 0 && (*av)[i + 1])
		{
			add_array(&res, PIPE_S);
			add_array(&res, (*av)[i + 1]);
		}
		i++;
	}
	return (res);
}
