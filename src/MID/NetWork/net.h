#ifndef __NET_H
#define __NET_H
//--------------------------------------------------
#include "header.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "enc28j60.h"
//--------------------------------------------------
#define IP_ADDR {192,168,1,197}
#define IP_GATE {192,168,1,1}
#define IP_MASK {255,255,255,0}
#define MAC_BROADCAST {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
#define MAC_NULL {0x00,0x00,0x00,0x00,0x00,0x00} 
//--------------------------------------------------
typedef struct enc28j60_frame{
	uint8_t addr_dest[6];
	uint8_t addr_src[6];
	uint16_t  type;
	uint8_t data[];
} enc28j60_frame_ptr;
//--------------------------------------------------
typedef struct arp_msg{
	uint16_t  net_tp;
	uint16_t  proto_tp;
	uint8_t macaddr_len;
	uint8_t ipaddr_len;
	uint16_t  op;
	uint8_t macaddr_src[6];
	uint8_t ipaddr_src[4];
	uint8_t macaddr_dst[6];
	uint8_t ipaddr_dst[4];
} arp_msg_ptr;
//--------------------------------------------------
typedef struct ip_pkt{
	uint8_t verlen;//������ ��������� � ����� ���������
	uint8_t ts;//��� �������
	uint16_t len;//�����
	uint16_t id;//������������� ������
	uint16_t fl_frg_of;//����� � �������� ���������
	uint8_t ttl;//����� �����
	uint8_t prt;//��� ���������
	uint16_t cs;//����������� ����� ���������
	uint8_t ipaddr_src[4];//IP-����� �����������
	uint8_t ipaddr_dst[4];//IP-����� ����������
	uint8_t data[];//������
} ip_pkt_ptr;
//--------------------------------------------------
typedef struct icmp_pkt{
	uint8_t msg_tp;//��� �������
	uint8_t msg_cd;//��� ���������
	uint16_t cs;//����������� ����� ���������
	uint16_t id;//������������� ������
	uint16_t num;//����� ������
	uint8_t data[];//������
} icmp_pkt_ptr;
//--------------------------------------------------
 typedef struct USART_prop{
  uint8_t usart_buf[25];
  uint8_t usart_cnt;
  uint8_t is_ip;
} USART_prop_ptr;
//-------------------------------------------------- 
#define be16toword(a)	((((a)>>8)&0xff)|(((a)<<8)&0xff00))
#define be32todword(a) ((((a)>>24)&0xff)|(((a)>>8)&0xff00)|(((a)<<8)&0xff0000)|(((a)<<24)&0xff000000))
//--------------------------------------------------
#define ETH_ARP	be16toword(0x0806)
#define ETH_IP	be16toword(0x0800)
//--------------------------------------------------
#define ARP_ETH	be16toword(0x0001)
#define ARP_IP	be16toword(0x0800)
#define ARP_REQUEST	be16toword(1)
#define ARP_REPLY	be16toword(2)
//--------------------------------------------------
#define IP_ICMP	1
#define IP_TCP	6
#define IP_UDP	17
//--------------------------------------------------
#define ICMP_REQ	8
#define ICMP_REPLY	0
//--------------------------------------------------
void net_ini(void);
void net_poll(void);
void eth_send(enc28j60_frame_ptr *frame, uint16_t type, uint16_t len);
void UART1_RxCpltCallback(void);
void TIM_PeriodElapsedCallback(void);
uint8_t ip_send(enc28j60_frame_ptr *frame, uint16_t len);
uint16_t checksum(uint8_t *ptr, int16_t len, uint8_t type);
void net_cmd(void);
//--------------------------------------------------
#include "arp.h"
#include "udp.h"
#include "ntp.h"
#include "tcp.h"
//--------------------------------------------------
#endif /* __NET_H */
