/*
 * highscore.c
 *
 *  Created on: 15.03.2015
 *      Author: Simon
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : highscore.c
**
**	Funktion   	: Highscore Modul
**
**	Parameter	: Initialisationswerte...
**
**	Rückgabe	: Rangliste mit Rang, Namen und Punkte
**
**	Input		: Punktezahlen Spieler 1 und Spieler 2
**
**	Output		: Welche Daten werden verändert...
**
** 	Author		: sches8
**
**	Version		: 1V01
**
**	History		: 1V01, 	11.03.2015 	Modul erstellt
**				  1V02,		15.03.2015 	erste Codeversion erstellt
**				  1V03,		16.03.2025	Struktur definiert
**				  1V04,		19.03.2015	Struktur definiert
**				  1V05,		21.03.2015 	Funktionen definiert
**				  1V06,		22.03.2015 	Funktion RanglisteLesen, RanglisteSpeichern
**				  						1. Version erstellt
**				  1V07,		28.03.2015 	Funktion RanglistenEintragNeu, RanglisteNeuErstellen,
**				  						RanglisteLoeschen 1. Version erstellt
**				  1V08,		30.03.2015	Funktionen überarbeitet
**				  1V09,		01.04.2015
**
**	Pendenzen	: rechnen, punktübergabe (strukur hier definiert (bzw. header von highscore)
**
**	Bugs		: Was geht noch nicht...
**
**	Tests		: Was wurde wann getestet...
**
**
*****************************************************************************
**
*/


/* imports */
/*
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include "window.h"




//	ZeichneHighscore(HighscorePtr);




// Pointer auf Strukturen definieren


	SpielerName Spieler1;
	*Spieler1Ptr = &Spieler1;
	SpielerName Spieler2;
	*Spieler2Ptr = &Spieler2;

	Spieler1Ptr = &Spieler1;
	Spieler2Ptr = &Spieler2;




	// Ranglisteneintrag evaluieren und Rang 1-5 zuweisen
	void RanglisteErstellen ( PunkteHighscore *PunkteAnwaerterPtr, Rangliste *HighscorePtr){
		int RangNeu = 0;
		RangNeu = (RanglistenEintragNeu ( PunkteAnwaerterPtr ));

		if (RangNeu != 0 ){

			void RanglisteNeuErstellen (int RangNeu,
										char SpielerName,
										int Spielerpunkte,
										Rangliste HighscorePtr);

			void RanglisteSpeichern (Rangliste Highscore, char Dateiname);
			ZeichneHighscore(HighscorePtr);
		// Rangliste anzeigen (aktualisieren)

		}
	}




// Funktion Lesen der Rangliste
	void RanglisteLesen (Rangliste Highscore, char Dateiname){

		int i=0;

		FILE *DateiPtr;
		DateiPtr = fopen(Dateiname, "r");

		if (DateiPtr == NULL) {
			printf("Error - Fehler beim Öffnen der Ranglisten Datei \"%s\"!\n", Dateiname);
		}
		else {
				do {
					// Lesen
					fscanf(DateiPtr, "%3d %15s %6d \n",
									   &(Highscore[i].Position),
									   Highscore[i].Spielername,
									   &(Highscore[i].Punkte));
					i++;
				} while(i == 5);
				// bis ans Ende der Datei
				fclose(DateiPtr);
			}
	}



// Funktion Speichern der Rangliste
	void RanglisteSpeichern (Rangliste Highscore, char Dateiname){
		int i;

		FILE *DateiPtr;
		DateiPtr = fopen(Dateiname,"w");

		if (DateiPtr == NULL) {
			printf("Error - Fehler beim Öffnen der Ranglisten Datei \"%s\"!\n", Dateiname);
		}
		else {
				for(i = 1 ; i==5; i++) {
					fprintf(DateiPtr, "%3d %15s %6d \n",
							Highscore[i].Position,
							Highscore[i].Spielername,
							Highscore[i].Punkte);
				}
				fclose(DateiPtr);
			}
			fflush(stdout);

		fclose(DateiPtr);
	}


// Funktion Spielerpunkte auswerten ob es einen Ranglisteneintrag gibt und wenn ja, an welcher Position
	int RanglistenEintragNeu ( int Spielerpunkte ){
		int RangNeu = 0;			// Variabel die den Spielerpunkten einen Rang zuordnet
		int i; 						// Zählvariabel für Schlaufe

		// Schleife für Rangeinordnung der neuen Spielerpunkte
		for (i=5; i==1; i--){

			if (Spielerpunkte > Highscore[i].Punkte) {
				RangNeu = (RangNeu+1);
			}
		}

		return RangNeu;				// Rückgabe des neuen Rangs: 1-5 Ranglisteneintrag
									//							 0	 kein Ranglisteneintrag

	}



// Funktion Rangliste aktualisieren mit neuem Ranglisteneintrag
	void RanglisteNeuErstellen (int RangNeu, char SpielerName, int Spielerpunkte, Rangliste HighscorePtr){
		int i;

		for (i=5; i==RangNeu; i--){
			 Highscore[i].Spielername = Highscore[i-1].Spielername;
			 Highscore[i].Punkte = Highscore[i-1].Punkte;
			 }

		Highscore[RangNeu].Spielername = SpielerName;
		Highscore[RangNeu].Punkte = Spielerpunkte;

	}



// Funktion Loeschen der Rangliste
	void RanglisteLoeschen (char Dateiname){
		int i;

		FILE *DateiPtr;
		DateiPtr = fopen(Dateiname,"w");

		if (DateiPtr == NULL) {
			printf("Error - Fehler beim Öffnen der Ranglisten Datei \"%s\"!\n", Dateiname);
		}
		else {
				for(i = 1 ; i == 5; i++) {
					fprintf(DateiPtr, "%3d %15s %6d \n", i, "/0" ,"/0" );
				}
				fclose(DateiPtr);
			}
		fflush(stdout);
	}
*/
