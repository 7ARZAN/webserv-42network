#include "../includes/libconfpp.h"

// ft_strchr - returns a pointer to the first c found in s
// or null if it isnt found
int	strschr(std::string s, int c)
{
	int	i;
	int	glen = s.length();

	i = 0;
	while (s[i] != (char) c)
	{
		if (i >= glen)
			return (-1);
		i++;
	}
	return (i);
}
