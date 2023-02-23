/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:47:49 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/23 16:56:45 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_list *export)
{
	t_env	*temp_var;

	while (export)
	{
		temp_var = (t_env *)(export->content);
		printf("declare -x %s", temp_var->key);
		if (temp_var->value)
			printf("=\"%s\"", temp_var->value);
		printf("\n");
		export = export->next;
	}
}

t_env	*get_key_value(char *str)
{
	t_env	*key_value;
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal != NULL)
		*equal = '\0';
	key_value = s_malloc(sizeof(t_env));
	key_value->key = ft_strdup(str);
	if (equal != NULL)
		key_value->value = ft_strdup(equal + 1);
	else
		key_value->value = NULL;
	return (key_value);
}

int	replace_value(char *key, char *value, t_list *env)
{
	t_env	*s;

	while (env)
	{
		s = (t_env *) env->content;
		if (!ft_strcmp(key, s->key))
		{
			if (!value)
				return (2);
			else
				s->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	else
		i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(char **var)
{
	int		i;
	int		j;
	int		s;
	t_env	*temp_var;
	t_list	*export;

	export = g_data.env;
	temp_var = s_malloc(sizeof(t_env));
	i = size_par(var);
	j = 0;
	s = 0;
	if (i == 1)
		print_export(export);
	else
	{
		while (++j < i)
		{
			temp_var = get_key_value(var[j]);
			s = replace_value(temp_var->key, temp_var->value, export);
			if (check_key(temp_var->key))
				printf("not a valid identifier\n");
			else if (s == 0)
				ft_lstadd_back(&export, ft_lstnew(temp_var));
		}
	}
}
