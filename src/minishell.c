/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/09/27 17:26:47 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

void	init_ms(t_ms *ms, char **env)
{
	init_env(ms, env);
}

void	realize_shell(t_ms *ms)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (input && *input)
		{
			add_history(input);
			ms->av = split_av(ms->env, input);
			if (!ms->av)
				continue ;
			free(input);
			input = NULL;
			ms->av = process_av(ms->av, ms->env);
			ms->inf = validate_inf(get_infile_path(&ms->av));//
			ms->outf = get_outfile_path(&ms->av);
			set_outfile_flag(ms, ms->outf);
			set_infile_flag(ms, ms->inf);
			ms->av_cmd = transform_av_cmd(ms->av);
			ms->cmds = transform_cmds(&ms->av);
			ms->args = transform_args(ms->av);
			do_execs(ms->av, ms->env, ms->raw_env);//
		}
		if ((input && ft_strcmp(input, "exit") == 0) || !input)
		{
			if (input)
			{
				free(input);
				break;
			}
			break ;
		}
		printf("%s\n", input);//test
	}
}

