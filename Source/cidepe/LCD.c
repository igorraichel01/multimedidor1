///////////////////////////////////////////////////////////////////////////
////                             LCD.H                                 ////
////                 Driver para modulo LCD ITM1602                    ////
////         Define fun��es para inicializar, movimentar,              ////
////                escrever e ler caracteres.						   ////	
///////////////////////////////////////////////////////////////////////////  

#include "lcd.h"
#include "HdsLCD.h"
#include "MdlLcd.h"
#include <stdio.h>
#include <string.h>

#define LCD_CUSTOM_CHAR_MASK 0x07U

static BYTE lcd_normaliza_linha(BYTE y)
{
    if (y == 2)
    {
        return LCD_LINHA_2;
    }

    if (y > LCD_LINHA_2)
    {
        return LCD_LINHA_1;
    }

    return y;
}

static char lcd_get_char(BYTE x, BYTE y)
{
    BYTE linha = lcd_normaliza_linha(y);

    if (x == 0 || x > LCD_NUM_COLUNAS)
    {
        return ' ';
    }

    return lcdVirtualScreen[linha][x - 1];
}

///////////////////// instru��es de baixo n�vel


void lcd_send_nibble( BYTE n )
{
    LCD_WriteNibble((unsigned char)n, LCD_CHAR);
}

void lcd_send_byte( BYTE address, BYTE n )
 {
    LCD_WriteByte((unsigned char)n, address == 0 ? LCD_COMMAND : LCD_CHAR);
}



/////////////////////////////FUN��ES//////////////////////////////


////////////// inicializa LCD //////////////////////////
void lcd_init()
 {
    lcd_set_language(LCD_IDIOMA_PORTUGUES);
    Lcd.Init();
    Lcd.Update();
}


/////////////// posiciona cursor //////////////////////
void lcd_posicaoxy( BYTE x, BYTE y)
 {
  BYTE linha = lcd_normaliza_linha(y);
  Lcd.Setxy( x-1,linha);
}



int lcd_getdigito( BYTE x, BYTE y) 
{
   char value = lcd_get_char(x, y);
	int digito;

	switch (value) {

	    case '0':
			digito=0;
			break;
	
	    case '1':
			digito=1;
			break;

	    case '2':
			digito=2;
			break;

	    case '3':
			digito=3;
			break;
	    case '4':
			digito=4;
			break;
	    case '5':
			digito=5;
			break;
	    case '6':
			digito=6;
			break;
	    case '7':
			digito=7;
			break;
	    case '8':
			digito=8;
			break;
	    case '9':
			digito=9;
			break;
		default:digito=0;

	}

    return(digito);
}
/////////// esreve uma linha //////////////////
void lcd_escreve( char *c) 
{
   //lcd_send_byte(1,*c);
	 Lcd.Add(c);
	
}

///////////limpa LCD///////////////////
void lcd_limpa()           
{
   LCD_ClearScreen();
   Lcd.Write(LCD_LINHA_1, (char *)"");
   Lcd.Write(LCD_LINHA_2, (char *)"");
   Lcd.Setxy(0, LCD_LINHA_1);
   Lcd.Update();
}

/////////// posiciona na linha 2///////////////////
void lcd_linha2()          
{
   //lcd_posicaoxy(1,LCD_LINHA_2);
	 lcd_posicaoxy(1,LCD_LINHA_2);
}

/////////// posiciona na linha 1///////////////////
void lcd_linha1()          
{
   //lcd_posicaoxy(1,LCD_LINHA_1);
	 lcd_posicaoxy(1,LCD_LINHA_1);
}

/////////// escreve um d�gito de tempo ///////////////////
void lcd_escreve_digito(int digito)          
{

	switch (digito) {

	    case 0:
			lcd_escreve((char *)"0");
			break;
	
	    case 1:
			lcd_escreve((char *)"1");
			break;
	
	    case 2:
			lcd_escreve((char *)"2");
			break;
	
	    case 3:
			lcd_escreve((char *)"3");
			break;
	
	    case 4:
			lcd_escreve((char *)"4");
			break;
	
	    case 5:
			lcd_escreve((char *)"5");
			break;
	
	    case 6:
			lcd_escreve((char *)"6");
			break;
	
	    case 7:
			lcd_escreve((char *)"7");
			break;
	
	    case 8:
			lcd_escreve((char *)"8");
			break;
	
	    case 9:
        case 10: 
			lcd_escreve((char *)"9");
			break;
	}

}

