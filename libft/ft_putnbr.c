/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:16:47 by amagnan           #+#    #+#             */
/*   Updated: 2018/09/11 16:16:48 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n *= -1;
			ft_putchar_fd('-', 2);
		}
		if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putchar_fd(((n % 10) + '0'), 2);
		}
		if (n < 10)
			ft_putchar_fd((n + '0'), 2);
	}
}