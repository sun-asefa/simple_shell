#include "shell.h"

/**
 * help_function - retrieves instruction on how to use builtin
 * @build: input build
 * Return: Always 1
 */
int help_function(config *build)
{
	type_b help_arr[] = {
		{"exit", help_guide_exit},
		{"env", help_env},
		{"history", help_history},
		{"alias", help_alias},
		{"cd", help_cd},
		{"setenv", help_set_env},
		{"unsetenv", help_unset_env},
		{"help", help_guide},
		{NULL, NULL}};
	register int i = 0, j = 1, argCount = count_args(build->args);
	_Bool foundCommand = false;

	if (argCount == 1)
	{
		return (display_help_menu());
	}
	while (j < argCount)
	{
		i = 0;
		while (help_arr[i].command)
		{
			if (_strcmp(build->args[j], help_arr[i].command) == 0)
				foundCommand = true;
			help_arr[i].func(build);
			break;
			i++;
		}
		j++;
	}
	if (foundCommand == false)
		errno = ENOBUILTIN;
	handle_errors(build);
	return (1);
}

/**
 * display_help_menu - displays available help options
 * Return: Always 1
 */
int display_help_menu(void)
{
	char str[81] = "Type help [built-in]\n\nIncluded built-ins:";
	char *str2 = "\n\n\texit\n\tenv\n\tcd\n\tsetenv\n\tunsetenv\n\thelp\n";

	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_exit - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_guide_exit(config *build)
{
	char str[82] = "exit: exit [n]\n\tExit the shell.\n\n\t";
	char *str2 = "Exit with a status of n, or if n is omitted, 0.\n";

	(void)build;
	_strcat(str, str2);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_env - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_env(config *build)
{
	char str[] = "env: env\n\tPrint the environment.\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_history - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_history(config *build)
{
	char str[] = "history: history\n\tNot supported in this version.\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
/**
 * help_alias - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_alias(config *build)
{
	char str[] = "alias: alias\n\tNot supported in this version.\n";

	(void)build;
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_cd - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_cd(config *build)
{
	char str[192] = "cd: cd [destination]\n\t";
	char *str2 = "Change directory to target destination.\n\t";
	char *str3 = "If [destination] is removed, user will taken to home.\n\t";
	char *str4 = "If \"-\" is used as second argument, user will be taken to ";
	char *str5 = "last directory.\n";

	(void)build;
	_strcat(str, str2);
	_strcat(str, str3);
	_strcat(str, str4);
	_strcat(str, str5);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_set_env - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_set_env(config *build)
{
	char str[186] = "setenv: setenv [var] [value]\n\t";
	char *str2 = "Set or update a variable in the environment.\n\n\t";
	char *str3 = "Creates a variable [var] with [value]. ";
	char *str4 = "If the [var] already exists in the environment, ";
	char *str5 = "the value is updated.\n";

	(void)build;
	_strcat(str, str2);
	_strcat(str, str3);
	_strcat(str, str4);
	_strcat(str, str5);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_unset_env - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_unset_env(config *build)
{
	char str[116] = "unsetenv: unsetenv [var]\n\t";
	char *str2 = "Unset a variable in the environment.\n\n\t";
	char *str3 = "[var] is an existing variable in the environment.\n";

	(void)build;
	_strcat(str, str2);
	_strcat(str, str3);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}

/**
 * help_guide - instructions on how to exit
 * @build: input build
 * Return: Always 1
 */
int help_guide(config *build)
{
	char str[129] = "help: help [built-in]\n\t";
	char *str2 = "Display information about built-in commands.\n\n\t";
	char *str3 = "If [built-in] is not specified, print a list of built-ins.\n";

	(void)build;
	_strcat(str, str2);
	_strcat(str, str3);
	write(STDOUT_FILENO, str, _strlen(str));
	return (1);
}
