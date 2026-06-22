/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:34:28 by fdreijer          #+#    #+#             */
/*   Updated: 2026/06/22 10:04:57 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(scene->mlx);
}

int	str_ends_with(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < len2)
		return (0);
	i = len2;
	while (i)
	{
		if (s1[len1 - len2 + i - 1] != s2[i - 1])
			return (0);
		i--;
	}
	return (1);
}

int	validate_args(int argc, char **argv, char **scene_file)
{
	if (argc != 2 || !argv || !argv[1] || !str_ends_with(argv[1], ".rt"))
		return (0);
	*scene_file = argv[1];
	return (1);
}

void	close_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	mlx_close_window(scene->mlx);
}

int	main(int argc, char **argv)
{
	char	*scene_file;
	t_scene	*scene;

	if (!validate_args(argc, argv, &scene_file))
		return (write(2, "Invalid file\n", 13), 1);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	if (!parse_file(scene, scene_file))
		free_scene_exit(scene, 0, "invalid scene\n", 1);
	scene->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	generate_rays(scene);
	mlx_key_hook(scene->mlx, &ft_hook, scene);
	mlx_close_hook(scene->mlx, close_hook, scene);
	mlx_loop(scene->mlx);
	mlx_delete_image(scene->mlx, scene->image);
	mlx_close_window(scene->mlx);
	mlx_terminate(scene->mlx);
	free_exit(scene);
}