long lcd_getDistancia()
{

	long k, c, d, u;
	long dist;

	k=lcd_getdigito( 5, 2);
	c=lcd_getdigito( 6, 2);
	d=lcd_getdigito( 7, 2);
	u=lcd_getdigito( 8, 2);
	

	dist=(long)(k*1000);
	dist=dist+(long)(c*100);
	dist=dist+(long)(d*10);
	dist=dist+(long)u;
	return(dist);
}

//###########################################################################
//###########################################################################
//Funcao especifica para receber o valor de massa - F12 - Energia cinetica
long lcd_getMassa()
{

	long k, c, d, u;
	long massa;

	k=lcd_getdigito( 4, 2);//O primeiro valor he o que fica a esquerda da virgula
	c=lcd_getdigito( 6, 2);
	d=lcd_getdigito( 7, 2);
	u=lcd_getdigito( 8, 2);


	//Composicao do valor final
	massa=(long)(k*1000);
	massa=massa+(long)(c*100);
	massa=massa+(long)(d*10);
	massa=massa+(long)u;

	return(massa);
}
//###########################################################################
//###########################################################################

void lcd_escreve_Dist(long dist){
	uint8 buflcd [10];
	
	/*
	uint8 k, c,d,u;
	uint8  dist_c;
	uint8 dist_d, dist_u;

	k=(dist/1000);
	dist_c=dist-(1000*k);
	c=(dist_c/100);
	dist_d=dist_c-(100*c);
	d=(dist_d/10);
	dist_u=dist_d-(10*d);
	u=dist_u;

	lcd_posicaoxy(5,LCD_LINHA_2);
	//lcd_escreve_digito((int)k);
	//lcd_escreve_digito((int)c);
	//lcd_escreve_digito((int)d);
	//lcd_escreve_digito((int)u);
	*/
	lcd_posicaoxy(5,LCD_LINHA_2);
	sprintf((char *)&buflcd,"%04lu",dist);
    lcd_escreve((char *)&buflcd);
	
	
/*
	if(FUNC==12)//Tentativa de diferenciar
	{
		lcd_posicaoxy(4,LCD_LINHA_2);
		lcd_escreve_digito((int)k);
		lcd_posicaoxy(6,LCD_LINHA_2);
		lcd_escreve_digito((int)c);
		lcd_escreve_digito((int)d);
		lcd_escreve_digito((int)u);
	}
	else
	{
		lcd_posicaoxy(5,LCD_LINHA_2);
		lcd_escreve_digito((int)k);
		lcd_escreve_digito((int)c);
		lcd_escreve_digito((int)d);
		lcd_escreve_digito((int)u);
	}
*/
}

//###########################################################################
//###########################################################################
void lcd_escreve_Massa(long massa)
{
   uint8 buflcd [10];
/*	
	long k, c, d, u;
	long massa_c;
	long massa_d, massa_u;

	k = (massa/1000);
	massa_c = massa - (1000 * k);
	c = (massa_c / 100);
	massa_d = massa_c - (100 * c);
	d = (massa_d / 10);
	massa_u = massa_d - (10 * d);
	u = massa_u;

	
	lcd_posicaoxy(6,LCD_LINHA_2);
	lcd_escreve_digito((int)c);
	lcd_escreve_digito((int)d);
	lcd_escreve_digito((int)u);

	lcd_posicaoxy(4,LCD_LINHA_2);//A posicao do digito (ou valor antes da virgula) possui um posicao diferenciada
	lcd_escreve_digito((int)k);
*/
   lcd_posicaoxy(4,LCD_LINHA_2);
   sprintf((char *)&buflcd,"%0.3f",(double)massa/1000);
   buflcd[1]=',';
   lcd_escreve((char *)&buflcd);

}
//###########################################################################
//###########################################################################

long lcd_getInt(){

	long d, u;
	long Interv;
	
	d=lcd_getdigito( 7, 2);
	u=lcd_getdigito( 8, 2);
	
	Interv=(long)(d*10);
	Interv=Interv+(long)u;
	return(Interv);
}
void lcd_escreve_Int(long interv){ 		//valores entre 1-> 99
	uint8 buflcd [10];
	/*
	long d, u;

	lcd_posicaoxy(7,LCD_LINHA_2);
	d=(interv/10);
	u=interv-(10*d);
	lcd_escreve_digito((int)d);
	lcd_escreve_digito((int)u);
 */
	lcd_posicaoxy(7,LCD_LINHA_2);
	sprintf((char *)&buflcd,"%02lu",interv);
  lcd_escreve((char *)&buflcd);
		
}


