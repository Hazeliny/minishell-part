/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:03:52 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 15:47:47 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

bool	process_pipes(t_pipe *pip)
{
	int	i;

	i = 0;
	pip->p_end = malloc(sizeof(int *) * pip->len);
	if (!pip->p_end)
		return (false);
	while (i < pip->len)
	{
		pip->p_end[i] = malloc(sizeof(int *) * 2);
		if (!pip->p_end[i])
			return (false);
		if (pipe(p_end[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

bool	init_pids(t_pipe *pip)
{
		int	i;

		pip->np = malloc(sizeof(pid_t) * pip->len);
		if (!pip->np)
			return (false);
		i = 0;
		while (i < pip->len)
		{
			pip->np[i] = -1;
			i++;
		}
		return (true);
}

bool	clean_fds(t_pipe *pip)
{
	int	i;

	if (!pip->p_end)
		return (false);
	i = 0;
	while (i < pip->len && pip->p_end[i])
	{
		close(pip->p_end[i][0]);
		close(pip->p_end[i][1]);
		if (pip->p_end[i])
			free(pip->p_end[i]);
		i++;
	}
	free(pip->p_end);
	if (pip->fdin != -1)
		close(pip->fdin);
	if (pip->fdout != -1)
		close(pip->fdout);
	return (true);
}

bool	wait_sons_id(t_pipe *pip)
{
	int	i;
	int	stat;

	i = 0;
	while (i < pip->len && pip->np[i] > 0)
	{
		waitpid(pip->np[i], &stat, 0);
//Aqui si debe haber algun tartamiento del senal???
		i++;
	}
	if (pip->fdout == -1)
		pip->exitstat = 1;
	else if (!pip->cms[pip->len - 1].exist)
		pip->exitstat = 127;
	else
		pip->exitstat = 0;
	return (true);
}

bool	run_pipe(t_pipe *pip)
{
	int		i;
	pid_t	p;

	if (!init_pids(pip))
		return (false);
	i = 0;
	while (i < pip->len)
	{
		p = fork();
		if (p < 0)
			return (clean_fds(pip));
		else if (!p)
		{
// Ver si necesita tratar algun senal?
			process_sons(pip, i);
		}
		else
			pip->np[i] = p;
		i++;
	}
	clean_fds(pip);
	wait_sons_id(pip);
	return (true);
}
