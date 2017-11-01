#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "sorter.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

//SEGFAULT IF PARAMATERS ARE NOT RIGHT (./sorter, but with no -c or parameter field to sort on)



movie* freePtr(movie* node){
	if(node == NULL){
		return NULL;
	}
	
	free(node->color);
	free(node->director_name);
	free(node->actor_2_name);
	free(node->genres);
	free(node->actor_1_name);
	free(node->movie_title);
	free(node->actor_3_name);
	free(node->plot_keywords);
	free(node->movie_imdb_link);
	free(node->language);
	free(node->country);
	free(node->content_rating);
	free(freePtr(node->next));
	
	
	
	return NULL;

}

//The function will be given a char** variable that holds all of the parsed content to be inputted into each Linked List node. Then the function will initialize and return a node to be inserted at the end of the linked list structure.
movie * createNode(char** catToked, int hasQuotes){
	movie * ptr = (movie*)malloc(sizeof(movie));
	
	ptr->color = strdup(catToked[0]);
	ptr->director_name = strdup(catToked[1]);
	ptr->num_critic_for_reviews = atol(catToked[2]);
	ptr->duration = atol(catToked[3]); 
	ptr->director_facebook_likes = atol(catToked[4]);
	ptr->actor_3_facebook_likes = atol(catToked[5]);
	ptr->actor_2_name = strdup(catToked[6]);
	ptr->actor_1_facebook_likes = atol(catToked[7]);
	ptr->gross = atol(catToked[8]);
	ptr->genres = strdup(catToked[9]);
	ptr->actor_1_name = strdup(catToked[10]);
	ptr->movie_title = strdup(catToked[11]);
	ptr->num_voted_users = atol(catToked[12]);
	ptr->cast_total_facebook_likes = atol(catToked[13]);
	ptr->actor_3_name = strdup(catToked[14]);
	ptr->facenumber_in_poster = atol(catToked[15]);
	ptr->plot_keywords = strdup(catToked[16]);
	ptr->movie_imdb_link = strdup(catToked[17]);
	ptr->num_user_for_reviews = atol(catToked[18]);
	ptr->language = strdup(catToked[19]);
	ptr->country = strdup(catToked[20]);
	ptr->content_rating = strdup(catToked[21]);
	ptr->budget = atol(catToked[22]);
	ptr->title_year = atol(catToked[23]);
	ptr->actor_2_facebook_likes = atol(catToked[24]);
	ptr->imdb_score = atof(catToked[25]);
	ptr->aspect_ratio= atof(catToked[26]);
	ptr->movie_facebook_likes = atol(catToked[27]);
	if(hasQuotes == 0){
		ptr->quotes = 0;
	}
	else{
		ptr->quotes = 1;
	}
	
	ptr->next = NULL;

	return ptr;

}

//This method accepts a string and removes all leading and trailing spaces.
char* spaceTrim(char* string){
	char* endOfString;
	
	
	if(string == NULL){			
		return NULL;
	}
	
	//While the value stored at the front of the char* string is a space, increment the string address by the size of a character (1 byte)
	while(*string == ' '){
		string = string + 1;
	}
	
	if(*string == ' '){
		return NULL;
	}
	
	endOfString = string + strlen(string) - 1;
	
	//Same concept as deleting leading spaces, but we are also making sure we stop once we reach the last actual character in the string.
	while(endOfString > string && (*endOfString == ' ')){
		endOfString = endOfString - 1;
	}
	
	//Set null terminator again
	*(endOfString + 1) = '\0';
	
	return string;
}

//This function determines what field we will be sorting by based on the user input.

