#ifndef UDP_H_
#define UDP_H_
//--------------------------------------------------
#include "header.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "enc28j60.h"
#include "net.h"
//--------------------------------------------------
#define LOCAL_PORT 333
//--------------------------------------------------
typedef struct udp_pkt {
  uint16_t port_src;//���� �����������
  uint16_t port_dst;//���� ����������
  uint16_t len;//�����
  uint16_t cs;//����������� ����� ���������
  uint8_t data[];//������
} udp_pkt_ptr;
//--------------------------------------------------
 uint8_t udp_read(enc28j60_frame_ptr *frame, uint16_t len);
uint8_t udp_send(uint8_t *ip_addr, uint16_t port);
//--------------------------------------------------
#endif /* UDP_H_ */
