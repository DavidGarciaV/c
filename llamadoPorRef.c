#include<stdio.h>

void Increment(int *p) /*El argumento de la funcion recibe la direccion de memoria a donde apunta el puntero*/
{
    *p = (*p) + 1;  /*Aquí estoy desreferenciado. A el valor que corresponde la dirección de memoria le estoy sumando 1*/
   /*Asumiendo que *p = 5 --> esta expresion equivale a 5 = 5 + 1;*/
}
