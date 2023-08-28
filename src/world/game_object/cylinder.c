/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:17:41 by htsang            #+#    #+#             */
/*   Updated: 2023/08/28 12:33:16 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MINIRT/world/game_object.h"
#include "MINIRT/scene.h"
#include "MINIRT/ray.h"
#include "MINIRT/unit.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct s_mrt_cylinder	*mrt_cylinder(\
struct s_mrt_scene_cylinder *scene_cylinder)
{
	struct s_mrt_cylinder	*cyl;

	cyl = malloc(sizeof(struct s_mrt_cylinder));
	if (!cyl)
		return (NULL);
	*cyl = (struct s_mrt_cylinder){.scene = scene_cylinder};
	return (cyl);
}

bool	intersect_caps_book(struct s_mrt_ray *ray, double min, double max)
{
	double	t;
	double	x;
	double	z;

	if (fabs(ray->direction.y) < 0.2)
		return (false);
	t = (min - ray->origin.y) / ray->direction.y;
	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	if ((x * x + z * z) <= 1)
		return (true);
	t = (max - ray->origin.y) / ray->direction.y;
	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	if ((x * x + z * z) <= 1)
		return (true);
	return (false);
}

bool	is_in_range_book(struct s_mrt_ray *ray, struct s_mrt_cylinder *cylinder, \
double t0, double t1)
{
	double	y0;
	double	y1;
	double	min;
	double	max;

	y0 = ray->origin.y + t0 * ray->direction.y;
	y1 = ray->origin.y + t1 * ray->direction.y;
	min = cylinder->scene->center.y;
	max = cylinder->scene->center.y + cylinder->scene->height;
	if (min < y0 && y0 < max)
		return (true);
	if (min < y1 && y1 < max)
		return (true);
	return (false);
}

bool	intersect_caps(struct s_mrt_ray *ray, double min, double max)
{
	double	t;
	double	x;
	double	z;

	if (fabs(ray->direction.y) < 0.2)
		return (false);
	t = (min - ray->origin.y) / ray->direction.y;
	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	if ((x * x + z * z) <= 1)
		return (true);
	t = (max - ray->origin.y) / ray->direction.y;
	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	if ((x * x + z * z) <= 1)
		return (true);
	return (false);
}

bool	is_in_range(struct s_mrt_ray *ray, struct s_mrt_cylinder *cylinder, \
double t0, double t1)
{
	t_mrt_point3d	p0;
	t_mrt_point3d	p1;
	t_mrt_point3d	start;
	t_mrt_point3d	end;

	p0 = ray_at(ray, t0);
	p1 = ray_at(ray, t1);
	start = cylinder->scene->center;
	end = vec3( \
	start.x + cylinder->scene->height * cylinder->scene->orientation.x, \
	start.y + cylinder->scene->height * cylinder->scene->orientation.y, \
	start.z + cylinder->scene->height * cylinder->scene->orientation.z);
	if ((p0.x > start.x && p0.x < end.x) || (p0.y > start.y && p0.y < end.y) \
	|| (p0.z > start.z && p0.z < end.z))
		return (true);
	if ((p1.x > start.x && p1.x < end.x) || (p1.y > start.y && p1.y < end.y) \
	|| (p1.z > start.z && p1.z < end.z))
		return (true);
	return (false);
}

bool	mrt_cylinder_is_hit(struct s_mrt_ray *ray, \
struct s_mrt_cylinder *cylinder)
{
	t_mrt_vec3	x;
	double		r;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		tmp;
	double		t0;
	double		t1;

	x = vec3_subtract(ray->origin, cylinder->scene->center);
	r = cylinder->scene->diameter / 2;
	tmp = vec3_dot(ray->direction, cylinder->scene->orientation);
	tmp = tmp * tmp;
	a = vec3_dot(ray->direction, ray->direction) - tmp;
	tmp = vec3_dot(ray->direction, cylinder->scene->orientation);
	tmp = tmp * vec3_dot(x, cylinder->scene->orientation);
	b = (vec3_dot(ray->direction, x) - tmp) * 2;
	tmp = vec3_dot(x, cylinder->scene->orientation);
	c = vec3_dot(x, x) - tmp * tmp - r * r;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	return (is_in_range(ray, cylinder, t0, t1));
}

/**
 * Center: Can only change y
 * Orientation: Can't change
 * Diameter: Can change
 * Height: Can change
 * Color: Can change
*/

bool	mrt_cylinder_is_hit_book(struct s_mrt_ray *ray, \
struct s_mrt_cylinder *cylinder)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t0;
	double	t1;

	a = ray->direction.x * ray->direction.x;
	a = a + ray->direction.z * ray->direction.z;
	if (fabs(a) < 0.2)
		return (false);
	b = 2 * ray->origin.x * ray->direction.x;
	b = b + 2 * ray->origin.z * ray->direction.z;
	c = ray->origin.x * ray->origin.x;
	c = c + ray->origin.z * ray->origin.z - \
	(cylinder->scene->diameter / 2) * (cylinder->scene->diameter / 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	return (is_in_range(ray, cylinder, t0, t1));
}


/**
 * Formula for ray cylinder intersection:
 *
 * D: ray_direction
 * V: unit length vector of cylinder axis
 * X: O - C (ray_origin - start cap point of cylinder)
 * r: radius
 *
 * a   = D|D - (D|V)^2
 * b/2 = D|X - (D|V)*(X|V)
 * c   = X|X - (X|V)^2 - r*r
 * discriminant = b*b - 4ac
*/

bool	mrt_cylinder_is_hit_internet(struct s_mrt_ray *ray \
	, struct s_mrt_cylinder *cylinder)
{
	t_mrt_vec3	x;
	double		r;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		tmp;

	x = vec3_subtract(ray->origin, cylinder->scene->center);
	r = cylinder->scene->diameter / 2;
	tmp = vec3_dot(ray->direction, cylinder->scene->orientation);
	tmp = tmp * tmp;
	a = vec3_dot(ray->direction, ray->direction) - tmp;
	tmp = vec3_dot(ray->direction, cylinder->scene->orientation);
	tmp = tmp * vec3_dot(x, cylinder->scene->orientation);
	b = (vec3_dot(ray->direction, x) - tmp) * 2;
	tmp = vec3_dot(x, cylinder->scene->orientation);
	c = vec3_dot(x, x) - tmp * tmp - r * r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	return (true);
}

void	mrt_cylinder_free(struct s_mrt_cylinder *cylinder)
{
	free(cylinder->scene);
}

/*
Plan for truncating + capping the cylinder:
Get the intersection point P.
	Formula for the 2 intersection points, I guess:
		t0 ← (-b - √(disc)) / (2 * a)
		t1 ← (-b + √(disc)) / (2 * a)
Draw a Vector V from P to Center (Center - P)
Calculate if V is rather in the direction of orientation
	or in the direction of -orientaion?
If it's rather in the direction of -orientation, render it
If it's equal to both directions, render it
If it's rather in the direction of orientation, dismiss
*/
