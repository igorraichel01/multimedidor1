#include "LCD.h"
#include "MdlLcd.h"
#include "HdsMux.h"
#include "MdlMSG.h"
#include <stdio.h>
#include <string.h>

//int centmili;
//int decmili;
//int mili;
//int centi;
//int deci;
//int sec;
//int decisec;
float fTimeruS;


int IDIOMA;							// define o idioma 1-Port   2-Eng   3-Spa


void msg_atualizaTimer(){

  lcd_posicaoxy(3,LCD_LINHA_1);
  uint8 buflcd [15];
  float fTimeInSeconds=fTimeruS/1000000;
  uint16 uiDecimal= (uint16)fTimeInSeconds;
  uint32 ulFracionario= (fTimeInSeconds -uiDecimal)*100000; 

  sprintf((char *)&buflcd,"%02u,%05lu",uiDecimal,ulFracionario);
  lcd_escreve((char *)&buflcd);


	
}

void msg_zeraTimer(){
    fTimeruS=0;
}



// TELAS DE MENSAGENS


//***** TELAS INICIAIS*********
void telaInicial_1()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG1);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG2);
}

void telaInicial_2()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG3[IDIOMA-1][0]);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG4[IDIOMA-1][0]);
}


//**********************************************
// ********** TELAS DE ESTADOS *****************


void tela0()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG0_1[IDIOMA-1][0]);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG0_2[IDIOMA-1][0]);
}


/*   {"<     ok     >"}   */

void tela1_2()
{
	 Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR__OK__MAIOR);
	
}

void tela1()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG1_1[IDIOMA-1][0]);
	tela1_2();
}


void tela2()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG2_1);
	tela1_2();
}


void tela3(){
 Lcd.Write(LCD_LINHA_1, (char *)&MSG3_1[IDIOMA-1][0]);
 tela1_2();
}

void tela4()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG4_1[IDIOMA-1][0]);
  tela1_2();
}

	
void tela5()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG5_1[IDIOMA-1][0]);
  tela1_2();
	}

	
void tela6()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG6_1[IDIOMA-1][0]);
  tela1_2();
	}

void tela7()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG7_1[IDIOMA-1][0]);
  tela1_2();
}
	
void tela8()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG8_1[IDIOMA-1][0]);
  tela1_2();
	}

	
void tela9()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG9_1);
		tela1_2();
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG9_1);
		tela1_2();
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG9_1);
		tela1_2();
	}	

}
void tela10()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG10_1);
		tela1_2();
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG10_1);
		tela1_2();
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG10_1);
		tela1_2();
	}	
}
void tela11()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG11_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG11_2[IDIOMA-1][0]);
	
}

void tela12()
{
		Lcd.Write(LCD_LINHA_1, (char *)&MSG12_1[IDIOMA-1][0]);
	  Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 
/*	
	if (IDIOMA==1){
		lcd_linha2();
		//lcd_escreve((char *)&MSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2a);
	}else if(IDIOMA==2){ 
		lcd_linha2();
		//lcd_escreve((char *)&IMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&IMSG12_2a);
	}else if(IDIOMA==3){
		lcd_linha2();
		//lcd_escreve((char *)&SMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&SMSG12_2a);
	}
*/	
}

void tela13()
{
	 	Lcd.Write(LCD_LINHA_1, (char *)&MSG13_1[IDIOMA-1][0]);
	  Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 
	
/*	
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG13_1);
		lcd_linha2();
	//	lcd_escreve((char *)&MSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2a);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG13_1);
		lcd_linha2();
		//lcd_escreve((char *)&IMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&IMSG12_2a);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG13_1);
		lcd_linha2();
	//	lcd_escreve((char *)&SMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&SMSG12_2a);
	}
*/	
	
}

void tela14()
{

	Lcd.Write(LCD_LINHA_1, (char *)&MSG14_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 
}

void tela15()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG15_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 
}
void tela17()
{
		Lcd.Write(LCD_LINHA_1, (char *)&MSG17_1[IDIOMA-1][0]);
	  Lcd.Write(LCD_LINHA_2, (char *)&MSG17_2); 
}

void tela21()
{
		Lcd.Write(LCD_LINHA_1, (char *)&MSG21_1[IDIOMA-1][0]);
	  Lcd.Write(LCD_LINHA_2, (char *)&MSG11_2[IDIOMA-1][0]);
}

