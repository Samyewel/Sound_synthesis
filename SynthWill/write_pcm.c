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

#include "wavfile/wavfile.h"

const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

void add_note(double frequency, double duration, FILE *f)
{
	int length = (int)(duration * 44100.0);
	short waveform[length];
	int i;
	int volume = 32000;

	for(i=1; i < length; i++) 
	{
		double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume*sin(frequency*t*2*M_PI);
	}


	wavfile_write(f,waveform,length);
	
}

int main()
{
	FILE *f = wavfile_open("sound.wav");
	if(!f) {
		printf("couldn't open sound.wav for writing: %s",strerror(errno));
		return 1;
	}

	add_note(440.0, 4.0, f);
	wavfile_close(f);
	return (0);
}