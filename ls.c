#include <stdio.h>
#include <dirent.h> 
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	struct dirent *d; 
	DIR *dir;
	int opt;

	if(argc == 3) { 
		dir = opendir(argv[1]); 
		if(dir == NULL) { 
			perror(argv[1]); 
			closedir(dir);
			return -1;
		}
	}
	else if(argc == 2) { 
		if(argv[1][0] != '-')
			dir = opendir(argv[1]); 
			if(dir == NULL) { 
	    			perror(argv[1]);
	    			closedir(dir);
	    			return -1;
	 		}
		else 
			dir = opendir("."); 
	}
	else if(argc == 1) { 
		dir = opendir(".");
	}
	else{ 
		printf(" Extra arguments !\n");
		printf(" Usage: %s <dir>[optional] <option>[optional]\n",argv[0]);
		printf(" Options: -r Show directories only\n\t  -f Show files only\n"); 
	}


	opt = getopt(argc, argv, "rf"); 
    switch(opt) 
    { 
        case 'r': 
            while((d = readdir(dir)) != NULL){
            	if((*d).d_type == DT_DIR) 
            		printf("%s\n", (*d).d_name); 
            }
            break; 
        case 'f':
            while((d = readdir(dir)) != NULL){
            	if((*d).d_type == DT_REG) 
            		printf("%s\n", (*d).d_name);
            }
            break; 
        case '?': 
            printf(" Unknown option: %c\n", optopt);
            break; 
    	default: 
    		while((d = readdir(dir)) != NULL){
            	printf("%s\n", (*d).d_name);
            }
    		break;

    } 

	closedir(dir); 

	return 0;
}
