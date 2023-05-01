/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaisonn <amaisonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:22:14 by amaisonn          #+#    #+#             */
/*   Updated: 2023/04/12 13:27:47 by amaisonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_cmd(t_pipex *data, char *cmd, char **args)
{
	if (ft_strnstr(cmd, "which: no", 10) != NULL)
	{
		free(args[0]);
		free(args[1]);
		free(args[2]);
		free(args);
		free(cmd);
		error(data, -8);
	}
}

static char	*pipetochar(t_pipex *data, int *pipecmd)
{
	char	*res;

	do_close(data, pipecmd[1]);
	res = ft_calloc(200, sizeof(char));
	read(pipecmd[0], res, 200);
	do_close(data, pipecmd[0]);
	res[ft_strlen(res) - 1] = '\0';
	return (res);
}

char	**get_args(char *argv)
{
	char	**res;

	res = ft_split(argv, ' ');
	return (res);
}

static void	process(t_pipex *data, int *pipecmd, char *cmd, char **env)
{
	char	**args;
	int		i;

	i = 0;
	do_close(data, pipecmd[0]);
	do_dup2(data, pipecmd[1], 1);
	do_dup2(data, pipecmd[1], 2);
	do_close(data, pipecmd[1]);
	args = ft_calloc(3, sizeof(char *));
	args[1] = ft_calloc((ft_strlen(cmd) + 1), sizeof(char));
	args[2] = ft_calloc(1, sizeof(char));
	while (cmd[i])
	{
		args[1][i] = cmd[i];
		i++;
	}
	args[0] = ft_strdup("which");
	args[1][i] = '\0';
	args[2] = 0;
	if (execve("/usr/bin/which", args, env) == -1)
		error(data, -6);
}

char	*get_cmd_path(t_pipex *data, char *cmd, char **env)
{
	pid_t	pid;
	int		pipecmd[2];
	char	*res;

	if (pipe(pipecmd) == -1)
		error(data, -2);
	pid = fork();
	if (pid == -1)
		error(data, -5);
	else if (pid == 0)
		process(data, pipecmd, cmd, env);
	else if (pid > 0)
	{
		waitpid(pid, NULL, WNOHANG);
		res = pipetochar(data, pipecmd);
		return (res);
	}
	return ("error");
}