void tela22()
{
	
		Lcd.Write(LCD_LINHA_1, (char *)&MSG22_1[IDIOMA-1][0]);
	  Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 

}


void tela52()
{
	
	Lcd.Write(LCD_LINHA_1, (char *)&MSG52_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 
/*	
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG52_1);
		lcd_linha2();
		//lcd_escreve((char *)&MSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2a);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG52_1);
		lcd_linha2();
		//lcd_escreve((char *)&IMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&IMSG12_2a);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG52_1);
		lcd_linha2();
	//	lcd_escreve((char *)&SMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&SMSG12_2a);
	}
 */

}


void tela72()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG72_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG72_2); 
}

void tela92()
{
	
	Lcd.Write(LCD_LINHA_1, (char *)&MSG92_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___mm____OK); 
/*	
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG92_1);
		lcd_linha2();
	//	lcd_escreve((char *)&MSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2a);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG92_1);
		lcd_linha2();
	//	lcd_escreve((char *)&IMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&IMSG12_2a);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG92_1);
		lcd_linha2();
	//	lcd_escreve((char *)&SMSG12_2);
		lcd_escreve((char *)&"<   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&SMSG12_2a);
	}
*/
}





void tela99()
{
	
	Lcd.Write(LCD_LINHA_1, (char *)&MSG99_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG________________OK); 
/*	
	
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG99_1);
		lcd_linha2();
		lcd_escreve((char *)&"      ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG99_2);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG99_1);
		lcd_linha2();
		lcd_escreve((char *)&"      ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&IMSG99_2);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG99_1);
		lcd_linha2();
		lcd_escreve((char *)&"      ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&SMSG99_2);
	}
*/	
	
	
}
void tela100()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG100_1[IDIOMA-1][0]);
	Lcd.Write(LCD_LINHA_2, (char *)&MSG100_2[IDIOMA-1][0]);
	
}


void tela102()
{
    
    Lcd.Write(LCD_LINHA_1, (char *)&MSG102_1); 
    msg_atualizaTimer();
  
	Lcd.Write(LCD_LINHA_2, (char *)&MSG100_2[IDIOMA-1][0]);
	
}

void tela106()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG106_1[IDIOMA-1][0]);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG106_2[IDIOMA-1][0]);
}

void Salvar_usb()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG106_1[IDIOMA-1][0]);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG_SALVAR_USB[IDIOMA-1][0]);
}

   

void tela110()
{
	 Lcd.Write(LCD_LINHA_1, (char *)&MSG110_1[IDIOMA-1][0]);
     Lcd.Write(LCD_LINHA_2, (char *)&MSG110_2[IDIOMA-1][0]);
    
}

void tela111()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG110_1[IDIOMA-1][0]);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG111_2[IDIOMA-1][0]);
}
// mostra tempos

void tela149()
{
	  Lcd.Write(LCD_LINHA_1, (char *)&MSG102_1); 
	  Lcd.Write(LCD_LINHA_2, (char *)&MSG_OK);
/*	
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG102_1);
		Lcd.Write(LCD_LINHA_2, (char *)&MSG_OK);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG102_1);
		Lcd.Write(LCD_LINHA_2, (char *)&MSG_OK);
		
		
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG102_1);
		Lcd.Write(LCD_LINHA_2, (char *)&MSG_OK);;
	}
 */	
}


void tela150()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG150_1);
		tela1_2();
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG150_1);
		tela1_2();
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG150_1);
		tela1_2();
	}
}
void tela151()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG151_1);
		tela1_2();
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG151_1);
		tela1_2();
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG151_1);
		tela1_2();
	}
	lcd_linha1();
	lcd_escreve((char *)&MSG151_1);
}
void tela152()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG152_1);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG152_1);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG152_1);
	}
}
void tela153()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG153_1);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG153_1);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG153_1);
	}
}
void tela154()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG154_1);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG154_1);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG154_1);
	}
}
void tela155()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG155_1);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG155_1);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG155_1);
	}
}
void tela156()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG156_1);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG156_1);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG156_1);
	}
}


// mostra velocidades
void tela169()
{
	
	 Lcd.Write(LCD_LINHA_1, (char *)&MSG170_1); 
	 Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR__OK__MAIOR); 
	
	
}
void tela170()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG170_1); 
	tela1_2();
	
}
void tela171()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG171_1); 

}
void tela172()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG172_1);
	
	

}
void tela173()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG173_1);
}

