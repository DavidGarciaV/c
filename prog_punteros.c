/*strlen: return length of string s*/

int strlen(char *s)
{
    int n;

    for(n = 0; *s != '\0'; s++) /*puedo incrementar s porque es un puntero*/
        n++;
    return n;
}
