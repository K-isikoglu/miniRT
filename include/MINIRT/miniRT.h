/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:24:47 by htsang            #+#    #+#             */
/*   Updated: 2023/08/07 10:10:54 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MINIRT/unit.h"
# include "MINIRT/renderer.h"
# include "MINIRT/world.h"
# include <stdlib.h>

struct s_mrt
{
	t_mrt_renderer					renderer;
	struct s_mrt_world				world;
	struct s_mrt_renderer_config	renderer_config;
};

int							mrt_init(struct s_mrt *world, \
struct s_mrt_scene scene);

void						mrt_free(struct s_mrt *world);

#endif