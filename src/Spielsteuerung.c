/*
 * Spielsteuerung.c
 *
 *  Created on: 12.03.2015
 *      Author: Michael
 */


/*
 * SpielSteuerung.c
 *
 *  Created on: 08.03.2015
 *      Author: Eliott Kupferschmied
 */

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        	: SpielSteuerung.c
**
**	Funktion   	: Hauptsteuermodul Spielsteuerung
**
**	Parameter	: Initialisationswerte...
**
**	R�ckgabe	: Was gibts zur�ck..
**
**	Input		: Spieldaten
**
**	Output		: Welche Daten werden ver�ndert...
**
** 	Author		: kupfe1/alles1
**
**	Version		: 1V06
**
**	History		: .....
**
**	Pendenzen	: Implementierung Level 5 und Punkte
**
**	Bugs		: Was geht noch nicht...
**
**	Tests		: Test von 1V00 am 10.03.2015
**				  Test von 1V01 am 12.03.2015
**				  Test von 1V02 am 16.03.2015
**				  Test von 1V03 am 18.03.2015
**				  Test von 1V04 am 22.03.2015
**				  Test von 1V05 am 23.03.2015
**				  Test von 1V06 am 01.04.2015
**
**
*****************************************************************************
**
*/
/* imports */
#include "error.h"
#include "window.h"
#include "communication.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Spielsteuerung.h"
#include "Header.h"

/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktionsname   	: SpielSteuerung
**
**	Funktion   			: Hauptmodul der Spielsteuerung
**
**	R�ckgabe			: Nichts
**
**	Input				: Zeiger auf die Spielparameter
**
**	Output				: Es wird direkt an die Adresse der Anzeigeparameter geschrieben.
**
** 	Author				: kupfe1/alles1
**

******************************************************************************/

