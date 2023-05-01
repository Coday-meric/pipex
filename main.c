/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:22:01 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/12 13:28:01 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(t_pipex *data, int code)
{
	if (code == -1)
		ft_putstr_fd("Le nombre d'arguments doit etre de 4 ou plus !\n", 2);
	if (code == -2)
		ft_putstr_fd("Pipe non cree !\n", 2);
	else if (code == -3)
		ft_putstr_fd("Dup non effectue !\n", 2);
	else if (code == -4)
		ft_putstr_fd("Close non effectue !\n", 2);
	else if (code == -5)
		ft_putstr_fd("Fork non cree !\n", 2);
	else if (code == -6)
		ft_putstr_fd("Execution commande impossible !\n", 2);
	else if (code == -7)
		ft_putstr_fd("Fichier inexistant ou inaccessible !\n", 2);
	else if (code == -8)
		ft_putstr_fd("Commande inexistante !\n", 2);
	free(data);
	exit(EXIT_FAILURE);
}

static void	process(int i, t_pipex *data, char **argv, char **env)
{
	char	*cmd;
	char	**args;

	if (i == 1)
	{
		first_child(data, argv[1]);
		i++;
	}
	else if (i >= 2 && i < data->argc - 3 && data->argc > 5)
	{
		mid_child(data);
		i++;
	}
	else if (i == data->argc - 3)
	{
		i++;
		final_child(data, argv[i + 1]);
	}
	args = get_args(argv[i]);
	cmd = get_cmd_path(data, args[0], env);
	check_cmd(data, cmd, args);
	if (execve(cmd,get_args(argv[i]), env) == -1)
		error(data, -6);
}

static void	init_fork(t_pipex *data, int argc)
{
	if (argc < 5)
		error(data, -1);
	data->argc = argc;
}

static void	parent(int i, t_pipex *data)
{
	waitpid(-1, NULL, WNOHANG);
	do_close(data, data->pipefd[1]);
	data->pipeprev = data->pipefd[0];
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*data;
	pid_t	pid;
	int		i;

	data = malloc(sizeof(t_pipex));
	i = 1;
	init_fork(data, argc);
	while (i < argc - 2)
	{
		if (pipe(data->pipefd) == -1)
			error(data, -2);
		pid = fork();
		if (pid == -1)
			error(data, -5);
		else if (pid == 0)
			process(i, data, argv, env);
		else if (pid > 0)
		{
			parent(i, data);
			i++;
		}
	}
	free(data);
	return (0);
}
