/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:44:46 by linyao            #+#    #+#             */
/*   Updated: 2024/09/19 17:34:55 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

bool	append_char(char **arr, char c)
{
	char	*new_arr;
	size_t	arr_len;

	if (!*arr)
	{
		*arr = malloc(sizeof(char) * 2);
		if (!*arr)
			return (false);
		(*arr)[0] = c;
		(*arr)[1] = '\0';
		return (true);
	}
	arr_len = ft_strlen(*arr);
	new_arr = (char *)ft_realloc(*arr, arr_len + 1, \
					arr_len + 2);
	if (!new_arr)
		return (false);
	new_arr[arr_len] = c;
	new_arr[arr_len + 1] = '\0';
	*arr = new_arr;
	return (true);
}

bool	is_ordinary(char c)
{
	if (c != ' ' && c != '\t' && c != MORE && c != LESS && c != PIPE \
					&& c != S_QUOTE && c != D_QUOTE)
		return (true);
	return (false);
}

void	renovar_array(char ***new_array, char **new_arr, char **str)
{
	if ((**str == ' ' || **str == '\t') && *new_arr)
	{
		store_to_array(new_array, new_arr);
		move_over(str);
	}
}
