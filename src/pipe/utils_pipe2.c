/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:49:22 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 17:31:25 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

void	redirection(t_pip *pip, int in, int out)
{
	if (n == 0)
	{
		dup2(pip->fdin, STDIN_FILENO);
		close(pip->p_end[0][0]);
		dup2(pip->p_end[0][1], STDOUT_FILENO);
		exe;
	}
	else if (n != pip->len - 1)
	{
		close(pip->p_end[n][0]);
		dup2(pip->p_end[n][1], STDOUT_FILENO);
		exe;
	}
	else
	{
		close(pip->p_end[n][1]);
		dup2(pip->p_end[n][0], STDIN_FILENO);
		exe;
	}
/*
	if (dup2(in, STDIN_FILENO) == -1)
	{
		clean_fds(pip);
		clean_pipe(pip);
		exit(-1);
	}
	close(in);
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		clean_fds(pip);
		clean_pipe(pip);
		exit(-1);
	}
	close(out);
*/
}

void	exec_son(t_pipe *pip, int in, int out, int n)
{
	redirection(pip, in, out);
	clean_fds(pip);
	
}

void	process_sons(t_pipe *pip, int n)
{
	if (!pip->cms[n].exist)
	{
		clean_fds(pip);
		clean_pipe(pip);
		exit(-1);
	}
	if (n == 0)
		exec_son(pip, pip->fdin, pip->p_end[n][1], n);
	else if (n != pip->len - 1)
		exec_son(pip, pip->p_end[n - 1][0], pip->p_end[n][1], n);
	else
		exec_son(pip, pip->p_end[n - 1][0], pip->fdout, n);
}
