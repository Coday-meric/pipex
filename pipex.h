/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:22:27 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/12 13:28:14 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./lib/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int	pipefd[2];
	int	pipeprev;
	int	argc;
}	t_pipex;

void	first_child(t_pipex *data, char *file);
void	mid_child(t_pipex *data);
void	final_child(t_pipex *data, char *file);
void	do_close(t_pipex *data, int fd);
void	do_dup2(t_pipex *data, int fd1, int fd2);
void	error(t_pipex *data, int code);
void	check_cmd(t_pipex *data, char *cmd, char **args);
char	*get_cmd_path(t_pipex *data, char *cmd, char **env);
char	**get_args(char *argv);

#endif //PIPEX_H
