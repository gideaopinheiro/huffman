#include "compressor.c"
#include "decompressor.c"

int main(int argc, char *argv[])
{
	FILE *input_file;
 
	while(True){
		if(strcmp(argv[1], "-c")==0){
			
			input_file = fopen(argv[2], "rb");
			fseek(input_file, 0, SEEK_SET);

			if(input_file == NULL){
				printf("%s is empty, try with other file.", argv[2]);
				break;
			}
			else{
				compress_file(input_file, argv[2]);
				printf("The process id done!\n");
				fclose(input_file);
				break;
			}
		}
		else if(strcmp(argv[1], "-d")==0){
			input_file = fopen(argv[2], "rb");
			fseek(input_file, 0, SEEK_SET);

			if(input_file == NULL){
				printf("%s is empty, try with other file.", argv[2]);
				break;
			}
			else{
				decompress_file(input_file);
				printf("\nThe process is done.\n");
				fclose(input_file);
				break;
			}
		}
	}

}