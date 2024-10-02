/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:34:55 by linyao            #+#    #+#             */
/*   Updated: 2024/10/02 16:20:13 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

static void	join_k_v(char *s1, char *s2, char ***res)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	add_array(res, join);
	free(join);
}

char	**hash_to_array(t_hash *t)
{
	int		i;
	char	**res;
	t_node	*tmp;

	i = 0;
	res = NULL;
	while (i < HASH_LEN)
	{
		if (t->slot[i])
		{
			join_k_v(t->slot[i]->key, t->slot[i]->value, &res);
			tmp = t->slot[i]->next;
			while (tmp)
			{
				join_k_v(tmp->key, tmp->value, &res);
				tmp = tmp->next;
			}
		}
		i++;
	}
	return (res);
}
