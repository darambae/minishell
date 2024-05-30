#include "../../minishell.h"


int ft_pwd()
{
	char	*buf;

    buf = NULL;
    buf = getcwd(buf, 0);
    printf("%s\n", buf);
    free(buf);
    return (0);
}
