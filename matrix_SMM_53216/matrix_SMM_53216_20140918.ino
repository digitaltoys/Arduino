//**************************************************************//
//  Name    : matrix_SMM_53216                                  //
//  Author  : pepsiman                                          //
//  Date    : 2013/07/15                                        //
//  Version : 1.0                                               //
//  Notes   : SMM-53216 매트릭스 모듈에 문자열 출력 프로그램                  //
//          : 기본 아스키 문자 폰트 포함                                  //
//****************************************************************

#include <Arduino.h>
#include <MsTimer2.h>
#include <Time.h>
#define TIME_MSG_LEN  11   // time sync to PC is HEADER and unix time_t as ten ascii digits
#define TIME_HEADER  255   // Header tag for serial time sync message

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

//#define DS1307_ADDRESS 0x68
//#define SECONDS_PER_DAY 86400L

//int rtc_address = B1101000;
//int rtc_array[7];

//#include <DHT.h>
//#define DHTPIN 7     // what pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//int cycleTime = 2000; // 2 second delay (slow sensor)
//
//DHT dht(DHTPIN, DHTTYPE);
//float h;
//float t;


/*
// defines 5x7 ascii characters 0x20-0x7F (32-127)
unsigned char  font_5x7[96][5] = {
        {0x00,0x00,0x00,0x00,0x00}, //
        {0x00,0x00,0xfa,0x00,0x00}, // !
        {0x00,0xe0,0x00,0xe0,0x00}, // "
        {0x28,0xfe,0x28,0xfe,0x28}, // #
        {0x24,0x54,0xfe,0x54,0x48}, // $
        {0xc4,0xc8,0x10,0x26,0x46}, // %
        {0x6c,0x92,0xaa,0x44,0x0a}, // &
        {0x00,0xa0,0xc0,0x00,0x00}, // '
        {0x00,0x38,0x44,0x82,0x00}, // (
        {0x00,0x82,0x44,0x38,0x00}, // )
        {0x10,0x54,0x38,0x54,0x10}, // *
        {0x10,0x10,0x7c,0x10,0x10}, // +
        {0x00,0x0a,0x0c,0x00,0x00}, // ,
        {0x10,0x10,0x10,0x10,0x10}, // -
        {0x00,0x06,0x06,0x00,0x00}, // .
        {0x04,0x08,0x10,0x20,0x40}, // /
        {0x7c,0x8a,0x92,0xa2,0x7c}, // 0
        {0x00,0x42,0xfe,0x02,0x00}, // 1
        {0x42,0x86,0x8a,0x92,0x62}, // 2
        {0x84,0x82,0xa2,0xd2,0x8c}, // 3
        {0x18,0x28,0x48,0xfe,0x08}, // 4
        {0xe4,0xa2,0xa2,0xa2,0x9c}, // 5
        {0x3c,0x52,0x92,0x92,0x0c}, // 6
        {0x80,0x8e,0x90,0xa0,0xc0}, // 7
        {0x6c,0x92,0x92,0x92,0x6c}, // 8
        {0x60,0x92,0x92,0x94,0x78}, // 9
        {0x00,0x6c,0x6c,0x00,0x00}, // :
        {0x00,0x6a,0x6c,0x00,0x00}, // ;
        {0x00,0x10,0x28,0x44,0x82}, // <
        {0x28,0x28,0x28,0x28,0x28}, // =
        {0x82,0x44,0x28,0x10,0x00}, // >
        {0x40,0x80,0x8a,0x90,0x60}, // ?
        {0x4c,0x92,0x9e,0x82,0x7c}, // @
        {0x7e,0x88,0x88,0x88,0x7e}, // A
        {0xfe,0x92,0x92,0x92,0x6c}, // B
        {0x7c,0x82,0x82,0x82,0x44}, // C
        {0xfe,0x82,0x82,0x44,0x38}, // D
        {0xfe,0x92,0x92,0x92,0x82}, // E
        {0xfe,0x90,0x90,0x80,0x80}, // F
        {0x7c,0x82,0x82,0x8a,0x4c}, // G
        {0xfe,0x10,0x10,0x10,0xfe}, // H
        {0x00,0x82,0xfe,0x82,0x00}, // I
        {0x04,0x02,0x82,0xfc,0x80}, // J
        {0xfe,0x10,0x28,0x44,0x82}, // K
        {0xfe,0x02,0x02,0x02,0x02}, // L
        {0xfe,0x40,0x20,0x40,0xfe}, // M
        {0xfe,0x20,0x10,0x08,0xfe}, // N
        {0x7c,0x82,0x82,0x82,0x7c}, // O
        {0xfe,0x90,0x90,0x90,0x60}, // P
        {0x7c,0x82,0x8a,0x84,0x7a}, // Q
        {0xfe,0x90,0x98,0x94,0x62}, // R
        {0x62,0x92,0x92,0x92,0x8c}, // S
        {0x80,0x80,0xfe,0x80,0x80}, // T
        {0xfc,0x02,0x02,0x02,0xfc}, // U
        {0xf8,0x04,0x02,0x04,0xf8}, // V
        {0xfe,0x04,0x18,0x04,0xfe}, // W
        {0xc6,0x28,0x10,0x28,0xc6}, // X
        {0xc0,0x20,0x1e,0x20,0xc0}, // Y
        {0x86,0x8a,0x92,0xa2,0xc2}, // Z
        {0x00,0x00,0xfe,0x82,0x82}, // [
        {0x40,0x20,0x10,0x08,0x04}, // "\"
        {0x82,0x82,0xfe,0x00,0x00}, // ]
        {0x20,0x40,0x80,0x40,0x20}, // ^
        {0x02,0x02,0x02,0x02,0x02}, // _
        {0x00,0x80,0x40,0x20,0x00}, // `
        {0x04,0x2a,0x2a,0x2a,0x1e}, // a
        {0xfe,0x12,0x22,0x22,0x1c}, // b
        {0x1c,0x22,0x22,0x22,0x04}, // c
        {0x1c,0x22,0x22,0x12,0xfe}, // d
        {0x1c,0x2a,0x2a,0x2a,0x18}, // e
        {0x10,0x7e,0x90,0x80,0x40}, // f
        {0x10,0x28,0x2a,0x2a,0x3c}, // g
        {0xfe,0x10,0x20,0x20,0x1e}, // h
        {0x00,0x22,0xbe,0x02,0x00}, // i
        {0x04,0x02,0x22,0xbc,0x00}, // j
        {0x00,0xfe,0x08,0x14,0x22}, // k
        {0x00,0x82,0xfe,0x02,0x00}, // l
        {0x3e,0x20,0x18,0x20,0x1e}, // m
        {0x3e,0x10,0x20,0x20,0x1e}, // n
        {0x1c,0x22,0x22,0x22,0x1c}, // o
        {0x3e,0x28,0x28,0x28,0x10}, // p
        {0x10,0x28,0x28,0x18,0x3e}, // q
        {0x3e,0x10,0x20,0x20,0x10}, // r
        {0x12,0x2a,0x2a,0x2a,0x04}, // s
        {0x20,0xfc,0x22,0x02,0x04}, // t
        {0x3c,0x02,0x02,0x04,0x3e}, // u
        {0x38,0x04,0x02,0x04,0x38}, // v
        {0x3c,0x02,0x0c,0x02,0x3c}, // w
        {0x22,0x14,0x08,0x14,0x22}, // x
        {0x30,0x0a,0x0a,0x0a,0x3c}, // y
        {0x22,0x26,0x2a,0x32,0x22}, // z
        {0x00,0x10,0x6c,0x82,0x00}, // {
        {0x00,0x00,0xfe,0x00,0x00}, // |
        {0x00,0x82,0x6c,0x10,0x00}, // }
        {0x40,0x80,0xc0,0x40,0x80}, // ~
        {0x00,0x00,0x00,0x00,0x00}, //
};

// defines 8x8 ascii characters 0x20-0x7F (32-127)
unsigned char  font_8x8[96][8] = {
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //
        {0x00,0x60,0xfa,0xfa,0x60,0x00,0x00,0x00}, // !
        {0x00,0xe0,0xe0,0x00,0xe0,0xe0,0x00,0x00}, // "
        {0x28,0xfe,0xfe,0x28,0xfe,0xfe,0x28,0x00}, // #
        {0x24,0x74,0xd6,0xd6,0x5c,0x48,0x00,0x00}, // $
        {0x62,0x66,0x0c,0x18,0x30,0x66,0x46,0x00}, // %
        {0x0c,0x5e,0xf2,0xba,0xec,0x5e,0x12,0x00}, // &
        {0x20,0xe0,0xc0,0x00,0x00,0x00,0x00,0x00}, // '
        {0x00,0x38,0x7c,0xc6,0x82,0x00,0x00,0x00}, // (
        {0x00,0x82,0xc6,0x7c,0x38,0x00,0x00,0x00}, // )
        {0x10,0x54,0x7c,0x38,0x38,0x7c,0x54,0x10}, // *
        {0x10,0x10,0x7c,0x7c,0x10,0x10,0x00,0x00}, // +
        {0x00,0x05,0x07,0x06,0x00,0x00,0x00,0x00}, // ,
        {0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00}, // -
        {0x00,0x00,0x06,0x06,0x00,0x00,0x00,0x00}, // .
        {0x06,0x0c,0x18,0x30,0x60,0xc0,0x80,0x00}, // /
        {0x7c,0xfe,0x9a,0xb2,0xfe,0x7c,0x00,0x00}, // 0
        {0x42,0x42,0xfe,0xfe,0x02,0x02,0x00,0x00}, // 1
        {0x46,0xce,0x9a,0x92,0xf6,0x66,0x00,0x00}, // 2
        {0x44,0xc6,0x92,0x92,0xfe,0x6c,0x00,0x00}, // 3
        {0x18,0x38,0x68,0xc8,0xfe,0xfe,0x08,0x00}, // 4
        {0xe4,0xe6,0xa2,0xa2,0xbe,0x9c,0x00,0x00}, // 5
        {0x3c,0x7e,0xd2,0x92,0x9e,0x0c,0x00,0x00}, // 6
        {0xc0,0xc6,0x8e,0x98,0xf0,0xe0,0x00,0x00}, // 7
        {0x6c,0xfe,0x92,0x92,0xfe,0x6c,0x00,0x00}, // 8
        {0x60,0xf2,0x92,0x96,0xfc,0x78,0x00,0x00}, // 9
        {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00}, // :
        {0x00,0x05,0x37,0x36,0x00,0x00,0x00,0x00}, // ;
        {0x10,0x38,0x6c,0xc6,0x82,0x00,0x00,0x00}, // <
        {0x28,0x28,0x28,0x28,0x28,0x28,0x00,0x00}, // =
        {0x00,0x82,0xc6,0x6c,0x38,0x10,0x00,0x00}, // >
        {0x40,0xc0,0x8a,0x9a,0xf0,0x60,0x00,0x00}, // ?
        {0x7c,0xfe,0x82,0xba,0xba,0xf8,0x78,0x00}, // @
        {0x3e,0x7e,0xc8,0xc8,0x7e,0x3e,0x00,0x00}, // A
        {0x82,0xfe,0xfe,0x92,0x92,0xfe,0x6c,0x00}, // B
        {0x38,0x7c,0xc6,0x82,0x82,0xc6,0x44,0x00}, // C
        {0x82,0xfe,0xfe,0x82,0xc6,0xfe,0x38,0x00}, // D
        {0x82,0xfe,0xfe,0x92,0xba,0x82,0xc6,0x00}, // E
        {0x82,0xfe,0xfe,0x92,0xb8,0x80,0xc0,0x00}, // F
        {0x38,0x7c,0xc6,0x82,0x8a,0xce,0x4e,0x00}, // G
        {0xfe,0xfe,0x10,0x10,0xfe,0xfe,0x00,0x00}, // H
        {0x00,0x82,0xfe,0xfe,0x82,0x00,0x00,0x00}, // I
        {0x0c,0x0e,0x02,0x82,0xfe,0xfc,0x80,0x00}, // J
        {0x82,0xfe,0xfe,0x10,0x38,0xee,0xc6,0x00}, // K
        {0x82,0xfe,0xfe,0x82,0x02,0x06,0x0e,0x00}, // L
        {0xfe,0xfe,0x60,0x30,0x60,0xfe,0xfe,0x00}, // M
        {0xfe,0xfe,0x60,0x30,0x18,0xfe,0xfe,0x00}, // N
        {0x38,0x7c,0xc6,0x82,0xc6,0x7c,0x38,0x00}, // O
        {0x82,0xfe,0xfe,0x92,0x90,0xf0,0x60,0x00}, // P
        {0x78,0xfc,0x84,0x8e,0xfe,0x7a,0x00,0x00}, // Q
        {0x82,0xfe,0xfe,0x98,0x9c,0xf6,0x62,0x00}, // R
        {0x64,0xe6,0xb2,0x9a,0xde,0x4c,0x00,0x00}, // S
        {0xc0,0x82,0xfe,0xfe,0x82,0xc0,0x00,0x00}, // T
        {0xfe,0xfe,0x02,0x02,0xfe,0xfe,0x00,0x00}, // U
        {0xf8,0xfc,0x06,0x06,0xfc,0xf8,0x00,0x00}, // V
        {0xfe,0xfe,0x0c,0x18,0x0c,0xfe,0xfe,0x00}, // W
        {0xc6,0xee,0x38,0x10,0x38,0xee,0xc6,0x00}, // X
        {0xe0,0xf2,0x1e,0x1e,0xf2,0xe0,0x00,0x00}, // Y
        {0xe6,0xce,0x9a,0xb2,0xe2,0xc6,0x8e,0x00}, // Z
        {0x00,0xfe,0xfe,0x82,0x82,0x00,0x00,0x00}, // [
        {0x80,0xc0,0x60,0x30,0x18,0x0c,0x06,0x00}, // "\"
        {0x00,0x82,0x82,0xfe,0xfe,0x00,0x00,0x00}, // ]
        {0x10,0x30,0x60,0xc0,0x60,0x30,0x10,0x00}, // ^
        {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01}, // _
        {0x00,0x00,0xc0,0xe0,0x20,0x00,0x00,0x00}, // `
        {0x04,0x2e,0x2a,0x2a,0x3c,0x1e,0x02,0x00}, // a
        {0x82,0xfc,0xfe,0x22,0x22,0x3e,0x1c,0x00}, // b
        {0x1c,0x3e,0x22,0x22,0x36,0x14,0x00,0x00}, // c
        {0x0c,0x1e,0x12,0x92,0xfc,0xfe,0x02,0x00}, // d
        {0x1c,0x3e,0x2a,0x2a,0x3a,0x18,0x00,0x00}, // e
        {0x12,0x7e,0xfe,0x92,0xc0,0x40,0x00,0x00}, // f
        {0x19,0x3d,0x25,0x25,0x1f,0x3e,0x20,0x00}, // g
        {0x82,0xfe,0xfe,0x10,0x20,0x3e,0x1e,0x00}, // h
        {0x00,0x22,0xbe,0xbe,0x02,0x00,0x00,0x00}, // i
        {0x02,0x23,0x21,0xbf,0xbe,0x00,0x00,0x00}, // j
        {0x82,0xfe,0xfe,0x08,0x1c,0x36,0x22,0x00}, // k
        {0x00,0x82,0xfe,0xfe,0x02,0x00,0x00,0x00}, // l
        {0x3e,0x3e,0x30,0x18,0x30,0x3e,0x1e,0x00}, // m
        {0x3e,0x3e,0x20,0x20,0x3e,0x1e,0x00,0x00}, // n
        {0x1c,0x3e,0x22,0x22,0x3e,0x1c,0x00,0x00}, // o
        {0x21,0x3f,0x1f,0x25,0x24,0x3c,0x18,0x00}, // p
        {0x18,0x3c,0x24,0x25,0x1f,0x3f,0x21,0x00}, // q
        {0x22,0x3e,0x1e,0x22,0x38,0x18,0x00,0x00}, // r
        {0x12,0x3a,0x2a,0x2a,0x2e,0x24,0x00,0x00}, // s
        {0x00,0x20,0x7c,0xfe,0x22,0x24,0x00,0x00}, // t
        {0x3c,0x3e,0x02,0x02,0x3c,0x3e,0x02,0x00}, // u
        {0x38,0x3c,0x06,0x06,0x3c,0x38,0x00,0x00}, // v
        {0x3c,0x3e,0x06,0x0c,0x06,0x3e,0x3c,0x00}, // w
        {0x22,0x36,0x1c,0x08,0x1c,0x36,0x22,0x00}, // x
        {0x39,0x3d,0x05,0x05,0x3f,0x3e,0x00,0x00}, // y
        {0x32,0x26,0x2e,0x3a,0x32,0x26,0x00,0x00}, // z
        {0x10,0x10,0x7c,0xee,0x82,0x82,0x00,0x00}, // {
        {0x00,0x00,0x00,0xee,0xee,0x00,0x00,0x00}, // |
        {0x82,0x82,0xee,0x7c,0x10,0x10,0x00,0x00}, // }
        {0x40,0xc0,0x80,0xc0,0x40,0xc0,0x80,0x00}, // ~
        {0x1e,0x3e,0x62,0xc2,0x62,0x3e,0x1e,0x00}, //
};
*/

