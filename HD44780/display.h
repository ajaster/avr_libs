#ifndef _DISPLAY
#define _DISPLAY

/* Display define */
#define DDRDISP DDRA
#define DISP    PORTA
#define DB4     PA3
#define DB5     PA4
#define DB6     PA5
#define DB7     PA6
#define RS      PA1
#define DE      PA2
/*              */

#define  DBON(DB) (DISP |=  (1 << (DB)))
#define DBOFF(DB) (DISP &= ~(1 << (DB)))

void RSstate(byte mode);
void db(byte dn, byte allbyte);
void clearDisp(void);
void setCursor(byte pos, byte line, byte disp);
byte printWithMenu(const char str[], char leng, byte curs);
void printDisp(const char str[]);
byte nextDisp(void);
void prevDisp(void);
void displayInit(void);
int  displayMain(void);
byte getCurrentMenuNum(void);
byte setNextMenuPos(byte curPos);
byte drawCursorNext(void);
void printReg(byte reg);
void clearCurrentStr(void);
void setCursorOnStr(byte n);

#endif //DISPLAY
