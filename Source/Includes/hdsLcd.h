


#ifndef __HDS_LCD__
#define __HDS_LCD__

#include "InventTypes.h"
#include "specialchars.h"


#define bool  uint8_t 

//#include <type.h>

//#include "definitions.h"
//#include "dDAC.h"

#define LCD_COMMAND  ( true  )
#define LCD_CHAR     ( false )
#define LCD_DELAY      ( 50  )



#define LCD_NUM_BITS  4
#define LCD_SHIFT_CURSOR_RIGHT  (  1 )
#define LCD_SHIFT_CURSOR_LEFT   ( -1 )

enum { LCD_BKL_CTRL ,
        LCD_E_CTRL ,
        LCD_RS_CTRL ,
        LCD_RW_CTRL ,
        LCD_MAX_CTRL } ;

		
  #define LCD_LINE_SIZE          ( 16  ) + 1     /*!< N�mero m�ximo caracteres em uma linha  */
  #define LCD_LINE_COUNT          ( 2 )         /*!< N�mero de linhas definidas para cada tela  */
	#define LCD_LINE_1      ( 0x80 )
	#define LCD_LINE_2      ( 0xC0 )
	#define LCD_LINE_3      ( 0x94 )
	#define LCD_LINE_4      ( 0xD4 )        


#define LCD_NO_CURSOR           ( 0xff )


// posi��es de bits de controle >>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD_CTRL_GRP_FUNCTIONS       5
#define LCD_CTRL_IDX_INTERFACE       4
#define LCD_CTRL_IDX_LINHAS          3
#define LCD_CTRL_IDX_PIXELS          2


#define LCD_CTRL_GRP_MOVING          4
#define LCD_CTRL_IDX_SHIFT_WHAT      3
#define LCD_CTRL_IDX_SHIFT_DIR       2

#define LCD_CTRL_GRP_DISPLAY         3
#define LCD_CTRL_IDX_DISPLAY         2
#define LCD_CTRL_IDX_CURSOR          1
#define LCD_CTRL_IDX_BLINK_CURSOR    0

#define LCD_CTRL_GRP_CURSOR          2
#define LCD_CTRL_IDX_CURSOR_DIR      1
#define LCD_CTRL_IDX_SCROLL          0
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#define LCD_CURSOR_ON      1
#define LCD_CURSOR_OFF     0
#define LCD_CURSOR_RIGHT   1
#define LCD_CURSOR_LEFT    0
#define LCD_SHIFT_CURSOR   0
#define LCD_SHIFT_DISPLAY  1


// configura��es DEFAULT do LCD    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LCD_CONFIG_INTERFACE        (  0  )  /*!< Configura��o de interface (1 = 8bits 0 = 4bits)   */
#define LCD_CONFIG_LINHAS           (  1  )  /*!< Configura��o de linhas (1 = 2 linhas  | 0 = 1 linha)   */
#define LCD_CONFIG_PIXELS           (  0  )  /*!< Configura��o de pixels (1 = 5x10  | 0 = 5x7 )   */


#define LCD_CONFIG_DISPLAY          (  1  ) /*!< Configura��o de display (1 = ON  | 0 = OFF)   */
#define LCD_CONFIG_CURSOR           (  0  ) /*!< Configura��o de cursor (1 = ON  | 0 = OFF)   */
#define LCD_CONFIG_BLINK_CURSOR     (  1  ) /*!< Configura��o de pisca cursor (1 = ON  | 0 = OFF)   */

#define LCD_CONFIG_CURSOR_DIR       (  1  ) /*!< Deslocamento de cursor (1 = esq->dir  | 0 = dir->esq)   */
#define LCD_CONFIG_SCROLL           (  0  ) /*!< Fun��o scroll          (1 = ON  | 0 = OFF)   */
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// m�scaras de configura��o default:
#define LCD_CONFIG_GRP_FUNCTIONS    (1 << LCD_CTRL_GRP_FUNCTIONS) | ( LCD_CONFIG_INTERFACE << LCD_CTRL_IDX_INTERFACE) | (LCD_CONFIG_LINHAS << LCD_CTRL_IDX_LINHAS) | (LCD_CONFIG_PIXELS << LCD_CTRL_IDX_LINHAS)
#define LCD_CONFIG_GRP_DISPLAY      (1 << LCD_CTRL_GRP_DISPLAY) | ( LCD_CONFIG_DISPLAY      << LCD_CTRL_IDX_DISPLAY ) | ( LCD_CONFIG_CURSOR << LCD_CTRL_IDX_CURSOR ) |  ( LCD_CONFIG_BLINK_CURSOR << LCD_CTRL_IDX_BLINK_CURSOR )
#define LCD_CONFIG_GRP_CURSOR       ( 1 << LCD_CTRL_GRP_CURSOR) | (LCD_CONFIG_CURSOR_DIR << LCD_CTRL_IDX_CURSOR_DIR) | (LCD_CONFIG_SCROLL << LCD_CTRL_IDX_SCROLL)
#define LCD_CONFIG_CLEAR    ( 0x01 ) 


