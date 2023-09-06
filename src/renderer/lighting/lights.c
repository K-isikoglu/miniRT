/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:07:45 by htsang            #+#    #+#             */
/*   Updated: 2023/09/06 06:51:30 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINIRT/renderer/lighting.h"
#include "MINIRT/unit.h"
#include <math.h>
#include <stdio.h>

void	mrt_lights_set_ambient(struct s_mrt_lights *lights, \
t_mrt_color effective_color, double ambient_effectiveness)
{
	lights->ambient = vec3_smultiply(effective_color, ambient_effectiveness);
}

void	mrt_lights_set_diffuse(struct s_mrt_lights *lights, \
struct s_mrt_lights_calculation *calculation, double diffuse_effectiveness)
{
	lights->diffuse = vec3_smultiply(calculation->effective_color, \
		diffuse_effectiveness * calculation->light_normal_angle);
}

void	mrt_lights_set_specular(struct s_mrt_lights *lights, \
struct s_mrt_lights_calculation *calculation, \
struct s_mrt_lighting *lighting_data)
{
	double	factor;

	factor = pow(calculation->reflect_eye_angle, \
		lighting_data->material.shininess);
	lights->specular = vec3_smultiply(lighting_data->light_source.color, \
		lighting_data->material.specular * factor);
}
	// if (factor > 0)
	// {
	// 	printf("ambient: ");
	// 	vec3_print(lights->ambient);
	// 	printf("diffuse: ");
	// 	vec3_print(lights->diffuse);
	// 	printf("reflect_eye_angle: %f\n", calculation->reflect_eye_angle);
	// 	printf("specular: ");
	// 	vec3_print(lights->specular);
	// 	printf("\n");
	// }

t_mrt_vec3	mrt_lights_combine_diffuse_level(struct s_mrt_lights *lights)
{
	return (vec3_add(lights->ambient, lights->diffuse));
}

t_mrt_vec3	mrt_lights_combine_specular_level(struct s_mrt_lights *lights)
{
	return (vec3_add(lights->ambient, \
		vec3_add(lights->diffuse, lights->specular)));
}
