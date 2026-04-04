/*
// define as funcoes de cada tecla e outras funcoes relacionadas



void chama_funcao(char _tecla)			tecla chama a funcao e altera a tela



*/

void chama_funcao(char _tecla){

	switch (_tecla) {
	
	    case '1':
			 break;
	
	    case '2':
	         break;
		
		case '3':
				bobina_init();
				lcd_linha1();
				lcd_escreve(0x7F);
			
				lcd_escreve(" funcao ");
				lcd_linha2();
				lcd_posicaoxy(14,2);
				lcd_escreve(0x7E);
				 break;
	
	    case '4':
				sensores_init();
				lcd_linha1();
				lcd_escreve("teste sensores");
				lcd_linha2();
				
	           break;

		case '5':
				lcd_limpa();
				 break;
	
	    case '6':
	           break;
		
		case '7':
				 break;
	
	    case '8':
	           break;
		
		case '9':
				 break;
	
	    case '0':
	           break;
		
		case 'A':
				 break;
	
	    case 'B':
	           break;
		
		case 'C':
				 break;
	
	    case 'D':
	           break;

	}
	
}
	