void tela174()
{
	
	Lcd.Write(LCD_LINHA_1, (char *)&MSG174_1);
	
	
}
void tela175()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG175_1);
		
}
void tela176()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG176_1);
}



void tela240()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG240_1);
		lcd_linha2();
		lcd_escreve((char *)&MSG240_2);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG240_1);
		lcd_linha2();
		lcd_escreve((char *)&IMSG240_2);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG240_1);
		lcd_linha2();
		lcd_escreve((char *)&SMSG240_2);
	}
}


void tela241()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG240_3);
		lcd_linha2();
		lcd_escreve((char *)&MSG240_4);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG240_3);
		lcd_linha2();
		lcd_escreve((char *)&IMSG240_4);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_linha1();
		lcd_escreve((char *)&SMSG240_3);
		lcd_linha2();
		lcd_escreve((char *)&SMSG240_4);
	}
}





void tela250()
{
	
	Lcd.Write(LCD_LINHA_1, (char *)&MSG250_1);
	tela1_2();
}


void tela251()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG251_1);
	tela1_2();
}

void tela350()
{
	tela1_2();
}

void tela410()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG110_1[IDIOMA-1][0]);
  Lcd.Write(LCD_LINHA_2, (char *)&MSG410_2[IDIOMA-1][0]);
}

void tela450()
{
	tela1_2();
}

void tela470()
{
	tela1_2();
}
/* mesma tela250
void tela550()
{
	lcd_linha1();
	lcd_escreve((char *)&MSG550_1);
	lcd_linha2();
	lcd_escreve((char *)&MSG1_2a);
	lcd_escreve((char *)&MSG1_2);
	lcd_escreve((char *)&MSG1_2b);
} mesma 251
void tela551()
{
	lcd_linha1();
	lcd_escreve((char *)&MSG551_1);
	lcd_linha2();
	lcd_escreve((char *)&MSG1_2a);
	lcd_escreve((char *)&MSG1_2);
	lcd_escreve((char *)&MSG1_2b);
}*/
void tela552()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG552_1);
	tela1_2();
	
	
}
void tela553()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSG553_1);
	tela1_2();
}


void tela702()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG102_1); 
    
    lcd_posicaoxy(3,LCD_LINHA_1);

	    msg_atualizaTimer();
		//lcd_escreve_digito(decisec);
		//lcd_escreve_digito(sec);
        lcd_posicaoxy(7,LCD_LINHA_1);
		//lcd_escreve((char *)",");
		//lcd_escreve_digito(deci);
		lcd_escreve((char *)&" S0"); 
		lcd_posicaoxy(12,LCD_LINHA_1);
		lcd_escreve((char *)&" S1>"); 
		
		Lcd.Write(LCD_LINHA_2, (char *)&MSG100_2[IDIOMA-1][0]);
	
	
}
void tela710()
{
    Lcd.Write(LCD_LINHA_1, (char *)&MSG110_1[IDIOMA-1][0]);
    Lcd.Write(LCD_LINHA_2, (char *)&MSG710_2[IDIOMA-1][0]);
 
}
void tela750()
{
      Lcd.Write(LCD_LINHA_1, (char *)&MSG102_1); 
        
		//lcd_posicaoxy(11,LCD_LINHA_1);
		lcd_posicaoxy(12,LCD_LINHA_1);//Deixado um espaco
							//entre [unidade] e a proxima
							//mensagem
		//lcd_escreve((char *)&" S0>");//Comando anterior
		lcd_escreve((char *)&"S0>");
		tela1_2();
   
    
}
void tela751()
{
      Lcd.Write(LCD_LINHA_1, (char *)&MSG102_1); 
    
    
		lcd_posicaoxy(12,LCD_LINHA_1);//Deixado um espaco
							//entre [unidade] e a proxima
							//mensagem
		//lcd_escreve((char *)&" S0<");
		lcd_escreve((char *)&"S0<");
		tela1_2();
}
void tela770()
{
      Lcd.Write(LCD_LINHA_1, (char *)&MSG102_1); 
      //lcd_posicaoxy(11,LCD_LINHA_1);//Altera identica a feita na
							//tela 750
		lcd_posicaoxy(12,LCD_LINHA_1);
		//lcd_escreve((char *)&" S1>");
		lcd_escreve((char *)&"S1>");
		tela1_2();
	
}

