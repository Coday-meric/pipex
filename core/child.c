/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:24:42 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/11 23:19:41 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	do_close(t_pipex *data, int fd)
{
	if (close(fd) == -1)
		error(data, -4);
}

void	do_dup2(t_pipex *data, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error(data, -3);
}

void	first_child(t_pipex *data, char *file)
{
	int	fd_in;

	if (access(file, R_OK) == -1)
		error(data, -7);
	fd_in = open(file, O_RDONLY);
	do_dup2(data, fd_in, 0);
	do_dup2(data, data->pipefd[1], 1);
	do_close(data, fd_in);
	do_close(data, data->pipefd[0]);
}

void	mid_child(t_pipex *data)
{
	do_dup2(data, data->pipeprev, 0);
	do_dup2(data, data->pipefd[1], 1);
	do_close(data, data->pipefd[0]);
}

void	final_child(t_pipex *data, char *file)
{
	int	fd_out;

	fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (access(file, W_OK) == -1)
		error(data, -7);
	do_dup2(data, fd_out, 1);
	do_dup2(data, data->pipeprev, 0);
	do_close(data, fd_out);
	do_close(data, data->pipeprev);
}
