#ifndef __SPECIAL_CHARS__
#define __SPECIAL_CHARS__

#define _X_ 1
#define ___ 0
#define CONCAT( b4,b3,b2,b1,b0 )  b4 << 4 | b3 << 3 | b2 << 2 | b1 << 1  | b0

#define CHAR_HEIGHT 8
#define CGRAM_SIZE 8
#define CGRAM_START_ADDR 0x40
#define CGRAM_NO_ADDR 0xFF

#define SPECIAL_CHAR_UNUSED  0x00
#define SPECIAL_CHAR_USED    0x01

#define HAS_LCD_DISPLAY  1

#define LCD_CHAR_A_GRAVE        ((char)0xC0)
#define LCD_CHAR_A_ACUTE        ((char)0xC1)
#define LCD_CHAR_A_CIRCUMFLEX   ((char)0xC2)
#define LCD_CHAR_A_TILDE        ((char)0xC3)
#define LCD_CHAR_C_CEDILLA      ((char)0xC7)
#define LCD_CHAR_E_ACUTE        ((char)0xC9)
#define LCD_CHAR_E_CIRCUMFLEX   ((char)0xCA)
#define LCD_CHAR_I_ACUTE        ((char)0xCD)
#define LCD_CHAR_N_TILDE        ((char)0xD1)
#define LCD_CHAR_O_ACUTE        ((char)0xD3)
#define LCD_CHAR_O_CIRCUMFLEX   ((char)0xD4)
#define LCD_CHAR_O_TILDE        ((char)0xD5)
#define LCD_CHAR_U_ACUTE        ((char)0xDA)
#define LCD_CHAR_U_DIAERESIS    ((char)0xDC)
#define LCD_CHAR_INVERTED_QMARK ((char)0xBF)
#define LCD_CHAR_INVERTED_EMARK ((char)0xA1)
#define LCD_CHAR_a_ACUTE        ((char)0xE1)
#define LCD_CHAR_a_TILDE        ((char)0xE3)
#define LCD_CHAR_c_CEDILLA      ((char)0xE7)
#define LCD_CHAR_e_ACUTE        ((char)0xE9)
#define LCD_CHAR_i_ACUTE        ((char)0xED)
#define LCD_CHAR_n_TILDE        ((char)0xF1)
#define LCD_CHAR_o_ACUTE        ((char)0xF3)
#define LCD_CHAR_o_TILDE        ((char)0xF5)
#define LCD_CHAR_u_ACUTE        ((char)0xFA)
#define LCD_CHAR_u_DIAERESIS    ((char)0xFC)

#endif
