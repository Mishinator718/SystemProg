#include "InterfaceDigitalOut.h"
#include "InterruptIn.h"
#include "PinNames.h"
#include "mbed.h"
#include "mbed_retarget.h"
    
DigitalOut oled1(PA_8);
InterruptIn ibutton1(BUTTON1);
static auto sleep_time = 1000ms;
Ticker toggle_led_ticker;

void led_ticker(){
    oled1 = !oled1;
}

void pressed(){
    toggle_led_ticker.detach();
    sleep_time += 250ms;
    if (sleep_time > 1000ms){
        sleep_time = 250ms;
    }
    toggle_led_ticker.attach(&led_ticker, sleep_time);
}

void released(){}

int main()
{
    // Initialise the digital pin LED1 as an output
    toggle_led_ticker.attach(&led_ticker, sleep_time);
    ibutton1.fall(&released);
    ibutton1.rise(&pressed);

    while (true) {
        led_ticker();
        ThisThread::sleep_for(sleep_time);
    }
}
