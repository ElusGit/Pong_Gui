/*
 * main.c
 *
 *  Created on: 12.03.2015
 *      Author: Simon
 */
/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        : main.c
**
**	Funktion   	: Menu State Machine
**
**	Parameter	: Initialisationswerte...
**
**	Rückgabe	: nichts
**
**	Input		: Tastatur stdin
**
**	Output		: Highscore, Spielmodus,
**
** 	Author		: sches8
**
**	Version		: 0.0.1
**
**	History		: 0V01,  	11.03.2015	Modul erstellt
**				  0V02,		16.03.2015	erste Codeversion erstellt
**				  0V03,		19.03.2015	Switch Anweisung definiert
**				  0V04,		21.03.2015	Switch Anweisung für Modus ohne Computer erstellt
**				  0V05,		23.03.2015	Switch Anweisung überarbeitet
**				  0V06,		29.03.2015	Funktionsaufruf für Spielsteuerung eingebaut
**				  0V07,		30.03.2015	Funktionsaufrufe in die Switch Anweisung eingebaut
**				  0V08,		01.04.2015	Neue Definition von MenuVar, Edit und SpielModus
**
**	Pendenzen	: Was gibts noch zu tun...
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
#include "error.h"
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "Spielsteuerung.h"


int gfxmain(int argc, char* argv []){


	// Strukturen definieren

	// Spielmodus
		SpielModus Modus;
		SpielModus *ModusPtr;
		ModusPtr=&Modus;
	//Level setzen provisorisch


	// Struktur der Rangliste definieren (Klasse erstellt)
/*		Rangliste Highscore[5] = {
									[0].Position = 1,
									[0].Spielername="Schafs1",
									[0].Punkte=185988,
									[1].Position = 2,
									[1].Spielername="00",
									[1].Punkte=19890,
									[2].Position = 3,
									[2].Spielername="kupfe",
									[2].Punkte=1859,
									[3].Position = 4,
									[3].Spielername="steve",
									[3].Punkte=129,
									[4].Position = 5,
									[4].Spielername="asdf123",
									[4].Punkte=1,
				   				 	};
				   				 	*/
	//	Rangliste *HighscorePtr;
	//	HighscorePtr = &Highscore;
	//	char Dateiname[100] = "Highscore.txt"; // Datei Rangliste Highscore
	//	void RanglisteSpeichern (Rangliste Highscore, char Dateiname);



	// Struktur für neue Punktestaende
		PunkteHighscore PunkteAnwaerter;
		PunkteHighscore *PunkteAnwaerterPtr = &PunkteAnwaerter;

	// Deklaration der Variablen
	// Textdateiname für Highscore Speicher

		//Provisorische Variablendeklaration
		int MenuEingabe=0;								//Variable um die Tastendrücke zu verwerten
		int Abbruch1;									//Abbruchflag für Untermenu im Case 1
		int AbbruchHauptmenu=1;							//Abbruchflag für das Hauptmenu

	// Schwierigkeitsgrad-Auswahl Funktion
		void SchwierigkeitsgradAuswahl(void){
				MenuVar(4);
				if(MenuEingabe != W_KEY_ESCAPE){
				MenuEingabe = GetKeyEvent();
					switch(MenuEingabe){
							case '1': ModusPtr->Schwierigkeitsgrad=1;
									SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
									break;
							case '2': ModusPtr->Schwierigkeitsgrad=2;
									SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
									break;
							case '3': ModusPtr->Schwierigkeitsgrad=3;
									SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
									break;
							case '4': ModusPtr->Schwierigkeitsgrad=4;
									SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
									break;
							case '5': ModusPtr->Schwierigkeitsgrad=5;
									SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
									break;
							//  Zurück ins Hauptmenu
							case '0': MenuVar(1);
									break;
							default: break;
					}
				}
		}


	// Highscore laden
	//	RanglisteLesen (HighscorePtr, Dateiname);
	//	ZeichneHighscore(HighscorePtr);


	// Fenster Öffnen
		OeffneGrafik();

	// Schleife State Machine der Menustruktur

		while(AbbruchHauptmenu != 0){									//Solange im Hauptmenu die Esc Taste nicht gedrückt wurde
			//Hauptmenu zeichnen
			MenuVar(1);
			//Taste auslesen
			MenuEingabe = GetKeyEvent();
			printf("%d\n",MenuEingabe);

			// State Machine der Menustruktur

			switch(MenuEingabe){										//Je nach Tastendruck den entsprechenden Case wählen

				// Hauptmenustruktur
				// 1 Levelmodus
				case '1': printf("case 1 levelmodus\n");
							//Abbruchflag für Untermenu initialisieren
							Abbruch1=1;

							while(Abbruch1 != 0){
								//Bild Zeichnen in der Schleife!!
								MenuVar(2);
								MenuEingabe = GetKeyEvent();

								switch(MenuEingabe){
										// 1.1 Levelmodus gegen Computer
										case '1':	printf("Aufruf Edit\n"); // Edit();						// Spielernamen eingeben
													printf("case 1 in levelmodus\n");
													//Spielparameter setzen
													ModusPtr->Schwierigkeitsgrad=1;
													ModusPtr->SpielMod=2;
													ModusPtr->ZweiSpieler=0;
													SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);			 // Spiel starten
													// evtl. Punkteeintrag Highscore
													break;


										// 1.2 Levelmodus Zweispieler
										case '2':	printf("Aufruf Edit\n"); // Edit();						// Spielernamen eingeben
													printf("case 2 in levelmodus\n");
													//Spielparameter setzen
													ModusPtr->Schwierigkeitsgrad=1;
													ModusPtr->SpielMod=2;
													ModusPtr->ZweiSpieler=1;
													SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);			 // Spiel starten

													//RanglisteErstellen (PunkteAnwaerterPtr, HighscorePtr);
													//ZeichneHighscore(HighscorePtr);

													break;

										// 1.0 zurück ins Hauptmenu
										case '0':	printf("case 0 in levelmodus\n");
													Abbruch1=0;												//Abbruchflag für Untermenu im Case 1 setzen
													break;


										default: 	break;
							}
						}

						break;						//Break Case Hauptmenu
				// 2 Einzelspiel
/*				case '2': MenuVar(3);
				printf("case 2 Einzelspiel");
						if(MenuEingabe != W_KEY_ESCAPE){
						MenuEingabe = GetKeyEvent();

						switch(MenuEingabe){
								// 2.1 Einzelspiel gegen den Computer
								case '1':	ModusPtr->SpielMod=2;
										ModusPtr->ZweiSpieler=0;
										SchwierigkeitsgradAuswahl();
										SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
										// Hauptmenu
										MenuVar(1);
										break;

								// 2.2 Einzelspiel Zweispieler
								case '2':	Edit();
										ModusPtr->SpielMod=2;
										ModusPtr->ZweiSpieler=1;
										SchwierigkeitsgradAuswahl();
										SpielSteuerung(ModusPtr, PunkteAnwaerterPtr);
										// Hauptmenu
										MenuVar(1);
										break;

								// 2.0 Zurück ins Hauptmenu
								case '0': MenuVar(1);
										break;
								default: break;

						}
						}
						break;*/

/*
				// 3 Highscore
				case 3:	MenuVar(5); // Highscoremenu
						if(IsKeyEventReady() != 0){
						MenuEingabe = GetKeyEvent();
							// Auswahl Levelmodus
							switch(MenuEingabe){
									// Einträge löschen
									case 1: RanglisteLoeschen (Dateiname);
											RanglisteLesen (HighscorePtr,Dateiname);
											ZeichneHighscore(HighscorePtr);
											MenuVar(1);
											break;
									// Beenden
									case 0: MenuVar(1);
											break;
											default: break;
							}
						}
						break;

		*/		// 4 Beenden
/*				case '4': 	SchliesseGrafik();
							system("PAUSE");
							return 0;
							break;*/
				case W_KEY_ESCAPE:
							AbbruchHauptmenu=0;										//Wird die Esc Taste im Hauptmenu gedrückt, Abbruchflag auf 0 setzen
							break;

				default: break;
			}
		}

		//Testprint Highscore
		printf("Spieler 1: %d\n", PunkteAnwaerterPtr->PunkteHighscore1);
		printf("Spieler 2: %d\n", PunkteAnwaerterPtr->PunkteHighscore2);

		//Schliessen des Fensters
		SchliesseGrafik();


return 0;
}


