/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:37:08 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 12:53:27 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_exit(void)
{
	ft_putstr_fd("Error: Incorrect numbers of arguments\n", 2);
	ft_putstr_fd("Pls Input: ./pipex infile cmd1 cmd2 ... outfile\n", 1);
	ft_putstr_fd("Or Input: ./pipex here_doc LIMITER  cmd cmd1 file\n", 1);
	exit(0);
}

void	handle_error(void)
{
	perror("Error");
	exit(-1);
}

int	open_file(char *file, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY);
	if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		handle_error();
	return (fd);
}

void	get_allpaths(t_pipe *pip)
{
	int	i;

	i = 0;
	if (!pip->envir)
		return ;
	while (pip->envir[i] && ft_strnstr(pip->envir[i], "PATH", 4) == NULL)
		i++;
	if (pip->envir[i] && ft_strnstr(pip->envir[i], "PATH", 4) != NULL)
		pip->paths = ft_split(pip->envir[i] + 5, ':');
}

bool	validate_cmd(t_pipe *pip, char *cmd, int n)
{
	if (!cmd)
		return (false);
	if (access(cmd, F_OK | X_OK) == 0 && ft_strncmp(cmd, "/", 1) == 0)
	{
		pip->cms[n].path = ft_strdup(cmd);
		if (!pip->cms[n].path)
			return (false);
		free(cmd);
		pip->cms[n].exist = true;
		return (true);
	}
	free(cmd);
	return (false);
}

void	extract_path(int n, t_pipe *pip)
{
	int		i;
	char	*path;
	char	*pathcmd;

	if (pip->cms[n].argv[0] && \
		validate_cmd(pip, ft_strdup(pip->cms[n].argv[0]), n))
		return ;
	i = 0;
	while (pip->paths[i])
	{
		path = ft_strjoin(pip->paths[i], "/");
		pathcmd = ft_strjoin(path, pip->cms[n].argv[0]);
		free(path);
		if (validate_cmd(pip, pathcmd, n))
			return ;
		i++;
	}
	if (!pip->paths[i])
	{
		ft_printf("cmd not found: %s\n", pip->cms[n].argv[0]);
		pip->cms[n].exist = false;
	}
}
