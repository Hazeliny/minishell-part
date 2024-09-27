/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:23:43 by linyao            #+#    #+#             */
/*   Updated: 2024/09/27 17:22:39 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

void	init_array(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		arr[i] = NULL;
		i++;
	}
}

//copy the content in old two-dimensional array into new one
//size of new one is reduced by one unit
//new array also ends with NULL (in init_array)
static char	**copy_new_arr(char **arr)
{
	int	i;
	int	len;
	char	**res;

	i = 0;
	len = count_arrays(arr);
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	init_array(res, len);
	while (i < len - 1)
	{
		res[i] = ft_strdup(arr[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	free_array(arr);
	return (res);
}

//delete the element about infile or outfile from two-dimensional array
bool	del_array_em(int inx, char ***av)
{
	int	l;

	l = count_arrays(*av);
	if (inx >= len || inx < 0)
		return (false);
	if (l == 1)
	{
		free_array(*av);
		return (true);
	}
	free((*av)[inx]);
	(*av)[inx] = NULL;
	while (inx < l - 1)
	{
		(*av)[inx] = (*av)[inx + 1];
		inx++;
	}
	(*av)[inx] = ft_strdup("blank");
	*av = copy_new_arr(*av);
	return (true);
}
