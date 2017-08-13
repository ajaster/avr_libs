/*
#####################################################
This is  HD44780 library by yota9
4 bit mode ONLY!
Including functions to make menu
FUNCTIONS:
-----------------------------------------------------
DBON/DBOFF(bit) - set/reset bit on port
displayInit() - init display
RSstate(n) - program(1) or command(0) mode
sigEn() - signal E
clearDisp() - clear display
db(b) - send byte on port; use to write 1 sybmol!
printDisp(str) - print string
printWithMenu(str) - print string, auto menu
setCursor(n) - set cursor to n position
nextDisp()/prevDisp() - next(+16)/prev(-16) display
getCurrentMenuNum() - 1-4 current menu position 
setNextMenuPos() - set next menu position
drawCursorNext() - change cursor to next position
printReg() - print bin register
-----------------------------------------------------
#####################################################
*/
#include "display.h"

byte cPos = 0;    //cursor position 0 - 4B
byte rsState = 0; //command or byte mode
byte dispNum = 0; //display number (0 or 1)
const byte DBOUT[] = {DB4, DB5, DB6, DB7};

static inline void sigEn(void){
  DBON(DE);
  delay_us(55);
  DBOFF(DE);
}

void RSstate(byte mode){
  if(mode){ //display
    DBON(RS);
    rsState = 1;
  }
  else{ //command
    DBOFF(RS);
    rsState = 0;
  }
}

void db(byte dn, byte allbyte){
  byte fbyte = dn >> 4;
  for(char i = 3; i >= 0; i--)
    (fbyte >> i) & 0x01 ? DBON(DBOUT[i]) : DBOFF(DBOUT[i]);
  sigEn();
  if(allbyte){
    for(char i = 3; i >= 0; i--)
      (dn >> i) & 0x01 ? DBON(DBOUT[i]) : DBOFF(DBOUT[i]);
    sigEn();
  }
  if(rsState)
    cPos += 1;
}

void clearDisp(void){
  RSstate(0);
  db(0b00000001, 1);
  delay_ms(2);
  RSstate(1);
  cPos = 0;
  dispNum = 0;
}


void setCursor(byte pos, byte line, byte disp){
  if(disp == 1)
    pos += 0x10;
  if(line == 1)
    pos += 0x28;
  if((pos < 0) && (pos > 0x4B))
    return;
  RSstate(0);
  if((pos < cPos) && (pos >= 0))
    for(char i = cPos; i > pos; i--)
      db(0b00010000, 1);
  else if((pos > cPos) && (pos <= 0x4B))
    for(char i = cPos; i < pos; i++)
      db(0b00010100, 1);
  cPos = pos;
  RSstate(1);
}

byte getCurrentMenuNum(void){
  if((cPos >= 0) && (cPos <= 0xF))
    return 1;
  else if((cPos >= 0x28) && (cPos <= 0x37))
    return 2;
  else if((cPos > 0xF) && (cPos < 0x28))
    return 3;
  else if((cPos > 0x37) && (cPos <= 0x4B))
    return 4;
  return 0;
}

byte setNextMenuPos(byte curPos){
  switch(curPos){
    case 2:
      setCursor(0x28, 0, 0);
      return 0x28;
    case 3:
      setCursor(0x10, 0, 0);
      return 0x10;
    case 4:
      setCursor(0x38, 0, 0);
      return 0x38;
    default:
      setCursor(0, 0, 0);
      return 0;
  }
}

void setCursorOnStr(byte n){
  switch(n){
  case 1:
    setCursor(0, 0, 0);
    break;
  case 2:
    setCursor(0, 1, 0);
    break;
  case 3:
    setCursor(0, 0, 1);
    break;
  case 4:
    setCursor(0, 1, 1);
    break;
  }
}

void clearCurrentStr(void){
	byte currentNum;
  currentNum = getCurrentMenuNum();
  setCursorOnStr(currentNum);
  for(byte i = 0; i < 15; i++)
    db(0b10010000, 1);
  setCursorOnStr(currentNum);
}

byte printWithMenu(const char str[], char leng, byte curs){
    //prints recursive
    // -> 1 str 1 screen - > 2 str 1 screen ->
    // -> 1 str 2 screen ->  2 str 2 screen ->
    byte i = 0, currentNum;
    currentNum = getCurrentMenuNum();
    setCursorOnStr(currentNum);
    if(!leng)
      leng = 16;
    for(i = 0; i < leng && str[i] != '\0'; i++)
      db(str[i], 1);
    if(curs){
      for(; i < 9; i++)
        db(0x20, 1);
      if(currentNum == 1){
        db('<', 1);
        db('-', 1);
      }
    }
    for(; i < 16; i++)
      db(0b10010000, 1); //free symbol
    setNextMenuPos(currentNum + 1);
    return currentNum;
}

byte drawCursorNext(void){
  byte cur = getCurrentMenuNum();
  switch(cur){
    case 1:
      setCursor(9, 0, 0);
      break;
    case 2:
      setCursor(9, 1, 0);
      break;
    case 3:
      setCursor(9, 0, 1);
      break;
    case 4:
      setCursor(9, 1, 1);
      break;
  }
  db(0x20, 1);
  db(0x20, 1);
  setCursor(setNextMenuPos(cur + 1) + 9, 0, 0);
  db('<', 1);
  db('-', 1);
  if(cur == 2)
    nextDisp();
  else if(cur == 4)
    prevDisp();
  delay_ms(300);
  return cur;
}

void printDisp(const char str[]){
  while(*str != '\0'){
    db((byte) *str, 1);
    str += 1;
  }
}

byte nextDisp(void){
  if(dispNum == 0){
    RSstate(0);
    for(char i = 0; i < 16; i++)
      db(0b00011000, 1);
    dispNum = 1;
    RSstate(1);
    return 0;
  }
  return 1;
}

void prevDisp(void){
  if(dispNum == 1){
    RSstate(0);
    for(char i = 0; i < 16; i++)
      db(0b00011100, 1);
    dispNum = 0;
    RSstate(1);
  }
}

void printReg(byte reg){
  for(char ii = 7; ii >= 0; ii--){
    char buf[2];
    buf[0] = ((reg & (1 << ii)) >> ii);
    buf[0] += 48;
    buf[1] = '\0';
    printDisp((const char*) &buf);
  }
}

void displayInit(void){
  delay_ms(15);
  DDRDISP |= (1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7) | (1 << RS) | (1 << DE);
  RSstate(0);
  DBOFF(DE);
  //preinit
  db(0b00110000, 0);
  delay_ms(5);
  db(0b00110000, 0);
  delay_us(100);
  db(0b00110000, 0);
  delay_us(100);
  //initing 4 bit mod
  db(0b00100000, 0);
  delay_us(100);
  //now 4 bit mode + 2 lines
  db(0b00101000, 1);
  db(0b00000001, 1); //clear display
  delay_ms(2);
  //make DDRAM increment
  db(0b00000110, 1);
  //turn on display
  db(0b00001100, 1);
  RSstate(1);
}

int displayMain(void){
  displayInit();
  setCursor(0, 1, 0);
  printDisp("ABC");
  /* printWithMenu("ABC"); */
  /* printWithMenu("DEF"); */
  /* printWithMenu("GHI"); */
  /* printWithMenu("JKL"); */
  /* delay(1500); */
  /* nextDisp(); */

  while(1);
  return 1;
}

#ifdef MAINdisp
void setup() {
}
void loop() {displayMain();}
#endif

