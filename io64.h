/**
 * Collection of functions to be used
 * from C to interact to IO ports
 */

#ifndef IO
#define IO

char inputb64(unsigned short port);
void outputb64(unsigned short port, unsigned char b);

#endif