//Hauptsteuerung
void SpielSteuerung(SpielModus *ModusPtr, PunkteHighscore *PunkteAnwaerterPtr){

	//Struktur und deren Pointer definieren
	Ball Spielball1;								//Definieren des ersten Spielballs
	Ball *Spielball1Ptr;							//Zeiger f�r den Spielball 1
	Ball Spielball2;								//Definieren des zweiten Spielballs (ab Level 5 im Zweispielermodus)
	Ball *Spielball2Ptr;							//Zeiger f�r den Spielball 2 (ab Level 5 im Zweispielermodus)
	Schlaeger Schlaeger1;							//Definieren von Schlaeger1 (links)
	Schlaeger *Schlaeger1Ptr;						//Zeiger f�r Schlaeger1
	Schlaeger Schlaeger2;							//Definieren von Schlaeger2 (rechts)
	Schlaeger *Schlaeger2Ptr;						//Zeiger f�r Schlaeger2
	AnzeigeParameter UebergabeAnzeige;				//Definieren der �bergabeparameter f�r die Grafikfunktionen
	AnzeigeParameter *UebergabeAnzeigePtr;			//Definieren des Zeigers f�r die �bergabeparameter
	Hinderniss Hinderniss1;							//Definieren von Hindernis 1 (links im Feld)
	Hinderniss *Hinderniss1Ptr;						//Zeiger f�r Hindernis 1
	Hinderniss Hinderniss2;							//Definieren von Hindernis 2 (r�echts im Feld)
	Hinderniss *Hinderniss2Ptr;						//Zeiger f�r Hindernis 2
	Timestamp Zeit;									//Definieren der Zeitparameter
	Timestamp *ZeitPtr;								//Zeiger f�r Zeitparameter

	//Pointer initialisieren
	Spielball1Ptr=&Spielball1;
	Spielball2Ptr=&Spielball2;
	Schlaeger1Ptr=&Schlaeger1;
	Schlaeger2Ptr=&Schlaeger2;
	UebergabeAnzeigePtr=&UebergabeAnzeige;
	Hinderniss1Ptr=&Hinderniss1;
	Hinderniss2Ptr=&Hinderniss2;
	ZeitPtr = &Zeit;

	//Steuervariablen
	int Ball1ImSpiel;								//Abbruchflag wenn der Ball 1 ins Aus geht
//	int Ball2ImSpiel;								//Abbruchflag wenn der Ball 2 ins Aus geht
	int EscGedrueckt;								//Abbruchflag wenn ESC gedr�ckt wird
	int ZeitZaehler;								//Z�hler um nach einer gewissen Spielzeit die Balleschwindigkeit zu erh�hen
	int Gewinner=0;									//Gewinner = 1 bei Sieg von Spieler 1, Gewinner = 2 bei Sieg von Spieler 2.
	int ZaehlerCountdown;							//Z�hlervariable f�r die Countdown Schleife

	//Zeiger f�r Steuervariablen
	int *GewinnerPtr;								//Zeiger f�r die Gewinnervariable

	//Zeiger f�r Steuervariablen initialisieren
	GewinnerPtr=&Gewinner;

	//Auswahl des Spielmodus
	if(ModusPtr->SpielMod==1){

		//Steuervariablen initialisieren
		Ball1ImSpiel=1;								//Abbruchflag wenn der Ball 1 ins Aus geht,
		EscGedrueckt=1;								//Abbruchflag wenn ESC gedr�ckt wird
		ZeitZaehler=0;								//Z�hler um nach einer gewissen Spielzeit die Balleschwindigkeit zu erh�hen


		//Wenn im Level 5 gespielt wird, zweiter Ball initialisieren
		if(ModusPtr->Schwierigkeitsgrad==5){

		//Startposition Ball	2					//Provisorisch
		Spielball2Ptr->xnull=400;
		Spielball2Ptr->ynull=500;
		Spielball2Ptr->vx=-3;
		Spielball2Ptr->vy=0;
		Spielball2Ptr->Zeit=1;
		Spielball2Ptr->GeschwindigkeitsFaktor=2;
		}


		//Schl�gerdimension berechenen, Startpositionen definieren und Steuerflags setzen
		BerechneSchlaegerdimension(Schlaeger1Ptr, Schlaeger2Ptr, ModusPtr, UebergabeAnzeigePtr);

		//Startposition Ball berechnen
		StartPosBall(Spielball1Ptr, ModusPtr, GewinnerPtr);

		//Hindernissposition berechen falls im Level 4 oder 5 gespielt wird
		if(ModusPtr->Schwierigkeitsgrad>=4){
			BerechneHindernissPos(Hinderniss1Ptr, Hinderniss2Ptr,UebergabeAnzeigePtr);
		}

		//Countdown
		for(ZaehlerCountdown=1; ZaehlerCountdown<=3;ZaehlerCountdown++){
//			InfoVar(ZaehlerCountdown);
			printf("Countdown: %d", ZaehlerCountdown);
			WaitMs(1000);
		}


			//Spielschleife
			while(Ball1ImSpiel != 0 && EscGedrueckt !=0){

			//Anzahl Inkremente bei denen die Geschwindigkeit, bis Faktor 3, erh�ht wird ist Abh�ngig vom gespielten Schwierigkeitsgrad. Bei h�heren Levels, bis zum Level 3, wird die Geschwindigkeit schneller erh�ht.
			if(ZeitZaehler>(2000/(ModusPtr->Schwierigkeitsgrad)) && (Spielball1Ptr->GeschwindigkeitsFaktor<8)){
				//Nur wenn der Ball auf H�he eines Schl�gers ist, Geschwindigkeitsfaktor des Balles erh�hen
				if((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos)){
					Spielball1Ptr->GeschwindigkeitsFaktor++;
					ZeitZaehler=0;							//Z�hler R�cksetzen
				}
			}

			//Ballposition berechnen
			Ball1ImSpiel=BallPos(Spielball1Ptr,Schlaeger1Ptr,Schlaeger2Ptr, &(UebergabeAnzeigePtr->XPosBall1),&(UebergabeAnzeigePtr->YPosBall1), ModusPtr,Hinderniss1Ptr,Hinderniss2Ptr, GewinnerPtr);

			//Position Schl�ger 1 und 2 berechnen
			EscGedrueckt=SchlaegerPos(Schlaeger1Ptr,Schlaeger2Ptr,UebergabeAnzeigePtr, ModusPtr);

			//Position Schl�ger 2 bei Spiel gegen den Computer
			if(ModusPtr->ZweiSpieler==0){
				ComputerSchlaeger2(ModusPtr,Schlaeger2Ptr,Spielball1Ptr,UebergabeAnzeigePtr);
			}

			//Bild Zeichnen
			ZeichneSpielfeld(UebergabeAnzeigePtr,ModusPtr);


			//Zeit inkrementieren
			ZeitZaehler++;
			//Testprint
			printf("%d\n",ZeitZaehler);
			//Warten
			WaitMs(2);

			}

	}

	//Levelmodus
	else
	{
		//Steuervariablen initialisieren
		EscGedrueckt=1;								//Abbruchflag wenn ESC gedr�ckt wird

		//Punkte GUI initialisieren
		PunkteGUI(ModusPtr, GewinnerPtr, UebergabeAnzeigePtr);

		//Punkte Highscore initialisieren
		Punkte(1, GewinnerPtr, PunkteAnwaerterPtr, ZeitPtr);

		//Levelschleife
		while(ModusPtr->Schwierigkeitsgrad<6 && EscGedrueckt != 0){

			//Steuervariablen initialisieren
			Ball1ImSpiel=1;							//Abbruchflag wenn der Ball ins Aus geht,
			ZeitZaehler=0;							//Z�hler um nach einer gewissen Spielzeit die Balleschwindigkeit zu erh�hen


			//Wenn im Level 5 gespielt wird, zweiter Ball initialisieren
			if(ModusPtr->Schwierigkeitsgrad==5){
			//Startposition Ball	2					//Provisorisch
			Spielball2Ptr->xnull=400;
			Spielball2Ptr->ynull=500;
			Spielball2Ptr->vx=-3;
			Spielball2Ptr->vy=0;
			Spielball2Ptr->Zeit=1;
			Spielball2Ptr->GeschwindigkeitsFaktor=2;
			}

			//Schl�gerdimension berechenen, Startpositionen definieren und Steuerflags setzen
			BerechneSchlaegerdimension(Schlaeger1Ptr, Schlaeger2Ptr, ModusPtr, UebergabeAnzeigePtr);

			//Hindernissposition berechen falls im Level 4 oder 5 gespielt wird
			if(ModusPtr->Schwierigkeitsgrad>=4){
				BerechneHindernissPos(Hinderniss1Ptr, Hinderniss2Ptr,UebergabeAnzeigePtr);
			}

			//Startposition Ball berechnen
			StartPosBall(Spielball1Ptr, ModusPtr, GewinnerPtr);


			//Countdown
			for(ZaehlerCountdown=1; ZaehlerCountdown<=3;ZaehlerCountdown++){
	//			InfoVar(ZaehlerCountdown);
				printf("Countdown: %d", ZaehlerCountdown);
				WaitMs(1000);
			}

				//Spielschleife
				while(Ball1ImSpiel != 0 && EscGedrueckt !=0){

				//Anzahl Inkremente bei denen die Geschwindigkeit, bis Faktor 3, erh�ht wird ist Abh�ngig vom gespielten Schwierigkeitsgrad. Bei h�heren Levels, bis zum Level 3, wird die Geschwindigkeit schneller erh�ht.
				if(ZeitZaehler>(2000/(ModusPtr->Schwierigkeitsgrad)) && (Spielball1Ptr->GeschwindigkeitsFaktor<8)){
					//Nur wenn der Ball auf H�he eines Schl�gers ist, Geschwindigkeitsfaktor des Balles erh�hen
					if((Spielball1Ptr->xpos<=Schlaeger1Ptr->xpos) || (Spielball1Ptr->xpos>=Schlaeger2Ptr->xpos)){
						Spielball1Ptr->GeschwindigkeitsFaktor++;
						ZeitZaehler=0;							//Z�hler R�cksetzen
					}
				}

				//Ballposition berechnen
				Ball1ImSpiel=BallPos(Spielball1Ptr,Schlaeger1Ptr,Schlaeger2Ptr,  &(UebergabeAnzeigePtr->XPosBall1), &(UebergabeAnzeigePtr->YPosBall1), ModusPtr, Hinderniss1Ptr, Hinderniss2Ptr, GewinnerPtr);

				//Position Schl�ger 1 und 2 berechnen
				EscGedrueckt=SchlaegerPos(Schlaeger1Ptr,Schlaeger2Ptr,UebergabeAnzeigePtr,ModusPtr);

				//Position Schl�ger 2 bei Spiel gegen den Computer
				if(ModusPtr->ZweiSpieler==0){
					ComputerSchlaeger2(ModusPtr,Schlaeger2Ptr,Spielball1Ptr,UebergabeAnzeigePtr);
				}

				//Bild Zeichnen (provisorisch)
				ZeichneSpielfeld(UebergabeAnzeigePtr,ModusPtr);



				//Level Anzeigen (Provisorisch)
				if(ModusPtr->Schwierigkeitsgrad==1){
				DrawTextXY(1300,600, COL_GREEN, "Level 1");
				}
				if(ModusPtr->Schwierigkeitsgrad==2){
				DrawTextXY(1300,600, COL_GREEN, "Level 2");
				}
				if(ModusPtr->Schwierigkeitsgrad==3){
				DrawTextXY(1300,600, COL_GREEN, "Level 3");
				}
				if(ModusPtr->Schwierigkeitsgrad==4){
				DrawTextXY(1300,600, COL_GREEN, "Level 4");
				}
				if(ModusPtr->Schwierigkeitsgrad==5){

				DrawTextXY(1300,600, COL_GREEN, "Level 5");
				}

				//Zeit inkrementieren
				ZeitZaehler++;
				//Testprint
				printf("Zaehler:%d\n",ZeitZaehler);
				printf("Faktor:%d\n",Spielball1Ptr->GeschwindigkeitsFaktor);

				//Warten
				WaitMs(2);

				}

			//Level inkrementieren
			ModusPtr->Schwierigkeitsgrad++;

			//PunkteGUI anpassen
			PunkteGUI(ModusPtr, GewinnerPtr, UebergabeAnzeigePtr);

			//Highscore Punkte berechnen
			Punkte(2, GewinnerPtr, PunkteAnwaerterPtr, ZeitPtr);
		}
	}
	return;
}
/*
**
*****************************************************************************
**	Ende
*****************************************************************************
*/


