/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:21:56 by swilliam          #+#    #+#             */
/*   Updated: 2022/05/26 14:43:16 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minisynth.h"

const char	*get_filename_ext(const char *filename)
{
    const char	*dot;

	dot = strrchr(filename, '.');
    if(!dot || dot == filename)
		return "";
    return (dot + 1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return ((int)write(1, "usage: ./minisynth file\n", 24));
	if (strcmp(get_filename_ext(argv[1]), "wav") == 0)
		playback(argv[1]);
	else if (strcmp(get_filename_ext(argv[1]), "synth") == 0)
	{

	}
	else
		return ((int) write(1, "Incorrect filetype used.\n", 25));
	return (0);
}