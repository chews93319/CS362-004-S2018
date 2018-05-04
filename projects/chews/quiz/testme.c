#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<time.h>

char inputChar()
{
	char c;
	char* source = "[({abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ})]";
	int r;

	r = random() % 59;
	c = source[r];
	
	return c;
}

char *inputString()
{
	char c;
	char* source = "abcdefghijklmnopqrstuvwxyz";
	int r, i;
	char* s;
	
	
	r = random() % 26;
	s = (char*) malloc(6*sizeof(char));
	
	for (i=0; i < 6; i++)
	{
		r = random() % 26;
		c = source[r];
		s[i]=c;
	}
	
	s[6] = '\0';
	
	return s;
}

void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;

	while (1)
	{
	  tcCount++;
	  c = inputChar();
	  s = inputString();
	  printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

	  if (c == '[' && state == 0) state = 1;
	  if (c == '(' && state == 1) state = 2;
	  if (c == '{' && state == 2) state = 3;
	  if (c == ' ' && state == 3) state = 4;
	  if (c == 'a' && state == 4) state = 5;
	  if (c == 'x' && state == 5) state = 6;
	  if (c == '}' && state == 6) state = 7;
	  if (c == ')' && state == 7) state = 8;
	  if (c == ']' && state == 8) state = 9;
	  if (s[0] == 'r' && s[1] == 'e'
		&& s[2] == 's' && s[3] == 'e'
		&& s[4] == 't' && s[5] == '\0'
		&& state == 9)
	  {
	    printf("error\n");
	    exit(200);
	  }
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}






