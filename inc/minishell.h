/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:14:45 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 16:56:52 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include "env.h"
# include <limits.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT "\x1b[1;32mminishell\x1b[0m\x1b[1;36m > \x1b[0m"
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define MORE '>'
# define LESS '<'
# define PIPE '|'
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define DOUBLE_MORE ">>"
# define DOUBLE_LESS "<<"
# define MORE_S ">"
# define LESS_S "<"
# define PIPE_S "|"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

struct	s_hash;

typedef struct s_ms
{
	int			ac;
	char			**av;//{"cat"}{"<"}{"infile"}{"|"}{"gre"}...
	struct s_hash	*env;
	char			**raw_env;
	char			**inf;//input for redirection
	char			**outf;//output for redirection
	char			**av_cmd;//arrays with arguments or "|"
	char			**cmds;//another way to combine cmd and parameters
	char			***args;//tridimensional arrays for command blocks
	bool			f_in;// "< infile"
	bool			f_heredoc;// "<< delimiter"
	bool			f_out_trunc;// "> outfile"
	bool			f_out_append;// ">> outfile"
}	t_ms;

typedef struct s_cmds
{
	char	**argv;
	char	*path;//same with fullpath in t_pipe, but exist in fullpath
	bool	exist;
}	t_cmds;

typedef struct s_pipe
{
	int		len;
	int		fdin;
	int		fdout;
	int		**p_end;
	pid_t	*np;
	bool	heredoc;
	int		exitstat;// status when exit, used for $? and $_
	char	**arv;
	char	**paths;//"/bin""usr/bin""/usr/local/bin"
	char	**envir;
	t_cmds	*cms;
}	t_pipe;

void	init_ms(t_ms *ms, char **env);
void	init_env(t_ms *ms, char **env);
void	realize_shell(t_ms *ms);

//------------------parse------------------
bool	handle_single(bool *s_close, bool *d_close, int *flag);
bool	handle_double(bool *s_close, bool *d_close, int *flag);
bool	check_quote(char *s);
void	split_into_arrays(char ***new, char *input);
char	**split_av(char *input);
void	store_to_array(char ***array, char **arr);
bool	add_array(char ***array, char *s);
bool	append_str(char **arr, char *env_val);
bool	append_char(char **arr, char c);
void    renovar_array(char ***new_array, char **new_arr, char **str);
void	move_over(char **str);
char	*extract_key(const char *str);
void	handle_special(char ***array, char **arr, char **c);
void	handle_quote(t_hash *env, char ***array, char **arr, char **c);
bool	is_ordinary(char c);
bool	is_compliance(char **arrays);
void	free_array(char **arrays);
int		count_arrays(char **arrays);
char	**process_av(char **av, struct s_hash *env);
void	check_handle_dollar(t_hash *env, char **arr, char **c, char ch);
char    **get_infile_path(char ***av);
void    delete_file_element(char ***av, char **fl);
int     find_index_array(char **ar, char *s);
bool    del_array_em(int inx, char ***av);
void    init_array(char **arr, int len);
char    **validate_inf(char **inf);
char    **get_outfile_path(char ***av);
char	**transform_av_cmd(char **av);
char	**transform_cmds(char ***av);
char    ***transform_args(char **av);

//---------------------------Redirection------------------------------
void	set_outfile_flag(t_ms *ms, char **out);
void	set_infile_flag(t_ms *ms, char **in);

//---------------------------Pipe-------------------------------------
char    **process_cmds(t_ms *ms);
bool    init_pipe(t_pipe *pip, int ac, char **av, char **env);
bool    init_cmds(t_pipe *pip);
int     execute_pipe(t_ms *ms, int ac, char **av, char **env);
void    print_error(char *s, char *file);
bool    clean_pipe(t_pipe *pip);
bool    check_cmd(t_ms *ms, t_pipe *pip);
void    get_allpaths(t_pipe *pip);
void    extract_path(int i, t_pipe *pip);
bool    validate_cmd(t_pipe *pip, char *cmd, int n);
bool    process_pipes(t_pipe *pip);
bool    run_pipe(t_pipe *pip);
bool    init_pids(t_pipe *pip);
bool    clean_fds(t_pipe *pip);
void    process_sons(t_pipe *pip, int n);
void    exec_son(t_pipe *pip, int in, int out, int n);
void    redirection(t_pip *pip, int in, int out);
bool    wait_sons_id(t_pipe *pip);

//Utils
bool	is_special(const char *s);

//Built-ins
int		blt_echo(char **av);
int		blt_exit(char **av);
int		blt_cd(char **av, t_hash *env);
int		blt_pwd(void);
int		blt_export(char **av, t_hash *env);
int		blt_unset(char **av, t_hash *env);

#endif
