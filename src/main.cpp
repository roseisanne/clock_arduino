#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timerISR.h"

#define NUM_TASKS 1

typedef struct _task{
  signed char state; 
  unsigned long period; 
  unsigned long elapsedTime; 
  int (*TickFct)(int); 
} task;

const unsigned long pledclock = 100;
const unsigned long pleftbut = 100;
const unsigned long prightbut = 100;
const unsigned long pbuzzer = 100;
const unsigned long plight = 100;
const unsigned long plcyd = 500;
const unsigned long MainPeriod = 100;

task tasks[NUM_TASKS]; 

void TimerISR() {
  for ( unsigned int i = 0; i < NUM_TASKS; i++ ) {
    if ( tasks[i].elapsedTime == tasks[i].period ) { 
      tasks[i].state = tasks[i].TickFct(tasks[i].state); 
      tasks[i].elapsedTime = 0; 
    }
  tasks[i].elapsedTime += MainPeriod;
  }
}



unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
  return (b ? (x | (0x01 << k)) : (x & ~(0x01 << k)) );
  // Set bit to 1 Set bit to 0
}

unsigned char GetBit(unsigned char x, unsigned char k) {
  return ((x & (0x01 << k)) != 0);
}

int nums[10] = {
  0b0111111, // 0
  0b0000110, // 1
  0b1011011, // 2
  0b1001111, // 3
  0b1100110, // 4
  0b1101101, // 5
  0b1111101, // 6
  0b0000111, // 7
  0b1111111, // 8
  0b1101111, // 9
};


void outNum(int num){
  PORTB = nums[num] & 0x3F; 
  PORTD = nums[num] & 0xD0;
}


void ADC_init() {
  ADMUX = 0b01000000;
  ADCSRA = 0b10000111;
  ADCSRB = 0x00;
}

unsigned int ADC_read(unsigned char chnl){
  ADMUX = (ADMUX & 0xF0) | (0x0F & chnl);
  ADCSRA = (ADCSRA & 0xBF) | 0x40;
  while((ADCSRA >> 6) & 0x01) {} 
  uint8_t low, high;
  low = ADCL;
  high = ADCH;
  return ((high << 8) | low) ;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

enum clock_LED {on, off};
int TickFct_clock(int state){
  switch(state){
    case on:
    break;
    case off:
    break;
    default:
    state = on;
    break;
  }

  switch(state){
    case on: 
    break;
    case off: 
    break;
    default:
    break;
  }
}

enum leftbut {lpress};
enum rightbut {rpress};
enum rgblight{settings, loff};

enum alarm{aon, aoff};
int Tickf_alarm(int state){
  switch(state){

  }
}

enum lcd{son, soff};

int main(void) {
  DDRC = 0x8F;
  PORTC = 0x70;
  DDRD = 0xFF;
  PORTD = 0x00;
  DDRB = 0xFF;
  PORTB = 0x00;

    ADC_init();
  // unsigned char i = 0;
  // tasks[i].period = pleftbut;
  // tasks[i].state = lrest;
  // tasks[i].elapsedTime = tasks[i].period;
  // tasks[i].TickFct = &TickFct_Leftbut;

  TimerSet(MainPeriod);
  TimerOn();
  while (1) {}
  return 0;
}