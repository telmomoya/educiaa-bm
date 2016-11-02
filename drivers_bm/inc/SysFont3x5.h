#ifndef SYSFONT3x5_H
#define SYSFONT3x5_H

#define SYSFONT3x5_WIDTH 3
#define SYSFONT3x5_HEIGHT 5

/*
 * added to allow fontname to match header file name.
 * as well as keep the old name for backward compability
 */

static const uint8_t SysFont3x5[]= {
    0x0, 0x0, // size of zero indicates fixed width font, actual length is width * height
    0x03, // width
    0x05, // height
    0x20, // first char
    0x60, // char count

    // Fixed width; char width table not used !!!!

    // font data

        0x00, 0x00, 0x00,                        // Code for char
        0x00, 0x17, 0x00,                        // Code for char !
        0x03, 0x00, 0x03,                        // Code for char "
        0x0A, 0x1F, 0x0A,                        // Code for char #
        0x14, 0x1F, 0x0A,                        // Code for char $
        0x09, 0x04, 0x12,                        // Code for char %
        0x0A, 0x15, 0x0A,                        // Code for char &
        0x00, 0x03, 0x00,                        // Code for char '
        0x0E, 0x11, 0x00,                        // Code for char (
        0x00, 0x11, 0x0E,                        // Code for char )
		0x00, 0x03, 0x03,                        // Code for char º
        0x08, 0x1C, 0x08,                        // Code for char +
        0x10, 0x08, 0x00,                        // Code for char ,
        0x08, 0x08, 0x08,                        // Code for char -
		0x00, 0x10, 0x00,                         // Code for char .
        0x10, 0x08, 0x04,                        // Code for char /
        0x1F, 0x11, 0x1F,                        // Code for char 0
        0x12, 0x1F, 0x10,                        // Code for char 1
        0x1D, 0x15, 0x17,                        // Code for char 2
        0x15, 0x15, 0x1F,                        // Code for char 3
        0x07, 0x04, 0x1F,                        // Code for char 4
        0x17, 0x15, 0x1D,                        // Code for char 5
        0x1F, 0x15, 0x1D,                        // Code for char 6
        0x01, 0x05, 0x1F,                        // Code for char 7
        0x1F, 0x15, 0x1F,                        // Code for char 8
        0x07, 0x05, 0x1F,                        // Code for char 9
        0x00, 0x14, 0x00,                        // Code for char :
        0x10, 0x0A, 0x00,                        // Code for char ;
        0x04, 0x0A, 0x11,                        // Code for char <
        0x14, 0x14, 0x14,                        // Code for char =
        0x11, 0x0A, 0x04,                        // Code for char >
        0x02, 0x19, 0x06,                        // Code for char ?
        0x0E, 0x15, 0x12,                        // Code for char @
        0x1F, 0x05, 0x1F,                        // Code for char A
        0x1F, 0x15, 0x1F,                        // Code for char B
        0x1F, 0x11, 0x11,                        // Code for char C
        0x1F, 0x11, 0x0E,                        // Code for char D
        0x1F, 0x15, 0x15,                        // Code for char E
        0x1F, 0x05, 0x01,                        // Code for char F
        0x1F, 0x15, 0x1D,                        // Code for char G
        0x1F, 0x04, 0x1F,                        // Code for char H
        0x11, 0x1F, 0x11,                        // Code for char I
        0x18, 0x10, 0x1F,                        // Code for char J
        0x1F, 0x08, 0x14,                        // Code for char K
        0x1F, 0x10, 0x10,                        // Code for char L
        0x1F, 0x02, 0x1F,                        // Code for char M
        0x1F, 0x02, 0x1F,                        // Code for char N
        0x1F, 0x11, 0x1F,                        // Code for char O
        0x1F, 0x05, 0x07,                        // Code for char P
        0x0F, 0x09, 0x1F,                        // Code for char Q
        0x1F, 0x09, 0x16,                        // Code for char R
        0x17, 0x15, 0x1D,                        // Code for char S
        0x01, 0x1F, 0x01,                        // Code for char T
        0x1F, 0x10, 0x1F,                        // Code for char U
        0x0E, 0x18, 0x0E,                        // Code for char V
        0x0E, 0x1C, 0x0E,                        // Code for char W
        0x1B, 0x04, 0x1B,                        // Code for char X
        0x03, 0x1C, 0x03,                        // Code for char Y
        0x19, 0x15, 0x13,                        // Code for char Z
        0x1F, 0x11, 0x00,                        // Code for char [
        0x04, 0x08, 0x10,                        // Code for char BackSlash
        0x00, 0x11, 0x1F,                        // Code for char ]
        0x02, 0x01, 0x02,                        // Code for char ^
        0x10, 0x10, 0x10,                        // Code for char _
        0x01, 0x02, 0x00,                        // Code for char `
        0x1D, 0x15, 0x1E,                        // Code for char a
        0x1F, 0x14, 0x08,                        // Code for char b
        0x0E, 0x11, 0x11,                        // Code for char c
        0x1C, 0x14, 0x1F,                        // Code for char d
        0x1F, 0x15, 0x17,                        // Code for char e
        0x1E, 0x05, 0x00,                        // Code for char f
        0x12, 0x15, 0x1F,                        // Code for char g
        0x1F, 0x04, 0x18,                        // Code for char h
        0x00, 0x1D, 0x00,                        // Code for char i
        0x18, 0x10, 0x1D,                        // Code for char j
        0x1F, 0x08, 0x14,                        // Code for char k
        0x00, 0x1F, 0x00,                        // Code for char l
        0x1F, 0x01, 0x1F,                        // Code for char m
        0x1F, 0x01, 0x1F,                        // Code for char n
        0x0E, 0x11, 0x0E,                        // Code for char o
        0x1F, 0x05, 0x02,                        // Code for char p
        0x02, 0x05, 0x1F,                        // Code for char q
        0x1F, 0x01, 0x01,                        // Code for char r
        0x16, 0x15, 0x0D,                        // Code for char s
        0x02, 0x1F, 0x12,                        // Code for char t
        0x0E, 0x08, 0x1E,                        // Code for char u
        0x0E, 0x18, 0x0E,                        // Code for char v
        0x06, 0x18, 0x06,                        // Code for char w
        0x1A, 0x04, 0x1A,                        // Code for char x
        0x03, 0x04, 0x1F,                        // Code for char y
        0x09, 0x15, 0x12,                        // Code for char z
        0x04, 0x1F, 0x11,                        // Code for char {
        0x00, 0x1F, 0x00,                        // Code for char |
        0x11, 0x1F, 0x04,                        // Code for char }
        0x0C, 0x04, 0x06,                        // Code for char ~
        0x03, 0x03, 0x00                         // Code for char 
};

#endif
