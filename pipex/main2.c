#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ft_split.c"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strcat;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strcat = malloc(len1 + len2 + 1);
	if (strcat == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		strcat[i] = s1[i];
		i++;
	}
	while (i < len1 + len2 + 1)
	{
		strcat[i] = s2[i - len1];
		i++;
	}
	return (strcat);
}

char *get_cmd(char *cmd, char **envp)
{
    char **dirs;
    char *slash_cmd = ft_strjoin("/", cmd); //free in the end
    char *full_cmd;
    while (*envp)
    {
        if (ft_strncmp((const char *) *envp, "PATH=", 5) == 0)
            break ;
        envp++;
    }
    if (!*envp)
    {
        free(slash_cmd);
        return NULL;
    }

    dirs = ft_split(*envp, ':'); //free in the end
    int i = 0;
    while (dirs[i])
    {
        full_cmd = ft_strjoin(dirs[i++], slash_cmd);
        if (access(full_cmd, X_OK) == 0)
            break ;
        free(full_cmd);
    }
 
    if (!dirs[i])
        full_cmd = NULL;
    free(slash_cmd);
    i = 0;
    while (dirs[i])
        free(dirs[i++]);
    free(dirs);
    return full_cmd;
}

int main(int argc, char **argv, char **envp)
{
    char **cmd_args = ft_split(argv[2], ' ');
    char *full_cmd = get_cmd(cmd_args[0], envp);
    int i = 0;
    if (full_cmd)
    {
        int pid = fork();
        if (pid == 0)
        {
            char *env[] = {NULL};
            execve(full_cmd, cmd_args, env);
        }
        wait(NULL);
        free(full_cmd);
    }
    else
        printf("No such command!\n");
    while(cmd_args[i])
        free(cmd_args[i++]);
    free(cmd_args);
    return 1;
}