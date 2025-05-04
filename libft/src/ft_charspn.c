#include "libft.h"

size_t	ft_charspn(char const *s, char reject)
{
	char	*end;

	end = ft_strchr(s, reject);
	if (!end)
		return (ft_strlen(s));
	return (end - s);
}
