/**
 * Collection of functions to be used
 * from C to interact to IO ports
 */

#ifndef IO
#define IO

char inputb32(unsigned short port);
void outputb32(unsigned short port, unsigned char b);

#endif
