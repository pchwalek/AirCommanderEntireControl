/*
  AirCommanderControl.h - Library to control Air Commander Entire via Serial
  Author: Patrick Chwalek (patrickchwalek.com)

  MIT License

  Copyright (c) 2022 pchwalek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 */

#ifndef AirCommanderControl_h
#define AirCommanderControl_h

#include "Arduino.h"

// reference: https://airpixel.cz/docs/serial-api-control/

#define TIME_BTWN_FRAMES  100 // 100 ms

#define SYNC_CMD        0xFA
#define MENU_CMD        0xA0
#define ZOOM_P_CMD      0xA1
#define ZOOM_N_CMD      0xA2
#define PHOTO_CMD       0xA3
#define VIDEO_CMD       0xA4
#define DISP_CMD        0xA5
#define PLAY_CMD        0xA6
#define DOWN_CMD        0xA7
#define UP_CMD          0xA8
#define RIGHT_CMD       0xA9
#define LEFT_CMD        0xAA
#define OK_PRESS_CMD    0xAB
#define APERTURE_N_CMD  0x10
#define APERTURE_P_CMD  0x11
#define SPEED_N_CMD     0x20
#define SPEED_P_CMD     0x21
#define AF_CMD          0xF1
#define AF_MF_CMD       0xAF
#define C1_CMD          0xC1
#define C2_CMD          0xC2
#define C3_CMD          0xC3

class AirCommanderControl
{
    private:
        HardwareSerial* _serial;

        uint8_t incomingByte;
        uint8_t heartbeatIdx = 0;
        uint8_t descriptorIdx = 0;

        unsigned long commanderLastPktTime = 0;
        uint8_t msgTimerFlag = 0;

    public:
        AirCommanderControl(HardwareSerial* refSer);
        void begin(void);
        void sendHeartbeat(void);
        void sendDescriptor(void);
        void serialHandler(void);
        void sendCommand(uint8_t cmd, uint8_t param=0x00);
        
        void photo(void);
        void video(void);
        void menu(void);
        void sync(void);
        void zoom_p(void);
        void zoom_n(void);
        void display(void);
        void press_play(void);
        void press_down(void);
        void press_up(void);
        void press_right(void);
        void press_left(void);
        void press_ok(void);
        void aperture_n(void);
        void aperture_p(void);
        void speed_n(void);
        void speed_p(void);
        void af(void);
        void af_mf(void);
        void c1(void);
        void c2(void);
        void c3(void);
};
#endif
