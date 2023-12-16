#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define  BUFFER_SIZE 20 

size_t	ft_strlen(char *str)
{
	size_t	len;
	
	len = 0;
	while(*str++)
		len++;
	return len;
}

char	*ft_strchrnl(char *str)
{
	while(*str)
	{
		if (*str == '\n')
			return str;
		str++;
	}
	return NULL;
}

void	ft_strcpy(char *dst, char *src)
{
	while(*src)
		*dst++ = *src++;
	*dst = '\0';
}

void	ft_strcat(char *dst, char *src)
{
	while(*dst)
		dst++;
	ft_strcpy(dst, src);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;

	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	return result;
}

char	*ft_substr(char *str, size_t len)
{
	size_t	i;
	char	*sub;

	sub = (char *)malloc(len + 1); 

	i = 0;
	while (i < len)
	{
		sub[i] = str[i];
		i++;
	}
	sub[i] = '\0';
	return sub;
}	
		
char 	*ft_strdup(char *str)
{
	char	*dup;
	
	dup = (char *)malloc(ft_strlen(str) + 1);
	ft_strcpy(dup, str);
	return dup;
}

char	*get_next_line(int fd)
{
	int		br;
	static char	prev_line[BUFFER_SIZE + 1];
	char		*next_line;
	char		*sub_line;
	char		*tmp_line;
	char		buff[BUFFER_SIZE + 1];
	char		*nl;

	next_line = ft_strdup(prev_line);
	while((br = read(fd, buff, BUFFER_SIZE)))	
	{
		
		buff[br] = '\0';
		nl = ft_strchrnl(buff);
		if (!nl)
		{
			tmp_line = next_line;
			next_line = ft_strjoin(next_line, buff);
			free(tmp_line);
		}
		else
		{	
			sub_line = ft_substr(buff, nl - buff);
			tmp_line = next_line;
			next_line = ft_strjoin(next_line, sub_line);
			free(sub_line);
			free(tmp_line);
			ft_strcpy(prev_line, nl + 1); 
			return next_line;
		}
	}	
	return next_line;	
	
}

int main()
{

	int fd = open("test.txt", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	return 0;
}
