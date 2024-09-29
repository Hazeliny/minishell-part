/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:22:24 by linyao            #+#    #+#             */
/*   Updated: 2024/09/29 21:22:31 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

static void	init_var(int *i, int *num_cmd, char ****res, char ***line_av)
{
	*i = 0;
	*num_cmd = 0;
	*res = NULL;
	*line_av = NULL;
}

static void	dl_pm(char ***line_av, char *s, bool *para_exist, int *i)
{
	add_array(line_av, s);
	*para_exist = true;
	(*i)++;
}

static void	rise_dimension(char ****res_cmd, int n)
{
	int	i;
	char	***res;

	i = 0;
	res = malloc(sizeof(char **) * (n + 1));
	if (!res)
		return ;
	while (i <= n)
		res[i++] = NULL;
	i = 0;
	while (i < n - 1)
	{
		res[i] = (*res_cmd)[i];
		i++;
	}
	free(*res_cmd);
	*res_cmd = res;
}

static void	set_null(char ***res, char ***line_av)
{
	*res = NULL;
	if (*line_av)
		free_array(*line_av);
}

//transform two-dimensional array into three-dimensional one without "|"
//such as {"grep" "pattern"}{"awk" "'{print $1}'"}{"sort"}{"uniq"}{"wc" "-l"}
char	***transform_args(char **av)
{
	int	i;
	int	num_cmd;
	char	***res;
	char	**line_av;
	bool	para_exist;

	if (!av || !*av || !**av)
		return (NULL);
	init_var(&i, &num_cmd, &res, &line_av);
	while (av[i])
	{
		i++;
		para_exist = false;
		while (av[i] && ft_strcmp(av[i], PIPE_S) != 0)
			dl_pm(&line_av, av[i], &para_exist, &i);
		if (!para_exist)
			add_array(&line_av, "ocupied");
		num_cmd++;
		rise_dimension(&res, num_cmd);
		res[num_cmd - 1] = line_av;
		set_null(&res[num_cmd], &line_av);
		if (av[i])
			i++;
	}
	return (res);
}
