#include "msp.h"
#include <stdio.h>

#define TIMER 130000

int main(){
      WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

      P1SEL0 &= (uint8_t)(~((1 << 4) | (1 << 1) | (1<<0)));
      P1SEL1 &= (uint8_t)(~((1 << 4) | (1 << 1) | (1<<0)));
      P2SEL0 &= (uint8_t)(~((1<<2)| (1<<1)| (1<<0)));
      P2SEL1 &= (uint8_t)(~((1<<2)| (1<<1)| (1<<0)));
      P1DIR &= (uint8_t)(~((1<<4) |(1<<1)));
      P1DIR |= (uint8_t)(1<<0);
      P2DIR |= (uint8_t)(((1<<2) |(1<<1) |(1<<0)));
      P1OUT |= (uint8_t) ((1<<4)|(1<<1));
      P1OUT &= ~(uint8_t)(1<<0);
      P2OUT &= ~(uint8_t)(((1<<2) |(1<<1) |(1<<0)));
      P1REN |= (uint8_t)((1<<4)| (1<<1));
      
      uint8_t overflow = ((1<<0)|(1<<1)|(1<<2));
      uint8_t rbg_state = 0;
      static int current_led = 0;
      static int red_state = 0;
      static int i = 100;
      static int time = 0;
      static int active = 0;
      static int next = 0;

      while(1){
            while(i>0){i--;}
            if(!(P1IN & (uint8_t)(1<<1))){
                  active = 0;
                  time = 0;
                  next = 0;
                  P2->OUT &= ~(uint8_t)((1<<0)|(1<<1)|(1<<2));
                  P1->OUT &= ~(uint8_t)(1<<0);
                  if(current_led == 0){
                        current_led = 1;
                  }
                  else{
                        current_led = 0;
            }
      }
      else{if(!(P1IN&(uint8_t)(1<<4)) || active == 1){
            active = 1;
            time++;
            if(time == TIMER){
                  next = 1;
                  time = 0;
            }
      if(current_led == 0){
            if(next == 1){
                  if(red_state == 0){
                              P1->OUT |= (uint8_t)(1<<0);
                              red_state = 1;
                          next = 0;
                  } else{
                    P1->OUT &= ~(uint8_t)(1<<0);
                    red_state = 0;
                    next = 0;
                  }
            }
            }
      else{
        if(next == 1){
          rbg_state += 1;
          rbg_state &= overflow;
          P2->OUT &= !(uint8_t)((1<<0)|(1<<1)|(1<<2));
          P2->OUT |= rbg_state;
          next = 0;
       }
}
      }
}
      }
}
