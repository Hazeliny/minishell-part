/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:26:01 by linyao            #+#    #+#             */
/*   Updated: 2024/09/29 15:26:06 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

static char	**merge(char *s1, char *s2)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, " ");
	res = ft_strjoin(tmp, s2);
	free(tmp);
	return (res);
}

static void	merge_cmd_para(char **av, char **s, int *i)
{
	char	*tmp;

	if (!*s)
		*s = merge(av[*i], av[(*i) + 1]);
	else
	{	
		tmp = *s;
		*s = merge(*s, av[(*i) + 1]);
		free(tmp);
	}
	(*i)++;
}

static void	complete_cmd_para(char ***res, char **s, int *i, char *str)
{
	if (!*s)
		add_array(res, str);
	else
		add_array(res, *s);
	free(*s);
	*s = NULL;
	(*i)++;
}

//to reprocess arrays without redirection arguments of infile and outfile
//{"grep" ""pattern"" "|" "sort" "|" "uniq" "|" "wc" "-l" "|" "echo" "$PATH"} -->
//{"grep pattern" "| sort" "| uniq" "| wc -l" "| echo $PATH"}
char    **transform_av_cmd(char **av)
{
	int	i;
	char	*s;
	char	**res;

	i = 0;
	s = NULL;
	res = NULL;
	if (!av || !*av)
		return (NULL);
	while (av[i])
	{
		if (av[i] && av[i + 1] && ft_strcmp(av[i + 1], PIPE_S) != 0)
			merge_cmd_para(av, &s, &i);
		else if (av[i] && (av[i + 1] && ft_strcmp(av[i + 1], PIPE_S) == 0 \
						|| !av[i + 1]))
			complete_cmd_para(&res, &s, &i, av[i]);
	}
	return (res);
}
