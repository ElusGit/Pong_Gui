/**
*****************************************************************************
**	Projekt Pong
**	BTE 5052	FS2015
*****************************************************************************
**
**	File        	: GUI.c
**
**	Funktion   	: Grundmodul für die graphische Darstellung des Spielfelds
**					Testversion für Modulkommunikation)
**
**	Parameter	: void
**
**	Rückgabe	: void
**
**	Input		: struct AnzeigeParameter
**
**	Output		: -
**
** 	Author		: Michael Schmutz
**
**	Version		: 1.0
**
**	History		: 	09.03.2015: Erstellt
**					11.03.2015:	Implementierung AnzeigeParameterPointer
**					12.03.2015: Anpassung an Steuerung, Uebernahme der Pointer aus Steuerung
**					28.03.2015: Erstellung ZeichneHighscore
**
**	Pendenzen	: Punktestände (Fehlermeldung pointe...)
**
**	Bugs		:
**
**	Tests		:
**
**
*****************************************************************************
**/

#include "error.h"
#include "window.h"
#include "Spielsteuerung.h"
#include "Header.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


 /**
*****************************************************************************
**	Projekt Pong / OeffneGrafik
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktion   	: Stellt das Grundfenster zur Verfügung

**	Input		: Void
**
**	Output		: Void
**
** 	Author		: Michael Schmutz

*****************************************************************************
**/

void OeffneGrafik()
	{
	InitGraphic(1600, 810);
	}

/**
*****************************************************************************
**	Projekt Pong / SchliesseGrafik
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktion   	: Schliesst das Grundfenster

**	Input		: Void
**
**	Output		: Void
**
** 	Author		: Michael Schmutz

*****************************************************************************
**/

void SchliesseGrafik()
	{
	CloseGraphic();
	}

/**
*****************************************************************************
**	Projekt Pong / ZeichneSpielfeld
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktion   	: Erstellt & aktualisiert das gesamte Spielfeld inkl Pads, Ball, Hindernissen und Spielpunktestand

**	Input		: AnzeigeParameter
**
**	Output		: Void
**
** 	Author		: Michael Schmutz

*****************************************************************************
**/

void ZeichneSpielfeld(AnzeigeParameter *PtrA,SpielModus *ModusPtr)
	{

	char SpielPunktebuffer1[1];
	char SpielPunktebuffer2[1];
	snprintf(SpielPunktebuffer1,sizeof(SpielPunktebuffer1), "%d\n ",PtrA->Punkte1);
	snprintf(SpielPunktebuffer2,sizeof(SpielPunktebuffer2), "%d\n ",PtrA->Punkte2);



			// Hintergruende

			DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK, 1) ;		// Spielfeld
			DrawFilledRectangle(1300,0, 400, 810, COL_BLACK, 1) ;	//	Bereich Highscore
			DrawFilledRectangle(0,750,1300,60,COL_BLACK,1);			// Bereich Spielernamen / Punkte

			SelectFont("LCD", 30, FONT_BOLD);

			//Spielernamen

			DrawTextXY(300,800, COL_GREEN, "Fritzu");
			DrawTextXY (750,800, COL_GREEN, "Haensu");

			//Felder für Punktezahl

			DrawFilledRectangle(520,795,30,50,COL_BLACK_TRANSPARENT,1);
			DrawFilledRectangle(650,795,30,50,COL_BLACK_TRANSPARENT,1);

			DrawTextXY (521,796,COL_GREEN,SpielPunktebuffer1);
			DrawTextXY (651,796,COL_GREEN,SpielPunktebuffer2);

			// Mittellinie

			DrawLine (650,0,650,50,COL_GREEN_3,4);
			DrawLine (650,60,650,110,COL_GREEN_3,4);
			DrawLine (650,120,650,170,COL_GREEN_3,4);
			DrawLine (650,180,650,230,COL_GREEN_3,4);
			DrawLine (650,240,650,290,COL_GREEN_3,4);
			DrawLine (650,300,650,350,COL_GREEN_3,4);
			DrawLine (650,360,650,410,COL_GREEN_3,4);
			DrawLine (650,420,650,470,COL_GREEN_3,4);
			DrawLine (650,480,650,530,COL_GREEN_3,4);
			DrawLine (650,540,650,590,COL_GREEN_3,4);
			DrawLine (650,600,650,650,COL_GREEN_3,4);
			DrawLine (650,660,650,700,COL_GREEN_3,4);
			DrawLine (650,710,650,750,COL_GREEN_3,4);


			// Pads 1 & 2 zeichnen

			DrawFilledRectangle(10,PtrA->YPosPad1 ,15,PtrA->LaengePad,COL_GREEN,1) ;
			DrawFilledRectangle(1274,PtrA->YPosPad2 ,15,PtrA->LaengePad,COL_GREEN,1) ;

			// Hindernisse zeichnen
			if(ModusPtr->Schwierigkeitsgrad>=4){
			DrawFilledRectangle(PtrA->XPosHindernis1,PtrA->YPosHindernis1 ,15,150,COL_GREEN,1) ;
			DrawFilledRectangle(PtrA->XPosHindernis2,PtrA->YPosHindernis2,15,150,COL_GREEN,1) ;
			}
			// Begrenzungsbalken zeichnen

			DrawFilledRectangle(0,0,1300,10,COL_GREEN,1) ;
			DrawFilledRectangle(0,750,1300,10,COL_GREEN,1) ;

			// Ball zeichnen

			DrawFilledCircle(PtrA->XPosBall1,(PtrA->YPosBall1),20,20, COL_GREEN, 1) ;

			if(ModusPtr->Schwierigkeitsgrad==5 && ModusPtr->ZweiSpieler==1){
			DrawFilledCircle(PtrA->XPosBall2,(PtrA->YPosBall2),20,20, COL_RED, 1) ;
			}
			WaitMs(5);

	}
