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

movie * headMovies = NULL;

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
	ptr->aspect_ratio= atol(catToked[26]);
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


//This function prints out the contents of each node in the Linked List.
void printNodes(movie * currPtr, FILE* outputFile)
{
	int i;
	while(currPtr != NULL){
	for(i = 0; i < 28; i++)
	{
		switch(i)
		{
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
	printf("%d\n", getpid());
	//(*processCount)++;
	printf("argc = %d\n", argc);
	if(argc < 3){
		printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
		exit(0);
	}
	
	//Comment this if out if testing in gdb
	if (strcmp(argv[1], "-c") != 0){
		printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
		exit(0);
	}
	
	DIR* searchDir = NULL;
	DIR* outputDir = NULL;
	
	//Checking to see if we are going to be searching in a specific directory instead of current
	if((argc >= 4) && (argv[3] != NULL)){
		if(strcmp(argv[3], "-d") != 0){
			printf("Fatal Error: The format of the input is incorrect. Please use the format: ./sorter.c -c <column heading> <-d thisdir> <-o thatdir>\n");
			exit(0);
		}
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
			}
		}
	}
	//Checking to see if we are going to be outputting to a specific directory instead of current
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
	
	printf("Past input checks\n");
	struct dirent *directoryPtr;
	int forkPid = 0;
	
	if(searchDir == NULL){
		char cwd[1024];
		searchDir = opendir(getcwd(cwd, 1024));
	}
	
	if(searchDir != NULL){
		while((directoryPtr = readdir(searchDir)) != NULL){
			forkPid = fork();
			if(forkPid == 0){
				printf("%d\n", getpid());
				break;
			}
		}
	}
	
	//If we encounter a directory within the directory, we must now enter that directory and repeat the process
	
	/*
	if((forkPid == 0) && (directoryPtr->d_type == DT_DIR)){
		DIR* newSearchDir = opendir(directoryPtr->d_name);
		struct dirent *newDirectoryPtr;
		while((newDirectoryPtr = readdir(newSearchDir)) != NULL){
			forkPid = fork();
		}
	}
	*/
	//If we encounter a file, we must check if it is a CSV, then sort
	//if((forkPid == 0) && (directoryPtr->d_type == DT_REG)){
	if(forkPid == 0){
		char* fileName = directoryPtr->d_name;
		printf("File name = %s\n", fileName);
		
		//If the file is not a CSV or the file is already sorted, ignore it and exit.
		if(strstr(fileName, ".csv") == NULL){
			printf("Fatal Error: The file is not a CSV file.\n");
			exit(0);
		}
		if(strstr(fileName, "-sorted") != NULL){
			printf("Fatal Error: The file is already sorted.\n");
			exit(0);
		}
		
		FILE* filePointer = fopen(fileName, "r");
		
		if(filePointer == NULL){
			printf("Fatal Error: The file does not exist.\n");
			exit(0);
		}
		
		//What we will be sorting by (category name) is in argv[2]
		//The index of this field in the catToked char** will be stored in sortingBy
		int sortingBy = -1;
	
		sortingBy = sortByCategory(argv[2]);
	
		int i;
		int j;
		int hasQuotes = 0;
	
		char* line = (char*)malloc(sizeof(char)*500);
	
		memset(line, '\0', 500);
	
		fgets(line, 500, filePointer);
		
		if(strcmp(line, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes") ==  0){
			printf("Fatal Error: The input file does not adhere to specified format\n");
			exit(0);
		}
	
		if(line == NULL){
			printf("Fatal Error: The input file is blank.\n");
			exit(0);
		}
	
		//Points to the last node in the linked list to add to the list faster.
		movie * rearMovies = (movie*)malloc(sizeof(movie));

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
	
		while(fgets(line, 500, stdin)){
	
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
			
				headMovies = createNode(catToked, hasQuotes);
			
				rearMovies = headMovies;
			}
		
			else{
			
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
		
		
		//Create new file name to output to.
		char* newFileName = (char*)malloc(sizeof(char)*(strlen(fileName) + 30));
		int endOfFileName = strlen(fileName) - 4;
		memcpy(newFileName, fileName, endOfFileName);
		strcat(newFileName, "-sorted-");
		strcat(newFileName, argv[2]);
		strcat(newFileName, ".csv");
		printf("NEW FILE NAME: %s\n", newFileName);
		FILE* outputFile = fopen(newFileName, "w");
		
		if(outputFile == NULL){
			printf("Fatal Error: Error in creating output file.\n");
		}
		
		printf("Printing out into the file: %s\n", newFileName);
		printNodes(currPtr, outputFile);
	
		//This section of code will free the allocated memory for each pointer, struct, etc
		freePtr(headMovies);
		free(rearMovies);
		free(currPtr);
		free(line);
		free(templine);
		exit(0);
	}
	
	//Keep waiting until all children have finished
	
	if (forkPid != 0){
		wait(NULL);
		//printf("Number of total processes: %d\n", *processCount);
	}
	return 0;
}
