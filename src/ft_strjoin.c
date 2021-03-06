/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:04:01 by casubmar          #+#    #+#             */
/*   Updated: 2020/05/05 17:15:29 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

char	*ft_strjoin(char const *s1, char const *s2, char const *s3,
				 char const *s4)
{
	size_t	len;
	char	*res;

	if (!s1 || !s2 || !s3 || !s4)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len + 2);
	ft_strlcat(res, s2, len + 2);
	ft_strlcat(res, s3, len + 2);
	ft_strlcat(res, s4, len + 2);
	return (res);
}
