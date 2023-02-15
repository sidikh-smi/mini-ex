
#include "../include/minishell.h"

int builtins(t_list *list, t_list *envi)
{
	t_parser *d = (t_parser *)list->content;
	

	if(!ft_strncmp(d->cmd[0],"echo",5)) 
		echo(d->cmd);
	// else if(!ft_strncmp(d->cmd[0],"cd",3)) 
	// 	cd(envi);
	else if(!ft_strncmp(d->cmd[0],"pwd",4))
		pwd();
	else if(!ft_strncmp(d->cmd[0],"export",7))
		export(d->cmd[1],envi);
	else if(!ft_strncmp(d->cmd[0],"unset",6))
		unset(d->cmd[1] ,envi);
	else if(!ft_strncmp(d->cmd[0],"env",4))
		env(envi);
	else if(!ft_strncmp(d->cmd[0],"exit", 5))
		f_exit(d->cmd);
	else 
		return 1;
	return 0;
}

void unset(char *var, t_list *envi)
{
	(void)var;
	t_env * temp_var;
	t_list *previous;

	temp_var = malloc(sizeof(t_env));
	if (envi->content == NULL)
		return ;
	while(envi)
	{	
		temp_var = (t_env *) envi->content;
		if(!ft_strncmp(temp_var->key,var,ft_strlen(var)))
		{
			if(envi->next)
				previous->next = envi->next;
			else
				previous->next = NULL;
			free(envi);
			return ;
		}
		previous  = envi;
		envi = envi->next;
	}
}
void	env(t_list* senv)
{
	t_list *curr;
	t_env *curr_value;

	curr = senv;
	while (curr)
	{
		curr_value = (t_env *)(curr->content);
		printf("%s=%s\n", curr_value->key, curr_value->value);
		curr = curr->next;
	}
}

void	export(char *var , t_list *env)
{	
	char **all;
	t_env * temp_var;
	temp_var = malloc(sizeof(t_env));
	all = ft_split(var, '=');
	temp_var->key = all[0];
	temp_var->value= all[1];
	ft_lstadd_back(&env, ft_lstnew(temp_var));
}

void	pwd(void)
{
	char s[PATH_MAX];
	if (getcwd(s, sizeof(s)) != NULL)
		printf("%s\n", s);
}

int	remove_line(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	else
		return (0);
	while (s[i])
	{
		if (s[i] == 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo(char **s)
{
	int	i;
	int	remove_new_line;

	i = 1;
	remove_new_line = 0;
	while (s[i])
	{
		if (remove_line(s[1]))
		{
			remove_new_line = 1;
			i++;
		}
		printf("%s", s[i]);
		if (s[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!remove_new_line)
		printf("\n");
}

int	size_par(char **s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i][j])
			j++;
		i++;
	}
	return (i);
}

void	one_par(char *s)
{
	if (!not_number(s))
		
}

void	f_exit(char **s)
{
	int	size;

	size = size_par(s);
	//printf(">> %d\n", size);
	if (size == 2)
		one_par(s[1]);
}