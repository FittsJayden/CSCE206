// Christiana Chamon Garcia
// CSCE 206 - Fall 2022
// Project #3 Starter Code 

// Jayden Fitts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Header structure
struct header {
    char chunkid[4];
    unsigned int chunksize;
    char format[4];
    char subchunk1id[4];
    unsigned int subchunk1size;
    unsigned short int audioformat;
    unsigned short int numchannels;
    unsigned int samplerate;
    unsigned int byterate;
    unsigned short int blockalign;
    unsigned short int bitspersample;
    char subchunk2id[4];
    unsigned int subchunk2size;
};

// Definition for printheader Function
void printheader(struct header aa) {      
    printf("ChunkID = %.4s\n",aa.chunkid);                                 
    printf("ChunkSize = %d\n",aa.chunksize);
    printf("Format = %.4s\n",aa.format);
    printf("Subchunk1ID = %.4s\n",aa.subchunk1id);
    printf("Subchunk1Size = %d\n",aa.subchunk1size);
    printf("Audio Format = %d\n",aa.audioformat);
    printf("Number of Channels = %d\n",aa.numchannels);
    printf("SampleRate = %d\n",aa.samplerate);
    printf("ByteRate = %d\n",aa.byterate);
    printf("BlockAlign = %d\n",aa.blockalign);
    printf("BitsPerSample = %d\n",aa.bitspersample);
    printf("Subchunk2ID = %.4s\n",aa.subchunk2id);
    printf("Subchunk2Size = %d\n",aa.subchunk2size);
}

int main() {   
    printf("This program reads an audio file called ""Alejandro_project.wav"" located in the directory. It will generate two new audio files:\n");
    printf("1) Alejandro_fast.wav, which will play at double speed\n");
    printf("2) Alejandro_slow.wav, which will play at half speed\n");

    // Declare vars that will be used to open and read
	char buffer, input[]="Alejandro_project.wav", pinput[252], fast_input[256],slow_input[256],slowdown_input[256];
	char fast_audio[18] = "_fast.wav";
	char slow_audio[18] = "_slow.wav";
	int g, h, m;
	struct header headerin, headerfast, headerslow;
    short int byteBuffer;
	FILE* fp;
	FILE* fastfp;
	FILE* slowfp;
   
    char *pos = strchr(input, '.');
    memset(pinput, 0, sizeof(pinput));

    if (pos) {
        strncpy(pinput,input, pos-input);
    }

    strcpy(fast_input, pinput);
    strcpy(slow_input, pinput);
    strcpy(slowdown_input, pinput);	

    // Parse input to save only the directory location for saving output files
	if( (fp=fopen(input,"rb"))==NULL){
		printf("no original file\n");
    	getchar();
   		exit(EXIT_FAILURE);
    }
    strcat(fast_input, fast_audio);  
    if((fastfp=fopen(fast_input,"wb+"))==NULL) {
	    printf("Alejandro_project_fast.wav no file created\n");
	    getchar();
	    exit(EXIT_FAILURE);
    }
    strcat(slow_input, slow_audio);
    if((slowfp=fopen(slow_input,"wb+"))==NULL) {
	    printf("Alejandro_project_slow.wav no file created\n");
	    getchar();
	    exit(EXIT_FAILURE);
    }
  
    // Read headers into structs
	fread(&headerin,44,1,fp);
	fseek(fp,0,SEEK_SET);
	fread(&headerfast,44,1,fp);
	fseek(fp,0,SEEK_SET);
	fread(&headerslow,44,1,fp);
	fseek(fp,0,SEEK_SET);
   
    // Write headers
	fwrite(&headerfast,44,1,fastfp);
	fseek(fastfp,0,SEEK_SET);
	fwrite(&headerslow,44,1,slowfp);
	fseek(slowfp,0,SEEK_SET);
   
    // Print original header
	printf("\nORIGNAL HEADER FILE\n\n");
	printheader(headerin);
	printf("\n\n");





	
    fseek(fp, 0, SEEK_SET);
    fastfp = fopen(fast_input, "wb");
    headerfast.samplerate *= 2;
    headerfast.byterate = 2 * headerfast.samplerate;
    fseek(fastfp, 0, SEEK_SET);
    fwrite(&headerfast, 44, 1, fastfp);
    for (g=0; g < (headerfast.subchunk2size / 2); ++g) {
        fread(&byteBuffer, 2, 1, fp);
        fwrite(&byteBuffer, 2, 1, fastfp);
    }
    fclose(fastfp);



    fseek(fp, 0, SEEK_SET);
    slowfp = fopen(slow_input, "wb");
    headerslow.samplerate /= 2;
    headerslow.byterate = 2 * headerslow.samplerate;
    fseek(slowfp, 0, SEEK_SET);
    fwrite(&headerslow, 44, 1, slowfp);
    for (h=0; h < (headerslow.subchunk2size / 2); ++h) {
        fread(&byteBuffer, 2, 1, fp);
        fwrite(&byteBuffer, 2, 1, slowfp);
    }
    fclose(slowfp);






	printf("\nFAST HEADER FILE\n\n");
	printheader(headerfast);
	printf("\n\n");

	printf("\nSLOW HEADER FILE\n\n");
	printheader(headerslow);
	printf("\n\n");

    return 0;
}
