/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisynth.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swilliam <swilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:23:20 by swilliam          #+#    #+#             */
/*   Updated: 2022/05/26 15:01:32 by swilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISYNTH_H

#define MINISYNTH_H
#define MINIAUDIO_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>

/*
** Playback
*/
int playback(char *file);
FILE * wavfile_open( const char *filename );
void wavfile_write( FILE *file, short data[], int length );
void wavfile_close( FILE * file );

#define WAVFILE_SAMPLES_PER_SECOND 44100

#endif