#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

int main() {

	size_t line_length = 0;
	char* lineptr = NULL;
	while (1) {
		lineptr = NULL;
		line_length = 0;
		printf("$ ");
		ssize_t size_read = 0;
		if ((size_read = getline(&lineptr, &line_length, stdin)) == -1) {
			perror("Could not read line.");
			continue;
		}

		// Strip newline.
		char* end = rindex(lineptr, '\n');
		*end = '\0';

		char* cmd[100];
		for (int i = 0; i < 100; ++i) {
			cmd[i] = NULL;
		}
		char* token = NULL;
		int i = 0;
		while ((token = strsep(&lineptr, " "))) {
			cmd[i] = token;
			i++;
		}

		pid_t pid = fork();

		// Child process
		if (pid == 0) {
			int res = execvp(cmd[0], cmd);
			if (res == -1) {
				perror("Could not execute");
			}
		}
		else {
			int status = 0;
			waitpid(pid, &status, 0);
		}

		free(lineptr);
	}

	return 0;
}
