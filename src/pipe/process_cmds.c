/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:44:14 by linyao            #+#    #+#             */
/*   Updated: 2024/09/30 13:44:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

char	**process_cmds(t_ms *ms)
{
	int	i;
	int	j;
	char	**res_av;

	j = 0;
	i = 2;
	res_av = malloc((ms->ac + 4) * sizeof(char *));
	if (!res_av)
		return (NULL);
	res_av[0] = ft_strdup("./minishell");
	if (!ms->inf)
		res_av[1] = ft_strdup("../../infile");
	else if (ms->f_heredoc)
	{
		res_av[1] = ft_strdup("here_doc");
		res_av[2] = ft_strdup(ms->inf[count_arrays(ms->inf) - 1]);
		i++;
	}
	else
		res_av[1] = ft_strdup(ms->inf[count_arrays(ms->inf) - 1]);
	while (j < ms->ac)
		res_av[i++] = ft_strdup(ms->av_cmd[j++]);
	if (ms->f_out_trunc == false && ms->f_out_append == false)
		res_av[i] = ft_strdup("../../outfile");
	else
		res_av[i] = ft_strdup(ms->outf[count_array(ms->outf) - 1]);
	res_av[i + 1] = NULL;
	return (res_av);
}
