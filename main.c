#include <REGX52.H>


#define Led_ON P0_0 = 0				//zapala diode poprzez podanie 0 na P0_0
#define Led_OFF P0_0 = 1			//gasi diode poprzez podanie 1 na P0_0
//  wiersz  kolumna
// 7,6,5,4  3 2 1 0
// 1 1 1 0  1 1 1 1   0xEF
// 1 1 0 1  1 1 1 1   0xDF
// 1 0 1 1  1 1 1 1   0xBF
// 0 1 1 1  1 1 1 1   0x7F
unsigned char code Tab[] = {0xEF,0xDF,0xBF,0x7F};


unsigned char code Przycisk_7 = 0xB7;		//przycisk 7 na klawiaturze

unsigned char code Kombinacja[] = {0x7B, 0xE7, 0xEB};  //Kombinacja 012

void wait(void)					
{
	unsigned int L;
	for(L=0; L<5000; L++)				//odlicza od 0 do 5000 dzieki czemu nasz program na chwile sie zawiesza w danym satnie
	{;}
}

void mrugniecia(unsigned char ile)
{
	unsigned char i=0;					
		for(i=0; i<ile; i++)			//od 0 do ile
		{	
			Led_ON;			//zaapalamy led
			wait();			//czekamy chwile
			Led_OFF;			//gasimy led
			wait();		//czekamy chwile
		}
}
	

void main (void)
  {
    volatile unsigned char data ind = 0;
		unsigned char good = 0;		//flaga ktora sprawdza sekwencje
    
    for(;;)
      {
        P2 = Tab[ind];
				
				if(P2 == Przycisk_7) mrugniecia(3);		//jezeli nacisniemy przycisk 7 to mrugamy 3 razy
				
				if(P2 == Kombinacja[0])			//jezeli nacisniemy pierwszy przycisk z sekwencji
				{
					good = 1;		//to ustawiamy flage na 1
					while(P2 == Kombinacja[0]);		// dopoki przytrzymujemy przycisk to sie nic nie dzieje
				}
				if(P2 == Kombinacja[1])		//jezeli nacisniemy drugi przycisk z sekwencji
				{	
					if(good == 1) good = 2;		//jezeli flaga jest ustawiona na 1 a wiec mamy juz pierwszy przycisk to ustawiamy flage na 2
					else good = 0;				//w przecinym razie zerujemy flage
					while(P2 == Kombinacja[1]);// dopoki przytrzymujemy przycisk to sie nic nie dzieje
				}
				if(P2 == Kombinacja[2])		//jezeli nacisniemy trzeci przycisk z sekwencji
				{
					if(good == 2) mrugniecia(5); 			//jezei falga jest ustawiona na 2 wiec mamy juz dwa przyciski to mrugamy 5 razy
					good = 0;			// ustawiamy flage na 0
					while(P2 == Kombinacja[2]);// dopoki przytrzymujemy przycisk to sie nic nie dzieje
				}
				
				
				
				
							
        ind++;
        if (ind == 4) {ind = 0;}
      }
  }