void tela900()
{
   	Lcd.Write(LCD_LINHA_1, (char *)&MSG900_1[IDIOMA-1][0]);
    tela1_2();
 	
}
void tela902()
{
    Lcd.Write(LCD_LINHA_2, (char *)&MSG902_2[IDIOMA-1][0]);
}

void tela990()
{
	Lcd.Write(LCD_LINHA_1, (char *)&MSGL_0);
	Lcd.Write(LCD_LINHA_2, (char *)&MSGL_1);
}

void tela1012()
{
    
   Lcd.Write(LCD_LINHA_1, (char *)&MSG1012_1[IDIOMA-1][0]);
   tela1_2();
	
}

void tela1021()
{
	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG1021_1);
		lcd_linha2();
		lcd_escreve((char *)&MSG12_2);
		lcd_escreve((char *)&"   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2a);
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG1021_1);
		lcd_linha2();
		lcd_escreve((char *)&IMSG12_2);
		lcd_escreve((char *)&"   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&IMSG12_2a);
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG1021_1);
		lcd_linha2();
		lcd_escreve((char *)&SMSG12_2);
		lcd_escreve((char *)&"   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&SMSG12_2a);
	}

}
//F12 - Energia Cinetica
//dados sobre a massa
void tela1022()
{

   Lcd.Write(LCD_LINHA_1, (char *)&MSG1022_1[IDIOMA-1][0]);
   Lcd.Write(LCD_LINHA_2, (char *)&MSG__MENOR___Kg____OK);


/*

	if (IDIOMA==1){
		lcd_linha1();
		lcd_escreve((char *)&MSG1022_1);
		lcd_linha2();
		lcd_escreve((char *)&MSG12_2);
		lcd_escreve((char *)&"  ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2b);	// Tela padrao para unidade de massa
		//Adcionado a virgula especifica para F12 - valor da massa
		//Fabio Bairros - 24/01/2014
		lcd_posicaoxy(5,LCD_LINHA_2);
		lcd_escreve((char *)",");		//Posciona a virgula
	}else if(IDIOMA==2){
		lcd_linha1();
		lcd_escreve((char *)&IMSG1022_1);
		lcd_linha2();
		lcd_escreve((char *)&IMSG12_2);
		lcd_escreve((char *)&"   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2b);
		//Adcionado a virgula especifica para F12 - valor da massa
		//Fabio Bairros - 24/01/2014
		lcd_posicaoxy(5,LCD_LINHA_2);
		lcd_escreve((char *)',');		//Posciona a virgula
	}else if(IDIOMA==3){
		lcd_linha1();
		lcd_escreve((char *)&SMSG1022_1);
		lcd_linha2();
		lcd_escreve((char *)&SMSG12_2);
		lcd_escreve((char *)&"   ");
		lcd_posicaoxy(9,LCD_LINHA_2);
		lcd_escreve((char *)&MSG12_2b);
		//Adcionado a virgula especifica para F12 - valor da massa
		//Fabio Bairros - 24/01/2014
		lcd_posicaoxy(5,LCD_LINHA_2);
		lcd_escreve((char *)',');		//Posciona a virgula
	}
*/

}

void tela1253()
{
     Lcd.Write(LCD_LINHA_1, (char *)&MSG1253_1);
     tela1_2();
}



void telaDebug()
{
	
	lcd_linha1();
	lcd_escreve((char *)&MSGDEBUG_1);
	lcd_linha2();
	lcd_escreve((char *)&MSGDEBUG_2);
	
}



void telaUsbIn()
{
  Lcd.Write(LCD_LINHA_1, (char *)&MSG_USB[IDIOMA-1][0]);
  Lcd.Write(LCD_LINHA_2, (char *)&MSG_USB_IN[IDIOMA-1][0]);

  Lcd.Update();
  MuxTimers.Delayms(1000);

}

void telaUsbOut()
{
  Lcd.Write(LCD_LINHA_1, (char *)&MSG_USB[IDIOMA-1][0]);
  Lcd.Write(LCD_LINHA_2, (char *)&MSG_USB_OUT[IDIOMA-1][0]);

  Lcd.Update();
  MuxTimers.Delayms(1000);
}
