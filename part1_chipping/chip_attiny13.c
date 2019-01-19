#define SETOUTPUT(ddr, n) ddr |= _BV(n);
#define SETINPUT(ddr, n) ddr &= ~_BV(n);
#define SETHIGH(port, n) port |= _BV(n);
#define SETLOW(port, n) port &= ~_BV(n);
#include <avr/io.h>
#include <util/delay.h>
#define gate 3
#define data 4
#define bitdur 4
#define pause 72
char scee[4] = "SCEE";
void wb(){_delay_ms(bitdur);}
void uart_start(){SETHIGH(PORTB, data);wb();}
void uart_stop(){SETLOW(PORTB, data);wb();}
void inject_scee(){
    for(int i=0;i<4;i++){
        uart_start();
        for(int j=0;j<8;j++){
            char val = ((scee[i] & (1<<j)) == 0);
            if(val){
                SETHIGH(PORTB, data);
            }else{
                SETLOW(PORTB, data);
            }
            wb();
        }
        uart_stop();
        uart_stop();
    }
    _delay_ms(pause);
}
int main(){
    OSCCAL = 69;
    SETOUTPUT(DDRB, data);
    SETOUTPUT(DDRB, gate);
    while(1){
        inject_scee();
    }
}
