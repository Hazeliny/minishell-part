/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:00:30 by linyao            #+#    #+#             */
/*   Updated: 2024/09/30 11:01:23 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

bool	do_execute(t_ms *ms)
{
	int	i;
	bool	flag_pipe;
	char	**av;

	i = 0;
	flag_pipe = false;
	while (ms->cmds[i])
	{
		if (ms->cmds[i][0] == '|')
		{
			ms->ac = count_arrays(ms->av_cmd);
			av = process_cmds(ms);//Ver si se necesita
			execute_pipe(ms, ms->ac + 3, av, hash_to_array(ms->env));
			free_array(av);
			flag_pipe = true;
		}
		i++;
	}
	if (!flag_pipe)
		exec_one_cmd(ms);
	return (true);
}
