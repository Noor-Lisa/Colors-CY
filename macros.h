#ifndef __MACROS_H
#define __MACROS_H

// Valeur absolue
#define ABS(x) (((x) < 0)? -(x) : (x))      
#define MAX(a, b) (((a) > (b))? (a) : (b))
// Maximum entre a et b

// Calcule la taille d un tableau en nombre d elements.
#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(*array))


#endif  // __MACROS_H