int sortByCategory(char* sortColumnName){
	if(strcmp(sortColumnName, "color") == 0) {
		return 0;
	}
	else if(strcmp(sortColumnName, "director_name") == 0) {
		return 1;
	}
	else if(strcmp(sortColumnName, "num_critic_for_reviews") == 0) {
		return 2;
	}
	else if(strcmp(sortColumnName, "duration") == 0) {
		return 3;
	}
	else if(strcmp(sortColumnName, "director_facebook_likes") == 0) {
		 return 4;
	}
	else if(strcmp(sortColumnName, "actor_3_facebook_likes") == 0) {
		return 5;
	}
	else if(strcmp(sortColumnName, "actor_2_name") == 0) {
		return 6;
	}
	else if(strcmp(sortColumnName, "actor_1_facebook_likes") == 0) {
		return 7;
	}
	else if(strcmp(sortColumnName, "gross") == 0) {
		return 8;
	}
	else if(strcmp(sortColumnName, "genres") == 0) {
		return 9;
	}
	else if(strcmp(sortColumnName, "actor_1_name") == 0) {
		return 10;
	}
	else if(strcmp(sortColumnName, "movie_title") == 0) {
		return 11;
	}
	else if(strcmp(sortColumnName, "num_voted_users") == 0) {
		return 12;
	}
	else if(strcmp(sortColumnName, "cast_total_facebook_likes") == 0) {
		return 13;
	}
	else if(strcmp(sortColumnName, "actor_3_name") == 0) {
		return 14;
	}
	else if(strcmp(sortColumnName, "facenumber_in_poster") == 0) {
		return 15;
	}
	else if(strcmp(sortColumnName, "plot_keywords") == 0) {
		return 16;
	}
	else if(strcmp(sortColumnName, "movie_imdb_link") == 0) {
		return 17;
	}
	else if(strcmp(sortColumnName, "num_user_for_reviews") == 0) {
		return 18;
	}
	else if(strcmp(sortColumnName, "language") == 0) {
		return 19;
	}
	else if(strcmp(sortColumnName, "country") == 0) {
		return 20;
	}
	else if(strcmp(sortColumnName, "content_rating") == 0) {
		return 21;
	}
	else if(strcmp(sortColumnName, "budget") == 0) {
		return 22;
	}
	else if(strcmp(sortColumnName, "title_year") == 0) {
		return 23;
	}
	else if(strcmp(sortColumnName, "actor_2_facebook_likes") == 0) {
		return 24;
	}
	else if(strcmp(sortColumnName, "imdb_score") == 0) {
		return 25;
	}
	else if(strcmp(sortColumnName, "aspect_ratio") == 0) {
		return 26;
	}
	else if(strcmp(sortColumnName, "movie_facebook_likes") == 0) {
		return 27;
	}
	else {
		printf("Fatal Error: Please input a proper category title\n");
		exit(0);
	}
}

