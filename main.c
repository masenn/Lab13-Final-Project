#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "wav.h"

#define TEST_FREQ 440
#define SAMPLE_FREQ 16000
#define NUM_SECS 5
#define BIT_DEPTH 16
#define NUM_CHANNELS 2
#define VOLUME .3

#define AMP_DEPTH 2
#define AMP_FREQ 1

void load_params(char* file);

double to_double(char* c) {
    char *endptr;
    double value;

    // Convert string to double
    value = strtod(c, &endptr);

    // Check for conversion errors
    if (*endptr != '\0') {
        printf("Conversion error with string \"%s\"\n",c);
        return 0;
    } else {
        return value;
    }
}

int main(){
    load_params("config.csv");
 
   //  int frames_per_process = total_images / nprocs;
   //  int remaining_frames = total_images % nprocs;

   //  pid_t pids[nprocs];
   //  for (int i = 0; i < nprocs; i++) {
	// 	//Process****************************************************************
   //      if ((pids[i] = fork()) == 0) { // Child process
   //          int start_frame = i * frames_per_process;
   //          int end_frame = start_frame + frames_per_process;
   //          if (i == nprocs - 1) {
   //              end_frame += remaining_frames; // Last process handles the extra frames
   //          }
			

   //          }
   //          exit(0);
   //      } else if (pids[i] < 0) { // Fork failed
   //          perror("fork");
   //          exit(-1);
   //      }

    // Parent  waits for all children to finish
   //  for (int proc = 0; proc < nprocs; proc++) {
   //      wait(NULL);
   //  }
}

void load_params(char* file){
   FILE* fp;
   fp = fopen(file,"r");
   if(fp==NULL){
      printf("Cannot find file: %s\n",file);
      return;
   }
   // WaveParameters params[];
   char buf[300];
   char* data[8];
   int count = 0; 
   int isHeader = 1;
   int line = 1;
   while(fgets(buf,sizeof(buf),fp)!=NULL){
      //placing into the array
      char* token = strtok(buf, " \n,\r");
      while (token != NULL) {
         if(count > 8) {
            printf("Error in csv formatting!\n\n"); 
            break;
         }
         data[count] = token;
         count++;
        //  printf("%d: %s\n",count,data[count-1]);
         token = strtok(NULL, " \n,\r");
      }
      if(count!=8){
         printf("Error on line %d. Returning!\n",line);
         return;
      }
      count = 0; 
      if(!isHeader){
        WaveParameters wave;
        static char name[64];
        strcpy(name, data[0]);
        printf("name: %s\n---\n",data[0]);
        //name,samp_freq,samp_channels,samp_length,bit_depth,amp_depth,freq_depth,rot_freq
        wave.sample_freq = (int)to_double(data[1]);
        wave.sample_channels = (int)to_double(data[2]);
        wave.sample_length = (int)to_double(data[3]);
        wave.bit_depth = (int)to_double(data[4]);
        wave.amp_depth = to_double(data[5]);
        wave.freq_depth = to_double(data[6]);
        wave.rot_freq = to_double(data[7]);
        wave.MAX_VAL = pow(2,wave.bit_depth)/2;

        // printf("%s %s %s\n",data[1],data[2],data[3]);
        generate_package(name,&wave);
      } else {
         isHeader = 0; 
      }
      line++;
   }
   fclose(fp);
}