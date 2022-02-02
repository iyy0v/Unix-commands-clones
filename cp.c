#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fs,fd;
	char buf;

	if(argc != 3) {
		printf("Usage: %s <Source_file> <Destination_file>\n",argv[0]);
		exit(1);
	}

	if(access(argv[1],F_OK)==0) { // Verify the existance of the source file
		if(access(argv[1],R_OK)==0) { // Verify the 'Read' permission of the source file
			fs = open(argv[1],O_RDONLY);
		}
		else{
			printf("ERROR: Unable to read the file %s !\n",argv[1]);
			exit(1);
		}
	}
	else{
		printf("ERROR: The source file %s doesn't exist !\n",argv[1]);
		exit(1);
	}

	if(access(argv[2],F_OK)==0) { // Recreate the destination file if it already exists
		fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC);	
	}
	else{ // Create the destination file if it doesn't exist
		fd = open(argv[2],O_WRONLY | O_CREAT);
	}

	while(read(fs,&buf,1) != 0) { write(fd,&buf,1); } // Copy the content of the source file to the destination file
	
	close(fs);
	close(fd);

	return 0;
}
