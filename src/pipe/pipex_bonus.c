/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:35:59 by linyao            #+#    #+#             */
/*   Updated: 2024/10/02 12:04:42 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	execute_pipe(t_ms *ms, int ac, char **av, char **env)
{
	t_pipe	pip;

	if (ac < 2)
		return (print_error("argument0 error", NULL), EXIT_FAILURE);
	if (!init_pipe(&pip, ac, av, env))
		return (clean_pipe(&pip), \
			print_error("init_pipe error", NULL), EXIT_FAILURE);
	if (ac < 2 + pip.heredoc)
		return (clean_pipe(&pip), \
			print_error("argument1 error", NULL), EXIT_FAILURE);
	if (!check_cmd(ms, &pip))
		return (clean_pipe(&pip), \
			print_error("check cmd error", NULL), EXIT_FAILURE);
	if (!process_pipes(&pip))
		return (clean_pipe(&pip), \
			print_error("process pipe error", NULL), EXIT_FAILURE);
	if (!run_pipe(&pip))
		return (clean_pipe(&pip), \
			print_error("run pipe error", NULL), EXIT_FAILURE);
	clean_pipe(&pip);
	return (pip.exitstat);
}
