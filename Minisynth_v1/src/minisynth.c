/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:21:56 by swilliam          #+#    #+#             */
/*   Updated: 2022/05/26 19:36:52 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minisynth.h"

void	end_process(char *error_message)
{
	if (error_message)
	{
		dprintf(STDERR_FILENO, "\e[4;31m[ERROR]\e[0m \e[4;37m%s\n\e[0m", error_message);
		return (exit(EXIT_FAILURE));
	}
	return (exit(EXIT_SUCCESS));
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
	t_minisynth *track_info;

	track_info = (t_minisynth *)malloc(sizeof(t_minisynth));
	if (argc == 2)
	{
		if (get_filename_ext(argv[1]) == 1)
			if (playback(argv[1]) == 0)
				end_process(NULL);
		if (get_filename_ext(argv[1]) == 2)
			write_wave(argv[1], track_info);
		if (get_filename_ext(argv[1]) == 0)
			end_process("Incorrect file type used.");
	}
	else
		end_process("Usage: ./minisynth *.wav / *.synth");
	end_process(NULL);
	return (0);
}