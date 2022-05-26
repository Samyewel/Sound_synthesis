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

#include "wavfile.h"

const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

int main()
{
	
	double frequency = 220.0;
	int volume = 32000;
	int length = NUM_SAMPLES;
	int num_notes = 4;

	length *= num_notes;
	short waveform[length];

	int i;
	int j;
	int q = 0;
	for (j = 1; j < 5; j++)
	{
		for(i=1;i<NUM_SAMPLES;i++) 
		{
			double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
			waveform[q + i] = volume*sin(frequency*(double)j*t*2*M_PI);
		}
		q += i;

	}

	FILE * f = wavfile_open("sound.wav");
	if(!f) {
		printf("couldn't open sound.wav for writing: %s",strerror(errno));
		return 1;
	}

	wavfile_write(f,waveform,length);
	wavfile_close(f);

	return 0;
}