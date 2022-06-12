#include "shell.h"

/**
 * implement_cd - execute cd builtin
 * @build: input build
 * Return: 1 on success, 0 on failure
 */
int implement_cd(config *build)
{
	register uint count = 0;
	_Bool can_change = false;

	count = count_args(build->args);
	if (count == 1)
	{
		can_change = cd_to_home(build);
	}
	else if (count == 2 && _strcmp(build->args[1], "-") == 0)
	{
		can_change = cd_to_previous(build);
	}
	else
	{
		can_change = cd_to_custom(build);
	}
	if (can_change)
	{
		update_environ(build);
	}
	return (1);
}

/**
 * cd_to_home - change directory to home
 * @build: input build
 * Return: true on success, false on failure
 */
_Bool cd_to_home(config *build)
{
	register int i;
	char *str, *ptr;

	i = search_node(build->env, "HOME");
	if (i == -1)
	{
		return (true);
	}
	str = get_node_at_index(build->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	return (true);
}

/**
 * cd_to_previous - change directory to previous directory -
 * address is found in OLDPWD env var
 * @build: input build
 * Return: true on success, false on failure
 */
_Bool cd_to_previous(config *build)
{
	register int i;
	char *str, *ptr;
	char *current = NULL;

	current = getcwd(current, 0);
	i = search_node(build->env, "OLDPWD");
	if (i == -1)
	{
		chdir(current);
		write(STDOUT_FILENO, current, _strlen(current));
		put_new_line();
		return (true);
	}
	str = get_node_at_index(build->env, i);
	ptr = _strchr(str, '=');
	ptr++;
	chdir(ptr);
	write(STDOUT_FILENO, ptr, _strlen(ptr));
	put_new_line();
	return (true);
}

/**
 * cd_to_custom - change directory to what user inputs in
 * @build: input build
 * Return: true on success, false on failure
 */
_Bool cd_to_custom(config *build)
{
	register int changeStatus;

	changeStatus = chdir(build->args[1]);
	if (changeStatus == -1)
	{
		errno = EBADCD;
		handle_errors(build);
		return (false);
	}
	return (true);
}

/**
 * updateEnviron - change environmental variables
 * @build: input build
 * Return: true on success false on failure
 */
_Bool update_environ(config *build)
{
	register int i;

	i = update_old(build);
	update_cur_dir(build, i);
	return (true);
}
/**
 * update_old - updates OLDPWD to current PWD
 * @build: input build
 * Return: index in linked list of PWD on success -
 * If PWD or OLDPWD does not exist in environ vars,
 * return -1
 */
int update_old(config *build)
{
	register int pwdIndex = 0, index = 0;
	static char old[BUFSIZE];
	char *current = NULL;

	_strcat(old, "OLD");
	pwdIndex = search_node(build->env, "PWD");
	if (pwdIndex == -1)
	{
		return (-1);
	}
	current = get_node_at_index(build->env, pwdIndex);
	_strcat(old, current);
	get_null_bytes(old, _strlen(current) + 4);
	/* free(current); */
	index = search_node(build->env, "OLDPWD");
	if (index == -1)
	{
		return (-1);
	}
	delete_node_at_index(&build->env, index);
	add_node_at_index(&build->env, index, old);
	get_null_bytes(old, 0);
	return (pwdIndex);
}

/**
 * update_cur_dir - updates PWD to accurately reflect current directory
 * @build: input build
 * @index: index in linked list of where to insert PWD env var
 * Return: true on success, false on failure
 */
_Bool update_cur_dir(config *build, int index)
{
	static char tmp[BUFSIZE], cwd[BUFSIZE];

	getcwd(tmp, BUFSIZE);
	_strcat(cwd, "PWD=");
	_strcat(cwd, tmp);
	if (index > -1)
	{
		delete_node_at_index(&build->env, index);
		add_node_at_index(&build->env, index, cwd);
	}
	else
		add_node_at_index(&build->env, 0, cwd);
	get_null_bytes(tmp, 0);
	get_null_bytes(cwd, 0);
	return (true);
}
