#ifndef TEST_IMAGE_H
#define TEST_IMAGE_H

extern unsigned char smiley[8][8];
extern unsigned char half_smiley[64];
extern unsigned char smiley_flat[64];
extern unsigned char blank[8][8];

unsigned char *test_slash();
unsigned char *test_backslash();
unsigned char *test_pipe();
unsigned char *test_dot();
unsigned char *test_comma();
unsigned char *test_dollar();

#endif