/**
*****************************************************************************
**	Projekt Pong / OeffneGrafik
**	BTE 5052	FS2015
*****************************************************************************
**
**	Funktion   	: Erstellt und aktualisiert die Highscoretabelle

**	Input		: Rangliste Highscore[5]
**
**	Output		: Void
**
** 	Author		: Michael Schmutz

*****************************************************************************
**/
void ZeichneHighscore(Rangliste Highscore[5])
	{


char Textbuffer1[128];
char Textbuffer2[128];
char Textbuffer3[128];
char Textbuffer4[128];
char Textbuffer5[128];

char Punktebuffer1[10];
char Punktebuffer2[10];
char Punktebuffer3[10];
char Punktebuffer4[10];
char Punktebuffer5[10];

 // Werte in Textbuffer/ Punktebuffer schreiben
SelectFont("LCD", 30, FONT_BOLD);
DrawTextXY(1340,50, COL_GREEN,"Highscore");

snprintf(Textbuffer1,sizeof(Textbuffer1), "%d\t %s",Highscore[0].Position,Highscore[0].Spielername);
snprintf(Textbuffer2,sizeof(Textbuffer2), "%d\t %s",Highscore[1].Position,Highscore[1].Spielername);
snprintf(Textbuffer3,sizeof(Textbuffer3), "%d\t %s",Highscore[2].Position,Highscore[2].Spielername);
snprintf(Textbuffer4,sizeof(Textbuffer4), "%d\t %s",Highscore[3].Position,Highscore[3].Spielername);
snprintf(Textbuffer5,sizeof(Textbuffer5), "%d\t %s",Highscore[4].Position,Highscore[4].Spielername);


snprintf(Punktebuffer1,sizeof(Punktebuffer1), "%d",Highscore[0].Punkte);
snprintf(Punktebuffer2,sizeof(Punktebuffer2), "%d",Highscore[1].Punkte);
snprintf(Punktebuffer3,sizeof(Punktebuffer3), "%d",Highscore[2].Punkte);
snprintf(Punktebuffer4,sizeof(Punktebuffer4), "%d",Highscore[3].Punkte);
snprintf(Punktebuffer5,sizeof(Punktebuffer5), "%d",Highscore[4].Punkte);





// Tabelle schreiben

// Pos und Name

SelectFont("LCD", 15, FONT_BOLD);
DrawTextXY(1300,100, COL_GREEN,Textbuffer1);
DrawTextXY(1300,150, COL_GREEN,Textbuffer2);
DrawTextXY(1300,200, COL_GREEN,Textbuffer3);
DrawTextXY(1300,250, COL_GREEN,Textbuffer4);
DrawTextXY(1300,300, COL_GREEN,Textbuffer5);

// Punkte

DrawTextXY(1500,100, COL_GREEN,Punktebuffer1);
DrawTextXY(1500,150, COL_GREEN,Punktebuffer2);
DrawTextXY(1500,200, COL_GREEN,Punktebuffer3);
DrawTextXY(1500,250, COL_GREEN,Punktebuffer4);
DrawTextXY(1500,300, COL_GREEN,Punktebuffer5);


}

















/*****************************************************************************/
/*  End Module  : Mainmodule                                                 */
/*****************************************************************************/



