/* Write a C program that mimics the cp command using open() system call to open source.txt file
in read-only mode and copy the contents of it to destination.txt using read() and write() system
calls. */

#include <stdio.h>											// Standard Input Output Functions
#include <fcntl.h>											// defines options flags
#include <unistd.h>											// Prototypes for many system calls
#include <string.h>											// Commenly used for string handling functions (strerror())
#include <errno.h>											// Declares errno and defines error constants

/*	read(fd, buffer, count) 
	reads at most count bytes from the open file referred to by fd and stores them in buffer.
	The read() call returns the number of bytes actually read. If no further bytes could 
	be read (i.e., end-of-file was encountered), read() returns 0.
*/

/*  write(fd, buffer, count)
	writes up to count bytes from buffer to the open file referred to by fd. 
	The write() call returns the number of bytes actually written, which may be less than count.
*/

int main (int argc, char* argv[])							
{
	if (argc != 3) {
        printf("Need 2 arguments for copy program\n");
        return 1;
     }

	char *source = argv[1];									// source file
	int return_val;											// return_val
	return_val = access (source, F_OK);						// access checks if file exits
	if (return_val == 0) 									// if return_val is 0, file exists
		printf("%s does exist\n", source);
	else													// if return_val is negative
	{
		if (errno == ENOENT) 								// errno - ENOENT - Error NO ENTry
			printf("cat: %s: No such file"
					" or directory\n", source);
		else if (errno == EACCES)							// EACCESS - permisssion denied
			printf("%s is not accessible"
				"(permisssion denied)\n", source);
		return 0;
	}

	int fd, n;
	fd = open(source, O_RDONLY);

	if (fd != -1)
	{
		printf("%s opened for read access only! \n", source);
		
		char *destination = argv[2];							// destination file
		return_val = access (destination, F_OK);				// access checks if file exits
		int dd;	

		mode_t filePerms;
		filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

		if (return_val == 0) 									// if return_val is 0, file exists
			printf("%s does exist\n", destination);
		else													// if return_val is negative file doesn't exist
		{
			if (errno == EACCES)								// EACCESS - permisssion denied
			{
				printf("%s is not accessible"
					"(permisssion denied)\n", destination);
				return 1;
			}
			else if (errno == ENOENT) 							// errno - ENOENT - Error NO ENTry
			{
				printf("cp: %s: No such file"
						" or directory\n", destination);

				dd = open(destination, O_CREAT | O_RDWR, filePerms);		// if dest file doesn't exist, create one.
				if (fd != -1)
				{
					printf("%s created successfully! \n", destination);
					printf("%s opened for read and write access! \n", destination);
				}
			}
		}

		dd = open(destination, O_CREAT | O_RDWR, filePerms);
		char buff[BUFSIZ];

		while((n = read(fd, buff, 101)) > 0)
        {
        	printf("buff: %s\n", buff);
        	// write(dd, buff, n);
    	}

		close (dd);
		close (fd);
	}

	return 0;
}