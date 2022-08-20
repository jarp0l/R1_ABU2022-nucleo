#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "stm32f3xx.h"

#define XBeeDataDelim 0x7e
#define XBeeDataEscape 0x7d
#define Zigbee_Transmit_Request 0x10
#define Explicit_Addressing_Zigbee_Command_Frame 0x11
#define Remote_Command_Request 0x17
#define Create_Source_Route 0x21
#define AT_Command_Response 0x88
#define Modem_Status 0x8A
#define Zigbee_Transmit_Status 0x8B
#define Zigbee_Receive_Packet 0x90
#define Zigbee_Explicit_Rx_Indicator 0x91
#define Zigbee_IO_Data_Sample_Rx_Indicator 0x92
#define XBee_Sensor_Read_Indicator 0x94
#define Node_Identification_Indicator 0x95
#define Remote_Command_Response 0x97
#define Extended_Modem_Status 0x98

#define Packet_Misaligned 0x11
#define Packet_Error 0x12
#define Packet_Checksum_Error 0x12
#define Packet_Success 0x00

#define Payload_Size 0x08

typedef struct XBeeRecData {
    uint8_t delim;
    uint8_t msblength;
    uint8_t lsblength;
    uint8_t frameID;
    uint32_t receiveraddressUP;
    uint32_t receiveraddressLW;
    uint16_t srcaddress;
    uint8_t recoption;
    uint8_t payload[8];
    uint8_t checksum;
} XBeeReceivePacket;

typedef struct XBeeTranData {
    uint8_t delim;
    uint8_t msblength;
    uint8_t lsblength;
    uint8_t frametype;
    uint8_t frameid;
    uint32_t receiveraddressUP;
    uint32_t receiveraddressLW;
    uint16_t networkdestaddress;
    uint8_t srcendpoint;
    uint8_t destendpoint;
    uint16_t cid;
    uint16_t pfid;

} XBeeTransmitPacket;

typedef struct XBee {
    UART_HandleTypeDef *huart;
    XBeeReceivePacket *rpac;
    uint8_t *rxbuffer;
} XBeeUartHandle;

void XBeeSetRxBuffer(XBeeUartHandle *hndl, uint8_t *buffer) {
    hndl->rxbuffer = buffer;
}

uint8_t XBeeDecodePacket(XBeeUartHandle *hndl) {
    uint16_t checksum = 0x0000;
    uint8_t data[24] = {0};
    bool _escape = false;
    int i, j;
    for (i = 0, j = 0; j < 4; ++i) {
        if (i > 0 && hndl->rxbuffer[i] == XBeeDataEscape) {
            _escape = true;
            continue;
        }
        if (_escape) {
            data[j] = hndl->rxbuffer[i] ^ 0x20;
            _escape = false;
        } else
            data[j] = hndl->rxbuffer[i];
        if (j == 3)
            checksum += data[j];
        ++j;
    }
    uint16_t length;
    hndl->rpac->delim = data[0];
    hndl->rpac->lsblength = data[1];
    hndl->rpac->msblength = data[2];
    hndl->rpac->frameID = data[3];
    switch (hndl->rpac->frameID) {
    case Zigbee_Receive_Packet:
        length = (data[1] << 8 | data[2]) + 4;
        for (; j < length; ++i) {
            if (hndl->rxbuffer[i] == XBeeDataEscape) {
                _escape = true;
                continue;
            }
            if (_escape) {
                data[j] = hndl->rxbuffer[i] ^ 0x20;
                _escape = false;
            } else
                data[j] = hndl->rxbuffer[i];
            if (j != 23)
                checksum += data[j];
            ++j;
        }
        checksum = 0xFF - (0x00FF & checksum);
        if (checksum != data[length - 1])
            return Packet_Checksum_Error;
        hndl->rpac->receiveraddressUP =
            (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
        hndl->rpac->receiveraddressLW =
            (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];
        hndl->rpac->srcaddress = (data[12] << 8) | data[13];
        hndl->rpac->recoption = data[14];
        for (j = 0; j < Payload_Size; ++j)
            hndl->rpac->payload[j] = data[15 + j];
        hndl->rpac->checksum = checksum;
        return Packet_Success;
        break;

    case Modem_Status:
        length = (data[1] << 8 | data[2]) + 4;
        for (; j < length; ++i) {
            if (hndl->rxbuffer[i] == XBeeDataEscape) {
                _escape = true;
                continue;
            }
            if (_escape) {
                data[j] = hndl->rxbuffer[i] ^ 0x20;
                _escape = false;
            } else
                data[j] = hndl->rxbuffer[i];
            if (j != 5)
                checksum += data[j];
            ++j;
        }
        checksum = 0xFF - (0x00FF & checksum);
        if (checksum != data[5])
            return Packet_Checksum_Error;
        hndl->rpac->recoption = data[4];
        break;

    default:
        break;
    }
    return 1;
}

bool XBeeReadPacket(XBeeUartHandle *hndl) {
    bool decoded = false;
    if (!XBeeDecodePacket(hndl))
        return !decoded;
    return decoded;
};