/*
void lcd_escreve_tempo(long tempo){
	
	int dk, k, c,d,u;
	long temp_k, temp_c;
	int temp_d, temp_u;

	dk=(int)(tempo/10000);
	temp_k=tempo-(10000*dk);
	k=(int)(temp_k/1000);
	temp_c=temp_k-(1000*k);
	c=(int)(temp_c/100);
	temp_d=temp_c-(100*c);
	d=(int)(temp_d/10);
	temp_u=temp_d-(10*d);
	u=(int)temp_u;
	
	lcd_escreve_digito(dk);
	lcd_escreve_digito(k);
	lcd_escreve(',');
	lcd_escreve_digito(c);
	lcd_escreve_digito(d);
	lcd_escreve_digito(u);

}
void lcd_escreve_tempo(double tempo){
	
	int dk, k, c,d,u,ud,uc;
	double temp_k, temp_c;
	long temp_d, temp_u;
	int temp_ud, temp_uc;

	dk=(int)(tempo/1000000);
	temp_k=tempo-(1000000*dk);
	k=(int)(temp_k/100000);
	temp_c=temp_k-(100000*k);
	c=(int)(temp_c/10000);
	temp_d=temp_c-(10000*c);
	d=(int)(temp_d/1000);
	temp_u=temp_d-(1000*d);
	u=(int)(temp_u/100);
	temp_ud=temp_u-(100*u);
	ud=(int)(temp_ud/10);
	temp_uc=temp_ud-(10*ud);
	uc=(int)temp_uc;
	

	lcd_escreve_digito(dk);
	lcd_escreve_digito(k);
	lcd_escreve(',');
	lcd_escreve_digito(c);
	lcd_escreve_digito(d);
	lcd_escreve_digito(u);
	lcd_escreve_digito(ud);
	lcd_escreve_digito(uc);

}*/


/*
 tempo 2 o valor em segundos
 tempo valor em ms 


*/

void lcd_escreve_tempo2(float ftempo){

  uint8 buflcd [15];
  uint16 uiDecimal= (uint16)ftempo;
  uint32 ulFracionario= (ftempo -uiDecimal)*100000; 

  sprintf((char *)&buflcd,"%02u,%05lu",uiDecimal,ulFracionario);
  lcd_escreve((char *)&buflcd);


}



void lcd_escreve_tempo(int32 tempo, int32 tempo2){


  uint8 buflcd [15];
	//sprintf((char *)&buflcd,"%02lu,%05lu",tempo2,tempo);
  //lcd_escreve((char *)&buflcd);

	int32 dk, k, c,d,u,ud,uc;
	int32 temp_k;
	int32 temp_u;
	int32 temp_ud, temp_uc;

	dk=(int32)(tempo2/100);
	temp_k=tempo2-(100*dk);
	k=(int32)(temp_k/10);
	c=(int32)temp_k-(10*k);
	
	d=(int32)(tempo/1000);
	temp_u=tempo-(1000*d);
	u=(int32)(temp_u/100);
	temp_ud=temp_u-(100*u);
	ud=(int32)(temp_ud/10);
	temp_uc=temp_ud-(10*ud);
	uc=(int32)temp_uc;
	
/*
	lcd_escreve_digito(dk);
	lcd_escreve_digito(k);
	lcd_escreve((char *)',');
	lcd_escreve_digito(c);
	lcd_escreve_digito(d);
	lcd_escreve_digito(u);
	lcd_escreve_digito(ud);
	lcd_escreve_digito(uc);
	*/
	
	buflcd[0]=dk+0x30;
	buflcd[1]=k+0x30;
	buflcd[2]=',';
	buflcd[3]=c+0x30;
	buflcd[4]=d+0x30;
	buflcd[5]=u+0x30;
	buflcd[6]=ud+0x30;
	buflcd[7]=uc+0x30;
	buflcd[8]=0;
	
lcd_escreve((char *)&buflcd);


}
void lcd_escreve_veloc(float veloc){
	uint8 buflcd [15];
	int c, d, u, dc, cc, m;
	float temp_d, temp_u;
	float temp_dc;
	int32 temp_dcI, temp_cc, temp_m;
	int32 aux;

	if(veloc>999){
		veloc=999;
	}
	
	//Se for negativa 
	if(veloc<0)
	   veloc*=-1;	
	
	
	aux=(int)(veloc/100);
	temp_d=(float)veloc-(100*aux);
	c=(int)(aux);

	aux=(int)(temp_d/10);
	temp_u=(float)temp_d-(10*aux);
	d=(int)(aux);
	u=(int)(temp_u);

	temp_dc=(float)veloc-(int32)(veloc);
	temp_dcI=(int32)(temp_dc*1000);
	aux=(int)(temp_dcI/100);
	temp_cc=(int32)temp_dcI-(aux*100);
	dc=(int)(aux);

	aux=(int)(temp_cc/10);
	temp_m=(int32)temp_cc-(aux*10);
	cc=(int)aux;
	m=(int)temp_m;
	
/*
	lcd_escreve_digito(c);
	lcd_escreve_digito(d);
	lcd_escreve_digito(u);
	lcd_escreve((char *)',');
	lcd_escreve_digito(dc);
	lcd_escreve_digito(cc);
	lcd_escreve_digito(m);
*/
  buflcd[0]=c+0x30;
	buflcd[1]=d+0x30;
	buflcd[2]=u+0x30;
	buflcd[3]=',';
	buflcd[4]=dc+0x30;
	buflcd[5]=cc+0x30;
	buflcd[6]=m+0x30;
	buflcd[7]=0;
	
lcd_escreve((char *)&buflcd);


}
int lcd_desloca_H(int posCursor, int _setaH){

	int tempSeta;

	tempSeta=_setaH+posCursor;
	if(tempSeta>8){
		posCursor=5;
	}else if (tempSeta<5){
		posCursor=8;
	}else{
		posCursor=tempSeta;
	}
	lcd_posicaoxy(posCursor,LCD_LINHA_2);

	return(posCursor);

}
int lcd_desloca_H2(int posCursor, int _setaH){

	int tempSeta;

	tempSeta=_setaH+posCursor;
	if(tempSeta>8){
		posCursor=7;
	}else if (tempSeta<7){
		posCursor=8;
	}else{
		posCursor=tempSeta;
	}
	lcd_posicaoxy(posCursor,LCD_LINHA_2);

	return(posCursor);

}

