/*
 * File:   LCD16x2.c
 * Author: 21192688
 *
 * Created on 15 de Abril de 2021, 13:33
 */

#include "config.h"
#include <xc.h>

#define _XTAL_FREQ 4000000      // Frequência do Cristal
#define EN PORTDbits.RD7        // Enable
#define RS PORTDbits.RD6        // RS
#define DADOS PORTB
#define LCD_CLEAR    0x01
#define LCD_ON       0x0F

void LCD_on ( void )
{
    // Iniciar Display
    EN = 1;
    RS = 0;
    DADOS = 0x0F;
    EN = 0;
    __delay_us(40);
    EN = 1;
}

void LCD_init ( void )
{
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    TRISB = 0;
    ANSELH = 0;
    DADOS = 0;
    PORTB = 0;
    EN = 1;
    RS = 0;
}

void LCD_printChar ( char c )
{
    // Inserir Dado
    RS = 1;
    DADOS = c;
    EN = 0;
    __delay_us(40);
    EN = 1;
}

void LCD_instruction ( char i )
{
    EN = 1;
    RS = 0;
    DADOS = i ;
    EN = 0;
    if ( i == LCD_CLEAR )
         __delay_us(2);
    else
    __delay_us(40);
    EN = 1;
}

void LCD_clear ( )
{
     // Limpar Display
    EN = 1;
    RS = 0;
    DADOS = 0x01;
    EN = 0;
    __delay_us(40);
    EN = 1;
}

void LCD_lincol ( char lin , char col )
{
    RS = 0;
    DADOS = 0x80 + ((lin*40) + col) ;
    EN = 0;
    __delay_us(40);
    EN = 1;
}

void LCD_printStr ( char * ptr )
{
    int cont = 0;
    
    while ( * ( ptr + cont ) )
    {
        LCD_printChar( * ( ptr+cont ) );
        cont++;
    }     
}


void main(void) 
{
    int n;
    
    LCD_init();
    LCD_on();
    
    
    LCD_lincol(1,2);
    LCD_printStr(" Suzan ");
    __delay_ms(250);
    LCD_lincol(0,2);
    LCD_printStr( " Soares ");
    __delay_ms(250);       

    while (1)
    {
//        for ( n = 0; n < 128; n++ )       
//        {           
//        LCD_pos(n);
//        LCD_printStr( " oi ");
//        __delay_ms(250);
//        LCD_pos(39);
//        LCD_printStr(" SALVE ");
//        __delay_ms(250);
//        }
    }
}