void sortFile(char* fileName, char** argv, int sortingBy){
	movie * headMovies = NULL;
	
	FILE* filePointer = fopen(fileName, "r");

	if(filePointer == NULL){
		printf("Fatal Error: The file does not exist.\n");
		exit(0);
	}
	//Create new file name to output to.
	char* newFileName = (char*)malloc(sizeof(char)*(strlen(fileName) + 30));
	//Determine where endOfFileName is, subtract 4 (accounts for ".csv"). Then, concatenate "-sorted-<category>.csv".
	int endOfFileName = strlen(fileName) - 4;
	memcpy(newFileName, fileName, endOfFileName);
	strcat(newFileName, "-sorted-");
	strcat(newFileName, argv[2]);
	strcat(newFileName, ".csv");
	//printf("NEW FILE NAME: %s\n", newFileName);
	
	//printf("Printing out into the file: %s\n", newFileName);
	
	
	


	int i;
	int j;
	int hasQuotes = 0;

	char* line = (char*)malloc(sizeof(char)*500);
	char* categories = "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes";

	memset(line, '\0', 500);

	fgets(line, 500, filePointer);

	if(strcmp(line, categories) ==  0){
		//printf("Fatal Error: The input file does not adhere to specified format\n");
		exit(0);
	}

	FILE* outputFile = fopen(newFileName, "r");
	
	
	//If outputFile already exists, don't even bother with rest of method.
	if(outputFile != NULL){
		//printf("Fatal Error: File \"%s\" already exists.\n", newFileName);
		exit(0);
	}
	else{
		//printf("OUTPUTFILE OPENED\n\n");
		outputFile = fopen(newFileName, "w");
	}
	
	if(line == NULL){
		printf("Fatal Error: The input file is blank.\n");
		exit(0);
	}

	//Points to the last node in the linked list to add to the list faster.
	movie * rearMovies = NULL;
	rearMovies = (movie*)malloc(sizeof(movie));

	char* tempTok;
	char* quotesDetectedTok;
	char* templine = (char*)malloc(sizeof(char)*500);
	char* parseSeg1;
	char* movie_titleTok;
	char* parseSeg3;

	//catToked = tokenized data corresponding to each category
	char** catToked = (char**)(malloc(sizeof(char*) * 28));

	//Allocates memory for each character of each string. Sets each character to the null string terminator needs to go through 28 fields in the final version
	for(i = 0; i < 28; i++){
		catToked[i] = (char*)(malloc(sizeof(char) * 70));
		for(j = 0; j < 70; j++){
			catToked[i][j] = '\0';
		}
	}

	while(fgets(line, 500, filePointer) != NULL){

		//printf("This is what the line says: %s\n", line);

		memcpy(templine, line, 500);

		//We will begin by tokenize by quotation marks, which will cause one of two things. First, if there are no quotation marks, the line will be 1 whole fragment, and we can proceed as usual. However, if strtok() returns a 1 while tokenizing for quotation marks, the line will be split into 3 tokens: before the movie title, the movie title, and after the movie title.

		tempTok = strsep(&line, "\"");

		/*
		printf("value of tempTok after \" search = %s\n", tempTok);
		printf("templine after strsep is: %s\n", templine);
		printf("value of tempTok before , search = %s\n", tempTok);
		*/

		//If there were no quotations detected, we will proceed as normal.
		//printf("result of strcmp: %d\n", strcmp(tempTok, templine));
		if (strcmp(tempTok, templine) == 0){
			tempTok = strsep(&templine, ",");

			for(i = 0; i < 28 && tempTok != NULL; i++){
	
				tempTok = spaceTrim(tempTok);

				//printf("tempTok = %s ||||\n", tempTok);
	
				if(strcmp(tempTok, "") == 0){
					//printf("blank line found\n");
					catToked[i][0] = '-';
					catToked[i][1] = '1';
				}
				else{
					catToked[i] = tempTok;
				}
				//printf("Content %d of catToked: %s\n", i, catToked[i]);
	
				tempTok = strsep(&templine, ",");
			}
		}
		else{
			parseSeg1 = tempTok;
			movie_titleTok = strsep(&line, "\"");
			parseSeg3 = strsep(&line, "\"");

			quotesDetectedTok = strsep(&parseSeg1, ",");

			for(i = 0; i < 12 && quotesDetectedTok != NULL; i++){
				quotesDetectedTok = spaceTrim(quotesDetectedTok);
	
				catToked[i] = quotesDetectedTok;
	
				quotesDetectedTok = strsep(&parseSeg1, ",");
	
			}

			//We have separated out the movie title, now trim the spaces and put it into its respective field
			movie_titleTok = spaceTrim(movie_titleTok);
			hasQuotes = 1;

			catToked[11] = movie_titleTok;

			quotesDetectedTok = strsep(&parseSeg3, ",");
			//We do this twice as the first token will be NULL as there is still a comma present before the first actual field.
			quotesDetectedTok = strsep(&parseSeg3, ",");

			for(i = 12; i < 28 && quotesDetectedTok != NULL; i++){
	
				quotesDetectedTok = spaceTrim(quotesDetectedTok);
	
				catToked[i] = quotesDetectedTok;
	
				quotesDetectedTok = strsep(&parseSeg3, ",");
			}
		}

		//If there is no head node, allocate space for it and set its values. Set rear pointer = head.

		if(headMovies == NULL){
			//printf("NEW HEAD NODE CREATED\n\n");
			headMovies = createNode(catToked, hasQuotes);

			rearMovies = headMovies;
		}

		else{
			//printf("NEW NODE CREATED\n\n");
			//Allocate memory for new node added to end of list. Set its values, then increment the rear pointer, making the new node the rear pointer for the list.
			rearMovies->next = createNode(catToked, hasQuotes);

			rearMovies = rearMovies->next;
		}	
	
		//Resetting the catToked
		for(i = 0; i < 28; i++){
			for(j = 0; j < 70; j++){
				catToked[i][j] = '\0';
			}
		}

		//Change name, should never use same pointer that we freed in realloc()
		line = realloc(line, 500);
		templine = realloc(templine, 500);
		hasQuotes = 0;
	}

	//Given the head pointer to the start of the Linked List structure and a category to sort by, perform a merge sort.
	merge(&headMovies, sortingBy);

	movie* currPtr = (movie*)malloc(sizeof(movie));
	currPtr = headMovies;
	
	//printf("\n\nTIME TO PRINT\n\n");
	printNodes(currPtr, outputFile);

	//This section of code will free the allocated memory for each pointer, struct, etc
	
	
	freePtr(headMovies);
	free(rearMovies);
	free(currPtr);
	free(line);
	free(templine);
	fclose(outputFile);
	fclose(filePointer);
	//return childCount;

}

