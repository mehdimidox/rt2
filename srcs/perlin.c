/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erahimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:42:42 by erahimi           #+#    #+#             */
/*   Updated: 2020/02/29 13:42:44 by erahimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"



const int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

double	ft_acc(t_vect c[2][2][2], t_vect v, double acc)
{
	int i,j,k;
	t_vect		weight;
	t_vect		noise;

	noise = constrector(v.x * v.x * (3.0 - 2.0 * v.x), v.y * v.y * (3.0 - 2.0 * v.y),
			v.z * v.z * (3.0 - 2.0 * v.z));
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			k = 0;
			while (k < 2)
			{
				weight = constrector(v.x - i, v.y - j, v.z - k);
acc += (i * noise.x + (1 - i) * (1 - noise.x)) * (j * noise.y + (1 - j) * (1 - noise.y)) * (k * noise.z + (1 - k) * (1 - noise.z)) *
					dot(c[i][j][k], weight);
                      k++;
			}
             j++;
		}
          i++;
	}
	return (acc);
}

double	noise(t_vect *ran, t_vect v)
{
	t_vect		c[2][2][2];
	t_vect		acc;
	int i,j,k;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			k = 0;
			while (k < 2) {
				c[i][j][k] =  ran[hash[((int)floor(v.x) + i) & 255]
					^ hash[((int)floor(v.y) + j) & 255]
					^ hash[((int)floor(v.z) + k) & 255]];
                k++;
			}
            j++;
		}
        i++;
	}
	acc = constrector(ft_frac(v.x),ft_frac(v.y), ft_frac(v.z));
	return (ft_acc(c, acc, 0.0));
}

double	perlin_noise(t_vect *ran, t_vect v, int depth)
{
	double			acc;
	double			weight;
	int				i;

	acc = 0.0;
	weight = 1.0;
	i = -1;
	while (++i < depth)
	{
		acc += weight * noise(ran, v);
		weight *= 0.5;
		v = multiplication(v, 2);
	}
	return (fabs(acc));
}

t_vect perlin(t_vect *ran, t_vect v, t_object *obj)
{
    return (multiplication(obj->color, 9.0 * perlin_noise(ran, v, 2.0)));
}