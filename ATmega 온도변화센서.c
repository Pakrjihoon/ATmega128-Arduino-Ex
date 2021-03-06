#include <mega128.h>
#include <delay.h>
#include <stdlib.h>

#define LCD_FUNCSET 0x38
#define LCD_ONOFF 0x0e
#define LCD_ENTMODE 0x06
#define LCD_CLR 0x01
#define LCD_SHIFT 0x18
#define LCD_RS PORTA.0
#define LCD_RW PORTA.1
#define LCD_E PORTA.2
#define LCD_DATA PORTB

void lcd_char(unsigned char ch){
    LCD_RS = 1; LCD_RW = 0;
    LCD_DATA = ch;
    LCD_E = 1;
    delay_us(40);
    LCD_E = 0;
}

void lcd_command(unsigned char inst){
    LCD_RS = 0; LCD_RW = 0;
    LCD_DATA = inst;
    LCD_E = 1;
    delay_us(40);
    LCD_E = 0;
}

void lcd_str(unsigned char *str){
    while (*str)
          {
            lcd_char(*str);
            str++;
          }
}

void lcd_init(void){
    lcd_command(LCD_FUNCSET);
    lcd_command(LCD_ONOFF);
    lcd_command(LCD_ENTMODE);
    lcd_command(LCD_CLR);
}

void lcd_position(unsigned char x,unsigned char y){
    unsigned char position;
    
    if(y > 1) y = 1;
    if(x > 15) x = 15;
    position = y ? x+0xC0 : x+0x80;
    lcd_command(position);
    
}

void port_init(void){
    DDRA = 0xff;
    DDRB = 0xff;
    DDRF = 0;
    DDRC = 0xff;
    PORTA = 0xff;
    PORTB = 0xff;
    PORTC = 0;
    ADMUX = 0;
    ADCSRA = 0x8F;
    SREG = 0x80;
}

void AD_disp(int adcval){
    float temp;
    unsigned char buf[10];
    lcd_command(0x80);
    temp = ((150 + 55)/1023.)*adcval-55;
    ftoa(temp,2,buf);
    lcd_str("temp : ");
    lcd_str(buf);
    lcd_str(" C");
    if(temp > 25.){
        lcd_command(0xC0);
        lcd_str("fire!!!!!!!!!!");
        PORTC = 0xff;
    }
    else{
        lcd_command(0xC0);
        lcd_str("                      ");
        PORTC = 0;
    }
}

void main(){
    
    
    port_init();
    delay_ms(5);
    lcd_init();
    delay_ms(5);
    ADCSRA = 0xCF;
    while(1){
        
        
    }
    
}
interrupt [ADC_INT] void adc_int(void)
{
    int ad_val;
    
        
    ad_val = (int)ADCL + ((int)ADCH<<8);
        
    AD_disp(ad_val);
        
    delay_ms(20);
    
    ADCSRA = 0xCF;
}
