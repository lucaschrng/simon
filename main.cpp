#include <Arduino.h>
#include <time.h>

// jaune 10 rouge 11 vert 12 bleu 13
// Liste pour les leds, les boutons et les notes de musique
char arrayCouleur[]={10,11,12,13};
char arrayBoutons[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 4, 5};
int notes []={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 880, 831, 659, 622};
bool isWinning =true;
int HowMany=-1;
int speed = 500;
int AlreadyDid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int lastIndex;


void setup() {
	srand(time(NULL));
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
	pinMode(5, INPUT);
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(10, OUTPUT);
  	pinMode(9, OUTPUT);
}
// Boucle de Gameplay principal, a chaque tour on allume une nouvelle Led
void GamePlay(){

    HowMany+=1;
	if (speed > 100)
	{
		speed -= 50;
	}
	//on genere aleatoirement une nouvelle couleur 
    int RandomIndex=rand()%4;
    int couleur=arrayCouleur[RandomIndex];
    AlreadyDid[HowMany]=couleur;
// on allume chaque lampe pour faire le pattern en ajoutant une nouvelle a chaque fois, le speed augmente a chaque tour
    for (int b = 0; b < HowMany; b++)
    {
		
	  delay(speed);
      digitalWrite(AlreadyDid[b],HIGH);
      tone(9, notes[AlreadyDid[b]], 200);
      delay(speed);
      digitalWrite(AlreadyDid[b],LOW);
      lastIndex=b;
    }
}
// On verifie si les inputs bouttons sont corrects,dans le bonne ordre et avec une limite de temp
void gameVerify(){
	for (int i = 0; i < HowMany; i++)
	{
		if (isWinning)
		{
			bool isLosing = true;
			for (int j = 0; j < 4000; j++)
			{
				delay(1);
				if (digitalRead(arrayBoutons[AlreadyDid[i]])){
					isLosing = false;
					digitalWrite(AlreadyDid[i], HIGH);
          				tone(9, notes[AlreadyDid[i]], 200);
					delay(200);
					digitalWrite(AlreadyDid[i], LOW);
					j = 4001;
				};
				if (j < 4001)
				{
					for (int k = 10; k < 14; k++)
					{
						if (k != AlreadyDid[i]){
							if (digitalRead(arrayBoutons[k])){
								isLosing = true;
								isWinning = false;
								j = 4001;
							};
						}
					}
				}
				
			}
		if(isLosing){
			isWinning = false;
        		tone(9, 432, 500);
			}
		}
		
		
	}
	
}

void loop() {
 while (isWinning)
  {
  GamePlay();
	gameVerify();
	delay(500);
  }
}
