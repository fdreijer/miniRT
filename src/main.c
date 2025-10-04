/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:11:15 by kali              #+#    #+#             */
/*   Updated: 2025/10/04 18:14:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main(void)
{
	char	*scene_file = "scenes/scene.rt";
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	(void)(scene && scene_file);
}