/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-kha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:36:13 by ibel-kha          #+#    #+#             */
/*   Updated: 2020/02/23 22:12:44 by ibel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_vect		get_normal(t_vect vect, t_object *o, t_rt *rt)
{
	t_vect	v2;
	t_vect	temp;

	if (o->type == 1)
		return (t(o, rt->cam.cam_ray.d, normale(soustraction(vect,
		 o->position))));
	if (o->type == 2)
		return (t(o,  rt->cam.cam_ray.d, o->direction));
	v2 = soustraction(rt->cam.cam_ray.o, o->position);
	temp = soustraction(soustraction(vect, o->position),
			multiplication(o->direction, dot(rt->cam.cam_ray.d,
					o->direction) * rt->t + dot(v2, o->direction)));
	if (o->type == 3)
		return (t(o, rt->cam.cam_ray.d, normale(temp)));
	temp = multiplication(o->direction, dot(rt->cam.cam_ray.d,
				o->direction) * rt->t + dot(v2, o->direction));
	temp = multiplication(temp, 1 + tan(o->r) * tan(o->r));
	return (t(o, rt->cam.cam_ray.d, normale(soustraction(soustraction(vect, 
	o->position), temp))));
}

t_vect		get_reflected(t_vect vect, t_vect v, t_object *object, t_rt *rt)
{
	t_vect	n;
	t_vect	r;

	n = get_normal(vect, object, rt);
	r = soustraction(v, multiplication(n, 2.0 * dot(v, n)));
	return (normale(r));
}

int			inter(t_rt *rt, t_object *object_temp, double *dist)
{
	if (object_temp->type == 1)
		return (sphere_intersection(rt, object_temp, dist));
	else
	{
		if (object_temp->type == 2)
			return (plane_intersection(rt, object_temp, dist));
		else
		{
			if (object_temp->type == 3)
				return (cylinder_intersection(rt, object_temp, dist));
			else
			{
				return (cone_intersection(rt, object_temp, dist));
			}
		}
	}
}

void		swap_object(t_rt *rt, t_object *object)
{
	t_object	*tmp;

	tmp = rt->object;
	object->next = tmp;
	rt->object = object;
}

int			cylinder_suit(t_rt *rt, t_object *object, int j, int *k)
{
	object->direction = extraconsterctor(rt->image[*k + 5], &j);
	if (rt->image[*k + 5][j] != ')' || !(j = 9))
		return (-1);
	object->rotation = extraconsterctor(rt->image[*k + 6], &j);
	if (rt->image[*k + 6][j] != ')')
		return (-1);
	if ((ft_strcmp(rt->image[*k], "cone") == 0))
		object->type = 4;
	else
		object->type = 3;
	j = 12;
	object->translation = extraconsterctor(rt->image[*k + 7], &j);
	if (rt->image[*k + 7][j] != ')')
		return (-1);
	swap_object(rt, object);
	*k += 9;
	return (1);
}
