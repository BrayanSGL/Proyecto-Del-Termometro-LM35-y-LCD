#include "mbed.h"
#include "TextLCD.h"
#include "Keypad.h"

TextLCD lcd(D7, D6, D5, D4, D3, D2, TextLCD::LCD16x2); //rs,e,d4-d7
Keypad teclado(D8, D9, D10, D11, D12, D13, D14, D15);
AnalogIn sensor(A5);
DigitalOut ledRojo(A3);
DigitalOut ledAmarillo(A2);
DigitalOut ledVerde(A1);
DigitalOut Zumba(A4);

char key, option = '0';
int miles = 0, centena = 0, decena = 0, unidad = 0, numero = 0, password = 1234, newPassword = 0, back = 0, opc = 0;
;

//Prototipo de funciones

char menu();

int escribirPin();

float manual();

int automatico();

char cambioPin();

char pin();

//Metodo principal

int main()
{
    for (int i = 15; i >= -21; i--)
    {
        lcd.printf("                 ");
        lcd.locate(i, 0);
        lcd.printf("Sensor de temperatura");
        lcd.locate(0, 1);
        lcd.printf(" BRAYAN GALEANO ");
        wait(0.3);
        lcd.cls();
    }

    lcd.printf(" BRAYAN GALEANO ");
    lcd.locate(3, 1);
    lcd.printf("20192573049");
    wait(5);
    lcd.cls();

    option = pin();
}

//Definición ded funciones

char pin() //CONTRASEÑA VALIDACIÓN
{

    lcd.printf("    Password:   ");
    /////////
    while (true)
    {

        numero = escribirPin();

        if (numero == password)
        {
            lcd.cls();
            lcd.printf("   BIENVENIDO     SR. GALEANO   ");
            wait(2);
            option = menu();
            //return 'G';
        }
        else
        {
            lcd.cls();
            lcd.printf(".....ERROR......");
            wait(2);
            lcd.cls();
            option = pin();
        }
    }
}

char menu() //MENU
{
    lcd.cls();
    lcd.printf("......MENU......");
    lcd.printf("................");
    wait(2);
    lcd.cls();
    ledRojo = 0;
    ledAmarillo = 0;
    ledVerde = 0;
    Zumba = 0;
    while (true)
    {
        key == '\0';
        lcd.printf("    A)Manual    ");
        lcd.printf("B)Auto   C)Clave");

        while (true)
        {
            back = teclado.ReadKey();
            if (back == 65)
            {
                lcd.cls();
                lcd.printf(".....MANUAL.....");
                lcd.printf("................");
                wait(2);
                lcd.cls();
                option = manual();
            }

            if (back == 66)
            {
                lcd.cls();
                lcd.printf("...AUTOMATICO...");
                lcd.printf("................");
                wait(2);
                lcd.cls();
                option = automatico();
            }

            if (back == 67)
            {
                lcd.cls();
                lcd.printf("......CLAVE.....");
                lcd.printf("................");
                wait(2);
                lcd.cls();
                option = cambioPin();
            }
        }
    }
}

char cambioPin() //Cambio de PIN
{
    int test = 0;
    lcd.printf("    Password:   ");
    test = escribirPin();

    if (test == password)
    {
        lcd.cls();
        lcd.printf("   Nuevo PIN:   ");
        /////////
        while (true)
        {

            newPassword = escribirPin();
            password = newPassword;
            lcd.cls();
            lcd.printf("  Cambio Listo  ");
            wait(2);
            lcd.cls();
            option = pin();
        }
    }
    else
    {
        option = menu();
    }
    return '\0';
}

float manual() //MANUAL
{
    int test = 0, nBack = 0;
    float valor = 0;
    float vector[4];
    lcd.printf("    Password:   ");
    test = escribirPin();

    if (test == password)
    {
        lcd.cls();
        while (true)
        {
            nBack = teclado.ReadKey();
            lcd.printf("Temperatura:");
            lcd.locate(12, 0);
            //for (int i=0; i<4; i++) {
            //  vector[i]=(sensor.read()*330);
            // valor= valor +vector[i];
            // }
            //valor=valor/4;
            valor = sensor.read() * 330;
            lcd.printf("%.1f", valor);

            ////Map
            wait(0.3);
            lcd.cls();

            if (nBack == 65)
            {
                option = menu();
            }
        }
    }
    else
    {
        option = menu();
    }
    return 0;
}

int automatico() //AUTOMATICO
{
    int test = 0, nBack = 0;
    float valor = 0;
    float vector[4];
    lcd.printf("    Password:   ");
    test = escribirPin();

    if (test == password)
    {
        lcd.cls();
        lcd.printf("  Temp Ref:");

        int ref;

        lcd.locate(6, 1);
        //////////
        key == '\0';
        while (key == '\0')
        {
            key = teclado.ReadKey();
        }
        decena = key - 48;
        lcd.printf("%d", decena);
        while (key != '\0')
        {
            key = teclado.ReadKey();
        }
        //////////
        key == '\0';
        while (key == '\0')
        {
            key = teclado.ReadKey();
        }
        unidad = key - 48;
        lcd.printf("%d", unidad);
        while (key != '\0')
        {
            key = teclado.ReadKey();
        }

        ref = (decena * 10) + (unidad);

        lcd.cls();

        while (true)
        {
            nBack = teclado.ReadKey();
            lcd.locate(10, 0);
            lcd.printf("Ref:");

            lcd.locate(14, 0);
            lcd.printf("%d", ref);

            lcd.locate(0, 1);
            lcd.printf("Temperatura:");
            lcd.locate(12, 1);
            valor = sensor.read() * 330;
            lcd.printf("%.1f", valor);

            if (valor > ref)
            {
                ledRojo = 1;
                ledAmarillo = 0;
                ledVerde = 0;
                Zumba = 1;
                lcd.printf("ALTO");
            }
            if (valor <= ref && valor >= ref - (ref * 0.2))
            {
                ledRojo = 0;
                ledAmarillo = 1;
                ledVerde = 0;
                Zumba = 0;
                lcd.printf("MEDIO");
            }
            if (valor < ref - (ref * 0.2))
            {
                ledRojo = 0;
                ledAmarillo = 0;
                ledVerde = 1;
                Zumba = 0;
                lcd.printf("BAJO");
            }

            ////Map
            wait(0.3);
            lcd.cls();
            if (nBack == 65)
            {
                option = menu();
            }
        }
    }
    else
    {
        option = menu();
    }
    return 0;
}

int escribirPin() //ESCRITURA
{
    int Nnumero;

    lcd.locate(6, 1);

    key == '\0';
    while (key == '\0')
    {
        key = teclado.ReadKey();
    }
    miles = key - 48;
    lcd.printf("%d", miles);
    while (key != '\0')
    {
        key = teclado.ReadKey();
    }
    //////////
    key == '\0';
    while (key == '\0')
    {
        key = teclado.ReadKey();
    }
    centena = key - 48;
    lcd.printf("%d", centena);
    while (key != '\0')
    {
        key = teclado.ReadKey();
    }
    //////////
    key == '\0';
    while (key == '\0')
    {
        key = teclado.ReadKey();
    }
    decena = key - 48;
    lcd.printf("%d", decena);
    while (key != '\0')
    {
        key = teclado.ReadKey();
    }
    //////////
    key == '\0';
    while (key == '\0')
    {
        key = teclado.ReadKey();
    }
    unidad = key - 48;
    lcd.printf("%d", unidad);
    while (key != '\0')
    {
        key = teclado.ReadKey();
    }

    Nnumero = (miles * 1000) + (centena * 100) + (decena * 10) + (unidad);

    return Nnumero;
}