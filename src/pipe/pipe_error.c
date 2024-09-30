/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:15:35 by linyao            #+#    #+#             */
/*   Updated: 2024/09/30 17:15:40 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"
#include "../../inc/pipex_bonus.h"

void	print_error(char *s, char *file)
{
	ft_putstr_fd(s, 2);
	if (file)
		ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
}
