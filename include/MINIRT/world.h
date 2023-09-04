/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:10:11 by htsang            #+#    #+#             */
/*   Updated: 2023/09/04 10:32:02 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "MINIRT/scene.h"
# include "MINIRT/image.h"
# include "MINIRT/renderer.h"
# include "MINIRT/world/camera.h"
# include "MINIRT/world/light.h"
# include "MINIRT/world/game_object.h"

/////////////////////////////////////////
////////////   world entry   ////////////
/////////////////////////////////////////

union u_world_entry_object
{
	struct s_mrt_sphere			*sphere;
	struct s_mrt_plane			*plane;
	struct s_mrt_cylinder		*cylinder;
	struct s_mrt_light_ambient	*light_ambient;
	struct s_mrt_light_point	*light_point;
	struct s_mrt_camera			*camera;
	void						*address;
};

struct s_mrt_world_entry
{
	enum e_mrt_scene_entry_identifier	identifier;
	union u_world_entry_object			object;
};

/** TODO: do we really need the object too?
 * IF yes, is object enough or also entry?*/
struct	s_mrt_world_insec
{
	struct s_mrt_world_entry	*entry;
	double						t;
};

bool						mrt_world_entry_is_empty(\
struct s_mrt_world_entry *entry);

void						mrt_world_entry_free(\
struct s_mrt_world_entry *entry);

///////////////////////////////////////////
////////////   world entries   ////////////
///////////////////////////////////////////

typedef t_ft_vector	t_mrt_world_entries;

void						mrt_world_entries_free(t_mrt_world_entries *entry);

///////////////////////////////////
////////////   world   ////////////
///////////////////////////////////

struct s_mrt_world
{
	t_mrt_world_entries			lights;
	t_mrt_world_entries			objects;
	struct s_mrt_world_entry	camera;
};

struct s_mrt_camera			*mrt_world_get_camera(struct s_mrt_world *world);

///////////////////////////////////////////
////////////   world options   ////////////
///////////////////////////////////////////

struct s_mrt_world_options
{
	struct s_mrt_image	camera_image;
	double				camera_focal_length;
};

int							mrt_world_init(struct s_mrt_world *world);

void						mrt_world_free(struct s_mrt_world *world);

int							mrt_world_from_scene(struct s_mrt_scene *scene, \
struct s_mrt_world *world, struct s_mrt_world_options options);

#endif