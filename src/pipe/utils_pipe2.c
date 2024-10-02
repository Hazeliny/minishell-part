/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:49:22 by linyao            #+#    #+#             */
/*   Updated: 2024/10/02 11:55:48 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

void	redirection(t_pip *pip, int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
	{
		clean_fds(pip);
		clean_pipe(pip);
		exit(EXIT_FAILURE);
	}
	close(in);
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		clean_fds(pip);
		clean_pipe(pip);
		exit(EXIT_FAILURE);
	}
	close(out);
}

void	exec_son(t_pipe *pip, int in, int out, int n)
{
	redirection(pip, in, out);
	clean_fds(pip);
	if (execve(pip->cms[n]->path, pip->cms[n]->argv, pip->envir) == -1)
	{
		clean_pipe(pip);
		print_error("execve error", NULL);
	}
	exit(EXIT_FAILURE);
}

void	process_sons(t_pipe *pip, int n)
{
	if (!pip->cms[n].exist)
	{
		clean_fds(pip);
		clean_pipe(pip);
		exit(EXIT_FAILURE);
	}
	if (n == 0)
		exec_son(pip, pip->fdin, pip->p_end[n][1], n);
	else if (n != pip->len - 1)
		exec_son(pip, pip->p_end[n - 1][0], pip->p_end[n][1], n);
	else
		exec_son(pip, pip->p_end[n - 1][0], pip->fdout, n);
}
