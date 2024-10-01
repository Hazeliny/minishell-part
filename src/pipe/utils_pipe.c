/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:20:39 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 12:51:03 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

bool	init_cmds(t_pipe *pip)
{
	int	i;

	i = 0;
	pip->cms = malloc(sizeof(t_cmds) * pip->len);
	if (!pip->cms)
		return (false);
	while (i < pip->len)
	{
		pip->cms[i].argv = NULL;
		pip->cms[i].path = NULL;
		pip->cms[i].exist = false;
		i++;
	}
	return (true);
}

bool    init_pipe(t_pipe *pip, int ac, char **av, char **env)
{
	pip->fdin = -1;
	pip->fdout = -1;
	pip->p_end = NULL;
	pip->heredoc = false;
	pip->exitstat = EXIT_SUCCESS;
	pip->np = NULL;
	pip->arv = av;
	pip->paths = NULL;
	pip->envir = env;
	pip->cms = NULL;
	if (ft_strncmp(pip->arv[1], "here_doc", 8) == 0 && \
		ft_strncmp(pip->arv[0], "./minishell", 11) == 0)
		pip->heredoc = true;
	pip->len = ac - 3 - pip->heredoc;
	if (!init_cmds(pip))
		return (false);
	return (true);
}

bool	clean_pipe(t_pipe *pip)
{
	int	i;

	i = 0;
	while (i < pip->len && pip->cms && pip->cms[i].argv)
	{
		free_array(pip->cms[i].argv);
		if (pip->cms[i].exist)
			free(pip->cms[i].path);
		i++;
	}
	free(pip->cms);
	if (pip->paths)
		free_array(pip->paths);
	if (pip->inf != -1)
		close(pip->inf);
	if (pip->outf != -1)
		close(pip->outf);
	if (pip->p_end)
		free(pip->p_end);
	if (pip->heredoc)
		unlink("../../here_doc");
	free_array(pip->np);
	free_array(pip->arv);
	free_array(pip->envir);
	return (true);
}

bool	check_cmd(t_ms *ms, t_pipe *pip)
{
	int	i;

	get_allpaths(pip);
	if (pip->heredoc)
		open_heredoc(pip);
	else
		open_file(ms, pip);
	i = 0;
	while (i < pip->len)
	{
		pip->cms[i].exist = false;
		pip->cms[i].argv = \
			ft_split(pip->arv[i + 2 + pip->heredoc], " ");
		if (!pip->cms[i].argv)
			return (false);
		if (!(i == 0 && pip->fdin == -1) &&
			!(i == pip->len - 1 && pip->fdout == -1))
			extract_path(i, pip);
		i++;
	}
	return (true);
}
