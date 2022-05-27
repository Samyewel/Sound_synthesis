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
#include "../include/minisynth.h"

const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

void free_info(char **info)
{
	while (*info)
		free(*info++);
}

void get_tracks(char *str, char **instruments)
{
	char **list = ft_strsplit(str, ',');
	int num_tracks = 0;

	while (list[num_tracks])
	{
		instruments[num_tracks] = strdup(list[num_tracks]);
		num_tracks++;
	}
	instruments[num_tracks] = NULL;
	free_info(list);
}

void add_note(double frequency, double duration, int *vol, FILE *f, char *tone)
{
	int length = (unsigned long long)(duration * 44100.0);
	short waveform[length];
	unsigned long long i;

	if (!strcmp(tone, "square"))
	{
		for(i=1; i < length; i++) 
		{
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		//square
		waveform[i] = sin(frequency*t*2*M_PI) > 0 ? *vol * 1.0 : *vol * -1.0;
		}
	}
	if (!strcmp(tone, "saw"))
	{
		for(i=1; i < length; i++) 
		{
			double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
			//triangle GET SAW
			waveform[i] = *vol * asin(sin(frequency*t*2*M_PI)) * (2.0 / M_PI);
		}
	}
	if (!strcmp(tone, "sine"))
	{
		for(i=1; i < length; i++) 
		{
			double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
			//sine
			waveform[i] = *vol*sin(frequency*t*2*M_PI);
		}
	}
	if (!strcmp(tone, "triangle"))
	{
		for(i=1; i < length; i++) 
		{
			double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
			//triangle
			waveform[i] = *vol * asin(sin(frequency*t*2*M_PI)) * (2.0 / M_PI);
		}
	}
	wavfile_write(f,waveform,length);
}

int get_key_num(char *str, int *octave)
{
	int key_num = 1;

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
	//printf("key: %c num: %d\n", str[0], key_num);
	return (key_num);
}

void write_track(char *line, double tempo, int track, char *tone)
{
	char **inst1 = ft_strsplit(line, ' ');
	int i = 1;
	int octave = 4;
	int key_num = 1;
	double duration = 1.0;
	int vol = 3200;
	double freq = 440.0;
	char **info;
	
	
	char name[25] = "output/track";
	strcat(name, ft_itoa(track));
	strcat(name, ".wav");
	FILE *f = wavfile_open(name);
	if(!f) {
		printf("couldn't open sound.wav for writing: %s",strerror(errno));
		exit(0);
	}
	while (inst1[i])
	{
		info = ft_strsplit(inst1[i], '/');
		if (info[0][0] == '|')
		{
			i++;
			continue ;
		}
		if (info[0][0] == 'r')
		{
			key_num = 1;
			vol = 0;
		}
		else
		{
			key_num = get_key_num(info[0], &octave);
			vol = 3200.0;
		}
		if (info[1])
			duration = atof(info[1]);

		duration *= (double)60.0/tempo;

		freq = 440.0 * pow(2.0, ((double)(key_num - 49) / 12.0));
		add_note(freq, duration, &vol, f, tone);
		vol = 3200;
		free_info(info);
		i++;
	}
	free_info(inst1);
	wavfile_close(f);
}

//int main(int ac, char **av)
int write_wave(char *synthfile)
{
	char *line;
	
	int fd;
	
	
	double tempo = 120.0;
	int track;
	char **info;
	char **instruments;
	int i;

	//create instrument arr
	instruments = malloc(sizeof(char *) * 20);
	i = 0;
	while(i < 20)
		instruments[i++] = malloc(sizeof(char) * 9);

	fd = open(synthfile, O_RDONLY);

	//parse
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '#')
		{
			//printf("comment: %s\n", line);
			free(line);
			continue ;
		}
		if (strstr(line, "tempo"))
		{
			//get tempo
			info = ft_strsplit(line, ' ');
			tempo = atof(info[1]);
			free_info(info);
			free(line);
			//printf("tempo = %f\n", tempo);
			continue;
		}
		if (strstr(line, "tracks"))
		{
			//get tracks and instruments
			info = ft_strsplit(line, ' ');
			get_tracks(info[1], instruments);
			i = 0;
			//while (instruments[i])
			//	printf("%s\n", instruments[i++]);
			free_info(info);
			free(line);
			continue;
		}
		if (line[0] >= '1' && line[0] <= '9')
		{
			track = atoi(line);
			//printf("write track %d %s\n\n", track, instruments[track - 1]);
			write_track(line, tempo, track, instruments[track - 1]);
			free(line);
			continue;
		}
	}
	close(fd);
	
	return(1);
}
//gcc -Wall write_pcm.c wavfile/wavfile.c -L libft/ -lft -o test -lm && ./test examples/Super_Mario.synth

