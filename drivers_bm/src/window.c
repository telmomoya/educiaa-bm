/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

#include "window.h"

#include "GLCDColor.h"
#include "GLCDFonts.h"
#include "GLCDgui.h"
#include "GLCDguiEvent.h"
#include "GLCDLowLevel.h"
#include "GLCDPrimitives.h"
#include "SysFont3x5.h"
#include "SystemFont5x7.h"
#include "string.h"

#ifndef NULL
#define NULL	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/*==================[internal data declaration]==============================*/
WList WIndex;
static TWindow* ActiveWindow;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/



void GUI_Window_ListInit (void)
{
	WIndex.N_Windows = 0;
	ActiveWindow = NULL;
}

void GUI_Window_ObjectListInit (OList* pOList)
{
	pOList->N_Texts = 0;
	pOList->N_Pictures = 0;
	pOList->N_Buttons = 0;
}

void GUI_Window_Create ( char* _name, uint8_t* _color, char* _text )
{
	uint8_t i = (WIndex.N_Windows);
	_name = strcat (_name,"\n");
	_text = strcat (_text,"\n");


	strncpy (WIndex.Windows[i].name, _name, strlen(_name));
	strncpy (WIndex.Windows[i].text, _text, strlen(_text));
	WIndex.Windows[i].color = *_color;

	GUI_Window_ObjectListInit( &WIndex.Windows[i].WindowObjects );

	WIndex.N_Windows++;
}

void GUI_Window_Draw ( char* windowName )
{
    uint8_t xi, xf, yi, yf;
    //Search window in list in case we want to draw a window that isn't the active one
    if (strcmp(ActiveWindow->name, windowName) != 0)
    {
    	uint8_t i;
        for (i=0; i < WIndex.N_Windows; i++)
        {
        	if (strcmp(WIndex.Windows[i].name, windowName) == 0)
        	{
        		ActiveWindow = &WIndex.Windows[i];
        		break;
        	}
        }
    }

    // Clean the display
    GLCDPrimitives_ClearScreen ( ActiveWindow->color );

    // Window limiters lines
    xi = 0;
    xf = GLCDLowLevel_DISPLAY_WIDTH - 1;
    yi = 0;
    yf = GLCDLowLevel_DISPLAY_HEIGHT - 1;

    if (ActiveWindow->color == WHITE)
    {
    	GLCDPrimitives_DrawLine (xi, yi, xf, yi, BLACK);
    	GLCDPrimitives_DrawLine (xf, yi, xf, yf, BLACK);
    	GLCDPrimitives_DrawLine (xf, yf, xi, yf, BLACK);
    	GLCDPrimitives_DrawLine (xi, yf, xi, yi, BLACK);
        // Draw window name
        GLCDPrimitives_FillRect (xi, yi, GLCDLowLevel_DISPLAY_WIDTH, 8, BLACK);

//        ActiveWindow = &WIndex.Windows[0];
    	GLCD_SelectFont(System5x7, WHITE);
    	GLCD_CursorFreeTo(1,1);
    	GLCD_FreePuts( ActiveWindow->text );
    }
    else
    {
    	GLCDPrimitives_DrawLine (xi, yi, xf, yi, WHITE);
    	GLCDPrimitives_DrawLine (xf, yi, xf, yf, WHITE);
    	GLCDPrimitives_DrawLine (xf, yf, xi, yf, WHITE);
    	GLCDPrimitives_DrawLine (xi, yf, xi, yi, WHITE);
        // Draw window name
        GLCDPrimitives_FillRect (xi, yi, GLCDLowLevel_DISPLAY_WIDTH, 8, WHITE);

//        ActiveWindow = &WIndex.Windows[0];
        GLCD_SelectFont(System5x7, BLACK);
    	GLCD_CursorFreeTo(1,1);
    	GLCD_FreePuts( ActiveWindow->text );
    }

    GUI_Window_DrawObjects( &ActiveWindow->WindowObjects);

    // Send data to the GLCD
    GLCDLowLevel_SwapBuffer ();
}

void GUI_Window_DrawObjects (OList* pOList)
{
	uint8_t i;
	for (i = 0; i < pOList->N_Texts; i++)
		GUI_Text_Draw( &pOList->Texts[i]);

	for (i = 0; i < pOList->N_Buttons; i++)
		GUI_Button_Draw( &pOList->Buttons[i]);

	for (i = 0; i < pOList->N_Pictures; i++)
		GUI_Picture_Draw( &pOList->Pictures[i]);

//	for (i = 0; i < pOList->N_TextSliders; i++)
//		GUI_TextSlider_Draw(pOList->TextSliders[i]);
}

void GUI_Window_RedrawActiveWindow ()
{
	GUI_Window_Draw ( ActiveWindow->name );
}

//void GUI_Window_RaiseEvent (GLCDgui_TEvent* event)
//{
//	TList* pObjectsList;
//	TNode* pAuxNode;
//	uint8_t objectDetected = 0;
//
//	switch (event->eventType)
//	{
//		case GLCD_CLICK:
//			// Recorro la lista de objetos y si el evento le pertenece a algún objeto lo disparo
//			pObjectsList = &(pActiveWindow->objectsList);
//			pAuxNode = pObjectsList->first;
//			if ( pAuxNode != NULL )
//			{
//				objectDetected = GUI_Object_RaiseEvent ( (TObject*) pAuxNode->data, event );
//				while ( objectDetected == 0 && pAuxNode->next != NULL )
//				{
//					pAuxNode = pAuxNode->next;
//					objectDetected = GUI_Object_RaiseEvent ( (TObject*) pAuxNode->data, event );
//				}
//			}
//		break;
//
//		case GLCD_SCROLL_LEFTTORIGHT:
//			GUI_Window_Draw (pActiveWindow->fatherName);
//		break;
//	}
//}

