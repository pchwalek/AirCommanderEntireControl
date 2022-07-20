/*
  AirCommanderControl.cpp - Library to control Air Commander Entire via Serial
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

#include "AirCommanderControl.h"

/**
 *  Constructor class.
 */
AirCommanderControl::AirCommanderControl(HardwareSerial* refSer) {
    _serial = refSer;
}

/**
 * Begin the serial port
 *
 */
void AirCommanderControl::begin(void) {
    _serial->begin(115200);
}

/**
 * Send heartbeat message
 *
 */
void AirCommanderControl::sendHeartbeat(void) {
    _serial->write(0x2C);
    _serial->write(0x01);
    _serial->write(0x99);
    _serial->write(0xEF);
}

/**
 * Send descriptor message
 *
 */
void AirCommanderControl::sendDescriptor(void) {
    _serial->write(0x33);
    _serial->write(0x01);
    _serial->write(0x10);
    _serial->write(0x11);
}

/**
 * Handle RX interrupt.
 * This function sends a heartbeat message when requested by the Air Commander Entire.
 * This function also sends a descriptor messages, telling the Air Command Entire that
 * the attached MCU is an Air Commander Link Controller. 
 */
void AirCommanderControl::serialHandler(void) {
  
    while(_serial->available()){

        incomingByte = _serial->read();
        if( (heartbeatIdx > 0) || (incomingByte==0x60)){
            if(heartbeatIdx==0){
                heartbeatIdx++;
            }else if( (heartbeatIdx > 1) || (incomingByte==0x0B) ){
                if(heartbeatIdx==1){
                    heartbeatIdx++;
                }else if( incomingByte==0x6B ){
                    heartbeatIdx=0;
                    sendHeartbeat();
                }
            }else{
               heartbeatIdx = 0; 
            }
        }else if( (descriptorIdx > 0) || (incomingByte==0xCD)){
            if(descriptorIdx==0){
                descriptorIdx++;
            }else if( (descriptorIdx > 1) || (incomingByte==0xA9) ){
                if(descriptorIdx==1){
                    descriptorIdx++;
                }else if( (descriptorIdx > 2) || (incomingByte==0x00) ){
                    if(descriptorIdx==2){
                        descriptorIdx++;
                    }else if(incomingByte==0x00){
                        descriptorIdx=0;
                        sendDescriptor();
                    }
                }
            }else{
               descriptorIdx = 0; 
            }
        }else{
            heartbeatIdx = 0;
            descriptorIdx = 0;
        }
    }
}

/**
 *  Send photo command
 */
void AirCommanderControl::photo(void) {
    sendCommand(PHOTO_CMD);
}

/**
 *  Send video command
 */
void AirCommanderControl::video(void) {
    sendCommand(VIDEO_CMD);
}

/**
 *  Send menu command
 */
void AirCommanderControl::menu(void) {
    sendCommand(MENU_CMD);
}

/**
 *  Send sync command
 */
void AirCommanderControl::sync(void) {
    sendCommand(SYNC_CMD);
}

/**
 *  Send zoom_p command
 */
void AirCommanderControl::zoom_p(void) {
    sendCommand(ZOOM_P_CMD);
}

/**
 *  Send zoom_n command
 */
void AirCommanderControl::zoom_n(void) {
    sendCommand(ZOOM_N_CMD);
}

/**
 *  Send display command
 */
void AirCommanderControl::display(void) {
    sendCommand(DISP_CMD);
}

/**
 *  Send play button command
 */
void AirCommanderControl::press_play(void) {
    sendCommand(PLAY_CMD);
}

/**
 *  Send down button command
 */
void AirCommanderControl::press_down(void) {
    sendCommand(DOWN_CMD);
}

/**
 *  Send up button command
 */
void AirCommanderControl::press_up(void) {
    sendCommand(UP_CMD);
}

/**
 *  Send right button command
 */
void AirCommanderControl::press_right(void) {
    sendCommand(RIGHT_CMD);
}

/**
 *  Send left button command
 */
void AirCommanderControl::press_left(void) {
    sendCommand(LEFT_CMD);
}

/**
 *  Send ok button command
 */
void AirCommanderControl::press_ok(void) {
    sendCommand(OK_PRESS_CMD);
}

/**
 *  Send aperture_n command
 */
void AirCommanderControl::aperture_n(void) {
    sendCommand(APERTURE_N_CMD);
}

/**
 *  Send aperture_p command
 */
void AirCommanderControl::aperture_p(void) {
    sendCommand(APERTURE_P_CMD);
}

/**
 *  Send speed_n command
 */
void AirCommanderControl::speed_n(void) {
    sendCommand(SPEED_N_CMD);
}

/**
 *  Send speed_p command
 */
void AirCommanderControl::speed_p(void) {
    sendCommand(SPEED_P_CMD);
}

/**
 *  Send af command
 */
void AirCommanderControl::af(void) {
    sendCommand(AF_CMD);
}

/**
 *  Send af_mf command
 */
void AirCommanderControl::af_mf(void) {
    sendCommand(AF_MF_CMD);
}

/**
 *  Send c1 command
 */
void AirCommanderControl::c1(void) {
    sendCommand(C1_CMD);
}

/**
 *  Send c2 command
 */
void AirCommanderControl::c2(void) {
    sendCommand(C2_CMD);
}

/**
 *  Send c3 command
 */
void AirCommanderControl::c3(void) {
    sendCommand(C3_CMD);
}

/**
 *  Send command to camera
 *  @param cmd: command to be sent to the Air Commander Entire
 *  @param param: additional parameter to be sent (currently unused)
 */
void AirCommanderControl::sendCommand(uint8_t cmd, uint8_t param=0x00){
  // messages can only be sent every 100ms
  // TODO: improve the below to not deadlock
  while( (millis() - commanderLastPktTime) < TIME_BTWN_FRAMES);
  commanderLastPktTime = millis();
  
  _serial->write(0xAC);
  _serial->write(cmd);
  _serial->write(0xAC ^ cmd); // checksum
}
