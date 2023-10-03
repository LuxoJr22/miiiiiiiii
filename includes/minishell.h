/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sforesti <sforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:44:13 by sforesti          #+#    #+#             */
/*   Updated: 2023/10/03 18:57:59 by sforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <libft.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_file {
	int				type;
	char			*fd_file;
	struct s_file	*next;
}				t_file;

typedef struct s_cmd {
	char			*name;
	char			**arg;
	int				fd[2];
	int				in;
	int				out;
	int				here_doc;
	t_file			*file;
	struct s_cmd	*next;
}				t_cmd;

extern pid_t	g_pid;

void	ft_echo(char **str);
void	fonction(int signal);
void	exec_minishell(char *command, char **envp, t_cmd *cmd, char *line);
char	**env_change(char **envp, t_cmd *cmd);
char	**ft_split_f(char *s, char c);
void	ft_env(char **envp);
int		is_in(char *str, char c);
char	*process_line(char *str, char **ret, char **envp);
int		is_equal(char *search, char *str);
void	ft_exit(char **envp, char **arg);
void	process_redirect(char **envp, t_cmd *cmd);
char	**ft_export(char **envp, char **str);
char	**ft_unset(char **name, char **envp);
void	ft_cd(char *path, char **envp);
int		ft_atoi_f(char *str);
char	**split_path(char **envp);
char	*acces_cmd(char *cmdn, char **envp);
char	*ft_quote(char *str);
void	free_dptr(char	**dptr);
void	exec_cmd(t_cmd *cmd, char **envp, char *line);
char	*str_lower(char *str);
void	rl_replace_line(const char *text, int clear_undo);
int		count_pipe(char *line);
char	*ft_strjoin_env(char *s1, char *s2, int mode);
char	**pre_process(t_cmd *cmd, char **envp);
char	**ft_split_parse(char const *s, int mode);
int		manage_pipe(t_cmd *cmd, char **envp, char *line);
int		get_command(t_cmd *cmd, char **envp, char *line);
char	*ft_cutenv(char *str);
int		size_dptr(char **str);
t_cmd	*init_cmd_pipe(char *line, char **envp);
void	cmd_with_path(t_cmd *cmd, char	*path, char **envp);
void	ft_handle_ctrl_slash(int signal);
char	*join_path(char **str);
t_cmd	*init_cmd_basic(t_cmd *cmd, char *line, char **envp);
int		find_name(char	**str, int mode);
t_cmd	*manage_cmd(char *line, char **envp);
void	manage_exec(char *line, char **envp, t_cmd *cmd);
t_cmd	*parse_path(t_cmd *cmd, char *path);
void	ft_handle_ctrlc(int signal);
void	exec_for_pipe(t_cmd *cmd, char **envp);
int		create_infile(char *limiter, char **envp);
void	redirect_ex_cmd_basic(t_file *file);
void	redirect_en_cmd_basic(t_file *file);
char	*ft_union(char	**str);
t_cmd	*parsed_line(char *line, char **envp);
void	manage_redirec(t_cmd *cmd, char *line);
t_file	*init_tfile(char *line);
char	*reset_quote(char *str);
void	init_struct(t_cmd *cmd);
void	redirection(t_cmd *cmd, t_file *file, char **envp);
void	quit(int i);
void	handle_ctrl(void);
void	interrupt(int i);
char	*ft_getenv(char **envp, char *str);
char	**ft_fill_pa(char const *s, int mode, char **r_str, int verif);
int		index_env(char *name, char **envp);
int		is_env(char	*env, char	*str);
int		ft_in_env(char *str, char **envp);
int		ft_is_charset_pa(char const s, int mode);
char	*ft_fill_str_pa(char const *s, int start, int end, char c);
void	parsing_en_here_doc(t_cmd *cmd, t_file *file, int coor[2]);
void	parsing_en(t_cmd *cmd, t_file *file, int coor[2]);
void	parsing_ex_append(t_cmd *cmd, t_file *file, int coor[2]);
void	parsing_ex(t_cmd *cmd, t_file *file, int coor[2]);
void	choose_parsing(t_cmd *cmd, t_file *file, char *line, int coor[2]);
void	call_parsing_redir(t_cmd *cmd, char *line);
void	ft_pwd(char **envp);
void	free_list(t_cmd *cmd);
char	*ft_strmup(const char *s1);
int		add_var_env(char *var, char **envp, char *line);
int		size_alloc(char *str, char **envp);
int		is_good_name_var(char *str, int i);
char	*dup_name_var(int i, char *str, char *word);
char	*free_dptr_line(char **dptr, char *str);
int		is_in_quote(char *str, char c);
int		built_in(char *command, t_cmd *cmd, char **envp, char *line);
void	ft_init_signals(void);
void	verif_limiter(char *line, char *limiter);
void	export_sort(char **envp, int i, int index);
int		fill_envp(char **envn, char **envp, int i, int lvl);
char	*fd_to_str(int fd[2]);
void	change_env(char **envp, char *str);
int		verif(char *line);
char	*get_line_env(char *str, char *ret);
int		check(t_cmd *cmd, char **envp);

#endif