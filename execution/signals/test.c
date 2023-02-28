#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>

// void int_handler(int status) {
//     printf("\n"); // Move to a new line
//     rl_on_new_line(); // Regenerate the prompt on a newline
//     rl_replace_line("", 0); // Clear the previous text
//     rl_redisplay();
// }

int main(void)
{
	char			str[10];
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	printf("%lu\n", term.c_lflag);
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	scanf("%s", str);
	printf("%s\n", str);
	return (0);
}