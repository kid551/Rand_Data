#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 1024

float frand(float lower, float upper)
{
	float rand_num = rand();
	
	rand_num /= (float) RAND_MAX;
	
	rand_num = lower + (upper - lower) * rand_num;
	
	return rand_num;
}

int main(int argc, char * argv[])
{
	int return_code = 0;
	
	char filename_Wm[MAX_FILENAME_LENGTH] = {0};
	char filename_Wp[MAX_FILENAME_LENGTH] = {0};
	FILE * fp_Wp = NULL;
	FILE * fp_Wm = NULL;
	
	int seed = time(0);
	float rand_num;
	float value;
	
	int N = 0;
	
	float lower_bound_Wm = 0.0f;
	float upper_bound_Wm = 0.0f;
	float jump_Wm = 0.0f;
	float percent_highlight_Wm = 0.0f;
	float jump_highlight_Wm = 0.0f;
	float upper_highlight_Wm = 0.0f;
	
	float lower_bound_Wp = 0.0f;
	float upper_bound_Wp = 0.0f;
	float jump_Wp = 0.0f;
	float percent_highlight_Wp = 0.0f;
	float jump_highlight_Wp = 0.0f;
	float upper_highlight_Wp = 0.0f;
	
	long N3 = 0;
	long ii = 0;
	
	float * Wm = NULL;
	float * Wp = NULL;
	
	float * writer = NULL;
	
	if ((2 == argc) && ((0 == strcmp("--help", argv[1])) || (0 == strcmp("-h", argv[1]))))
	{
		printf("rand_data N 'file path for Wm' 'lower bound for Wm' 'rand jump width for Wm' 'percent for high light rand for Wm, like 0.1 for 10%' 'rand jump width for hight light rand for Wm' 'file path for Wp' 'lower bound for Wp' 'rand jump width for Wp' 'percent for high light rand for Wp, like 0.1 for 10%' 'rand jump width for hight light rand for Wp'\n");
		return_code = 0;
		goto exit_flag;
	}
	
	if (argc < 12)
	{
		printf("Error paramter! using --help or -h to show info.");
		return_code = -1;
		goto exit_flag;
	}
	
	N = atoi(argv[1]);
	N3 = N;
	N3 *= N3 * N3;
	
	sprintf(filename_Wm, "%s", argv[2]);
	lower_bound_Wm		= (float) atof(argv[3]);
	jump_Wm			= (float) atof(argv[4]);
	percent_highlight_Wm	= (float) atof(argv[5]);
	jump_highlight_Wm	= (float) atof(argv[6]);
	upper_bound_Wm		= lower_bound_Wm + jump_Wm;
	upper_highlight_Wm	= lower_bound_Wm + jump_highlight_Wm;
	
	sprintf(filename_Wp, "%s", argv[7]);
	lower_bound_Wp		= (float) atof(argv[8]);
	jump_Wp			= (float) atof(argv[9]);
	percent_highlight_Wp	= (float) atof(argv[10]);
	jump_highlight_Wp	= (float) atof(argv[11]);
	upper_bound_Wp		= lower_bound_Wp + jump_Wp;
	upper_highlight_Wp	= lower_bound_Wp + jump_highlight_Wp;
	
	printf("N = %d \n", N);
	printf("N3 = %d \n", N3);
	
	printf("Wm:\n");
	printf("[%f, %f]\n", lower_bound_Wm, upper_bound_Wm);
	printf("[%f, %f] for percent %f\n", lower_bound_Wm, upper_highlight_Wm, percent_highlight_Wm);
	
	printf("Wp:\n");
	printf("[%f, %f]\n", lower_bound_Wp, upper_bound_Wp);
	printf("[%f, %f] for percent %f\n", lower_bound_Wp, upper_highlight_Wp, percent_highlight_Wp);
	
	//reset seed;
	srand(time(0));
	
	//write & generate Wm
	fp_Wm = fopen(filename_Wm, "wb");
	
	fwrite(&N, sizeof(int), 1, fp_Wm);
	
	Wm = (float *)malloc(N3 * sizeof(float));
	writer = Wm;
	//printf("\n\n");
	//printf("Wm:\n");
	for (ii = 0;ii < N3;++ii)
	{
		value = frand(lower_bound_Wm, upper_bound_Wm);
		//see if highlight
		if (percent_highlight_Wm > 0)
		{
			rand_num = frand(0.0f, 1.0f);
			
			if (rand_num <= percent_highlight_Wm)
			{
				value = frand(lower_bound_Wm, upper_highlight_Wm);
			}
		}
		//printf("%f ", value);
		
		* writer = value;
		++writer;
	}
	fwrite(Wm, sizeof(float), N3, fp_Wm);
	writer = NULL;
	
	//write & generate Wp
	fp_Wp = fopen(filename_Wp, "wb");
	
	fwrite(&N, sizeof(int), 1, fp_Wp);
	
	Wp = (float *)malloc(N3 * sizeof(float));
	writer = Wp;
	//printf("\n\n");
	//printf("Wp:\n");
	for (ii = 0;ii < N3;++ii)
	{
		value = frand(lower_bound_Wp, upper_bound_Wp);
		//see if highlight
		if (percent_highlight_Wp > 0)
		{
			rand_num = frand(0.0f, 1.0f);
			
			if (rand_num <= percent_highlight_Wp)
			{
				value = frand(lower_bound_Wp, upper_highlight_Wp);
			}
		}
		//printf("%f ", value);
		
		* writer = value;
		++writer;
	}
	fwrite(Wp, sizeof(float), N3, fp_Wp);
	writer = NULL;
	
exit_flag:
	writer = NULL;
	if (Wm)
	{
		free(Wm);
		Wm = NULL;
	}
	if (Wp)
	{
		free(Wp);
		Wp = NULL;
	}
	
	if (fp_Wm)
	{
		fclose(fp_Wm);
		fp_Wm = NULL;
	}
	if (fp_Wp)
	{
		fclose(fp_Wp);
		fp_Wp = NULL;
	}
	
	return return_code;
}

