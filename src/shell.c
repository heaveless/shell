#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

int cmd_exit(char** args);

char* builtin_str[] = {
	"exit"
};

int (*builtin_func[])(char**) = {
	&cmd_exit
};

int cmd_exit(char** args) {
	return 0;
}

int num_builtins() {
	return sizeof(builtin_str) / sizeof(char*);
}

char* read_line(void) {
	int bufsize = RL_BUFSIZE;
	int position = 0;
	char* buffer = malloc(sizeof(char)* bufsize);
	int c;

	if (!buffer) {
		exit(EXIT_FAILURE);
	}

	while(1) {
		c = getchar();
		
		if (c == EOF) {
			exit(EXIT_SUCCESS);
		} else if (c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = c;
		}

		position++;

		if (position >= bufsize) {
			bufsize += RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) {
				exit(EXIT_FAILURE);
			}
		}
	}
}

char** split_line(char* line) {
	int bufsize = TOK_BUFSIZE,
			position = 0;

	char** tokens = malloc(bufsize * sizeof(char*));
	char* token,
		**tokens_backup;

	if (!tokens) {
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);
	if (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));

			if (!tokens) {
				free(tokens_backup);
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}

	tokens[position] = NULL;
	return tokens;
}

int execute(char** args) {
	int i;

	if (args[0] == NULL) {
		return 1;
	}

	for (i = 0; i < num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return 1;
}

void loop(void) {
	char* line;
	char** args;
	int status;

	do {
		printf("$ ");
		
		line = read_line();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while(status);
}

int main(int argc, char** argv) {
	loop();

	return EXIT_SUCCESS;
}
