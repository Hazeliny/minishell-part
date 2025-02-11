/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:12:36 by linyao            #+#    #+#             */
/*   Updated: 2024/10/03 12:00:00 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/env.h"

void	free_array(char **arrays)
{
	int	i;

	i = 0;
	if (!arrays || !*arrays)
		return ;
	while (arrays[i])
	{
		free(arrays[i]);
		i++;
	}
	if (arrays)
		free(arrays);
	arrays = NULL;
}

int	count_arrays(char **arrays)
{
	int	i;

	if (!arrays || !*arrays)
		return (0);
	i = 0;
	while (arrays[i])
		i++;
	return (i);
}

static bool	comply_rule(char *bf, char *af, char *mark)
{
	if (ft_strcmp(bf, mark) == 0 && ft_strcmp(af, LESS_S)  == 0)
		return (printf("Token next to another <\n"), false);
	if (ft_strcmp(bf, mark) == 0 && ft_strcmp(af, MORE_S) == 0)
		return (printf("Token next to another >\n"), false);
	if (ft_strcmp(bf, mark) == 0 && ft_strcmp(af, DOUBLE_LESS) == 0)
		return (printf("Token next to another <<\n"), false);
	if (ft_strcmp(bf, mark) == 0 && ft_strcmp(af, DOUBLE_MORE) == 0)
		return (printf("Token next to another >>\n"), false);
	if (ft_strcmp(bf, mark)== 0 && ft_strcmp(af, PIPE_S)  == 0)
		return (printf("Token next to another |\n"), false);
	return (true);
}

bool	is_compliance(char **as)
{
	int	i;
	int	len;

	if (!as || !*as)
		return (true);
	len = count_arrays(as);
	if (!ft_strcmp(as[len - 1], PIPE_S) || !ft_strcmp(as[len - 1], \
		LESS_S) || !ft_strcmp(as[len - 1], MORE_S) || \
		!ft_strcmp(as[len - 1], DOUBLE_LESS) || \
		!ft_strcmp(as[len - 1], DOUBLE_MORE))
		return (printf("Illegal shell command\n"), false);
	i = 0;
	while (i < len - 1)
	{
		if (as[i + 1] && !comply_rule(as[i], as[i + 1], LESS_S))
			return (false);
		if (as[i + 1] && !comply_rule(as[i], as[i + 1], MORE_S))
			return (false);
		if (as[i + 1] && !comply_rule(as[i], as[i + 1], DOUBLE_LESS))
			return (false);
		if (as[i + 1] && !comply_rule(as[i], as[i + 1], DOUBLE_MORE))
			return (false);
		i++;
	}
	return (true);
}

int	find_index_array(char **ar, char *s)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		if (ft_strcmp(ar[i], s) == 0)
			return (i);
		i++;
	}
	return (-1);
}