unsigned char  font2_8x8[96][8] =
{
    {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000000,
        B00000100
    },

    {
        B00001010,
        B00001010,
        B00001010,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000000,
        B00001010,
        B00011111,
        B00001010,
        B00011111,
        B00001010,
        B00011111,
        B00001010
    },

    {
        B00000111,
        B00001100,
        B00010100,
        B00001100,
        B00000110,
        B00000101,
        B00000110,
        B00011100
    },

    {
        B00011001,
        B00011010,
        B00000010,
        B00000100,
        B00000100,
        B00001000,
        B00001011,
        B00010011
    },

    {
        B00000110,
        B00001010,
        B00010010,
        B00010100,
        B00001001,
        B00010110,
        B00010110,
        B00001001
    },

    {
        B00000100,
        B00000100,
        B00000100,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000010,
        B00000100,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00000100,
        B00000010
    },

    {
        B00001000,
        B00000100,
        B00000010,
        B00000010,
        B00000010,
        B00000010,
        B00000100,
        B00001000
    },

    {
        B00010101,
        B00001110,
        B00011111,
        B00001110,
        B00010101,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000000,
        B00000000,
        B00000100,
        B00000100,
        B00011111,
        B00000100,
        B00000100,
        B00000000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000110,
        B00000100,
        B00001000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00001110,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000100
    },

    {
        B00000001,
        B00000010,
        B00000010,
        B00000100,
        B00000100,
        B00001000,
        B00001000,
        B00010000
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00010011,
        B00010101,
        B00011001,
        B00010001,
        B00001110
    },

    {
        B00000100,
        B00001100,
        B00010100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00011111
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00000010,
        B00000100,
        B00001000,
        B00010000,
        B00011111
    },

    {
        B00001110,
        B00010001,
        B00000001,
        B00001110,
        B00000001,
        B00000001,
        B00010001,
        B00001110
    },

    {
        B00010000,
        B00010000,
        B00010100,
        B00010100,
        B00011111,
        B00000100,
        B00000100,
        B00000100
    },

    {
        B00011111,
        B00010000,
        B00010000,
        B00011110,
        B00000001,
        B00000001,
        B00000001,
        B00011110
    },

    {
        B00000111,
        B00001000,
        B00010000,
        B00011110,
        B00010001,
        B00010001,
        B00010001,
        B00001110
    },

    {
        B00011111,
        B00000001,
        B00000001,
        B00000001,
        B00000010,
        B00000100,
        B00001000,
        B00010000
    },


    {
        B00001110,
        B00010001,
        B00010001,
        B00001110,
        B00010001,
        B00010001,
        B00010001,
        B00001110
    },

    {
        B00001111,
        B00010001,
        B00010001,
        B00001111,
        B00000001,
        B00000001,
        B00000001,
        B00000001
    },


    {
        B00000000,
        B00000100,
        B00000100,
        B00000000,
        B00000000,
        B00000100,
        B00000100,
        B00000000
    },

    {
        B00000000,
        B00000100,
        B00000100,
        B00000000,
        B00000000,
        B00000100,
        B00000100,
        B00001000
    },

    {
        B00000001,
        B00000010,
        B00000100,
        B00001000,
        B00001000,
        B00000100,
        B00000010,
        B00000001
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00011110,
        B00000000,
        B00011110,
        B00000000,
        B00000000
    },

    {
        B00010000,
        B00001000,
        B00000100,
        B00000010,
        B00000010,
        B00000100,
        B00001000,
        B00010000
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00000010,
        B00000100,
        B00000100,
        B00000000,
        B00000100
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00010101,
        B00010101,
        B00010001,
        B00010001,
        B00011110
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00010001,
        B00011111,
        B00010001,
        B00010001,
        B00010001
    },

    {
        B00011110,
        B00010001,
        B00010001,
        B00011110,
        B00010001,
        B00010001,
        B00010001,
        B00011110
    },

    {
        B00000110,
        B00001000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00001000,
        B00000110
    },

    {
        B00011100,
        B00010010,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010010,
        B00011100
    },

    {
        B00011111,
        B00010000,
        B00010000,
        B00011110,
        B00010000,
        B00010000,
        B00010000,
        B00011111
    },

    {
        B00011111,
        B00010000,
        B00010000,
        B00011110,
        B00010000,
        B00010000,
        B00010000,
        B00010000
    },

    {
        B00001110,
        B00010001,
        B00010000,
        B00010000,
        B00010111,
        B00010001,
        B00010001,
        B00001110
    },

    {
        B00010001,
        B00010001,
        B00010001,
        B00011111,
        B00010001,
        B00010001,
        B00010001,
        B00010001
    },

    {
        B00001110,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00001110
    },

    {
        B00011111,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00010100,
        B00001100
    },

    {
        B00010001,
        B00010010,
        B00010100,
        B00011000,
        B00011000,
        B00010100,
        B00010010,
        B00010001
    },

    {
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00011110
    },

    {
        B00010001,
        B00011011,
        B00011111,
        B00010101,
        B00010001,
        B00010001,
        B00010001,
        B00010001
    },

    {
        B00010001,
        B00011001,
        B00011001,
        B00010101,
        B00010101,
        B00010011,
        B00010011,
        B00010001
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00001110
    },

    {
        B00011110,
        B00010001,
        B00010001,
        B00011110,
        B00010000,
        B00010000,
        B00010000,
        B00010000
    },

    {
        B00001110,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010101,
        B00010011,
        B00001111
    },

    {
        B00011110,
        B00010001,
        B00010001,
        B00011110,
        B00011000,
        B00010100,
        B00010010,
        B00010001
    },

    {
        B00000111,
        B00001000,
        B00010000,
        B00001000,
        B00000100,
        B00000010,
        B00000010,
        B00011100
    },

    {
        B00011111,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100
    },

    {
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00001110
    },

    {
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00001010,
        B00000100
    },

    {
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010001,
        B00010101,
        B00010101,
        B00001010
    },

    {
        B00010001,
        B00011011,
        B00001010,
        B00000100,
        B00000100,
        B00001010,
        B00011011,
        B00010001
    },

    {
        B00010001,
        B00010001,
        B00001010,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100
    },

    {
        B00011111,
        B00000001,
        B00000010,
        B00000100,
        B00001000,
        B00010000,
        B00010000,
        B00011111
    },

    {
        B00001110,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00001000,
        B00001110
    },

    {
        B00010000,
        B00001000,
        B00001000,
        B00000100,
        B00000100,
        B00000010,
        B00000010,
        B00000001
    },

    {
        B00001110,
        B00000010,
        B00000010,
        B00000010,
        B00000010,
        B00000010,
        B00000010,
        B00001110
    },

    {
        B00000100,
        B00001010,
        B00010001,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00011111
    },

    {
        B00001000,
        B00000100,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00001110,
        B00010010,
        B00010010,
        B00010010,
        B00001111
    },

    {
        B00000000,
        B00010000,
        B00010000,
        B00010000,
        B00011100,
        B00010010,
        B00010010,
        B00011100
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00001110,
        B00010000,
        B00010000,
        B00010000,
        B00001110
    },

    {
        B00000000,
        B00000001,
        B00000001,
        B00000001,
        B00000111,
        B00001001,
        B00001001,
        B00000111
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00011100,
        B00010010,
        B00011110,
        B00010000,
        B00001110
    },

    {
        B00000000,
        B00000011,
        B00000100,
        B00000100,
        B00000110,
        B00000100,
        B00000100,
        B00000100
    },

    {
        B00000000,
        B00001110,
        B00001010,
        B00001010,
        B00001110,
        B00000010,
        B00000010,
        B00001100
    },

    {
        B00000000,
        B00010000,
        B00010000,
        B00010000,
        B00011100,
        B00010010,
        B00010010,
        B00010010
    },

    {
        B00000000,
        B00000000,
        B00000100,
        B00000000,
        B00000100,
        B00000100,
        B00000100,
        B00000100
    },

    {
        B00000000,
        B00000010,
        B00000000,
        B00000010,
        B00000010,
        B00000010,
        B00000010,
        B00001100
    },

    {
        B00000000,
        B00010000,
        B00010000,
        B00010100,
        B00011000,
        B00011000,
        B00010100,
        B00010000
    },

    {
        B00000000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00010000,
        B00001100
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00001010,
        B00010101,
        B00010001,
        B00010001,
        B00010001
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00010100,
        B00011010,
        B00010010,
        B00010010,
        B00010010
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00001100,
        B00010010,
        B00010010,
        B00010010,
        B00001100
    },

    {
        B00000000,
        B00011100,
        B00010010,
        B00010010,
        B00011100,
        B00010000,
        B00010000,
        B00010000
    },

    {
        B00000000,
        B00001110,
        B00010010,
        B00010010,
        B00001110,
        B00000010,
        B00000010,
        B00000001
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00001010,
        B00001100,
        B00001000,
        B00001000,
        B00001000
    },

    {
        B00000000,
        B00000000,
        B00001110,
        B00010000,
        B00001000,
        B00000100,
        B00000010,
        B00011110
    },

    {
        B00000000,
        B00010000,
        B00010000,
        B00011100,
        B00010000,
        B00010000,
        B00010000,
        B00001100
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00010010,
        B00010010,
        B00010010,
        B00010010,
        B00001100
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00010001,
        B00010001,
        B00010001,
        B00001010,
        B00000100
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00010001,
        B00010001,
        B00010001,
        B00010101,
        B00001010
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00010001,
        B00001010,
        B00000100,
        B00001010,
        B00010001
    },


    {
        B00000000,
        B00000000,
        B00010001,
        B00001010,
        B00000100,
        B00001000,
        B00001000,
        B00010000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00011111,
        B00000010,
        B00000100,
        B00001000,
        B00011111
    },

    {
        B00000010,
        B00000100,
        B00000100,
        B00000100,
        B00001000,
        B00000100,
        B00000100,
        B00000010
    },

    {
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100,
        B00000100
    },

    {
        B00001000,
        B00000100,
        B00000100,
        B00000100,
        B00000010,
        B00000100,
        B00000100,
        B00001000
    },

    {
        B00000000,
        B00000000,
        B00000000,
        B00001010,
        B00011110,
        B00010100,
        B00000000,
        B00000000
    }
};