// m�scaras para outras configura��es:
#define LCD_CONFIG_GRP_CURSOR_ON             (1 << LCD_CTRL_GRP_DISPLAY) | ( LCD_CONFIG_DISPLAY      << LCD_CTRL_IDX_DISPLAY    ) | ( LCD_CURSOR_ON << LCD_CTRL_IDX_CURSOR ) |  ( LCD_CONFIG_BLINK_CURSOR << LCD_CTRL_IDX_BLINK_CURSOR )
#define LCD_CONFIG_GRP_CURSOR_OFF            (1 << LCD_CTRL_GRP_DISPLAY) | ( LCD_CONFIG_DISPLAY      << LCD_CTRL_IDX_DISPLAY    ) | ( LCD_CURSOR_OFF << LCD_CTRL_IDX_CURSOR ) |  ( LCD_CONFIG_BLINK_CURSOR << LCD_CTRL_IDX_BLINK_CURSOR )
#define LCD_CONFIG_GRP_CURSOR_GO_RIGHT       ( 1 << LCD_CTRL_GRP_MOVING  | (LCD_SHIFT_CURSOR         << LCD_CTRL_IDX_SHIFT_WHAT ) | ( LCD_CURSOR_RIGHT << LCD_CTRL_IDX_SHIFT_DIR  ) )
#define LCD_CONFIG_GRP_CURSOR_GO_LEFT        ( 1 << LCD_CTRL_GRP_MOVING  | (LCD_SHIFT_CURSOR         << LCD_CTRL_IDX_SHIFT_WHAT ) | ( LCD_CURSOR_LEFT << LCD_CTRL_IDX_SHIFT_DIR  ) )




extern char lcdVirtualScreen[LCD_LINE_COUNT][LCD_LINE_SIZE-1];

typedef enum
{
    LCD_LANGUAGE_PORTUGUESE = 0,
    LCD_LANGUAGE_ENGLISH    = 1,
    LCD_LANGUAGE_SPANISH    = 2
} ELcdLanguage;




void  LCD_WriteNibble( unsigned char input , bool command );
void  LCD_WriteByte( unsigned char input , bool command );
void  lcdHwInit( void );
void LCD_DelayUs(uint32_t ulValue);

void LCD_WriteString(unsigned short usPos, unsigned short usLine ,unsigned char ucSize, const char * pcDisplay);
void LCD_WriteSmartString(unsigned short usPos, unsigned short usLine , const char * pcDisplay);
void LCD_WriteDumbString(unsigned short usPos, unsigned short usLine , const char * pcDisplay, unsigned int sz);
void LCD_WriteRawString(unsigned short usPos, unsigned short usLine , const char * pcDisplay);
bool LCD_WriteWordBreakString( unsigned short usPos, unsigned short  usLine, const char * string );
void LCD_ClearCGRAM( void );
void LCD_ClearUnusedCGRAM( void );
void LCD_ClearScreen( void );
void LCD_HoldWhileBusy( void );
unsigned char LCD_GetCurrentPosition( void );

void LCD_CheckChars( void );



void LCD_PutCursor( unsigned short usRelPos );
void LCD_ClearCursor( void );
void LCD_WriteCGRam( unsigned short usPos , const char * deff );
void LCD_LoadCustomChar( unsigned short usPos , const char * deff );
char LCD_OperateChar ( char input );
bool LCD_IsBackLightOn( void );
void LCD_BackLightOn ( bool val );
unsigned char LCD_MakePosCommand( unsigned short usPos, unsigned short usLine );

void LCD_SetCursorPosition( unsigned short value );
unsigned char LCD_GetCursorPosition( void );


// defini��o de tipo special char usado internamente
typedef struct sSpecialChar
{
    unsigned char ascii;
    char * draw;
    unsigned char CGRamAddr;
    unsigned char usedFlag;
} sSpecialChar;

extern sSpecialChar lcdSpecialChars[];
extern unsigned int lcdSpecialCharCount;
extern unsigned char lcdCGRamCount;
extern sSpecialChar * lcdUsedSpecialChars[ CGRAM_SIZE ];

void LCD_SetLanguage(uint8_t ucLanguage);
uint8_t LCD_GetLanguage(void);

#define CH_BLACK_HEX '�'
#define CH_HALF_BLACK_HEX '�' /* 179 */
#define CH_HGLASS_1_HEX  '�' /* 182 */
#define CH_HGLASS_2_HEX  '�'  /* 175 */
#define CH_HGLASS_3_HEX  '' /* 155 */



#endif
