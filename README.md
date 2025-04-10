# SYS_WB
https://gamma.app/docs/Zegary-Czasu-Rzeczywistego-RTC-w-Arduino-xolz48b2ulgxb15



Program przełączający cyklicznie 9 podprogramów (następny program po 9 to 1, a poprzedni
względem 1 to 9)
Przycisk RD6 – następny program
Przycisk RD13 – poprzedni program
Podprogramy:
1. 8 bitowy licznik binarny zliczający w górę (0…255)
2. 8 bitowy licznik binarny zliczający w dół (255…0)
3. 8 bitowy licznik w kodzie Graya zliczający w górę (repr. 0…255)
4. 8 bitowy licznik w kodzie Graya zliczający w dół (repr. 255…0)
5. 2x4 bitowy licznik w kodzie BCD zliczający w górę (0…99)
6. 2x4 bitowy licznik w kodzie BCD zliczający w dół (99…0)
7. 3 bitowy wężyk poruszający się lewo-prawo
8. Kolejka
9. 6 bitowy generator liczb pseudolosowych oparty o konfigurację 1110011     DLA mikrokontrolerra PIC24FJ128GA010 z konfiguracja :  #pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config OSCIOFNC = ON            // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF     



