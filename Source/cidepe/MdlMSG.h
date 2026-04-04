#ifndef __HDS_MSG__
#define __HDS_MSG__

#include "InventTypes.h"



typedef enum{
	
 eEstadoTelaInicio,
 eEstadoTelaIdioma, 		
 eEstadoEscolheTeste,  //Sensor digital ou Sensor Analógico	
 eEstadoExecutaDigital,
 eEstadoExecutaAnalog,	
}eEstadoInicio;



// Mensagens Gerais
 const char MSG1[17]   = {" *** CIDEPE *** "};
 const char MSG2[17]   = {" EQ228E  vy.13  "};

// tela L
 const char MSGL_0[17] = {" IDIOMA/LANGUAGE"};
 const char MSGL_1[17] = {"Port  Eng   Esp "};

						   
 //??const char MSG3[17]   = {"** CRONOMETRO **"};
  //??const char IMSG3[17]   = {"MULTIFUNCTIONAL "};
  //??const char SMSG3[17]   = {"** CRONOMETRO **"};

  //??const char MSG4[17]   = {" MULTIFUNCIONAL "};
  //??const char IMSG4[17]   = {"    TIMER       "};
  //??const char SMSG4[17]   = {" MULTIFUNCTIONAL"}; 
 const char MSG3[3][17]   = {{"** CRONOMETRO **"}, {"MULTIFUNCTIONAL "},{"** CRONOMETRO **"} };
 const char MSG4[3][17]   = {{" MULTIFUNCIONAL "}, {"    TIMER       "},{" MULTIFUNCTIONAL"} };
 
 
// tela 0
//?? const char MSG0_1[17] = {"ESCOLHA A FUNCAO"};
//?? const char MSG0_2[17] = {"funcao     ajuda"};
//?? const char IMSG0_1[17] = {" SELECT FUNCTION"};
 //??const char IMSG0_2[17] = {"Function    help"};
//?? const char SMSG0_1[17] = {"ESCOJA   FUNCION"};
//?? const char SMSG0_2[17] = {"Funcion    ayuda"};
					     //1         //240
 const char MSG0_1[3][17]   = {{"ESCOLHA A FUNCAO"}, {" SELECT FUNCTION"},{"ESCOJA   FUNCION"} };
 const char MSG0_2[3][17]   = {{"funcao     ajuda"}, {"Function    help"},{"Funcion    ayuda"} };
 
						
 
 
 const char MSG_OK[17] = {"       ok       "};
 const char MSG__MENOR_________OK[17] = {"<             ok"};
 const char MSG__MENOR[17] =            {"<               "};
 const char MSG________________OK[17] = {"<             ok"};
 const char MSG__MENOR__OK__MAIOR[17] = {"<      ok      >"};
 const char MSG__MENOR__MAIOR[17] = {"<              >"};
 const char MSG__MENOR___mm____OK[17] =  {"<       mm    ok"};
 const char MSG__MENOR___Kg____OK[17] =  {"<        Kg   ok"};
 const char MSG__NAO__SIM[3][17] = {{"nao          sim"},	{"no           yes"}, {"no            si"}};
 const char MSG__LIMPA_LINHA_2[17] = {"                "};
 const char MSG_1_10[17]           = {"1            10 "};

 
 const char MSG_USB[3][17] =     {{"   Pen Drive    "},	{"   Flash Drive  "}, {"    PenDrive   "}};
 const char MSG_USB_IN[3][17] =  {{"   Inserida    "},	{"   Inserted     "}, {"    Insertado  "}};
 const char MSG_USB_OUT[3][17] = {{"   Removida    "},	{"   Removeded    "}, {"    Remoto     "}};
#warning rever essa tradução
const char MSG_NO_PENDRIVEUSB[3][17] = {{"Inserir pendrive"},{" No Flash Drive "},{"Sin Unidad flash"}};
const char MSG_SAVE_AT_PENDRIVEUSB[3][17] ={{"     Salvar     "},	{"     save       "}, {"    guadar      "}};





/**************** Tela 1  *******************/ 
 //const char MSG1_1[17] = {"F1  2 ou 5 sens "};Sai conforme alteracao 07/10/2013
//?? const char MSG1_1[17] = {"F1  2 a  5 sens "};	//Incluido conforme alteracao 07/10/2013
//??const char IMSG1_1[17] = {"F1   2 to 5 sens"};//Incluido conforme alteracao 07/10/2013
//??const char SMSG1_1[17] = {"F1    2 a 5 sens"};//Incluido conforme alteracao 07/10/2013

const char MSG1_1[3][17] = {{"F1  2 a  5 sens "},	{"F1   2 to 5 sens"}, {"F1    2 a 5 sens"}};



