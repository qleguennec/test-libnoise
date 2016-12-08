/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:18:32 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/08 15:16:17 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise/libnoise.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define K 1706653698
#define X 800
#define Y 600
#define LEN X * Y
#define SIZE LEN * sizeof(cl_float2)

void	get_parameters(t_noise *n)
{
	n->grads = NULL;
	n->ngrads = 28;
	n->seed = 31209823423;
	noise_init(n);
}

void	bmp(t_noise *n, t_cl_info *cl)
{
	size_t		work_size[2] = {X, Y};
	size_t		i = 0;
	size_t		j = 0;
	cl_float2	arr[LEN];
	cl_kernel	krl;
	cl_float	out[LEN];

	while (i < Y)
	{
		j = 0;
		while (j < X)
		{
			arr[i * j].x = j;
			arr[i * j].y = i;
			j++;
		}
		i++;
	}
	(void)out;
	(void)work_size;
	krl = noise_krl_build(cl, n, arr, LEN);
	if (krl)
		printf("krl ok\n");
}

int		main(void)
{
	t_noise		n;
	t_cl_info	cl;

	get_parameters(&n);
	cl_init(&cl);
	bmp(&n, &cl);
	return (0);
}
