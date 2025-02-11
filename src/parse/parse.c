/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:41 by linyao            #+#    #+#             */
/*   Updated: 2024/10/03 16:54:36 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/env.h"

bool	handle_single(bool *s_close, bool *d_close, int *flag)
{
	if (*flag == DOUBLE_QUOTE)
	{
		*flag = SINGLE_QUOTE;
		if (!*d_close && !*s_close)
			return (false);
		else if (*d_close && !*s_close)
			*s_close = true;
		else if (*s_close)
			*s_close = false;
	}
	else if (*flag == SINGLE_QUOTE)
		*s_close = !*s_close;
	else if (*flag == 0)
	{
		*flag = SINGLE_QUOTE;
		*s_close = false;
	}
	return (true);
}

bool	handle_double(bool *s_close, bool *d_close, int *flag)
{
	if (*flag == SINGLE_QUOTE)
	{
		*flag = DOUBLE_QUOTE;
		if (!*s_close && !*d_close)
			return (false);
		else if (*s_close && !*d_close)
			*d_close = true;
		else if (*d_close)
			*d_close = false;
	}
	else if (*flag == DOUBLE_QUOTE)
		*d_close = !*d_close;
	else if (*flag == 0)
	{
		*flag = DOUBLE_QUOTE;
		*d_close = false;
	}
	return (true);
}

bool	check_quote(char *s)
{
	bool	single_quote_close;
	bool	double_quote_close;
	int		flag;

	single_quote_close = true;
	double_quote_close = true;
	flag = 0;
	while (*s)
	{
		if (*s == '\'')
		{
			if (!handle_single(&single_quote_close, &double_quote_close, &flag))
				return (false);
		}
		else if (*s == '\"')
		{
			if (!handle_double(&single_quote_close, &double_quote_close, &flag))
				return (false);
		}
		s++;
	}
	return (single_quote_close && double_quote_close);
}

void	split_into_arrays(t_hash *env, char ***new, char *input)
{
	char	*str;
	char	*new_arr;
	char	**new_array;

	new_arr = NULL;
	new_array = NULL;
	if (!input || !new)
		return ;
	str = ft_strtrim(input, " \t");
	input = str;
	while (*str)
	{
		renovar_array(&new_array, &new_arr, &str);
		handle_special(&new_array, &new_arr, &str);
		if (str == input && (*str == S_QUOTE || *str == D_QUOTE))
			return (void)(ft_printf("Wrong command format\n"), 0);
		else
			handle_quote(env, &new_array, &new_arr, &str);
		if (is_ordinary(*str))
			append_char(&new_arr, *str);
		if (*str)
			str++;
	}
	store_to_array(&new_array, &new_arr);
	*new = new_array;
	free(input);
}

char	**split_av(t_hash *env, char *input)
{
	char	**new;

	if (!input || !input[0])
		return (NULL);
	if (!check_quote(input))
	{
		perror("These quotes don't match.");
		return (NULL);
	}
	new = NULL;
	split_into_arrays(env, &new, input);
	if (!is_compliance(new))
		return (free_array(new), NULL);
	return (new);
}

int main(int ac, char **av, char **env)
{
	char	input[] = " 	cat << EOF | grep $HOME 'pattern' \"$PWD\" >>  output.txt ";
	char	**res1;
	char    **res;
	t_ms	ms;

	(void)av;
	(void)ac;
	init_env(&ms, env);
	res1 = split_av(ms.env, input);
//	printf("test\n");//
//	for (int i = 0; res1[i] != NULL; i++)
//        	printf("%s\n", res1[i]);
	res = process_av(res1, ms.env);
	for (int i = 0; res[i] != NULL; i++)
	{
		printf("%s\n", res[i]);
		free(res[i]);
	}
	free(res);

//	char	arr[3][10];
/*
	bool	b;
	b = check_quote("This \"is\' a \' test\" for\' \"something\"");
	if (b)
		printf("valid");
	else
		printf("invalid");
*/
//	arr = split_av("This \'is \" a \'test for \"something");
//	for (int i = 0; i < 3; i++)
//		printf("%s\n", arr[1]);

	return (0);
}