/**************** Tela 1_2 *******************/ 
const char MSG1_2[17] = {"<      ok      >"};





// tela 2






 const char MSG2_1[17] = {"F2  Vm  1 sensor"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//?? const char IMSG2_1[17] = {"F2  Vm  1 sensor"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//??	const char SMSG2_1[17] = {"F2  Vm  1 sensor"};
//const char MSG2_2[17] = {" <-   ok      ->"};
											
 
							//1		21  	3
// tela 3
 //??const char MSG3_1[17] = {"F3  10pass 1sens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//??  const char IMSG3_1[17] = {"F3  10pass 1sens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//?? const char SMSG3_1[17] = {"F3  10paso 1sens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
const char MSG3_1[3][17] = {{"F3  10pass 1sens"},	{"F3  10pass 1sens"}, {"F3  10paso 1sens"}};
							//2	   200     4

	
						
// tela 4
//?? const char MSG4_1[17] = {"F4 Pend/MHS 1sen"};
//const char MSG2_2[17] = {" <-   ok      ->"};
 //?? const char IMSG4_1[17] = {"F4 Pend/SHM 1sen"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//??	 const char SMSG4_1[17] = {"F4 Pend/MHS 1sen"};
//const char MSG2_2[17] = {" <-   ok      ->"};
const char MSG4_1[3][17] = {{"F4 Pend/MHS 1sen"},	{"F4 Pend/SHM 1sen"}, {"F4 Pend/MHS 1sen"}};
							//3		41  	5
 
	 
	 
	 
// tela 5
//?? const char MSG5_1[17] = {"F5  Bob e 1 sens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//??  const char IMSG5_1[17] = {"F5   Coil 1 sens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
//??	 const char SMSG5_1[17] = {"F5  Bob y 1 sens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
const char MSG5_1[3][17] = {{"F5  Bob e 1 sens"},	{"F5   Coil 1 sens"}, {"F5  Bob y 1 sens"}};
							//4		51  	6
							
// tela 6
//?? const char MSG6_1[17] = {"F6 MCircular1sen"};
//?? const char IMSG6_1[17] = {"F6 C.Motion 1sen"};
//?? const char SMSG6_1[17] = {"F6 MCircular1sen"};
//const char MSG2_2[17] = {" <-   ok      ->"};
 const char MSG6_1[3][17] = {{"F6 MCircular1sen"},	{"F6 C.Motion 1sen"}, {"F6 MCircular1sen"}};
 							//5		61  	7
						
// tela 7
//??  const char MSG7_1[17] = {"F7 Choq-Inl 2sen"};
//??  const char IMSG7_1[17] = {"F7 Ine-collision"};
//??  const char SMSG7_1[17] = {"F7 Choq-Ine 2sen"};
//const char MSG2_2[17] = {" <-   ok      ->"};
 const char MSG7_1[3][17] = {{"F7 Choq-Inl 2sen"},	{"F7 Ine-collision"}, {"F7 Choq-Ine 2sen"}};
 const char MSG_NUM_INTERVALOS[3][17]= {{"Num. Intervalos "},	{"Num. Intervals  "}, {"Num. Intervalos "}};
 					   //6		71  	8
						
	
	
// tela 8
//?? const char MSG8_1[17] = {"F8 Choq-Els 2sen"};
//?? const char IMSG8_1[17] = {"F8 Els-collision"};
//?? const char SMSG8_1[17] = {"F8 Choq-Els 2sen"};
//const char MSG2_2[17] = {" <-   ok      ->"};
  const char MSG8_1[3][17] = {{"F8 Choq-Els 2sen"},	{"F8 Els-collision"}, {"F8 Choq-Els 2sen"}};
							//7		81  	9
// tela 9
 const char MSG9_1[17] = {"F9 V Som 2sensAc"};
//const char MSG2_2[17] = {" <-   ok      ->"};
							//8		91  	10
// tela 10
 const char MSG10_1[17] = {"F10  t  manual  "};
//const char MSG2_2[17] = {" <-   ok      ->"};
							//9		99 	1
// tela 11
//?? const char MSG11_1[17] = {"INSERIR DIST.?  "};
//?? const char IMSG11_1[17] = {"INSERT DISTANCE?"};
//?? const char SMSG11_1[17] = {"INSERTAR DIST. ?"};
 const char MSG11_1[3][17] = {{"INSERIR DIST.?  "},	{"INSERT DISTANCE?"}, {"INSERTAR DIST. ?"}};
							//100		//12
 
//?? const char MSG11_2[17] = {" nao        sim "};
//?? const char IMSG11_2[17] = {" no         yes "};
//??  const char SMSG11_2[17] = {" no          si "};
const char MSG11_2[3][17] = {{" nao        sim "},	{" no         yes "}, {" no          si "}};
	
							

// tela 12
//?? const char MSG12_1[17] = {"d entre S0 e S1 "};
//?? const char IMSG12_1[17] = {"d  between S0-S1"};
//?? const char SMSG12_1[17] = {"d  entre S0 y S1"};
 const char MSG12_1[3][17] = {{"d entre S0 e S1 "},	{"d  between S0-S1"}, {"d  entre S0 y S1"}};
 
// const char MSG12_2 = (char)0x7F;  
//const char MSG12_2 = (char)0x3c;
const char MSG12_2 [2]= {"<"};

const char MSG12_2a[9] =  {"mm    ok"};



						 //11 			//13
const char MSG12_2b[9] =  {" kg   ok"}; //Mensagem padrao unidade de massa

// tela 13
//?? const char MSG13_1[17] = {"d entre S0 e S2 "};
//?? const char IMSG13_1[17] = {"d  between S0-S2"};
//?? const char SMSG13_1[17] = {"d  entre S0 y S2"};
 const char MSG13_1[3][17] = {{"d entre S0 e S2 "},	{"d  between S0-S2"}, {"d  entre S0 y S2"}};
						 //12 			//14		
	
	
						 //12 			//14						
// tela 14
//?? const char MSG14_1[17] = {"d entre S0 e S3 "};
//?? const char IMSG14_1[17] = {"d  between S0-S3"};
//?? const char SMSG14_1[17] = {"d  entre S0 y S3"};
 const char MSG14_1[3][17] = {{"d entre S0 e S3 "},	{"d  between S0-S3"}, {"d  entre S0 y S3"}};
						 //13 			//15
// tela 15
//?? const char MSG15_1[17] = {"d entre S0 e S4 "};
//?? const char IMSG15_1[17] = {"d  between S0-S4"};
//?? const char MSG15_1[17] = {"d  entre S0 y S4"};
const char MSG15_1[3][17] = {{"d entre S0 e S4 "},	{"d  between S0-S4"}, {"d  entre S0 y S4"}};
	
						 //14 			//100

// tela 17
//??const char MSG17_1[17]= {"No. de sensores?"};
//??const char IMSG17_1[17]= {"No. SENSORS ?   "};
//??const char SMSG17_1[17]= {"No. de sensores?"};
const char MSG17_1[3][17] = {{"No. de sensores?"},	{"No. SENSORS ?   "}, {"No. de sensores?"}};
const char MSG17_2[17]= {" 2            5 "};
			//18	  	 	 19

// tela 21
//?? const char MSG21_1[17] = {"INSERIR LARGURA?"};
//?? const char IMSG21_1[17] = {"INSERT WIDTH ?  "};
//?? const char SMSG21_1[17] = {"INSERTAR ANCHURA"};
const char MSG21_1[3][17] = {{"INSERIR LARGURA?"},	{"INSERT WIDTH ?  "}, {"INSERTAR ANCHURA"}};
	 
	 
//const char MSG11_2[17] = {" nao        sim "};
							//100		//22
// tela 22
//?? const char MSG22_1[17] = {"LARGURA DO OBJ. "};
//?? const char IMSG22_1[17] = {"OBJECT WIDTH    "};
//?? const char SMSG22_1[17] = {"ANCHURA DEL OBJ."};
const char MSG22_1[3][17] = {{"LARGURA DO OBJ. "},	{"OBJECT WIDTH    "}, {"ANCHURA DEL OBJ."}};
 
//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2a[17] =   {"       mm    ok"};
							 //21 			//100

// tela 52
//??const char MSG52_1[17] = {"d entre S0 e S1"};
//22/06/2012:Troca de "BOB" por "S0"
//Cl034 que aciona a bobina he conectado a S0
//??const char IMSG52_1[17] = {"d betweenCOIL-S0"};
//??const char SMSG52_1[17] = {"d entre bob y S0"};
const char MSG52_1[3][17] = {{"d entre S0 e S1"},	{"d betweenCOIL-S0"}, {"d entre bob y S0"}};

// tela 72
//CONST CHAR MSG72_1[17]=  {"Num. Intervalos "};
//CONST CHAR MSG72_2[17]=  {" 1           10 "};

const char MSG72_1[3][17] = {{"Num. Intervalos "},	{"Numb. Intervals "}, {"Num. Intervalos "}};
const char MSG72_2[17] = {" 1           10 "};;


// tela 92
//??const char MSG92_1[17] = {"d entre mic.    "};
//??const char IMSG92_1[17] = {"d between mic   "};
//??const char SMSG92_1[17] = {"d entre mic     "};
const char MSG92_1[3][17] = {{"d entre mic.    "},	{"d between mic   "}, {"d entre mic     "}};

// tela 99
//??const char MSG99_1[17]= {"Intervalos: 1a10"};
//??const char IMSG99_1[17]= {"Intervals: 1to10"};
//??const char SMSG99_1[17]= {"Intervalos: 1a10"};
const char MSG99_1[3][17] = {{"Intervalos: 1a10"},	{"Intervals: 1to10"}, {"Intervalos: 1a10"}};

//??const char SMSG99_2[17]= {"     ok "};
//??const char MSG99_2[17]= {"     ok "};
//??const char IMSG99_2[17]= {"     ok "};

							  //100

// tela 100
//??const char MSG100_1[17]= {"INICIE EXPERIM. "};
//??const char IMSG100_1[17]= {"START EXPERIMENT"};
//??const char SMSG100_1[17]= {"INICIAR EXPERIM."};
const char MSG100_1[3][17] = {{"INICIE EXPERIM. "},	{"START EXPERIMENT"}, {"INICIAR EXPERIM."}};

//??const char MSG100_2[17]= {"         cancela"};
//??const char IMSG100_2[17]= {"          cancel"};
//??const char SMSG100_2[17]= {"         cancela"};
const char MSG100_2[3][17] = {{"         cancela"},	{"          cancel"}, {"         cancela"}};
									   //0

// tela 102 a 105
const char MSG102_1[3]= {"t="};
//const char MSG100_2[17]= {"         cancela"};

// tela 106
//??const char MSG106_1[17]= {"EXP. FINALIZADO "};
//??const char IMSG106_1[17]= {"EXP. FINISHED   "};
//??const char SMSG106_1[17]= {"EXP. FINALIZADO "};
const char MSG106_1[3][17] = {{"EXP. FINALIZADO "},	{"EXP. FINISHED   "}, {"EXP. FINALIZADO "}};

//??const char MSG106_2[17]= {"ver  repetir  F?"};
//??const char IMSG106_2[17]= {"see  repeat   F?"};
//??const char SMSG106_2[17]= {"ver  repetir  F?"};
//const char MSG106_2[3][17] = {{"ver  repetir  F?"},	{"see  repeat   F?"}, {"ver  repetir  F?"}};
const char MSG106_2[3][17] = {{"ver  repetir   >"},	{"see  repeat    >"}, {"ver  repetir   >"}};
const char MSG_REPETIR_FUNCAO[3][17] = {{"repetir       F?"},	{"repeat        F?"}, {"repetir       F?"}};

const char MSG_SALVAR_USB[3][17] ={{"<    Salvar   F?"},	{"<    save     F?"}, {"<   guadar    F?"}};
const char MSG_USB_DIGITAL_OK[3][17] =     { { "Salvou dados    " }, { "Saved data      " }, { "Guardado        " } };
const char MSG_USB_DIGITAL_NOK[3][17] =     { { "Erro dados      " },  {  "Error data      " }, {  "Error           " } };


						 //110	  100	  1

// tela 110
//??const char MSG110_1[17]= {"  RESULTADO(S)  "};
//??const char IMSG110_1[17]= {"   RESULT(S)    "};
//??const char SMSG110_1[17]= {" RESULTADO(S)   "};
const char MSG110_1[3][17] = {{"  RESULTADO(S)  "},	{"   RESULT(S)    "}, {" RESULTADO(S)   "}};

//??const char MSG110_2[17]= {" t    vel   sair"};
//??const char IMSG110_2[17]= {" t    vel   quit"};
//??const char SMSG110_2[17]= {" t    vel  salir"};
const char MSG110_2[3][17] = {{" t    vel   sair"},	{" t    vel   quit"}, {" t    vel  salir"}};
						 //150	  170	 106

//??const char MSG111_2[17]= {" t          sair"};
//??const char IMSG111_2[17]= {" t          quit"};
//??const char SMSG111_2[17]= {" t         salir"};
const char MSG111_2[3][17] = {{" t          sair"},	{" t          quit"}, {" t         salir"}};

						//150	     	 106
// tela 150
 const char MSG150_1[6] = {"t0,1:"};	//SensorDigital.Result.tempos[0] SensorDigital.Result.tempos2[0]
// tela 151
 const char MSG151_1[6] = {"t0,2:"};	//SensorDigital.Result.tempos[1] SensorDigital.Result.tempos2[1]
// tela 152
 const char MSG152_1[6] = {"t0,3:"};	//SensorDigital.Result.tempos[2] SensorDigital.Result.tempos2[2]
// tela 153
 const char MSG153_1[6] = {"t0,4:"};	//SensorDigital.Result.tempos[3] SensorDigital.Result.tempos2[3]
// tela 154
 const char MSG154_1[6] = {"t1,2:"};	//SensorDigital.Result.tempos[4] SensorDigital.Result.tempos2[4]
// tela 155
 const char MSG155_1[6] = {"t2,3:"};	//SensorDigital.Result.tempos[5] SensorDigital.Result.tempos2[5]
// tela 156
 const char MSG156_1[6] = {"t3,4:"};	//SensorDigital.Result.tempos[6] SensorDigital.Result.tempos2[6]
// tela 170
 const char MSG170_1[7] = {"Vm0,1:"};
// tela 171
 const char MSG171_1[7] = {"Vm0,2:"};
// tela 172
 const char MSG172_1[7] = {"Vm0,3:"};
// tela 173
 const char MSG173_1[7] = {"Vm0,4:"};
// tela 174
 const char MSG174_1[7] = {"Vm1,2:"};
// tela 175
 const char MSG175_1[7] = {"Vm2,3:"};
// tela 176
 const char MSG176_1[7] = {"Vm3,4:"};

  

//const char MSG1_2[17] = {" <-     ok    ->"};
							//155 	106  	1

// tela 203
//const char MSG106_1[17]= {"EXP. FINALIZADO "};
//const char MSG106_2[17]= {"ver   novo    F?"};
						 //150	  107	  1


//tela 240
const char MSG240_1[17] = {"escolha a funcao"};
const char MSG240_2[17]= {"e pressione ok.."};
const char MSG240_3[17]= {"existem 12 tipos"};
const char MSG240_4[17]= {"  de funcoes.   "};


// tela 250
 const char MSG250_1[3] = {"t="};

// tela 251
 const char MSG251_1[4] = {"Vm="};


// tela 350  
// const char MSG350_1[4] = {"t0,"};

// tela 410
//const char MSG110_1[17]= {"   resultados   "};
//??const char MSG410_2[17]= {" t   freq   sair"};
//??const char IMSG410_2[17]= {" t   freq   quit"};
//??const char SMSG410_2[17]= {" t   freq  salir"};
const char MSG410_2[3][17] = {{" t   freq   sair"},	{" t   freq   quit"}, {" t   freq  salir"}};
						 //450	  470	 106


// tela 550
// const char MSG550_1[17] = {"t="};
// tela 551
// const char MSG251_1[17] = {"Vm="};
// const char MSG251_2[17] = {"m/s "};
// tela 552
 const char MSG552_1[4] = {"a ="};
// tela 553
 const char MSG553_1[4] = {"Vf="};

// tela 710
//const char MSG110_1[17]= {"   resultados   "};
//??const char MSG710_2[17]= {"t:S0  t:S1  sair"};
//??const char IMSG710_2[17]= {"t:S0  t:S1  quit"};
//??const char SMSG710_2[17]= {"t:S0  t:S1 salir"};
const char MSG710_2[3][17] = {{"t:S0  t:S1  sair"},	{"t:S0  t:S1  quit"}, {"t:S0  t:S1 salir"}};
						 //750	  770	 106

// tela 900
//??const char MSG900_1[17] = {"F11 teste sensor"};
//??const char IMSG900_1[17] = {"F11 sensor test "};
//??const char SMSG900_1[17] = {"F11  prueba sens"};
const char MSG900_1[3][17] = {{"F11 teste sensor"},	{"F11 sensor test "}, {"F11  prueba sens"}};

//const char MSG2_2[17] = {" <-   ok      ->"};
							//10  900     1

// tela 902
//const char MSG902_1[17] = {"S:0  1  2  3  4 "};
//??const char MSG902_2[17] = {"            sair"};
//??const char IMSG902_2[17] = {"            quit"};
//??const char SMSG902_2[17] = {"           salir"};
const char MSG902_2[3][17] = {{"            sair"},	{"            quit"}, {"           salir"}};
										//0


const char MSGDEBUG_1[17] = {"detectou a int0 "};
const char MSGDEBUG_2[17] = {"                "};

// tela 1012
//?? const char MSG1012_1[17] = {"F12  Ec Transl. "};
//?? const char IMSG1012_1[17] = {"F12  Ec Transl. "};
//?? const char SMSG1012_1[17] = {"F12  Ec Transl. "};
const char MSG1012_1[3][17] = {{"F12  Ec Transl. "},	{"F12  Ec Transl. "}, {"F12  Ec Transl. "}};

//const char MSG2_2[17] = {" <-   ok      ->"};
							//900 1021  	1

// tela 1021
 const char MSG1021_1[17] = {"COMPRIM. DO OBJ."};
//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2a[17] =   {"       mm    ok"};
							 //1012 			//1022

// tela 1022
 const char MSG1022_1[3][17] = {{" MASSA DO OBJ.  "},{"  OBJECT  MASS  "},{" MASA  DEL OBJ. "}};
//const char IMSG1022_1[17] = {"  OBJECT  MASS  "};
//const char SMSG1022_1[17] = {" MASA  DEL OBJ. "};


//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2a[17] =   {"       kg   ok"};
							 //1021 			//100

// tela 1253
//?? const char MSG1253_1[4] = {"Ec="};
//??const char IMSG1253_1[4] = {"Ec="};
//??  const char SMSG1253_1[4] = {"Ec="};
  const char MSG1253_1[4] = {"Ec="};

 
//////////////////////////////////////////////////////////
///   INGLES
/////////////////////////////////////////////////////////
// Mensagens Gerais
 const char IMSG1[17]   = {" *** CIDEPE *** "};
 const char IMSG2[17]   = {" EQ228E  v1.1   "};


	

// tela 1

 //const char IMSG1_1[17] = {"F1   2 or 5 sens"};Sai conforme alteracao 07/10/2013
//   const char IMSG1_1[17] = {"F1   2 to 5 sens"};//Incluido conforme alteracao 07/10/2013
 const char IMSG1_2[15] = {"      ok      "};

// const char IMSG1_2a = (char)0x7F;
 //const char IMSG1_2b = (char)0x7E;

 //const char MSG1_2a = (char)0x7F; - o caracter da seta nao
//aparece no modelo de display fdcc
//@@ const char IMSG1_2a = (char)0x3c;
 //const char MSG1_2b = (char)0x7E;
//const char MSG1_2a = (char)0x7F; - o caracter da seta nao
//aparece no modelo de display fdcc
//@@const char IMSG1_2b = (char)0x3e;


//const char MSG2_2[17] = {" <-     ok      ->"};
							//8 	1010  	2
// tela 2

// tela 3

// tela 4

// tela 5

// tela 6

// tela 7

// tela 8

// tela 9
 const char IMSG9_1[17] = {"F9 SV 2AcousSens"};
//const char MSG2_2[17] = {" <-   ok      ->"};
							//8		91  	10
// tela 10
 const char IMSG10_1[17] = {"F10  t  manual  "};
//const char MSG2_2[17] = {" <-   ok      ->"};
							//9		99 	1
// tela 11


							//100		//12

// tela 12

// const char IMSG12_2 = (char)0x7F;  
const char IMSG12_2 = (char)0x3c;
const char IMSG12_2a[9] =  {"mm    ok"};
						 //11 			//13

// tela 13

						 //12 			//14						
// tela 14

						 //13 			//15
// tela 15

						 //14 			//100

// tela 17

// tela 21

//const char IMSG11_2[17] = {" nao        sim "};
							//100		//22
// tela 22
 
//const char IMSG12_2 = (char)0x7F;  
//const char IMSG12_2a[17] =   {"       mm    ok"};
							 //21 			//100

// tela 52


// tela 92


// tela 99

							  //100

// tela 100


									   //0


// tela 102 a 105

//const char IMSG100_2[17]= {"         cancela"};

// tela 106


						 //110	  100	  1

// tela 110


						 //150	  170	 106


						//150	     	 106
// tela 150
 const char IMSG150_1[6] = {"t0,1:"};	//SensorDigital.Result.tempos[0] SensorDigital.Result.tempos2[0]
// tela 151
 const char IMSG151_1[6] = {"t0,2:"};	//SensorDigital.Result.tempos[1] SensorDigital.Result.tempos2[1]
// tela 152
 const char IMSG152_1[6] = {"t0,3:"};	//SensorDigital.Result.tempos[2] SensorDigital.Result.tempos2[2]
// tela 153
 const char IMSG153_1[6] = {"t0,4:"};	//SensorDigital.Result.tempos[3] SensorDigital.Result.tempos2[3]
// tela 154
 const char IMSG154_1[6] = {"t1,2:"};	//SensorDigital.Result.tempos[4] SensorDigital.Result.tempos2[4]
// tela 155
 const char IMSG155_1[6] = {"t2,3:"};	//SensorDigital.Result.tempos[5] SensorDigital.Result.tempos2[5]
// tela 156
 const char IMSG156_1[6] = {"t3,4:"};	//SensorDigital.Result.tempos[6] SensorDigital.Result.tempos2[6]
// tela 170

// tela 171

// tela 172

// tela 173
 // tela 174

// tela 175

// tela 176


  

//const char IMSG1_2[17] = {" <-     ok    ->"};
							//155 	106  	1

// tela 203
//const char IMSG106_1[17]= {"EXP. FINALIZADO "};
//const char IMSG106_2[17]= {"ver   novo    F?"};
						 //150	  107	  1


//tela 240
const char IMSG240_1[17] = {"Choose function "};
const char IMSG240_2[17]= {"and press ok..  "};
const char IMSG240_3[17]= {"there are 12    "};
const char IMSG240_4[17]= {"different types."};


// tela 250


// tela 251



// tela 350  
// const char IMSG350_1[4] = {"t0,"};

// tela 410
//const char IMSG110_1[17]= {"   resultados   "};

						 //450	  470	 106


// tela 550
// const char MSG550_1[17] = {"t="};
// tela 551
// const char MSG251_1[17] = {"Vm="};
// const char MSG251_2[17] = {"m/s "};
// tela 552

// tela 553


// tela 710
//const char IMSG110_1[17]= {"   resultados   "};

						 //750	  770	 106

// tela 900

//const char IMSG2_2[17] = {" <-   ok      ->"};
							//10  900     1

// tela 902
//const char IMSG902_1[17] = {"S:0  1  2  3  4 "};

										//0

// tela 1012

//const char MSG2_2[17] = {" <-   ok      ->"};
							//900 1021  	1

// tela 1021
 const char IMSG1021_1[17] = {" OBJECT  LENGTH "};
//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2a[17] =   {"       mm    ok"};
							 //1012 			//1022

// tela 1022
// const char IMSG1022_1[17] = {"  OBJECT  MASS  "};
//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2b[17] =   {"       g    ok"};
							 //1021 			//100

// tela 1253




/////////////////////////////////////////////////////////
///   ESPANHOL
/////////////////////////////////////////////////////////
// Mensagens Gerais



// tela 0

						 

// tela 1
 
 //const char SMSG1_1[17] = {"F1    2 o 5 sens"};Sai conforme alteracao 07/10/2013
//@@const char SMSG1_1[17] = {"F1    2 a 5 sens"};//Incluido conforme alteracao 07/10/2013
 const char SMSG1_2[15] = {"      ok      "};

// const char SMSG1_2a = (char)0x7F;
 //const char SMSG1_2b = (char)0x7E;

//const char MSG1_2a = (char)0x7F; - o caracter da seta nao
//aparece no modelo de display fdcc
const char SMSG1_2a = (char)0x3c;
 //const char MSG1_2b = (char)0x7E;
//const char MSG1_2a = (char)0x7F; - o caracter da seta nao
//aparece no modelo de display fdcc
const char SMSG1_2b = (char)0x3e;

//const char MSG2_2[17] = {" <-     ok      ->"};
							//8 	1010  	2
// tela 2

// tela 3

// tela 4

// tela 5

// tela 6

// tela 7

// tela 8

// tela 9
 const char SMSG9_1[17] = {"F9 VS 2sensAcous"};
//const char MSG2_2[17] = {" <-   ok      ->"};
							//8		91  	10
// tela 10
 const char SMSG10_1[17] = {"F10  t  manual  "};
//const char MSG2_2[17] = {" <-   ok      ->"};
							//9		99 	1
// tela 11


							//100		//12

// tela 12

// const char SMSG12_2 = (char)0x7F;  
const char SMSG12_2 = (char)0x3c;
const char SMSG12_2a[9] =  {"mm    ok"};
						 //11 			//13

// tela 13
				
// tela 14

						 //13 			//15
// tela 15

						 //14 			//100

// tela 17

// tela 21

//const char IMSG11_2[17] = {" nao        sim "};
							//100		//22
// tela 22

//const char IMSG12_2 = (char)0x7F;  
//const char IMSG12_2a[17] =   {"       mm    ok"};
							 //21 			//100

// tela 52


// tela 92


// tela 99

							  //100

// tela 100


									   //0


// tela 102 a 105

//const char IMSG100_2[17]= {"         cancela"};

// tela 106


						 //110	  100	  1

// tela 110


						 //150	  170	 106


						//150	     	 106
// tela 150
 const char SMSG150_1[6] = {"t0,1:"};	//SensorDigital.Result.tempos[0] SensorDigital.Result.tempos2[0]
// tela 151
 const char SMSG151_1[6] = {"t0,2:"};	//SensorDigital.Result.tempos[1] SensorDigital.Result.tempos2[1]
// tela 152
 const char SMSG152_1[6] = {"t0,3:"};	//SensorDigital.Result.tempos[2] SensorDigital.Result.tempos2[2]
// tela 153
 const char SMSG153_1[6] = {"t0,4:"};	//SensorDigital.Result.tempos[3] SensorDigital.Result.tempos2[3]
// tela 154
 const char SMSG154_1[6] = {"t1,2:"};	//SensorDigital.Result.tempos[4] SensorDigital.Result.tempos2[4]
// tela 155
 const char SMSG155_1[6] = {"t2,3:"};	//SensorDigital.Result.tempos[5] SensorDigital.Result.tempos2[5]
// tela 156
 const char SMSG156_1[6] = {"t3,4:"};	//SensorDigital.Result.tempos[6] SensorDigital.Result.tempos2[6]
// tela 170

// tela 171

// tela 172

// tela 173

// tela 174

// tela 175

// tela 176


  

//const char IMSG1_2[17] = {" <-     ok    ->"};
							//155 	106  	1

// tela 203
//const char IMSG106_1[17]= {"EXP. FINALIZADO "};
//const char IMSG106_2[17]= {"ver   novo    F?"};
						 //150	  107	  1


//tela 240
const char SMSG240_1[17] = {"Escoja   funcion"};
const char SMSG240_2[17]= {"y presione ok.. "};
const char SMSG240_3[17]= {"existen 12 tipos"};
const char SMSG240_4[17]= {"de funciones.   "};


// tela 250


// tela 251



// tela 350  
// const char IMSG350_1[4] = {"t0,"};

// tela 410
//const char IMSG110_1[17]= {"   resultados   "};

						 //450	  470	 106


// tela 550
// const char MSG550_1[17] = {"t="};
// tela 551
// const char MSG251_1[17] = {"Vm="};
// const char MSG251_2[17] = {"m/s "};
// tela 552

// tela 553


// tela 710
//const char IMSG110_1[17]= {"   resultados   "};

						 //750	  770	 106

// tela 900

//const char IMSG2_2[17] = {" <-   ok      ->"};
							//10  900     1

// tela 902
//const char IMSG902_1[17] = {"S:0  1  2  3  4 "};

										//0


// tela 1012

//const char MSG2_2[17] = {" <-   ok      ->"};
							//900 1021  	1

// tela 1021
 const char SMSG1021_1[17] = {" LARGO DEL OBJ. "};
//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2a[17] =   {"       mm    ok"};
							 //1012 			//1022

// tela 1022
// const char SMSG1022_1[17] = {" MASA  DEL OBJ. "};
//const char MSG12_2 = (char)0x7F;  
//const char MSG12_2b[17] =   {"       g    ok"};
							 //1021 			//100

// tela 1253




void msg_atualizaTimer(void);

void msg_zeraTimer(void);

// TELAS DE MENSAGENS


//***** TELAS INICIAIS*********
void telaInicial_1(void);

void telaInicial_2(void);

//**********************************************
// ********** TELAS DE ESTADOS *****************


void tela0(void);
void tela1_2(void);
void tela1(void);
void tela2(void);
void tela3(void);
void tela4(void);
void tela5(void);
void tela6(void);
void tela7(void);
void tela8(void);
void tela9(void);
void tela10(void);
void tela11(void);
void tela12(void);
void tela13(void);
void tela14(void);
void tela15(void);
void tela17(void);
void tela21(void);
void tela22(void);
void tela52(void);
void tela72(void);
void tela92(void);
void tela99(void);
void tela100(void);
void tela102(void);
void tela106(void);
void Salvar_usb(void);
void tela110(void);
void tela111(void);
// mostra tempos
void tela149(void);
void tela150(void);
void tela151(void);
void tela152(void);
void tela153(void);
void tela154(void);
void tela155(void);
void tela156(void);
// mostra velocidades
void tela169(void);
void tela170(void);
void tela171(void);
void tela172(void);
void tela173(void);
void tela174(void);
void tela175(void);
void tela176(void);
void tela240(void);
void tela241(void);
void tela250(void);
void tela251(void);
void tela350(void);
void tela410(void);
void tela450(void);
void tela470(void);

void telaUsbIn();
void telaUsbOut();


/* mesma tela250
void tela550(void)
{
	lcd_linha1(void);
	lcd_escreve(MSG550_1);
	lcd_linha2(void);
	lcd_escreve(MSG1_2a);
	lcd_escreve(MSG1_2);
	lcd_escreve(MSG1_2b);
} mesma 251
void tela551(void)
{
	lcd_linha1(void);
	lcd_escreve(MSG551_1);
	lcd_linha2(void);
	lcd_escreve(MSG1_2a);
	lcd_escreve(MSG1_2);
	lcd_escreve(MSG1_2b);
}*/
void tela552(void);
void tela553(void);
void tela702(void);
void tela710(void);
void tela750(void);
void tela751(void);
void tela770(void);
void tela900(void);
void tela902(void);
void tela990(void);
void tela1012(void);
void tela1021(void);
//F12 - Energia Cinetica
//dados sobre a massa
void tela1022(void);
void tela1253(void);
void telaDebug(void);

#endif

