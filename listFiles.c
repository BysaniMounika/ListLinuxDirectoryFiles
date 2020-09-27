#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>

// Global variables for output file pointer and counter.
FILE *output;
int N;

int isDirectory(char *path);
void listFiles(char *path, char *subString);
void removeWhiteSpaces(char *str);

int main(int argc, char *argv[]) {
	// Checking if we have received all params.
	if (argc != 4) {
		printf("Required parameters are missing.\n");
		return 0;
	}
	
	// Removing white spaces for all params.
	removeWhiteSpaces(argv[1]);
	removeWhiteSpaces(argv[2]);
	removeWhiteSpaces(argv[3]);
	
	// Check for directory existence.
	if (!isDirectory(argv[1])) {
		printf("Directory doesn't exist\n");
		return 0;
	}
	
	// Check for non-numeric characters in thirdParameter which we consider as N.
	int i;
	for (i = 0; argv[3][i] != '\0'; ++ i) {
		if (isalpha(argv[3][i])) {
			break;
		} 
	}
	
	// Converting N from string to integer.
	if (argv[3][i] != '\0') {
		printf("Third parameter has to be an integer.\n");
		return 0;
	}
	N = atoi(argv[3]);
	
	// Opening the file to display file entries.
	output = fopen("output.txt", "w");	
	// Prints Header line.
	fprintf(output, "%-4s %-15s %s\n", "Mode", "Size", "FileName");
	// Call to a function which performs core logic.
	listFiles(argv[1], argv[2]);
	// Close the file pointer.
	fclose(output);
	
	return 0;
}

int isDirectory(char *path) {
// Check if the path belongs to a directory.
	struct stat status;
	stat(path, &status);
	if (S_ISDIR(status.st_mode)) {
		return 1;
	}
	
	return 0;
}

void removeWhiteSpaces(char *str) {
// Function to remove white spaces in a string.
	int count = -1, i = 0;
	while (str[i] != '\0') {
		if (str[i] != ' ') {
			str[++count] = str[i];
		}
		++ i;
	}
	str[++ count] = '\0';
}

void listFiles(char *basePath, char *subString) {
// List all files in given path.
	char path[1000];
	struct dirent *dp;
	struct stat status;
	DIR *dir = opendir(basePath);
	if (!dir) {
		// Unable to open directory stream.
		return;
	}
	while ((dp = readdir(dir)) != NULL) {
		// Loop through entries in the directory stream.
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			// Creating path for an entry in directory.
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			if (stat(path, &status) == 0) {
				if(S_ISDIR(status.st_mode)) {
					// If an entry is a directory.
					listFiles(path, subString);
				} else {
					// If an entry is a file then display it's properities.
					if (strstr(dp->d_name, subString) != NULL) {
						char mode[4] = "";
						if (status.st_mode & R_OK) {
							// Displays R when read mode is enabled.
							strcat(mode, "R");
						} 
						if (status.st_mode & W_OK) {
							// Displays W when write mode is enabled.
							strcat(mode, "W");
						} 
						if (status.st_mode & X_OK) {
							// Displays X when execute mode is enabled.
							strcat(mode, "X");
						} 
						
						fprintf(output, "%-4s %-15ld %s\n", mode, status.st_size, dp->d_name);
						// Decrementing counter.
						-- N;
					}
				}
			}
		}
		if (N == 0) {
			// Stop further execution when N entries are listed.
			return;
		}
	} 
	// Close directory stream.
	closedir(dir);
}