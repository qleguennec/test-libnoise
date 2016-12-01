/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:18:32 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/01 06:44:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libnoise/libnoise.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define NSEEDS 4
#define X 5
#define Y 5
#define LEN X * Y

int		get_parameters(t_noise *n)
{
	size_t	ret;

	n->grads = NULL;
	n->used = NULL;
	n->ngrads = 256;
	n->seed = 12;
	n->k = 3926;
	ret = noise_init(n, NSEEDS);
	printf("testing for %u: %lu\n", n->k, ret);
	return (ret == 0);
}

void	bmp(t_noise *n)
{
	float			arr[LEN];
	unsigned char	*a;
	size_t			i;

	noise_fill(n, 255, arr, LEN);
	a = malloc(4);
	printf("%c%c%d%d%d", 0, 0, LEN * 4, 42, 18);
	i = 0;
	while (i < LEN)
	{
		*(unsigned int *)a = (unsigned int)arr[i];
		write(1, a, 4);
		i++;
	}
}

int		main(void)
{
	t_noise		n;

	while (!get_parameters(&n))
	{
		srand(time(NULL));
		free(n.grads);
		free(n.used);
		sleep(1);
	}
	printf("OK\n");
	n.dim[0] = X;
	n.dim[1] = Y;
	bmp(&n);
	return (0);
}
