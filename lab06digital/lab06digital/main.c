/*
 * lab06digital.c
 *
 * Created: 3/20/2025 7:25:09 PM
 * Author : Britany Barillas
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// Inicializa UART a 9600 baudios
void UART_init() {
	uint16_t ubrr = 103; // UBRR para 9600 con F_CPU de 16MHz
	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;
	UCSR0B = (1 << TXEN0);  // Habilita transmisión
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits
}

void UART_sendChar(char c) {
	while (!(UCSR0A & (1 << UDRE0))); // Espera a que esté listo
	UDR0 = c;
}

void UART_sendString(const char* str) {
	while (*str) {
		UART_sendChar(*str++);
	}
}

void setup() {
	// Configura PD2 a PD7 como entradas
	DDRD &= ~(1 << PD2 | 1 << PD3 | 1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);
	// Activa resistencias pull-up internas (opcional)
	PORTD |= (1 << PD2 | 1 << PD3 | 1 << PD4 | 1 << PD5 | 1 << PD6 | 1 << PD7);

	UART_init();
}

int main(void) {
	setup();

	while (1) {
		if (!(PIND & (1 << PD2))) {
			UART_sendString("Arriba\r\n");
			_delay_ms(200);
		}
		if (!(PIND & (1 << PD3))) {
			UART_sendString("Abajo\r\n");
			_delay_ms(200);
		}
		if (!(PIND & (1 << PD4))) {
			UART_sendString("Izquierda\r\n");
			_delay_ms(200);
		}
		if (!(PIND & (1 << PD5))) {
			UART_sendString("Derecha\r\n");
			_delay_ms(200);
		}
		if (!(PIND & (1 << PD6))) {
			UART_sendString("A\r\n");
			_delay_ms(200);
		}
		if (!(PIND & (1 << PD7))) {
			UART_sendString("B\r\n");
			_delay_ms(200);
		}
	}
}
