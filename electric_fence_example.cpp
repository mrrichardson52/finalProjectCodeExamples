   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   int main()
   {
       char *string;
       string = (char *)malloc(sizeof(char)*5);
       strcpy(string,"The is more than 5 bytes");
       printf("%s",string);
       return 0;
   }