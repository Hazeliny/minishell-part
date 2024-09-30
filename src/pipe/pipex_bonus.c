/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:35:59 by linyao            #+#    #+#             */
/*   Updated: 2024/08/26 17:47:34 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exe_cmd(char *cmd, char **env)
{
	char	**array_cmd;
	char	*path_env;

	array_cmd = ft_split(cmd, ' ');
	path_env = extract_path(array_cmd[0], env);
	if (!path_env)
	{
		free_array(array_cmd);
		handle_error();
	}
	if (execve(path_env, array_cmd, env) == -1)
	{
		free_array(array_cmd);
		free(path_env);
		handle_error();
	}
	free_array(array_cmd);
	free(path_env);
}

static void	put_in_pipe(char **av, int *p_end)
{
	char	*line;

	close(p_end[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, p_end[1]);
		free(line);
	}
}

static void	here_doc(char **av)
{
	int		p_end[2];
	pid_t	np;

	if (pipe(p_end) == -1)
		handle_error();
	np = fork();
	if (np == -1)
		handle_error();
	if (!np)
		put_in_pipe(av, p_end);
	else
	{
		close(p_end[1]);
		dup2(p_end[0], STDIN_FILENO);
		waitpid(np, NULL, 0);
	}
}

static void	run_pipe(char *cmd, char **env)
{
	int		p_end[2];
	pid_t	np;

	if (pipe(p_end) == -1)
		handle_error();
	np = fork();
	if (np == -1)
		handle_error();
	if (!np)
	{
		close(p_end[0]);
		dup2(p_end[1], STDOUT_FILENO);
		exe_cmd(cmd, env);
	}
	else
	{
		close(p_end[1]);
		dup2(p_end[0], STDIN_FILENO);
		waitpid(np, NULL, 0);
	}
}

int	execute_pipe(t_ms *ms, int ac, char **av, char **env)
{
	t_pipe	pipe;

	if (ac < 2)
		return (print_error("argument0 error", NULL), EXIT_FAILURE);
	if (!init_pipe(&pipe, ac, av, env))
		return (clean_pipe(&pipe), \
			print_error("init_pipe error", NULL), EXIT_FAILURE);
	if (ac < 2 + pipe.heredoc)
		return (clean_pipe(&pipe), \
			print_error("argument1 error", NULL), EXIT_FAILURE);
	if (!check_cmd(ms, &pipe))
		return (clean_pipe(&pipe), \
			print_error("check cmd error", NULL), EXIT_FAILURE);
	if (!process_pipes(&pipe))
		return (clean_pipe(&pipe), \
			print_error("process pipe error", NULL), EXIT_FAILURE);
	if (!run_pipe(&pipe))
		return (clean_pipe(&pipe), \
			print_error("run pipe error", NULL), EXIT_FAILURE);
	clean_pipe(&pipe);
	return (pipe.exitstat);
}
/*
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			handle_exit();
		fdout = open_file(av[ac - 1], 2);
		here_doc(av);
		i = 3;
	}
	else
	{
		fdin = open_file(av[1], 0);
		fdout = open_file(av[ac - 1], 1);
		dup2(fdin, STDIN_FILENO);
		i = 2;
	}
	while (i < ac - 2)
		run_pipe(av[i++], env);
	dup2(fdout, STDOUT_FILENO);
	exe_cmd(av[ac - 2], env);
}
*/
