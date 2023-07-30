/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/07/27 13:35:40 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINIRT/unit/color.h"
#include "MINIRT/ray.h"
#include "MINIRT/unit/vec3.h"

int	main(void)
{
	ray_ppm();
	return (0);
}

/*
#include "MINIRT/miniRT.h"
#include <MLX42/MLX42.h>

int	main(int argc, const char **argv)
{
	mlx_t					*mlx;
	mlx_image_t				*image;
	struct s_mrt_settings	settings;

	(void) argc;
	(void) argv;
	settings.width = 800;
	settings.height = 600;
	mlx = mlx_init(settings.width, settings.height, "miniRT", false);
	image = mlx_new_image(mlx, settings.width, settings.height);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
*/