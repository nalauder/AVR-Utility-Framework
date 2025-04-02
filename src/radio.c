#include "radio.h"

uint8_t ascending_number = 0X00;
#define TIME_GAP 500

void radio_init()
{
    nrf24_device(TRANSMITTER, RESET);
}

int radio_run(bool transmitter)
{
    if (transmitter)
        return radio_transmitter_run();
    else 
        return radio_receiver_run();
}

int radio_transmitter_run() {
    while (1)
    {
        _delay_ms(TIME_GAP);
        while (nrf24_transmit(&ascending_number, 1, NO_ACK_MODE) == TRANSMIT_FAIL) // wait until payload is loaded into TX buffer
        {
            // Serial.println("Transmit fail!");
        }
        while (nrf24_transmit_status() == TRANSMIT_IN_PROGRESS) // poll the transmit status, make sure the payload is sent
            ;
        // Serial.println("Sent!"); // payload is sent without acknowledge successfully
        ascending_number++;
    }

    return 0;
}

int radio_receiver_run() {
    
}