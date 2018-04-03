#include "net.h"
#include "network.h"
//-----------------------------------------------
//extern UART_HandleTypeDef huart1;
//-----------------------------------------------
uint8_t net_buf[ENC28J60_MAXFRAME];
extern uint8_t macaddr[6];
uint8_t ipaddr[4]=IP_ADDR;
uint8_t ipgate[4]=IP_GATE;
uint8_t ipmask[4]=IP_MASK;
uint32_t clock_cnt=0;//������� ������
char str1[60]={0};
uint32_t ping_cnt=0;//������� ������������ ������
extern char str[20];
USART_prop_ptr usartprop;
extern ntp_prop_ptr ntpprop;
//-----------------------------------------------
void net_ini(void)
{
	usartprop.usart_buf[0]=0;
	usartprop.usart_cnt=0;
	usartprop.is_ip=0;
	console_serial_print_log("MAC : 1 2 3 4 5 6\r\n");
	enc28j60_init(macaddr);
	ntpprop.set=0;
	ntpprop.ntp_cnt=0;
	ntpprop.ntp_timer=0;
}
//-----------------------------------------------
uint16_t checksum(uint8_t *ptr, int16_t len, uint8_t type)
{
	uint32_t sum=0;
	if(type==1)
	{
		sum+=IP_UDP;
		sum+=len-8;
	}
	if(type==2)
	{
		sum+=IP_TCP;
		sum+=len-8;
	}
	while(len>1)
	{
		sum += (uint16_t) (((uint32_t)*ptr<<8)|*(ptr+1));
		ptr+=2;
		len-=2;
	}
	if(len) sum+=((uint32_t)*ptr)<<8;
	while(sum>>16) sum=(uint16_t)sum+(sum>>16);
	return ~be16toword((uint16_t)sum);
}
//-----------------------------------------------
void eth_send(enc28j60_frame_ptr *frame, uint16_t type, uint16_t len)
{
	memcpy(frame->addr_src,macaddr,6);
	frame->type=type;
	enc28j60_packetSend((void*)frame,len+sizeof(enc28j60_frame_ptr));
}
//-----------------------------------------------
uint8_t ip_send(enc28j60_frame_ptr *frame, uint16_t len)
{
	uint8_t res=0;
	ip_pkt_ptr *ip_pkt = (void*)(frame->data);
	//�������� ��������� ������ IP
	ip_pkt->len=be16toword(len);
	ip_pkt->fl_frg_of=0;
	ip_pkt->ttl=128;
	ip_pkt->cs=0;
	memcpy(ip_pkt->ipaddr_dst,ip_pkt->ipaddr_src,4);
	memcpy(ip_pkt->ipaddr_src,ipaddr,4);
	ip_pkt->cs=checksum((void*)ip_pkt,sizeof(ip_pkt_ptr),0);
	//�������� �����
	eth_send(frame,ETH_IP,len);
	return res;
}
//-----------------------------------------------
uint8_t icmp_read(enc28j60_frame_ptr *frame, uint16_t len)
{
	uint8_t res=0;
	ip_pkt_ptr *ip_pkt = (void*)(frame->data);
	icmp_pkt_ptr *icmp_pkt = (void*)(ip_pkt->data);
	if(len>=sizeof(icmp_pkt_ptr))
	{
		if(icmp_pkt->msg_tp==ICMP_REQ)
		{
			icmp_pkt->msg_tp=ICMP_REPLY;
			icmp_pkt->cs=0;
			icmp_pkt->cs=checksum((void*)icmp_pkt,len,0);
			memcpy(frame->addr_dest,frame->addr_src,6);
			ip_send(frame,len+sizeof(ip_pkt_ptr));
			sprintf(str1,"%d.%d.%d.%d-%d.%d.%d.%d icmp request\r\n",
				ip_pkt->ipaddr_dst[0],ip_pkt->ipaddr_dst[1],ip_pkt->ipaddr_dst[2],ip_pkt->ipaddr_dst[3],
				ip_pkt->ipaddr_src[0],ip_pkt->ipaddr_src[1],ip_pkt->ipaddr_src[2],ip_pkt->ipaddr_src[3]);
			console_serial_print_log(str1);
		}
		else if (icmp_pkt->msg_tp==ICMP_REPLY)
		{
			sprintf(str1,"%d.%d.%d.%d-%d.%d.%d.%d icmp reply\r\n",
			ip_pkt->ipaddr_src[0],ip_pkt->ipaddr_src[1],ip_pkt->ipaddr_src[2],ip_pkt->ipaddr_src[3],
			ip_pkt->ipaddr_dst[0],ip_pkt->ipaddr_dst[1],ip_pkt->ipaddr_dst[2],ip_pkt->ipaddr_dst[3]);
			console_serial_print_log(str1);
		}
	}
	return res;
}
//-----------------------------------------------
uint8_t ip_read(enc28j60_frame_ptr *frame, uint16_t len)
{
	uint8_t res = 0;
	ip_pkt_ptr *ip_pkt = (void*)(frame->data);
	if((ip_pkt->verlen==0x45)&&(!memcmp(ip_pkt->ipaddr_dst,ipaddr,4)))
	{
		//����� ������
		len = be16toword(ip_pkt->len) - sizeof(ip_pkt_ptr);
		if(ip_pkt->prt==IP_ICMP)
		{
			icmp_read(frame,len);
		}
		else if(ip_pkt->prt==IP_TCP)
		{
			tcp_read(frame,len);
		}
		else if(ip_pkt->prt==IP_UDP)
		{
			udp_read(frame,len);
		}
	}
	return res;
}
//-----------------------------------------------
uint8_t icmp_request(uint8_t* ip_addr)
{
  uint8_t res=0;
	uint16_t len;
	enc28j60_frame_ptr *frame=(void*) net_buf;
	ip_pkt_ptr *ip_pkt = (void*)(frame->data);
	icmp_pkt_ptr *icmp_pkt = (void*)ip_pkt->data;
	//�������� ��������� ������ ICMP
	icmp_pkt->msg_tp = 8;
	icmp_pkt->msg_cd = 0;
	icmp_pkt->id = be16toword(1);
	icmp_pkt->num = be16toword(ping_cnt);
	ping_cnt++;
	strcpy((char*)icmp_pkt->data,"abcdefghijklmnopqrstuvwabcdefghi");
	icmp_pkt->cs = 0;
	len = strlen((char*)icmp_pkt->data) + sizeof(icmp_pkt_ptr);
	icmp_pkt->cs=checksum((void*)icmp_pkt,len,0);
	//�������� ��������� ������ IP
	len+=sizeof(ip_pkt_ptr);
	ip_pkt->len=be16toword(len);
	ip_pkt->id = 0;
	ip_pkt->ts = 0;
	ip_pkt->verlen = 0x45;
	ip_pkt->fl_frg_of=0;
	ip_pkt->ttl=128;
	ip_pkt->cs = 0;
	ip_pkt->prt=IP_ICMP;
	memcpy(ip_pkt->ipaddr_dst,ip_addr,4);
	memcpy(ip_pkt->ipaddr_src,ipaddr,4);
	ip_pkt->cs = checksum((void*)ip_pkt,sizeof(ip_pkt_ptr),0);
	//�������� ����� Ethernet
	eth_send(frame,ETH_IP,len);
  return res;
}
//--------------------------------------------------
uint16_t port_extract(char* ip_str, uint8_t len)
{
  uint16_t port=0;
  int ch1=':';
  char *ss1;
  uint8_t offset = 0;
  ss1=strchr(ip_str,ch1);
  offset=ss1-ip_str+1;
  ip_str+=offset;
  port = atoi(ip_str);
  return port;
}
//--------------------------------------------------
void ip_extract(char* ip_str, uint8_t len, uint8_t* ipextp)
{
	uint8_t offset = 0;
  uint8_t i;
  char ss2[5] = {0};
  char *ss1;
  int ch1 = '.';
  int ch2 = ':';
	for(i=0;i<3;i++)
	{
		ss1 = strchr(ip_str,ch1);
		offset = ss1-ip_str+1;
		strncpy(ss2,ip_str,offset);
		ss2[offset]=0;
		ipextp[i] = atoi(ss2);
		ip_str+=offset;
		len-=offset;
	}
	ss1=strchr(ip_str,ch2);
	if (ss1!=NULL)
	{
		offset=ss1-ip_str+1;
		strncpy(ss2,ip_str,offset);
		ss2[offset]=0;
		ipextp[3] = atoi(ss2);
		return;
	}
	strncpy(ss2,ip_str,len);
	ss2[len]=0;
	ipextp[3] = atoi(ss2);
}
//-----------------------------------------------
void eth_read(enc28j60_frame_ptr *frame, uint16_t len)
{
	uint8_t res=0;
	if(len>sizeof(enc28j60_frame_ptr))
	{
		if(frame->type==ETH_ARP)
		{
			res = arp_read(frame,len-sizeof(enc28j60_frame_ptr));
			if(res==1)
			{
				arp_send(frame);
			}
			else if(res==2)
			{
				arp_table_fill(frame);
				if((usartprop.is_ip==3)||(usartprop.is_ip==5)||(usartprop.is_ip==7))//������ �������� UDP-, ICMP- ��� NTP ������
				{
					memcpy(frame->addr_dest,frame->addr_src,6);
					net_cmd();
				}
			}
		}
		else if(frame->type==ETH_IP)
		{
			console_serial_print_log("prepare web for send");
			HTML_prepare_web();
			ip_read(frame,len-sizeof(ip_pkt_ptr));
		}
		else
		{
			sprintf(str1,"%02X:%02X:%02X:%02X:%02X:%02X-%02X:%02X:%02X:%02X:%02X:%02X; %d; %04X\r\n",
			frame->addr_src[0],frame->addr_src[1],frame->addr_src[2],frame->addr_src[3],frame->addr_src[4],frame->addr_src[5],
			frame->addr_dest[0],frame->addr_dest[1],frame->addr_dest[2],frame->addr_dest[3],frame->addr_dest[4],frame->addr_dest[5],
			len, be16toword(frame->type));
			console_serial_print_log(str1);
		}		
	}
}
//-----------------------------------------------
void net_poll(void)
{
	uint16_t len;
	//uint8_t ip[4]={0};
	enc28j60_frame_ptr *frame=(void*)net_buf;
	while((len=enc28j60_packetReceive(net_buf,sizeof(net_buf)))>0)
	{
		eth_read(frame,len);
	}
}
//-----------------------------------------------
void net_cmd(void)
{
  static uint8_t ip[4]={0};
	static uint16_t port=0;
	enc28j60_frame_ptr *frame=(void*)net_buf;
  if(usartprop.is_ip==1)//������ �������� ARP-�������
  {
    ip_extract((char*)usartprop.usart_buf,usartprop.usart_cnt,ip);
    arp_request(ip);
    usartprop.is_ip = 0;
    usartprop.usart_cnt=0;
  }
	else if(usartprop.is_ip==2)//������ ������� ��������� UDP-�����
	{
		ip_extract((char*)usartprop.usart_buf,usartprop.usart_cnt,ip);
		usartprop.is_ip=3;//������ �������� UDP-������
		usartprop.usart_cnt=0;
		arp_request(ip);//������ mac-�����
	}
  else if(usartprop.is_ip==3)//������ �������� UDP-������
  {
		port=port_extract((char*)usartprop.usart_buf,usartprop.usart_cnt);
		udp_send(ip,port);
    usartprop.is_ip=0;
  }
	else if(usartprop.is_ip==4)//������ ������� ��������� ICMP-�����
  {
    ip_extract((char*)usartprop.usart_buf,usartprop.usart_cnt,ip);
    usartprop.is_ip=5;//������ �������� ICMP-������
    usartprop.usart_cnt=0;
    arp_request(ip);//������ mac-�����
  }
  else if(usartprop.is_ip==5)//������ �������� ICMP-������
  {
    icmp_request(ip);
    usartprop.is_ip=0;
  }
	else if(usartprop.is_ip==6)//������ ������� ��������� NTP-�����
	{
		ip_extract((char*)usartprop.usart_buf,usartprop.usart_cnt,ip);
		memcpy(ntpprop.ip_dst,ip,4);
		usartprop.is_ip=7;//������ �������� NTP-������
		usartprop.usart_cnt=0;
		arp_request(ip);//������ mac-�����
	}
	else if(usartprop.is_ip==7)//������ �������� NTP-������
	{
		port=port_extract((char*)usartprop.usart_buf,usartprop.usart_cnt);
		ntpprop.port_dst = port;
		ntpprop.ntp_cnt = 10; //10 �������
		ntpprop.ntp_timer = 5;//5 ������ �� ��������� �������
		ntpprop.set=1;//���� ������� ������� �������
		memcpy(ntpprop.macaddr_dst,frame->addr_dest,6);
		ntp_request(ntpprop.ip_dst,ntpprop.port_dst);
		usartprop.is_ip=0;
	}
}
//-----------------------------------------------
void UART1_RxCpltCallback(void)
{
	uint8_t b;
	b=str[0];
	//���� ����� �������� �������� ����� ������
	if(usartprop.usart_cnt>25)
	{
		usartprop.usart_cnt=0;
	}
	else if(b == 'a')
	{
		usartprop.is_ip=1;//������ �������� ARP-�������
		net_cmd();
	}
	else if (b=='u')
	{
		usartprop.is_ip=2;//������ ������� ��������� UDP-�����
		net_cmd();
	}
	else if (b=='p')
	{
		usartprop.is_ip=4;//������ ������� ��������� ICMP-�����
		net_cmd();
	}
	else if (b=='n')
	{
		usartprop.is_ip=6;//������ ������� ��������� NTP-�����
		net_cmd();
	}
	else
	{
		usartprop.usart_buf[usartprop.usart_cnt] = b;
		usartprop.usart_cnt++;
	}
	console_serial_print_log_Print("HAL_UART_Receive_IT(&huart1, (uint8_t*)str,1");
}
//-----------------------------------------------
void TIM_PeriodElapsedCallback(void)
{
  //������� ������� � ���������� �� � clock_cnt
  clock_cnt++;
	if (ntpprop.set)
	{
		ntpprop.ntp_timer--;
		if ((ntpprop.ntp_timer<0)&&(ntpprop.ntp_cnt>0))
		{
			ntpprop.ntp_timer = 5;
			ntpprop.ntp_cnt--;
			sprintf(str1,"ntp_cnt: %d\r\n",ntpprop.ntp_cnt);
			console_serial_print_log(str1);
			ntp_request(ntpprop.ip_dst,ntpprop.port_dst);
		}
		else if (ntpprop.ntp_cnt<=0)
		{
			//������� ��� ����� � ��������
			ntpprop.set=0;
			ntpprop.ntp_cnt=0;
			ntpprop.ntp_timer=0;
		}
	}
}
//-----------------------------------------------