//###########################################################################
//###########################################################################
//
int lcd_desloca_H_massa(int posCursor, int _setaH)
{

	int tempSeta;

	tempSeta = _setaH + posCursor;

	if(tempSeta == 5)
	{
		if(posCursor == 4)
		{
			tempSeta = 6;//Pula para posicao 6 para nao ficar na virgula
						//Sentido esquerda-direita
		}
		else
		{
			tempSeta = 4;//Pula virgula
						//Sentido direta-esquerda
		}
	}

	if(tempSeta > 8)
	{
		posCursor = 4;

	}else if (tempSeta < 4)
	{
		posCursor = 8;

	}else
	{
		posCursor = tempSeta;
	}

	//lcd_posicaoxy(1,LCD_LINHA_2);
	//lcd_escreve_digito(posCursor);		//altera o digito

	lcd_posicaoxy(posCursor, 2);

	return(posCursor);

}
//###########################################################################
//###########################################################################
void lcd_atualiza_Dist(unsigned int _setaV, int posCursor)
{
	
	signed int tempSeta;
	char digito;
	
	digito = lcd_getdigito(posCursor, 2);
	lcd_posicaoxy(posCursor, LCD_LINHA_2);

	tempSeta = digito + _setaV;

	if(tempSeta > 9)
	{
		digito = 0;

	}else if (tempSeta < 0)
	{
		digito = 9;

	}else
	{
		digito = tempSeta;
	}
	
	lcd_escreve_digito(digito);		//altera o digito
	lcd_posicaoxy(posCursor,LCD_LINHA_2);

	
}
//###########################################################################
//###########################################################################
void lcd_atualiza_Massa(unsigned int _setaV, int posCursor)
{

	signed int tempSeta;
	char digito;
		
	digito = lcd_getdigito(posCursor, 2);

	lcd_posicaoxy(posCursor, 2);					

	tempSeta = digito + _setaV;

	if(tempSeta > 9)
	{
		digito = 0;

	}else if (tempSeta < 0)
	{
		digito = 9;
	}else
	{
		digito = tempSeta;
	}
	
	lcd_escreve_digito(digito);		//altera o digito			
	lcd_posicaoxy(posCursor, 2);					
}

//###########################################################################
//###########################################################################
void lcd_cursorBlack(int _posCursor)
{

	lcd_posicaoxy(_posCursor,LCD_LINHA_2);
	lcd_send_byte(1,0xFF);
	lcd_posicaoxy(_posCursor,LCD_LINHA_2);
}

void lcd_update(void)
{
    Lcd.Update();
}

void lcd_set_language(lcd_idioma_t idioma)
{
    LCD_SetLanguage(idioma);
    LCD_ClearCGRAM();
    Lcd.Update();
}

BYTE lcd_get_language(void)
{
    return (BYTE)LCD_GetLanguage();
}

void lcd_load_custom_char(BYTE posicao, const BYTE mapa[8])
{
    if (mapa == NULL)
    {
        return;
    }

    LCD_LoadCustomChar(posicao, (const char *)mapa);
}

void lcd_write_custom_char(BYTE posicao)
{
    lcd_send_byte(1, posicao & LCD_CUSTOM_CHAR_MASK);
}

//###########################################################################
//###########################################################################
