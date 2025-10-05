/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 08:12:21 by kali              #+#    #+#             */
/*   Updated: 2025/10/05 09:46:39 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *s)
{
	int		i;
	int		sign;
	double	result;
	double	div;

	i = 0;
	result = 0;
	div = 10.0;
	while (ft_isspace(s[i]))
		i++;
	sign = ((s[i] == '+' && ft_isdigit(s[++i])) || 1) \
- ((s[i] == '-' && s[i++]) * 2);
	while (ft_isdigit(s[i]))
		result = result * 10.0 + (s[i++] - '0');
	if (s[i] == '.')
	{
		while (ft_isdigit(s[++i]))
		{
			result += (s[i] - '0') / div;
			div *= 10;
		}
	}
	if (!ft_isspace(s[i]) && s[i])
		return (INFINITY);
	return (sign * result);
}


// int main()
// {
// 	printf("%.10lf\n", ft_atof("0"));
// 	printf("%.10lf\n", ft_atof("-1.1"));
// 	printf("%.10lf\n", ft_atof("100.01"));
// 	printf("%.10lf\n", ft_atof("0.00000001"));
// 	printf("%.10lf\n", ft_atof("+10.1010101010"));
// 	printf("%.10lf\n", ft_atof("-1000000.5"));
// 	printf("%.10lf\n", ft_atof("0.123456789"));
// 	printf("%.10lf\n", ft_atof(".555"));
// 	printf("%.10lf\n", ft_atof("-.1111111111"));
// 	printf("%.10lf\n", ft_atof("0.00010"));
// 	printf("%.10lf\n", ft_atof("0.9999999"));
// 	printf("%.10lf\n", ft_atof("99.9999"));
// 	printf("%.10lf\n", ft_atof("-1000"));
// }