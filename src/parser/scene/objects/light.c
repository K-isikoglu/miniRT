/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 01:50:14 by htsang            #+#    #+#             */
/*   Updated: 2023/09/06 16:09:26 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINIRT/parser/scene_parser.h"
#include "MINIRT/parser/general_parser.h"
#include "MINIRT/scene/s_objects.h"

static t_mrt_scene_parser_atom	mrt_scene_parser_light_point_run(\
t_mrt_scene_parser_atom input)
{
	t_mrt_range	range[1];

	range[0] = mrt_range(0.0, 1.0);
	return (mrt_combinator_struct_fields((struct s_ft_parser_entity[3]){\
		ft_parser_entity(&mrt_scene_parser_point3d, ft_tobject_ptr(NULL)), \
		ft_parser_entity(&mrt_scene_parser_float, ft_tobject_ptr(range)), \
		ft_parser_entity(&mrt_scene_parser_color, ft_tobject_ptr(NULL)) \
	}, 3, input, ft_tobject_str(" \t")));
}

t_mrt_scene_parser_atom	mrt_scene_parser_light_point(\
t_mrt_scene_parser_atom input, union u_ft_tobject option)
{
	struct s_mrt_scene_light_point	light_point;
	struct s_ft_parser_struct		parser;
	t_mrt_scene_parser_atom			result;
	bool							is_unique;

	(void) option;
	result = mrt_scene_parser_identifier(ft_parser_atom(\
		ft_tobject_ptr(&is_unique), input.string), ft_tobject_str("l"));
	if (!result.is_valid)
		return (ft_parser_atom_validity_set(input, false));
	parser = ft_parser_struct_init((void *[3]){&light_point.origin, \
		&light_point.ratio, &light_point.color}, 3);
	result = mrt_scene_parser_light_point_run(ft_parser_atom(\
		ft_tobject_ptr(&parser), result.string));
	if (result.is_valid)
	{
		if (mrt_scene_add_entry((struct s_mrt_scene *) input.payload.as_ptr, \
			mrt_scene_entry(&light_point, ENTRY_LIGHT_POINT), is_unique))
			return (ft_parser_atom_validity_set(input, false));
	}
	else
		return (ft_parser_atom_validity_set(input, false));
	return (result);
}

static t_mrt_scene_parser_atom	mrt_scene_parser_light_ambient_run(\
t_mrt_scene_parser_atom input)
{
	t_mrt_range	range[1];

	range[0] = mrt_range(0.0, 1.0);
	return (mrt_combinator_struct_fields((struct s_ft_parser_entity[2]){\
		ft_parser_entity(&mrt_scene_parser_float, ft_tobject_ptr(range)), \
		ft_parser_entity(&mrt_scene_parser_color, ft_tobject_ptr(NULL)) \
	}, 2, input, ft_tobject_str(" \t")));
}

t_mrt_scene_parser_atom	mrt_scene_parser_light_ambient(\
t_mrt_scene_parser_atom input, union u_ft_tobject option)
{
	struct s_mrt_scene_light_ambient	light_ambient;
	struct s_ft_parser_struct			parser;
	t_mrt_scene_parser_atom				result;
	bool								is_unique;

	(void) option;
	result = mrt_scene_parser_identifier(ft_parser_atom(\
		ft_tobject_ptr(&is_unique), input.string), ft_tobject_str("A"));
	if (!result.is_valid)
		return (ft_parser_atom_validity_set(input, false));
	parser = ft_parser_struct_init(\
		(void *[2]){&light_ambient.ratio, &light_ambient.color}, 2);
	result = mrt_scene_parser_light_ambient_run(ft_parser_atom(\
		ft_tobject_ptr(&parser), result.string));
	if (result.is_valid)
	{
		if (mrt_scene_add_entry((struct s_mrt_scene *) input.payload.as_ptr, \
			mrt_scene_entry(&light_ambient, ENTRY_LIGHT_AMBIENT), is_unique))
			return (ft_parser_atom_validity_set(input, false));
	}
	else
		return (ft_parser_atom_validity_set(input, false));
	return (result);
}
