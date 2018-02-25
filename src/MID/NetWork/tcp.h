#ifndef TCP_H_
#define TCP_H_
//--------------------------------------------------
#include "header.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "enc28j60.h"
#include "net.h"
//--------------------------------------------------
#define LOCAL_PORT_TCP 80
//--------------------------------------------------
typedef struct tcp_pkt {
  uint16_t port_src;//���� �����������
  uint16_t port_dst;//���� ����������
  uint32_t bt_num_seg;//���������� ����� ����� � ������ ������ (��������� �� ������ ���� � �������� ������)
  uint32_t num_ask;//����� ������������� (������ ���� � �������� + ���������� ������ � �������� + 1 ��� ����� ���������� ���������� �����)
  uint8_t len_hdr;//����� ���������
  uint8_t fl;//����� TCP
  uint16_t size_wnd;//������ ����
  uint16_t cs;//����������� ����� ���������
  uint16_t urg_ptr;//��������� �� ������� ������
  uint8_t data[];//������
} tcp_pkt_ptr;
//--------------------------------------------------
typedef struct tcp_prop {
	uint8_t macaddr_dst[6];//MAC-����� ����������
  uint8_t ipaddr_dst[6];//IP-����� ����������
  volatile uint16_t port_dst;//���� ����������
  volatile uint32_t seq_num;//���������� ����� �����
	volatile uint32_t seq_num_tmp;//���������� ����� ����� ���������
  volatile uint32_t ack_num;//����� �������������
  volatile uint32_t data_stat;//������ �������� ������
  volatile uint32_t data_size;//������ ������ ��� ��������
  volatile uint16_t last_data_part_size;//������ ��������� ����� ������ ��� ��������
	volatile uint16_t cnt_data_part;//����� ���������� ������ ������ ��� ��������
  volatile uint16_t cnt_rem_data_part;//���������� ���������� ������ ������ ��� ��������
	volatile uint8_t http_doc;//������� ��������� ��� ��������
} tcp_prop_ptr;
//-------------------------------------------------- 
//����� TCP
#define TCP_CWR 0x80
#define TCP_ECE 0x40
#define TCP_URG 0x20
#define TCP_ACK 0x10
#define TCP_PSH 0x08
#define TCP_RST 0x04
#define TCP_SYN 0x02
#define TCP_FIN 0x01
//--------------------------------------------------
//������� TCP
#define TCP_CONNECTED 1
#define TCP_DISCONNECTED 2
#define TCP_DISCONNECTING 3 //��������� ���������� ����� ������������� ����������
//--------------------------------------------------
//������� �������� ������
#define DATA_COMPLETED 0 //�������� ������ ���������
#define DATA_ONE 1 //������� ������������ �����
#define DATA_FIRST 2 //������� ������ �����
#define DATA_MIDDLE 3 //������� ������� �����
#define DATA_LAST 4 //������� ��������� �����
#define DATA_END 5 //��������� ���������� ����� �������� ������
//--------------------------------------------------
//�������� ���������� HTTP
#define INDEX_HTML 0
#define E404_HTML 1
//--------------------------------------------------
uint8_t tcp_read(enc28j60_frame_ptr *frame, uint16_t len);
//--------------------------------------------------
#endif /* TCP_H_ */
