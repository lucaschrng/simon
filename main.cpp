#include <Arduino.h>
#include <time.h>

// Liste pour les pin des leds : jaune -> 10; rouge -> 11, vert -> 12; bleu -> 13
char arrayCouleur[]={10,11,12,13};
// List des boutons, arrangés de façon à ce que leur index corresponde à la pin de la led de couleur
char arrayBoutons[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 4, 5};
// Liste des fréquencces de notes de musique, arrangés de façon à ce que leur index corresponde à la pin de la led de couleur
int notes []={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 880, 831, 659, 622};
//Initialisation des variables
bool isWinning =true;
int HowMany=-1;
int speed = 500;
int AlreadyDid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
// Boucle de Gameplay principal, à chaque tour on allume une nouvelle led
void GamePlay(){
	// HowMany designe le nombre de tour, étant donné qu'on l'incrémente de 1 à chaque tour
    HowMany+=1;
	// on arrete d'accelerer le delai quand ca devient trop rapide
	if (speed > 100)
	{
		// on réduit speed, le delai entre l'affichage de chaque led lors de la démonstration
		speed -= 50;
	}
//on genere aleatoirement une nouvelle couleur 
    int RandomIndex=rand()%4;
// on ajoute la couleur à la liste de couleurs
    int couleur=arrayCouleur[RandomIndex];
    AlreadyDid[HowMany]=couleur;
// on allume chaque lampe pour faire le pattern en en ajoutant une nouvelle à chaque fois, le delai (speed) diminue à chaque tour
    for (int b = 0; b < HowMany; b++)
    {
		
	  delay(speed);
      digitalWrite(AlreadyDid[b],HIGH);
	//émet une note propre à chaque led de couleur
      tone(9, notes[AlreadyDid[b]], 200);
      delay(speed);
      digitalWrite(AlreadyDid[b],LOW);
    }
}
// On verifie si les inputs bouttons sont corrects,dans le bonne ordre et avec une limite de temps
void gameVerify(){
	//on itère le nombre de couleurs qu'il y a dans la séquence préalabement générée
	for (int i = 0; i < HowMany; i++)
	{
		// tant qu'on ne perds pas
		if (isWinning)
		{
			// tant qu'on n'a pas appuyé sur le bon bouton, l'étape n'est pas validée
			bool isLosing = true;
			// test pendant 4 secondes si le joueur a appuyé sur le bouton
			for (int j = 0; j < 4000; j++)
			{
				delay(1);
				//si on appuie sur le bouton attendu
				if (digitalRead(arrayBoutons[AlreadyDid[i]])){
					isLosing = false;
					digitalWrite(AlreadyDid[i], HIGH);
          				tone(9, notes[AlreadyDid[i]], 200);
					delay(200);
					digitalWrite(AlreadyDid[i], LOW);
					j = 4001;
				};
				//le code test si on appuie sur les autres boutons
				if (j < 4001)
				{
					for (int k = 10; k < 14; k++)
					{
						//effectue le test pour tous les boutons sauf celui attendu
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
		//si la variable isLosing n'a pas été modifiée et est vraie, alors on perds
		if(isLosing){
			isWinning = false;
			//émet un son de défaite
        		tone(9, 432, 500);
			}
		}
		
		
	}
	
}

void loop() {
//tant que l'on a pas perdu
 while (isWinning)
  {
//on lance un round
  GamePlay();
	gameVerify();
	delay(500);
  }
}
