/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:41:17 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 21:52:40 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:05:46 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/21 23:41:15 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_builtin(t_list *list)
{
	t_parser	*d;

	d = (t_parser *)list->content;
	if (!ft_strcmp(d->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(d->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(d->cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(d->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(d->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(d->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(d->cmd[0], "env"))
		return (1);
	return (0);
}

void	builtins(t_list *list)
{
	t_parser	*d;

	d = (t_parser *)list->content;
	if (!ft_strcmp(d->cmd[0], "echo"))
		ft_echo(d->cmd, d->out_file);
	else if (!ft_strcmp(d->cmd[0], "cd"))
		ft_cd(d->cmd);
	else if (!ft_strcmp(d->cmd[0], "pwd"))
		ft_pwd(d->out_file);
	else if (!ft_strcmp(d->cmd[0], "export"))
		ft_export(d->cmd, d->out_file);
	else if (!ft_strcmp(d->cmd[0], "unset"))
		ft_unset(d->cmd);
	else if (!ft_strcmp(d->cmd[0], "env"))
		ft_env(d->out_file);
	else if (!ft_strcmp(d->cmd[0], "exit"))
		ft_exit(d->cmd);
	return ;
}

int	size_par(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_env(int fd)
{
	t_list	*curr;
	t_env	*curr_value;

	curr = g_data.env;
	while (curr)
	{
		curr_value = (t_env *)(curr->content);
		//printf("%s=%s\n", curr_value->key, curr_value->value);
		ft_putstr_fd(curr_value->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(curr_value->value, fd);
		ft_putstr_fd("\n", fd);
		curr = curr->next;
	}
}

void	ft_pwd(int fd)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
	}
}
