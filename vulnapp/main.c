#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define MAX_LEN_USER_CREDS 20


/*
 * This application demonstrates exploitable examples.
 *
 * Ex 1:  Buffer Overflow.  By entering "1s" repeating for the password (61 in total for me), we overflow the password array length writing a value into
 * 	  the next memory location, being "auth".  When auth is compared, thinking it is a boolean (1 or 0) but really an int, it's
 * 	  value for logic "true" just needs to be greater than 0 to be true.  Since we overflow the buffer into auth, we don't need
 * 	  to have a valid username or password and we are authorized.
 *
 * Ex 2:  The next exploit is replacing the memory location for the system call with an executable we would like.  Into this
 *        part of the code, we continue with our buffer overflow to then gain access of the system (theoretically, possibly by 
 *        injecting a reverse shell.  For demonstration, we'll change the command to echo somehting exciting to the terminal  :)
 *
 * To Build:
 * gcc -o vulnapp main.c
 */
int main() {
	char username[MAX_LEN_USER_CREDS];
	char password[MAX_LEN_USER_CREDS];
        int auth = 0;
	char cmd [] = "/bin/sh -c 'ls -la'";

	printf("Enter Username: ");
	scanf("%s", username);

	printf("Enter Password: ");
	scanf("%s", password);

	if(strcmp(username, "john") == 0 && strcmp(password, "abc123") == 0) {
		printf("you are authenticated %i\n", auth);
		auth = 1;
	} else {
		printf("You are not authenticated\n");
	}

	if(auth) {
 		system(cmd);
	}
	return 0;
}
