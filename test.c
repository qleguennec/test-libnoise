/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:18:32 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/14 14:23:54 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise/libnoise.h"
#include "libmlx/mlx.h"
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
	int			null;

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
	noise_krl_exec(cl, krl, n, work_size);
	cl_read(cl, out, LEN * sizeof(cl_float));
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, X, Y, "test-libnoise");
	void *img = mlx_new_image(mlx, X, Y);
	int *tex = (void *)mlx_get_data_addr(img, &null, &null, &null);
	i = 0;
	while (i < Y)
	{
		j = 0;
		while (j < X)
		{
			tex[i * j] = 0xFF * out[i * j];
			printf("%f\n", out[i * j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
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
