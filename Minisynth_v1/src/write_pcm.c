/*
This example program makes use of the simple
sound library to generate a sine wave and write the
output to sound.wav.
For complete documentation on the library, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2013/wavfile
Go ahead and modify this program for your own purposes.
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"
#include "../include/wavfile.h"

const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

void add_note(double frequency, double duration, int vol, FILE *f)
{
	int length = (int)(duration * 44100.0);
	short waveform[length];
	int i;

	for(i=1; i < length; i++)
	{
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = vol*sin(frequency*t*2*M_PI);
	}


	wavfile_write(f,waveform,length);

}

int get_key_num(char *str, int *octave, int *vol)
{
	int key_num;

	switch(str[0])
	{
		case 'a':
			key_num = 1;
			break;
		case 'b':
			key_num = 3;
			break;
		case 'c':
			key_num = 4;
			break;
		case 'd':
			key_num = 6;
			break;
		case 'e':
			key_num = 8;
			break;
		case 'f':
			key_num = 9;
			break;
		case 'g':
			key_num = 11;
			break;
		case 'r':
			*vol = 0;
			return (1);
	}
	if (str[1] == 'b' || str[1] == '#')
	{
		if (str[1] == 'b')
			key_num--;
		else if (str[1] == '#')
			key_num++;
		if (isdigit(str[2]))
			*octave = atoi(&str[2]);
	}
	else if (isdigit(str[1]))
		*octave = atoi(&str[1]);

	key_num = key_num + (12 * *octave);
	return (key_num);
}

void write_wave(char *synthfile)
{
	char *line;
	char **inst1;
	int fd;
	int vol = 3200;
	double freq = 440.0;
	double duration = 1.0;
	double tempo = 120.0;

	printf("test\n");
	FILE *f = wavfile_open("sound.wav");
	if(!f) {
		printf("couldn't open sound.wav for writing: %s",strerror(errno));
		return ;
	}
	fd = open(synthfile, O_RDONLY);
	printf("opened .wav file\n");
	while (get_next_line(fd, &line) > 0 && line[0] != '1')
		;
	//printf("%s\n", line);
	inst1 = ft_strsplit(line, ' ');
	int i = 1;
	int j;
	int octave = 1;
	int key_num;
	char **info;

	while (inst1[i])
	{
		j = 0;
		info = ft_strsplit(inst1[i], '/');
		key_num = get_key_num(info[0], &octave, &vol);
		if (info[1])
			duration = atof(info[1]);
		duration *= 60.0/tempo;
		freq = 440.0 * pow(2.0, ((double)(key_num - 49) / 12.0));
		add_note(freq, duration, vol, f);
		vol = 3200;
		//freeall(info);
		i++;
	}

	//freeall(inst1);
	close(fd);
	wavfile_close(f);
	printf("fd and wav file closed successfully");
	return ;
}
//gcc -Wall write_pcm.c wavfile/wavfile.c -L libft/ -lft -o test -lm && ./test Super_Mario.synth
//./a.out sound.wav