//holders for infromation you're going to pass to shifting function
const int colMatrix = 6;
const int rowMatrix = 2;
unsigned char multiMr[colMatrix][16];
unsigned char multiMg[colMatrix][16];
char temp[10]={0};
char temp2[10]={0};
char temp3[10]={0};
char temp4[10]={0};

int dataPin1 = 2;
int dataPin2 = 3;
int latchPin = 4;
int enPin = 5;
int clockPin = 6;

char week[][7] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};

int thermistorPin = 1;
float th;   // 써미스터 저항값 (kohm)
int vcc = 5100; // vcc : 4.970v 실측
int vo; // 측정 전압
float R2 = 5000; // R2 저항값
double analVal=0;
double tem[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#define R0 5000
#define T0 25 //room temperature
#define B 3970 //the coefficient of the thermistor
#define SERISR 5000 //seris resistor 10K


float GetTemperature(int pin) {
    double val=0;

    for (int i=0; i<6;i++) {
        val += analogRead(pin);    // read the value from the sensor
        delay(30);
    }
    tem[second()%20] = val / 6.0;

    val=0;
    int cnt=0;
    for (int i=0; i<20;i++) {
        if (tem[i]!=0){
            val += tem[i];    // read the value from the sensor
            cnt++;
        }
    }
    analVal = val / cnt;

    //analVal = analogRead(pin);    // read the value from the sensor

    vo = map(analVal,0,1023,0,vcc);
    //th = (((float)(vcc-vo)*10.0)/(float)vo)*1000.0;
    th = (R2 * vcc / vo) - R2;
    //ce = ((log(4.0*th - 3000.0) / (-0.024119329) + 473)-32.0)/1.8;
	float thermistorRValue;
	float temperature;
	//thermistorRValue = SERISR / 1023.0 / analogRead(pin);
	thermistorRValue = th;
	//Serial.println(thermistorRValue);
	temperature = log(thermistorRValue / R0) / B;
	temperature = 1.0 / (temperature + 1.0 / (T0 + 273.15));
	temperature -= 273.15 ;// kelvins to C
	//Serial.println(temperature);
	return temperature;
}

//void DS1307_save()
//{
//  Wire.beginTransmission(rtc_address);
//  Wire.write(0x00); // reset register pointer
//  for(int i=0; i<7; i++)
//  {
//    Wire.write(rtc_array[i]);
//  }
//  Wire.endTransmission();
//}
//
//void DS1307_read()
//{
//  // use the Wire lib to connect to tho rtc
//  // reset the resgiter pointer to zero
//  Wire.beginTransmission(rtc_address);
//  Wire.write(0x00);
//  Wire.endTransmission();
//
//  // request the 7 bytes of data    (secs, min, hr, dow, date. mth, yr)
//  Wire.requestFrom(rtc_address, 7);
//  for(int i=0; i<7; i++)
//  {
//  // store data in raw bcd format
//  rtc_array[i]=Wire.read();
//  }
//}
//
//void start_ball()
//{
//rtc_array[0]=0;    // Second
//rtc_array[1]=10*16 + 5;    // Minites
//rtc_array[2]=10*16 + 6;    // Hours -- 2 --
//rtc_array[3]=3;    // Sunday  1 , Monday  2 , Tuesday  3 etc in BCD -- Saturday -- 7 --
//rtc_array[4]=2*16 + 3;    // Date -- 17 --
//rtc_array[5]=0*16 + 7;    // Month -- 1 --
//rtc_array[6]=10*16 + 3;    // Year  -)- 09 --
//
//}
//
//void export_array()
//{
//    char buf[20]={0};
//    sprintf(buf, "20%02x/%02x/%02x %2x:%02x:%02x", rtc_array[6], rtc_array[5], rtc_array[4], rtc_array[2], rtc_array[1], rtc_array[0]);
//    Serial.println(buf);
//}

void shift2(int clockPin, word dataR, word dataG, int col){
    for (int i=col-1; i>=0; i--)
    {
        digitalWrite(clockPin, LOW);
        //digitalWrite(dataPin, ((data>>i) & 0x01));
        digitalWrite(dataPin1, ((dataR>>i) & 0x01));
        digitalWrite(dataPin2, ((dataG>>i) & 0x01));
        digitalWrite(clockPin, HIGH);
    }
}

void clearMatrix() {
    for (int r=0;r<rowMatrix*8;r++)
        for (int c=0;c<colMatrix;c++){
            multiMr[c][r]=0;
            multiMg[c][r]=0;
        }
}

void displayrow()
{
    for(int r=0;r<(rowMatrix*8);r++){
        digitalWrite(enPin, HIGH);
        digitalWrite(latchPin, LOW);
        for(int c=0;c<colMatrix;c++){
            //row addr
            digitalWrite( 8, r & 0x1);
            digitalWrite( 9, r>>1 & 0x1);
            digitalWrite(10, r>>2 & 0x1);
            digitalWrite(11, r>>3 & 0x1);

            //shiftOut(dataPin, clockPin, MSBFIRST, multiM[c][r]);
            shift2(clockPin, multiMr[c][r], multiMg[c][r], 6);
            //shift2(2, clockPin, multiM[c][r], 6);
       }
        digitalWrite(latchPin, HIGH);
        digitalWrite(enPin, LOW);
        delayMicroseconds(300);
    }
}

void displaystr()
{
    for(int r=0;r<16;r++){
        for (int i=0; i<6; i++)
        {
            if (r<8){
                multiMr[i][r] = font2_8x8[temp[i]-' '][r];
                multiMg[i][r] = font2_8x8[temp3[i]-' '][r];
            }
            else{
                multiMr[i][r] = font2_8x8[temp2[i]-' '][r%8];
                multiMg[i][r] = font2_8x8[temp4[i]-' '][r%8];
           }
        }
    }
}

char *ftoa(char *a, float f, int precision)
{
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};

  char *ret = a;
  long heiltal = (long)f;
  sprintf(a, "%2d", heiltal);
  //itoa(heiltal, a, 10);
  //Serial.println(f);
  //Serial.println(a);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}

void aSec(){
    //GetTemperature(thermistorPin);
    if ((second()/5)%2 == 0){
        sprintf(temp,  " %2d   ", day());
        sprintf(temp3, " %2d%s", day(), week[weekday()-1]);
        sprintf(temp2, " %2d:%02d", hourFormat12(), minute());
        sprintf(temp4, "      ");
    }
    else {
        char temper[10] = {0};
        float T = GetTemperature(thermistorPin);
        sprintf(temp,  " %sc", ftoa(temper, T, 1));
        sprintf(temp3, " %sc", ftoa(temper, T, 1));
        sprintf(temp2, " %2d:%02d", hourFormat12(), minute());
        sprintf(temp4, "      ");
    }
    displaystr();
}

void aHour(){
    DateTime current(rtc.now().unixtime() + 30);
    rtc.adjust(current);
    setTime(rtc.now().unixtime());
}

void aDay(){
    DateTime current(rtc.now().unixtime() + 30);
    rtc.adjust(current);
    setTime(rtc.now().unixtime());
}

void setup()
{
    // SMM-53216 pin
    pinMode(2, OUTPUT);//1 data1
    pinMode(3, OUTPUT);//2 data2
    pinMode(8, OUTPUT);//3 A0
    pinMode(9, OUTPUT);//4 A1
    pinMode(10, OUTPUT);//5 A2
    pinMode(11, OUTPUT);//6 A3
    pinMode(5, OUTPUT);//7 /en
    pinMode(4, OUTPUT);//8 latch
    pinMode(6, OUTPUT);//9 clock

    digitalWrite(2, LOW); //color1
    digitalWrite(3, LOW); //color2

    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);

    //set pins to output because they are addressed in the main loop
    Serial.begin(9600);
    Serial.println("matrix_SMM_53216.ino_20130721");
/*
    DATAARRAY[0] = B01100110; //0X24; //00100100
    DATAARRAY[1] = B10011001; //0X5A; //01011010
    DATAARRAY[2] = B10000001; //0X81; //10000001
    DATAARRAY[3] = B10000001; //0X81; //10000001
    DATAARRAY[4] = B01000010; //0X42; //01000010
    DATAARRAY[5] = B00100100; //0X24; //00100100
    DATAARRAY[6] = B00011000; //0X18; //00011000
    DATAARRAY[7] = B00000000; //0X81; //10000001
    DATAARRAY[8] = B00000000; //0X81; //10000001
*/

    //setTime(12,7,00,23,7,2013);

    Wire.begin();        // join i2c bus (address optional for master)
    rtc.begin();
    //rtc.adjust(DateTime(__DATE__, __TIME__));
    setTime(rtc.now().unixtime());

    MsTimer2::set(1000, aSec); // 1000ms period
    MsTimer2::start();

    clearMatrix();
//    dht.begin();
}

void test () {
    unsigned char ch = B00000001;
    int j=0;

    digitalWrite(8, j & 0x1);
    digitalWrite(9, j>>1 & 0x1);
    digitalWrite(10, j>>2 & 0x1);
    digitalWrite(11, j>>3 & 0x1);

        digitalWrite(enPin, HIGH);
        digitalWrite(latchPin, LOW);

        //shift2(dataPin, clockPin, ch, 8);

        digitalWrite(latchPin, HIGH);
        digitalWrite(enPin, LOW);
    //delayMicroseconds(400);
    delay(1000);
}

void loop(){
    static int hh=0;
    if (hh != hour()) {
            aHour();
        hh = hour();
    }

    //DateTime now = rtc.now();
    //DS1307_read();
    displayrow();

//    h = dht.readHumidity();
//    t = dht.readTemperature();
//    //t = (t*1.8)+32; //C to F conversion
//    Serial.println(h);
//    Serial.println(t);
//    delay(2000);

    //String tempVal = doubleToString(t, 2);
    //String humVal = doubleToString(h, 0);

}