void GUI_Window_AddText (char* _windowName, char* _name, uint16_t _xPos, uint16_t _yPos,
						 char* _fontName, uint8_t _fontColor, char* _text)
{
	TText* pText;
	TWindow* pWin;
	uint8_t i;
	uint8_t N;
    for (i=0; i < WIndex.N_Windows; i++)
   	{
    	if (strcmp(WIndex.Windows[i].name, _windowName) == 0)
       	{
       		pWin = &WIndex.Windows[i];
       		pText = &pWin->WindowObjects.Texts[pWin->WindowObjects.N_Texts];
       		GUI_Text_Create(pText, _windowName, _name, _xPos, _yPos, _fontName, _fontColor, _text);

       		N = WIndex.Windows[i].WindowObjects.N_Texts;
       		WIndex.Windows[i].WindowObjects.Texts[N] = *pText;
       		WIndex.Windows[i].WindowObjects.N_Texts++;
       		break;
       	}
    }
}

void GUI_Window_AddButton ( char* _windowName, char* _name, uint16_t _height, uint16_t _width,
							uint16_t _xPos,	uint16_t _yPos, uint8_t _color, char* _fontName,
							uint8_t _fontColor, char* _text)
{
	TButton* pButton;
	TWindow* pWin;

	uint8_t i;
    for (i=0; i < WIndex.N_Windows; i++)
   	{
       	if (strcmp(WIndex.Windows[i].name, _windowName))
       	{
       		pWin = &WIndex.Windows[i];
       		pButton = &pWin->WindowObjects.Buttons[pWin->WindowObjects.N_Buttons];
       		GUI_Button_Create(pButton, _windowName, _name, _height, _width, _xPos,
       						  _yPos, _color, _fontName, _fontColor, _text);
       		break;
       	}
    }
}

void GUI_Window_AddPicture (char* _windowName, char* _name, uint16_t _xPos, uint16_t _yPos,
		  	  	  	  	  	uint16_t _width, uint16_t _height, const uint8_t* _bitmap,
		  	  	  	  	  	uint8_t _color )
{
	TPicture* pPicture;
	TWindow* pWin;

	uint8_t i, N;
    for (i=0; i < WIndex.N_Windows; i++)
   	{
       	if (strcmp(WIndex.Windows[i].name, _windowName) == 0)
       	{
       		pWin = &WIndex.Windows[i];
       		pPicture = &pWin->WindowObjects.Pictures[pWin->WindowObjects.N_Pictures];
       		GUI_Picture_Create(pPicture, _windowName, _name, _xPos, _yPos, _width, _height, _bitmap, _color);

       		N = WIndex.Windows[i].WindowObjects.N_Pictures;
       		WIndex.Windows[i].WindowObjects.Pictures[N] = *pPicture;
       		WIndex.Windows[i].WindowObjects.N_Pictures++;
       		break;
       	}
    }
}

//void GUI_Window_AddTextSlider (char* _windowName, char* _name, uint16_t _xPos, uint16_t _yPos,
//						 char* _fontName, uint8_t _fontColor, char* _text)
//{
//	uint8_t i;
//	TText* pText;
//	TWindow* pWin;
//    for (i=0; i < WIndex->N_Windows; i++)
//   	{
//       	if (WIndex->Windows[i]->name == _windowName)
//       	{
//       		pWin = WIndex->Windows[i];
//       		pText = pWin->WindowObjects->Texts[pWin->WindowObjects->N_Texts];
//       		GUI_Text_Create(pText, _windowName, _name, _xPos, _yPos, _fontName, _fontColor, _text);
//       		break;
//       	}
//    }
//}

void GUI_Window_GetText (const char* const textName, TText* pText)
{
	TWindow* pWin;
	OList* pOList;
	uint8_t i, j;
	uint8_t end_search = FALSE;

	for (i = 0; i < WIndex.N_Windows; i++)
	{
		pWin = &WIndex.Windows[i];
		pOList = &pWin->WindowObjects;
		for (j = 0; j < pOList->N_Texts; j++)
		{
			pText = &pOList->Texts[j];
			if (pText->name == textName)
			{
				end_search = TRUE;
				break;
			}
		}
		if (end_search == TRUE)
			break;
		else
			pText = NULL;
	}
}

void GUI_Window_GetPicture (const char* const pictureName, TPicture* pPicture)
{
	TWindow* pWin;
	OList* pOList;
	uint8_t i, j;
	uint8_t end_search = FALSE;

	for (i = 0; i < WIndex.N_Windows; i++)
	{
		pWin = &WIndex.Windows[i];
		pOList = &pWin->WindowObjects;
		for (j = 0; j < pOList->N_Pictures; j++)
		{
			pPicture = &pOList->Pictures[j];
			if (pPicture->name == pictureName)
			{
				end_search = TRUE;
				break;
			}
		}
		if (end_search == TRUE)
			break;
		else
			pPicture = NULL;
	}
}
