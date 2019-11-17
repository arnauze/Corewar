/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_instructions_2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:49:48 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 18:13:37 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	This function checks if there is no param whereas one is expected.
**	Then, it checks if there is a param whereas none is expected.
**	Then, we remove the case when there is no param and none is expected \
**	(we do that to avoid a segfault with the tests after).
**	Then, it checks if there is a registry param whereas it should not.
**	Then, it checks if there is a direct param whereas it should not.
**	Then, it checks if there is a indirect param whereas it should not.
*/

int		check_valid_param(char *param, int reg, int dir, int ind)
{
	if (!param && (reg != 0 || dir != 0 || ind != 0))
		return (0);
	if (param && (reg == 0 && dir == 0 && ind == 0))
		return (0);
	if (!param && (reg == 0 && dir == 0 && ind == 0))
		return (1);
	if (check_valid_number_format_in_param(param) == 0)
		return (0);
	if (reg == 0 && param[0] == 'r')
		return (0);
	if (dir == 0 && param[0] == DIRECT_CHAR)
		return (0);
	if (ind == 0 && (param[0] != 'r' && param[0] != DIRECT_CHAR))
		return (0);
	if (param[0] == 'r' && (ft_atoi(param + 1) < 0 \
							|| ft_atoi(param + 1) > 99))
		return (0);
	return (1);
}
