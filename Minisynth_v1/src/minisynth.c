/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sam <sam@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:21:56 by swilliam          #+#    #+#             */
/*   Updated: 2022/05/27 14:18:21 by sam              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minisynth.h"
#include <dirent.h>

void	end_process(char *error_message)
{
	if (error_message)
	{
		dprintf(STDERR_FILENO, "\e[4;31m[ERROR]\e[0m \e[4;37m%s\n\e[0m", error_message);
		return (exit(EXIT_FAILURE));
	}
	return (exit(EXIT_SUCCESS));
}

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

void	play_output(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**files;
	int				filecount;

	filecount = 0;
	d = opendir("output");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			if (dir->d_type == DT_REG && get_filename_ext(dir->d_name) == 1)
			{

				files[filecount] = dir->d_name;
				printf("file %d = %s\n", filecount, files[filecount]);
				filecount++;
			}
		if (filecount >= 1)
			if (simple_mixing(filecount, files) == 0)
				printf("Output mixing complete.\n");
	}
	closedir(d);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && get_filename_ext(argv[1]) == 2)
		if (write_wave(argv[1]))
			play_output();
		else
			end_process("Writing failed.");
	else
		end_process("Usage: ./minisynth *.wav / *.synth");
	end_process(NULL);
	return (0);
}