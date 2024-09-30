/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:20:39 by linyao            #+#    #+#             */
/*   Updated: 2024/09/30 16:20:40 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

bool	init_cmds(t_pipe *pipe)
{
	int	i;

	i = 0;
	pipe->cms = malloc(sizeof(t_cmds) * pipe->len);
	if (!pipe->cms)
		return (false);
	while (i < pipe->len)
	{
		pipe->cms[i].argv = NULL;
		pipe->cms[i].path = NULL;
		pipe->cms[i].exist = false;
		i++;
	}
	return (true);
}

bool    init_pipe(t_pipe *pipe, int ac, char **av, char **env)
{
	pipe->fdin = -1;
	pipe->fdout = -1;
	pipe->p_end = NULL;
	pipe->heredoc = false;
	pipe->exitstat = EXIT_SUCCESS;
	pipe->pipes = NULL;
	pipe->arv = av;
	pipe->paths = NULL;
	pipe->envir = env;
	pipe->cms = NULL;
	if (ft_strncmp(pipe->arv[1], "here_doc", 8) == 0 && \
		ft_strncmp(pipe->arv[0], "./minishell", 11) == 0)
		pipe->heredoc = true;
	pipe->len = ac - 3 - pipe->heredoc;
	if (!init_cmds(pipe))
		return (false);
	return (true);
}

bool	clean_pipe(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->len && pipe->cms && pipe->cms[i].argv)
	{
		free_array(pipe->cms[i].argv);
		if (pipe->cms[i].exist)
			free(pipe->cms[i].path);
		i++;
	}
	free(pipe->cms);
	if (pipe->paths)
		free_array(pipe->paths);
	if (pipe->inf != -1)
		close(pipe->inf);
	if (pipe->outf != -1)
		close(pipe->outf);
	if (pipe->p_end)
		free(pipe->p_end);
	if (pipe->heredoc)
		unlink(".here_doc");
	free_array(pipe->pipes);
	free_array(pipe->arv);
	free_array(pipe->envir);
	return (true);
}

bool	check_cmd(t_ms *ms, t_pipe *pipe)
{
	int	i;

	get_allpaths(pipe);
	if (pipe->heredoc)
		open_heredoc(pipe);
	else
		open_file(ms, pipe);
	i = 0;
	while (i < pipe->len)
	{
		pipe->cms[i].exist = false;
		pipe->cms[i].argv = \
			ft_split(pipe->arv[i + 2 + pipe->heredoc], " ");
		if (!pipe->cms[i].argv)
			return (false);
		if (!(i == 0 && pipe->fdin == -1) &&
			!(i == pipe->len - 1 && pipe->fdout == -1))
			extract_path(i, pipe);
		i++;
	}
	return (true);
}
