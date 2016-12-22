#ifndef _V_ALLEG_H
#define _V_ALLEG_H 1

//#include <allegro.h>
typedef struct gRGB 
{
  unsigned char r, g, b;
   unsigned char filler;
 }
gRGB; 


// "borrowed" from allegro
  
#define gKEY_A KEY_A
#define gKEY_B KEY_B
#define gKEY_C KEY_C
#define gKEY_D KEY_D
#define gKEY_E KEY_E
#define gKEY_F KEY_F
#define gKEY_G KEY_G
#define gKEY_H KEY_H
#define gKEY_I KEY_I
#define gKEY_J KEY_J
#define gKEY_K KEY_K
#define gKEY_L KEY_L
#define gKEY_M KEY_M                
#define gKEY_N KEY_N
#define gKEY_O KEY_O              
#define gKEY_P KEY_P             
#define gKEY_Q KEY_Q            
#define gKEY_R KEY_R           
#define gKEY_S KEY_S          
#define gKEY_T KEY_T                
#define gKEY_U KEY_U               
#define gKEY_V KEY_V              
#define gKEY_W KEY_W             
#define gKEY_X KEY_X            
#define gKEY_Y KEY_Y           
#define gKEY_Z KEY_Z          
#define gKEY_0 KEY_0         
#define gKEY_1 KEY_1        
#define gKEY_2 KEY_2       
#define gKEY_3 KEY_3          
#define gKEY_4 KEY_4
#define gKEY_5 KEY_5              
#define gKEY_6 KEY_6              
#define gKEY_7 KEY_7              
#define gKEY_8 KEY_8              
#define gKEY_9 KEY_9              
#define gKEY_0_PAD KEY_0_PAD          
#define gKEY_1_PAD KEY_1_PAD          
#define gKEY_2_PAD KEY_2_PAD           
#define gKEY_3_PAD KEY_3_PAD           
#define gKEY_4_PAD KEY_4_PAD            
#define gKEY_5_PAD KEY_5_PAD            
#define gKEY_6_PAD KEY_6_PAD            
#define gKEY_7_PAD KEY_7_PAD            
#define gKEY_8_PAD KEY_8_PAD            
#define gKEY_9_PAD KEY_9_PAD            
#define gKEY_F1 KEY_F1               
#define gKEY_F2 KEY_F2
#define gKEY_F3 KEY_F3               
#define gKEY_F4 KEY_F4               
#define gKEY_F5 KEY_F5               
#define gKEY_F6 KEY_F6               
#define gKEY_F7 KEY_F7               
#define gKEY_F8 KEY_F8               
#define gKEY_F9 KEY_F9               
#define gKEY_F10 KEY_F10              
#define gKEY_F11 KEY_F11 
#define gKEY_F12 KEY_F12            
#define gKEY_ESC KEY_ESC
#define gKEY_LSHIFT KEY_LSHIFT
#define gKEY_RSHIFT KEY_RSHIFT
#define gKEY_ENTER KEY_ENTER
#define gKEY_SPACE KEY_SPACE
#define gKEY_ALT KEY_ALT
#define gKEY_UP KEY_UP
#define gKEY_DOWN KEY_DOWN
#define gKEY_LEFT KEY_LEFT
#define gKEY_RIGHT KEY_RIGHT
#define gKEY_RCONTROL KEY_RCONTROL
#define gKEY_BACKSPACE KEY_BACKSPACE
#define gKEY_SLASH KEY_SLASHvoid gExitEmulator (void);
void gset_color (int index, gRGB * p);
void gclear (void);
void dumpVirtualToScreen (void);
void gtextout (char *b, int x, int y, int color);
//void gtextoutb (char *b, int x, int y, int color, FONT * tfont);
void init_wrapper (void);
void gacquire_bitmap (void);
void grelease_bitmap (void);
void InitGraphics (void);
void gclear_to_color (int color);
void gUpdateRect (int x, int y, int sizeX, int sizeY);
void gPutPixel (int x, int y, int col);
void gbox (int x1, int y1, int x2, int y2, int color);
void grectangle (int x1, int y1, int x2, int y2, int color);
void ghline (int x1, int y1, int x2, int color);
void InitSystem (void);
void v_initmouse (void);
int galert (const char *s1, const char *s2, const char *s3, const char *b1,
	     const char *b2, int c1, int c2);

// sound functions 
void gInitSound (void);
unsigned char *gGetSampleBuffer (void);
void gPlaySound (void);
volatile int getVoicePos (void);
void playMainSample (void);
void gSoundSync (void);

// keyboard functions
void init_keyboard(void);
void UpdateKeyboard (void);

#endif	/* v_alleg.h */ 
