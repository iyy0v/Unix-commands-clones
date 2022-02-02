#include <stdio.h>
#include <dirent.h> 
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	struct dirent *d; 
	DIR *dir;
	int opt;

	if(argc == 3) { // Both the directory AND the option were given
		dir = opendir(argv[1]); 
		if(dir == NULL) { 
			perror(argv[1]); 
			closedir(dir);
			return -1;
		}
	}
	else if(argc == 2) { // Only the directory OR the option was given
		if(argv[1][0] != '-') 	// Only the flag was given
			dir = opendir(argv[1]); 
			if(dir == NULL) { 
	    			perror(argv[1]);
	    			closedir(dir);
	    			return -1;
	 		}
		else 			// Only the directory was given
			dir = opendir("."); 
	}
	else if(argc == 1) { // Nothing was given (default)
		dir = opendir(".");
	}
	else{  // Error: Extra arguments
		printf(" Extra arguments !\n");
		printf(" Usage: %s <dir>[optional] <option>[optional]\n",argv[0]);
		printf(" Options: -r Show directories only\n\t  -f Show files only\n"); 
	}


	opt = getopt(argc, argv, "rf"); 
    switch(opt) 
    { 		// Check the option
        case 'r': 	// Directories only
            while((d = readdir(dir)) != NULL){
            	if((*d).d_type == DT_DIR) 
            		printf("%s\n", (*d).d_name); 
            }
            break; 
        case 'f':	// Files only
            while((d = readdir(dir)) != NULL){
            	if((*d).d_type == DT_REG) 
            		printf("%s\n", (*d).d_name);
            }
            break; 
	    case '?': 	// Error: Unknown option
            printf(" Unknown option: %c\n", optopt);
            break; 
    	default: // No option
    		while((d = readdir(dir)) != NULL){
            	printf("%s\n", (*d).d_name);
            }
    		break;

    } 

	closedir(dir); 

	return 0;
}
