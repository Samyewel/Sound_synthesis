/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:21:56 by swilliam          #+#    #+#             */
/*   Updated: 2022/05/26 18:32:23 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minisynth.h"

/*
** ft_strdel:
** - Takes as a parameter the address of a string that need to be
**   freed with free(3), then sets its pointer to NULL.
*/

void	ft_strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}
/*
static void	parse_synthfile(const char *synthfile)
{
	char	*track;
	int	fd;
	int	i;

	fd = 0;
	i = 1;

	fd = open(synthfile, O_RDONLY);
	while (i > 0)
	{

	}
	printf("parse here\n");
}*/

static int	get_filename_ext(const char *filename)
{
    const char	*dot;

	dot = strrchr(filename, '.');
	if (dot != NULL)
	{
		 if (strcmp(dot, ".wav") == 0)
			return (1);
		else if (strcmp(dot, ".synth") == 0)
			return (2);
	}
    return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (get_filename_ext(argv[1]) == 1)
			if (playback(argv[1]) == 0)
				return (1);
		if (get_filename_ext(argv[1]) == 2)
			write_wave(argv[1]);
		if (get_filename_ext(argv[1]) == 0)
			return ((int) write(1, "Incorrect filetype used.\n", 25));
	}
	else
		return ((int)write(1, "usage: ./minisynth file\n", 24));
	return (0);
}