//This function will recursively traverse through the original given file path. If a directory is found within the original directory, the process will fork and recursively call the traverseDirectory() function. If a file is found, the function will determine whether or not it is a CSV, and then fork if it is.
void traverseDirectory(char* path, char** argv, int sortingBy, int processSum, int printed){
	
	//flag to see if we printed or not, defaul 0, will be set to current pid after pid printed, must be passed because same process can recursively call traverseDirectory()
	int printedpid = printed;
	
	int totalProcesses = processSum;
	int status;
	
	int pid = -1;
	DIR* directoryPointer;
	struct dirent* currentObject;
	struct stat buffer;
	
	//printf("path to file = %s\n", path);
	
	if((directoryPointer = opendir(path)) == NULL){
		printf("Fatal Error: The directory does not exist.\n");
		exit(0);
	}
	
	//This will change the current working directory (cwd) to the given location, which will be the path we send the function.
	chdir(path);
	
	//We will be reading through everything in the current directory.
	while((currentObject = readdir(directoryPointer)) != NULL){
		
		lstat(currentObject->d_name, &buffer);
		
		//printf("CURRENTOBJECT NAME = %s\n", currentObject->d_name);
		
		if((strcmp(currentObject->d_name, "..") == 0) || (strcmp(currentObject->d_name, ".") == 0)){
					continue;
		}
		//If the current object being read is a directory...
		if(S_ISDIR(buffer.st_mode)){
			//Fork a new process
			if(printedpid != getpid()) {
				if(pid == -1){
					printf("%d,", getpid());
					printedpid = getpid();
				}
			}
			fflush(0);
			pid = fork();
			if(pid != 0) {
				totalProcesses++;
				//printf("\nTraverse: I JUST FORKED-parent, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
			}
			if(pid == 0) {
				//printf("TEST TEST TEST TEST: %d\n", getpid());
				totalProcesses = 0;
				//printf("\nTraverse: I JUST FORKED-child, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
			
				//Print out PID of child process
				if(printedpid != getpid()) {
					printf("%d,", getpid());
					printedpid = getpid();
				}
				
				//These are edge names that mess up the traversal (".." make the pointer go up a level)
				if((strcmp(currentObject->d_name, "..") == 0) || (strcmp(currentObject->d_name, ".") == 0)){
					exit(totalProcesses);
				}
				
				//We create a char array located in the stack that will hold the path to the new directory we must traverse.
				char* newPath = NULL;
				newPath = getcwd(newPath, 1024);
				
				//This adds the "/" needed before we give another file direction
				strcat(newPath, "/");
				//This adds the new directory name to the new path
				strcat(newPath, currentObject->d_name);
				
				//Repeat process with new directory
				//printf("\nduplicate child prob gets here\n");
				traverseDirectory(newPath, argv, sortingBy, totalProcesses, printedpid);
				printf("\nbut does it get here\n");
			}
			
			
		}
		//The currentObject is a file so...
		else{
			//Ignore an already sorted file
			if(strstr(currentObject->d_name, "-sorted")){
					continue;
			}
			//Ignore non-csv files
			else if((strstr(currentObject->d_name, ".csv")) == NULL){
					continue;
			}
			//The only remaining option is for the file to be considered for sorting. Thus, fork a new process.
			else{
				//ONLY PRINTS CORRECTLY IF \n IS PRESENT IN BOTH
				if(printedpid != getpid()) {
					if(pid == -1){
						printf("%d,", getpid());
						printedpid = getpid();
					}
				}
				fflush(0);
				pid = fork();
				if(pid != 0) {
					totalProcesses++;
					//printf("\ntraverse-else: I JUST FORKED-parent, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
				}
				if(pid == 0) {
					totalProcesses = 0;
					//printf("\ntraverse-else: I JUST FORKED-child, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
				}
				
				if(pid == 0){
					if(printedpid != getpid()) {
						printf("%d,", getpid());
						printedpid = getpid();
					}
					sortFile(currentObject->d_name, argv, sortingBy);
				}
			}
		}
		//printf("\nare we restarting the loop before printing again? We must be\n");
		
	}
	//Traverse back up to previous file path
	chdir("..");
	closedir(directoryPointer);
	
	//printf("\nI am process: %d. My totalProcesses is : %d\n", getpid(), totalProcesses);
	int i = 0;
	int total = totalProcesses;
	for(i = 0; i < total; i++) {
		wait(&status);
		if(WIFEXITED(status)) {
			totalProcesses += WEXITSTATUS(status);
			//printf("\npid: %d, Exit status: %d\n", getpid(), WEXITSTATUS(status));
			//printf("\nI am process: %d. I should be updating totalProcesses, it is now: %d.\n", getpid(),  totalProcesses);
		}
	}
	//not sure if we need this addtional wait but just to be safe of any leftover children, let's do it anyways
	wait(NULL);
	//printf("Number of total processes: %d\n", *processCount);
	exit(totalProcesses);
	
}

