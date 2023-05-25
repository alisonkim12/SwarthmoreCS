// Some practice with strings and chars, and string library
// functions, and ctype library functions.
// (newhall, 2015)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {

 char *copy, *str, *substr;
 int i, len;

  str = readline("Enter a line: ");
  if(!str) {
    printf("Error readline failed\n");
    exit(1);
  }


  // let's print out some information about this string:
  len = strlen(str);
  printf("str %s is %d chars long\n", str, len);

  // make a copy of the string:
  // (1) allocate space for it (remember space for ending '\0')
  copy = malloc(sizeof(char)*(len+1));
  if(!copy) {
    printf("Error malloc failed\n");
    exit(1);
  }
  // (2) call strcpy (or strncpy for up to n chars of the string)
  strcpy(copy, str);

  printf("copy:%s at addr 0x%p   str:%s at addr 0x%p\n",
      copy, copy, str, str);

  // now let's print out substrings using the substr ptr
  for(i=0; i < len; i++) {
    substr = &(str[i]);
    printf("%s\n", substr);
  }

  // now let's print out some information about characters in the string:
  // try running this program for input lines with and without leading
  // whitespace and see what is printed out
  for(i=0; i < len; i++) {
    if(isalnum(str[i])) {
       printf("str[%d] = #%c# is alpha or num\n", i, str[i]);
    } else if(isspace(str[i])) {
       printf("str[%d] = #%c# is whitespace\n", i, str[i]);
    }
  }

  // TODO:
  // next, try creating substring that is the first token in str
  // (the idea is to make substr point to the first character of the
  // token, and to add a '\0' character at the end of the first token
  // in the str string)

  

   // then call printf to print out substr to see if it worked
  // printf("%s\n", substr);



  // when using readline, need to explicity free the string
  // it returns
  free(str);

  return 0;
}
