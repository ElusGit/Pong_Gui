/*
 * Edit.c
 *
 *  Created on: 31.03.2015
 *      Author: Michael
 */
#include "error.h"
#include "window.h"
#include "Spielsteuerung.h"
#include "Header.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void Edit(){

	char spielername1[15];
	char spielername2[15];
	int key;
	int i=0;
	strncpy(spielername1,"              ",15);
	strncpy(spielername2,"              ",15);


// Spieler 1


	for (i=0;i<=14;i++){

			DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
			DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
			DrawTextXY(550,51,COL_GREEN,"Level-Modus");
			DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
			DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");


			key=GetKeyPress();
			if((48<= key) && (key<= 122)) // 8 entspricht backspace, 13 = enter
			{
				DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
				DrawTextXY(550,51,COL_GREEN,"Level-Modus");

				DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
				DrawTextXY(550,130,COL_GREEN,"Name von Spieler 1 eingeben");

				spielername1[i]=key;
				DrawTextXY(550,200,COL_GREEN,spielername1);

			}

			if ((key==8) && (i>0)) // 8 entspricht backspace, 13 = enter
			{
				strncpy(spielername1,"______________",15);
				DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
				DrawTextXY(550,51,COL_GREEN,"Level-Modus");
				DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
				DrawTextXY(550,130,COL_GREEN,"Name von Spieler 1 eingeben");

				i=-1;

			}


	}

	// Spieler 2

i=0;
	for (i=0;i<=14;i++){
				DrawFilledRectangle(0, 0, 1300, 750, COL_BLACK,1) ;
					DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
					DrawTextXY(550,51,COL_GREEN,"Level-Modus");
					DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
					DrawTextXY(350,130,COL_GREEN,"Name von Spieler 1 eingeben");

				key=GetKeyPress();
				if((48<= key)&&(key<= 122))// 8 entspricht backspace,13 = enter
					{
					DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
					DrawTextXY(550,51,COL_GREEN,"Level-Modus");

					DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
					DrawTextXY(550,300,COL_GREEN,"Name von Spieler 2 eingeben");

					spielername2[i]=key;
					DrawTextXY(550,370,COL_GREEN,spielername2);
					}

			if ((key==8) && (i>0)) // 8 entspricht backspace
				{
					strncpy(spielername2,"______________",15);
					DrawEmptyRectangle(0, 0, 1300, 750, COL_GREEN, 4) ;
					DrawTextXY(550,51,COL_GREEN,"Level-Modus");
					DrawEmptyRectangle(150,90,1000,50, COL_GREEN, 2) ;
					DrawTextXY(550,300,COL_GREEN,"Name von Spieler 2 eingeben");

					i=-1;

				}


		}


}