//This function prints out the contents of each node in the Linked List.
void printNodes(movie * currPtr, FILE* outputFile)
{
	fprintf(outputFile, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");

	int i;
	while(currPtr != NULL){
		
		for(i = 0; i < 28; i++){
			switch(i){
				case 0: 
			
					if(strcmp(currPtr->color, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->color);
					break;
				case 1: 
					if(strcmp(currPtr->director_name, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->director_name); 
					break;
				case 2: 
					if(currPtr->num_critic_for_reviews == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->num_critic_for_reviews); 
					break;
				case 3: 
					if(currPtr->duration == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->duration); 
					break;
				case 4: 
					if(currPtr->director_facebook_likes == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->director_facebook_likes); 
					break;
				case 5: 
					if(currPtr->actor_3_facebook_likes == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->actor_3_facebook_likes); 
					break;
				case 6: 
					if(strcmp(currPtr->actor_2_name, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->actor_2_name); 
					break;
				case 7: 
					if(currPtr->actor_1_facebook_likes == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->actor_1_facebook_likes); 
					break;
				case 8:
					if(currPtr->gross == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->gross); 
					break;
				case 9: 
					if(strcmp(currPtr->genres, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->genres); 
					break;
				case 10: 
					if(strcmp(currPtr->actor_1_name, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->actor_1_name); 
					break;
				case 11:  
					if(strcmp(currPtr->movie_title, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					if(currPtr->quotes == 1){
						fprintf(outputFile,"\"%s\",", currPtr->movie_title);
					} 
					else{
						fprintf(outputFile,"%s,", currPtr->movie_title);
					}
					break;
				case 12: 
					if(currPtr->num_voted_users == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->num_voted_users); 
					break;
				case 13: 
					if(currPtr->cast_total_facebook_likes == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->cast_total_facebook_likes);
					break;
				case 14: 
					if(strcmp(currPtr->actor_3_name, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->actor_3_name);
					break;
				case 15:  
					if(currPtr->facenumber_in_poster == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->facenumber_in_poster); 
					break;
				case 16: 
					if(strcmp(currPtr->plot_keywords, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->plot_keywords); 
					break;
				case 17: 
					if(strcmp(currPtr->movie_imdb_link, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->movie_imdb_link); 
					break;
				case 18: 
					if(currPtr->num_user_for_reviews == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->num_user_for_reviews); 
					break;
				case 19: 
					if(strcmp(currPtr->language, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->language); 
					break;
				case 20: 
					if(strcmp(currPtr->country, "-1") == 0){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->country); 
					break;
				case 21: 
					if(strcmp(currPtr->content_rating, "-1") == 0 || (strcmp(currPtr->content_rating,"-1-1") == 0)){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%s,", currPtr->content_rating); 
					break;
				case 22: 
					if(currPtr->budget == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->budget); 
					break;
				case 23: 
					if(currPtr->title_year == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->title_year); 
					break;
				case 24: 
					if(currPtr->actor_2_facebook_likes == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%ld,", currPtr->actor_2_facebook_likes); 
					break;
				case 25:  
					if(currPtr->imdb_score == -1){
						fprintf(outputFile,",");
						break;
					}
					fprintf(outputFile,"%g,", currPtr->imdb_score); 
					break;
				case 26: 
					if(currPtr->aspect_ratio == -1){
						fprintf(outputFile,",");
						break;
					}
				 	fprintf(outputFile,"%g,", currPtr->aspect_ratio); 
				 	break;
				case 27: 
					if(currPtr->movie_facebook_likes == -1){
						fprintf(outputFile,"\n");
						break;
					}
					fprintf(outputFile,"%ld\n", currPtr->movie_facebook_likes); 
					break;
				default: 
					printf("Fatal Error: The category you would like to sort by is not present.\n");
					exit(0);
			}
		}
			currPtr = currPtr->next;
	}	
		
}

//The main function is our driver that will call various functions as necessary. Such functions perform the tasks of creating new Linked List nodes, trimming spaces of strings, determining the category we are sorting by, and printing out the sorted Linked List.
int main(int argc, char ** argv) {
	int totalProcesses = 0;
	int status;
	
	int initPID = getpid();
	printf("Initial PID: %d\n", initPID);
	printf("PIDS of all child processes: \n");
	
	int sortingBy = -1;
	sortingBy = sortByCategory(argv[2]);
	
	//The input format will be incorrect if argc is 1, or an even number
	if((argc == 1) || ((argc % 2) == 0)){
		printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
		exit(0);
	}
	
	//This must ALWAYS be present
	if (strcmp(argv[1], "-c") != 0){
		printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
		exit(0);
	}
	
	int forkPid;
	//Default for searchDir should be current directory, default for outputDir should be whatever searchDir is. Think Joe wanted to wait until after input checks to see if he has to do that.
	DIR* searchDir = NULL;
	DIR* outputDir = NULL;
	
	//Checking to see if we are going to be searching in a specific directory instead of current
	if((argc >= 4) && (argv[3] != NULL)){
		if((strcmp(argv[3], "-d") != 0) && (strcmp(argv[3], "-o") != 0)){
			printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
			exit(0);
		}
		else if(strcmp(argv[3], "-o") == 0) {
			if(argv[4] == NULL){
				printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> -o <outputdir>\n");
				exit(0);
			}
			else{
				outputDir = opendir(argv[4]);
				if(outputDir == NULL){
					printf("The file directory does not exist\n");
					exit(0);
				}
			}
		}
		//The 4 output will be -d
		else{
			if(argv[4] == NULL){
				printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
				exit(0);
			}
			else{
				searchDir = opendir(argv[4]);
				if(searchDir == NULL){
					printf("The file directory does not exist\n");
					exit(0);
				}
				fflush(0);
				forkPid = fork();
				if(forkPid != 0) {
					totalProcesses++;
					//printf("\nmain: I JUST FORKED-parent, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
				}
				if(forkPid == 0) {
					totalProcesses = 0;
					//printf("\nmain: I JUST FORKED-child, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
				}
				if(forkPid == 0){
					
					traverseDirectory(argv[4], argv, sortingBy, totalProcesses, 0);
				}
			}
		}
	}
	//Checking to see if we are going to be searching and outputting to a specific directory instead of current
	if((argc >= 6) && (argv[5] != NULL)){
		if(strcmp(argv[5], "-o") != 0){
			printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
			exit(0);
		}
		else{
			if(argv[6] == NULL){
				printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
				exit(0);
			}
			else{
				outputDir = opendir(argv[6]);
				if(outputDir == NULL){
					printf("The file directory does not exist\n");
					exit(0);
				}
			}
		}
	}

	char* cwd = NULL;
	
	//If we were not given a specific directory to traverse, we will utilize the current directory
	if(searchDir == NULL){
		cwd = getcwd(cwd, 1024);
		if(cwd == NULL) {
			printf("Fatal error: Something wrong with default directory. Please fix me.\n");
			exit(0);
		}
		//printf("CWD = %s\n", cwd);
		searchDir = opendir(cwd);
		if(searchDir == NULL){
			printf("Fatal error: Something wrong with default directory. Please fix me.\n");
			exit(0);
		}
		
		fflush(0);
		forkPid = fork();
		if(forkPid != 0) {
			totalProcesses++;
			//printf("\nmain-2: I JUST FORKED-parent, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
		}
		if(forkPid == 0) {
			totalProcesses = 0;
			//printf("\nmain-2: I JUST FORKED-child, my pid is : %d, totalProcesses is now: %d\n", getpid(), totalProcesses);
		}
		
		if(forkPid == 0){
			traverseDirectory(cwd, argv, sortingBy, totalProcesses, 0);
		}
	}
	/*
	if(forkPid != 0){
		wait(NULL);
	}
	*/
	int i = 0;
	int total = totalProcesses;
	for(i = 0; i < total; i++) {
		wait(&status);
		if(WIFEXITED(status)) {
			totalProcesses += WEXITSTATUS(status);
			//printf("\npid: %d, Exit status: %d\n", getpid(), WEXITSTATUS(status));
			//printf("\nI am process: %d. I should be updating totalProcesses, it is now: %d.\n", getpid(),  totalProcesses);
		}
	}
	wait(NULL);

	fflush(0);
	if(getpid() == initPID){
		totalProcesses++;
		printf("\nTotal number of processes: %d\n", totalProcesses);
	}
	//Jake: it seems that the first child is returning correctly and getting the proper status, let's do some more testing for children of children
	
	//Joe: Also, implement -o operation. Also, the fatal output error for if the file is already sorter is not necessary and will mess up the output.
	
	//NOTE: fflush(0) is necessary before forking in order to clear the I/O buffer to repeat incredibly repetitive output.
	
	exit(0);
}
