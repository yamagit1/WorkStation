#include "tcp.h"
#include "stm32f4_html.h"
//--------------------------------------------------
//extern UART_HandleTypeDef huart1;
//-----------------------------------------------
extern char str1[60];
extern uint8_t net_buf[ENC28J60_MAXFRAME];
extern uint8_t macaddr[6];
extern uint8_t ipaddr[4];
tcp_prop_ptr tcpprop;
volatile uint16_t tcp_mss = 458;
volatile uint8_t tcp_stat = TCP_DISCONNECTED;
//--------------------------------------------------
const char http_header[] = {"HTTP/1.1 200 OK\r\nServer: nginx\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n"};
const char error_header[] = {"HTTP/1.1 404 File not found\r\nServer: nginx\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n"};
//-----------------------------------------------
const uint8_t e404_htm[] = {
0x3c,0x68,0x74,0x6d,0x6c,0x3e,0x0a,0x20,0x20,0x3c,0x68,0x65,0x61,0x64,0x3e,0x0a,
0x20,0x20,0x20,0x20,0x3c,0x74,0x69,0x74,0x6c,0x65,0x3e,0x34,0x30,0x34,0x20,0x4e,
0x6f,0x74,0x20,0x46,0x6f,0x75,0x6e,0x64,0x3c,0x2f,0x74,0x69,0x74,0x6c,0x65,0x3e,
0x0a,0x20,0x20,0x3c,0x2f,0x68,0x65,0x61,0x64,0x3e,0x0a,0x3c,0x62,0x6f,0x64,0x79,
0x3e,0x0a,0x3c,0x68,0x31,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x74,0x65,0x78,
0x74,0x2d,0x61,0x6c,0x69,0x67,0x6e,0x3a,0x20,0x63,0x65,0x6e,0x74,0x65,0x72,0x3b,
0x22,0x3e,0x34,0x30,0x34,0x20,0x45,0x72,0x72,0x6f,0x72,0x20,0x46,0x69,0x6c,0x65,
0x20,0x4e,0x6f,0x74,0x20,0x46,0x6f,0x75,0x6e,0x64,0x3c,0x2f,0x68,0x31,0x3e,0x0a,
0x3c,0x68,0x32,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x74,0x65,0x78,0x74,0x2d,
0x61,0x6c,0x69,0x67,0x6e,0x3a,0x20,0x63,0x65,0x6e,0x74,0x65,0x72,0x3b,0x22,0x3e,
0x20,0x54,0x68,0x65,0x20,0x70,0x61,0x67,0x65,0x20,0x79,0x6f,0x75,0x20,0x61,0x72,
0x65,0x20,0x6c,0x6f,0x6f,0x6b,0x69,0x6e,0x67,0x20,0x66,0x6f,0x72,0x20,0x6d,0x69,
0x67,0x68,0x74,0x20,0x68,0x61,0x76,0x65,0x20,0x62,0x65,0x65,0x6e,0x20,0x72,0x65,
0x6d,0x6f,0x76,0x65,0x64,0x2c,0x20,0x3c,0x62,0x72,0x20,0x2f,0x3e,0x68,0x61,0x64,
0x20,0x69,0x74,0x73,0x20,0x6e,0x61,0x6d,0x65,0x20,0x63,0x68,0x61,0x6e,0x67,0x65,
0x64,0x2c,0x20,0x6f,0x72,0x20,0x69,0x73,0x20,0x74,0x65,0x6d,0x70,0x6f,0x72,0x61,
0x72,0x69,0x6c,0x79,0x20,0x75,0x6e,0x61,0x76,0x61,0x69,0x6c,0x61,0x62,0x6c,0x65,
0x2e,0x3c,0x2f,0x68,0x32,0x3e,0x0a,0x3c,0x2f,0x62,0x6f,0x64,0x79,0x3e,0x3c,0x2f,
0x68,0x74,0x6d,0x6c,0x3e};
//-----------------------------------------------
//���������� ��������� TCP-������
void tcp_header_prepare(tcp_pkt_ptr *tcp_pkt, uint16_t port, uint8_t fl, uint16_t len, uint16_t len_cs)
{
  tcp_pkt->port_dst = be16toword(port);
  tcp_pkt->port_src = be16toword(LOCAL_PORT_TCP);
  tcp_pkt->bt_num_seg = tcpprop.seq_num;
  tcp_pkt->num_ask = tcpprop.ack_num;
  tcp_pkt->fl = fl;
  tcp_pkt->size_wnd = be16toword(8192);
  tcp_pkt->urg_ptr = 0;
  tcp_pkt->len_hdr = len << 2;
  tcp_pkt->cs = 0;
  tcp_pkt->cs=checksum((uint8_t*)tcp_pkt-8, len_cs+8, 2);
}
//--------------------------------------------------
//���������� ��������� IP-������
void ip_header_prepare(ip_pkt_ptr *ip_pkt, uint8_t *ip_addr, uint8_t prt, uint16_t len)
{
  ip_pkt->len=be16toword(len);
  ip_pkt->id = 0;
  ip_pkt->ts = 0;
  ip_pkt->verlen = 0x45;
  ip_pkt->fl_frg_of=0;
  ip_pkt->ttl=128;
  ip_pkt->cs = 0;
  ip_pkt->prt=prt;
  memcpy(ip_pkt->ipaddr_dst,ip_addr,4);
  memcpy(ip_pkt->ipaddr_src,ipaddr,4);
  ip_pkt->cs = checksum((void*)ip_pkt,sizeof(ip_pkt_ptr),0);
}
//--------------------------------------------------
/*�������� ������ �� ������ ����������*/
uint8_t tcp_send_synack(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
	tcpprop.seq_num = rand();
	tcpprop.ack_num = be32todword(be32todword(tcp_pkt->bt_num_seg) + 1);
	tcp_pkt->data[0]=2;//Maximum Segment Size (2)
	tcp_pkt->data[1]=4;//Length
	tcp_pkt->data[2]=(uint8_t) (tcp_mss>>8);//MSS = 458
	tcp_pkt->data[3]=(uint8_t) tcp_mss;	
	len = sizeof(tcp_pkt_ptr)+4;
	tcp_header_prepare(tcp_pkt, port, TCP_SYN|TCP_ACK, len, len);
	len+=sizeof(ip_pkt_ptr);
	ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
	//�������� ��������� Ethernet
	memcpy(frame->addr_dest,frame->addr_src,6);
	eth_send(frame,ETH_IP,len);	
	tcp_stat = TCP_CONNECTED;
  return res;
}
//--------------------------------------------------
/*�������� ������ �� ������ ������������ � ����� �������� ������ �� ������� ��� �������*/
uint8_t tcp_send_finack(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
  tcpprop.seq_num = tcp_pkt->num_ask;
  tcpprop.ack_num = be32todword(be32todword(tcp_pkt->bt_num_seg) + 1);
  len = sizeof(tcp_pkt_ptr);
  tcp_header_prepare(tcp_pkt, port, TCP_ACK, len, len);
  len+=sizeof(ip_pkt_ptr);
  ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
  //�������� ��������� Ethernet
  memcpy(frame->addr_dest,frame->addr_src,6);
  eth_send(frame,ETH_IP,len);
	if(tcp_stat == TCP_DISCONNECTED) return 0;
	tcp_pkt->fl = TCP_FIN|TCP_ACK;
	len = sizeof(tcp_pkt_ptr);
	tcp_pkt->cs = 0;
	tcp_pkt->cs=checksum((uint8_t*)tcp_pkt-8, len+8, 2);
	len+=sizeof(ip_pkt_ptr);
	eth_send(frame,ETH_IP,len);
	tcp_stat = TCP_DISCONNECTED;	
  return res;
}
//--------------------------------------------------
/*������������� �� ����� ������ � ����� ��� �������*/
uint8_t tcp_send_data(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len=0;
  uint16_t sz_data=0;
  tcp_stat = TCP_CONNECTED;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
  sz_data = be16toword(ip_pkt->len)-20-(tcp_pkt->len_hdr>>2);
  tcpprop.seq_num = tcp_pkt->num_ask;
  tcpprop.ack_num = be32todword(be32todword(tcp_pkt->bt_num_seg) + sz_data);
  len = sizeof(tcp_pkt_ptr);
  //�������� ������������� �� ����� ������
  tcp_header_prepare(tcp_pkt, port, TCP_ACK, len, len);
  len+=sizeof(ip_pkt_ptr);
  ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
  //�������� ��������� Ethernet
  memcpy(frame->addr_dest,frame->addr_src,6);
  eth_send(frame,ETH_IP,len);
  //���� ������ "Hello!!!", �� �������� �����
  if (!strcmp((char*)tcp_pkt->data,"Hello!!!"))
  {
    strcpy((char*)tcp_pkt->data,"Hello to TCP Client!!!\r\n");
    tcp_pkt->fl = TCP_ACK|TCP_PSH;
    len = sizeof(tcp_pkt_ptr);
    len+=strlen((char*)tcp_pkt->data);
    tcp_pkt->cs = 0;
    tcp_pkt->cs=checksum((uint8_t*)tcp_pkt-8, len+8, 2);
    len+=sizeof(ip_pkt_ptr);
    ip_pkt->len=be16toword(len);
    ip_pkt->cs = 0;
    ip_pkt->cs = checksum((void*)ip_pkt,sizeof(ip_pkt_ptr),0);
    //�������� ��������� Ethernet
    eth_send(frame,ETH_IP,len);
  }
  return res;
}
//--------------------------------------------------
/*�������� ������������� ������ HTTP*/
uint8_t tcp_send_http_one(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len=0;
  uint16_t sz_data=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
	//�������� ������� ������������� �� ����� �������
	sz_data = be16toword(ip_pkt->len)-20-(tcp_pkt->len_hdr>>2);	
	tcpprop.seq_num = tcp_pkt->num_ask;
	tcpprop.ack_num = be32todword(be32todword(tcp_pkt->bt_num_seg) + sz_data);
	len = sizeof(tcp_pkt_ptr);
	tcp_header_prepare(tcp_pkt, port, TCP_ACK, len, len);
	len+=sizeof(ip_pkt_ptr);
	ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
	//�������� ��������� Ethernet
	memcpy(frame->addr_dest,frame->addr_src,6);
	eth_send(frame,ETH_IP,len);
	//���������� ��������
	if (tcpprop.http_doc==INDEX_HTML)
	{
		strcpy((char*)tcp_pkt->data,http_header);
		memcpy((void*)(tcp_pkt->data+strlen(http_header)),(void*)gBufferWebsite , strlen(gBufferWebsite));
	}
	else
	{
		strcpy((char*)tcp_pkt->data,error_header);
		memcpy((void*)(tcp_pkt->data+strlen(error_header)),(void*)e404_htm,sizeof(e404_htm));
	}
	len = sizeof(tcp_pkt_ptr);
	len+=tcpprop.data_size;
	tcp_pkt->fl = TCP_PSH|TCP_ACK;
	tcp_pkt->cs = 0;
	tcp_pkt->cs=checksum((uint8_t*)tcp_pkt-8, len+8, 2);
	len+=sizeof(ip_pkt_ptr);
	ip_pkt->len=be16toword(len);
	ip_pkt->cs = 0;
	ip_pkt->cs = checksum((void*)ip_pkt,sizeof(ip_pkt_ptr),0);
	//�������� ��������� Ethernet
	eth_send(frame,ETH_IP,len);
	//���������� ����� �� ������� - �� ����� � �������� ��������� ����������
	tcpprop.seq_num_tmp = be32todword(be32todword(tcpprop.seq_num)+tcpprop.data_size);
	tcpprop.data_stat=DATA_END;
  return res;
}
//--------------------------------------------------
/*�������� ������� ������ �������������� ������ HTTP*/
uint8_t tcp_send_http_first(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len=0;
  uint16_t sz_data=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
  //�������� ������� ������������� �� ����� �������
  sz_data = be16toword(ip_pkt->len)-20-(tcp_pkt->len_hdr>>2);
  tcpprop.seq_num = tcp_pkt->num_ask;
  tcpprop.ack_num = be32todword(be32todword(tcp_pkt->bt_num_seg) + sz_data);
  len = sizeof(tcp_pkt_ptr);
  tcp_header_prepare(tcp_pkt, port, TCP_ACK, len, len);
  len+=sizeof(ip_pkt_ptr);
  ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
  //�������� ��������� Ethernet
  memcpy(frame->addr_dest,frame->addr_src,6);
  eth_send(frame,ETH_IP,len);
	//���������� ������ ����� ��������
	if (tcpprop.http_doc==INDEX_HTML)
	{
		strcpy((char*)tcp_pkt->data,http_header);
		memcpy((void*)(tcp_pkt->data+strlen(http_header)),(void*)gBufferWebsite,tcp_mss-strlen(http_header));
	}
	else
	{
		strcpy((char*)tcp_pkt->data,error_header);
		memcpy((void*)(tcp_pkt->data+strlen(error_header)),(void*)e404_htm,tcp_mss-strlen(error_header));
	}
	tcp_pkt->fl = TCP_ACK;
	len = sizeof(tcp_pkt_ptr);
	len+=tcp_mss;
	tcp_pkt->cs = 0;
	tcp_pkt->cs=checksum((uint8_t*)tcp_pkt-8, len+8, 2);
	len+=sizeof(ip_pkt_ptr);
	ip_pkt->len=be16toword(len);
	ip_pkt->cs = 0;
	ip_pkt->cs = checksum((void*)ip_pkt,sizeof(ip_pkt_ptr),0);
	//�������� ��������� Ethernet
	eth_send(frame,ETH_IP,len);
	//����� �������, ��� ���� ����� ���������, ������� ���������� ���������� ������ ��������������
	tcpprop.cnt_rem_data_part--;	
  if(tcpprop.cnt_rem_data_part>1)
  {
    tcpprop.data_stat=DATA_MIDDLE;
  }
  else
  {
    tcpprop.data_stat=DATA_LAST;
  }	
  return res;
}
//--------------------------------------------------
/*�������� �������� ������ �������������� ������ HTTP*/
uint8_t tcp_send_http_middle(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len_tcp=0, len=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
	//���������� ���� �� ������� ������ ��������
	//�������� ��������� ������ TCP
	tcpprop.seq_num = be32todword(be32todword(tcpprop.seq_num)+tcp_mss);
	len_tcp = sizeof(tcp_pkt_ptr);
	if (tcpprop.http_doc==INDEX_HTML)
	{
		memcpy((void*)tcp_pkt->data,(void*)(gBufferWebsite+(tcp_mss*(tcpprop.cnt_data_part-tcpprop.cnt_rem_data_part))-strlen(http_header)),tcp_mss);
	}
	else
	{
		memcpy((void*)tcp_pkt->data,(void*)(e404_htm+(tcp_mss*(tcpprop.cnt_data_part-tcpprop.cnt_rem_data_part))-strlen(error_header)),tcp_mss);
	}
	len=len_tcp + tcp_mss;
	tcp_header_prepare(tcp_pkt, port, TCP_ACK, len_tcp, len);
	len+=sizeof(ip_pkt_ptr);
	ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
	//�������� ��������� Ethernet
	memcpy(frame->addr_dest,tcpprop.macaddr_dst,6);
	eth_send(frame,ETH_IP,len);
	//����� �������, ��� ��� ���� ����� ���������, ������� ���������� ���������� ������ ��������������
	tcpprop.cnt_rem_data_part--;
  if(tcpprop.cnt_rem_data_part>1)
  {
    tcpprop.data_stat=DATA_MIDDLE;
  }
  else
  {
    tcpprop.data_stat=DATA_LAST;
  }
  return res;
}
//--------------------------------------------------
/*�������� ���������� ������ �������������� ������ HTTP*/
uint8_t tcp_send_http_last(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len_tcp=0, len=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
	//���������� ��������� ����� ��������
	//�������� ��������� ������ TCP
	tcpprop.seq_num = be32todword(be32todword(tcpprop.seq_num)+tcp_mss);
	len_tcp = sizeof(tcp_pkt_ptr);
	if (tcpprop.http_doc==INDEX_HTML)
	{
		memcpy((void*)tcp_pkt->data,(void*)(gBufferWebsite+(tcp_mss*(tcpprop.cnt_data_part-1))-strlen(http_header)),tcpprop.last_data_part_size);
	}
	else
	{
		memcpy((void*)tcp_pkt->data,(void*)(e404_htm+(tcp_mss*(tcpprop.cnt_data_part-1))-strlen(error_header)),tcpprop.last_data_part_size);
	}
	len=len_tcp + tcpprop.last_data_part_size;
	tcp_header_prepare(tcp_pkt, port, TCP_PSH|TCP_ACK, len_tcp, len);
	len+=sizeof(ip_pkt_ptr);
	ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
	//�������� ��������� Ethernet
	memcpy(frame->addr_dest,tcpprop.macaddr_dst,6);
	eth_send(frame,ETH_IP,len);	
  //����������� �� ������ ��������
  tcpprop.seq_num_tmp = be32todword(be32todword(tcp_pkt->bt_num_seg)+tcpprop.last_data_part_size);
  tcpprop.data_stat=DATA_END;
  return res;
}
//--------------------------------------------------
/*������������� ����� ��������� ������������� �� ��������� ����� ������*/
uint8_t tcp_send_http_dataend(enc28j60_frame_ptr *frame, uint8_t *ip_addr, uint16_t port)
{
  uint8_t res=0;
  uint16_t len=0;
  ip_pkt_ptr *ip_pkt = (void*)(frame->data);
  tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
  tcpprop.seq_num = tcpprop.seq_num_tmp;
  tcpprop.ack_num = tcp_pkt->bt_num_seg;
  len = sizeof(tcp_pkt_ptr);
  tcp_header_prepare(tcp_pkt, port, TCP_FIN|TCP_ACK, len, len);
  len+=sizeof(ip_pkt_ptr);
  ip_header_prepare(ip_pkt, ip_addr, IP_TCP, len);
  //�������� ��������� Ethernet
  memcpy(frame->addr_dest,frame->addr_src,6);
  eth_send(frame,ETH_IP,len);
  tcpprop.data_stat=DATA_COMPLETED;
  tcp_stat = TCP_DISCONNECTED;
  return res;
}
//--------------------------------------------------
uint8_t tcp_read(enc28j60_frame_ptr *frame, uint16_t len)
{
  uint8_t res=0;
	uint16_t len_data=0;
	uint16_t i=0;
	ip_pkt_ptr *ip_pkt = (void*)(frame->data);
	tcp_pkt_ptr *tcp_pkt = (void*)(ip_pkt->data);
	memcpy(tcpprop.macaddr_dst,frame->addr_src,6);
	memcpy(tcpprop.ipaddr_dst,ip_pkt->ipaddr_src,4);
	tcpprop.port_dst = be16toword(tcp_pkt->port_src);
	len_data = be16toword(ip_pkt->len)-20-(tcp_pkt->len_hdr>>2);
	sprintf(str1,"%d.%d.%d.%d-%d.%d.%d.%d %d tcp\r\n",
		ip_pkt->ipaddr_src[0],ip_pkt->ipaddr_src[1],ip_pkt->ipaddr_src[2],ip_pkt->ipaddr_src[3],
		ip_pkt->ipaddr_dst[0],ip_pkt->ipaddr_dst[1],ip_pkt->ipaddr_dst[2],ip_pkt->ipaddr_dst[3], len_data);
	Console_Log(str1);
	//���� ���� ������, �� ������� �� � ������������ ���������
	if (len_data)
	{
		for (i=0;i<len_data;i++)
		{
			Console_put_char(tcp_pkt->data+i);
		}
		Console_Trace("\r\n");
		//���� ������� ���� �������������, �� ���������� ���� ������
		if (tcp_pkt->fl&TCP_ACK)
		{
			//���� ������ "GET /", �� ������ ��� ������ HTTP
			if (strncmp((char*)tcp_pkt->data,"GET /", 5) == 0)
			{
				//���� ������, �� ��� ������ ������� ��������
				if((char)tcp_pkt->data[5]==' ')
				{
					tcpprop.http_doc = INDEX_HTML;
					//������� �������� � ������ ������ ���������
					tcpprop.data_size = strlen(http_header);
					//����� ������ ������ ���������
					tcpprop.data_size += strlen(gBufferWebsite);
				}
				else
				{
					tcpprop.http_doc = E404_HTML;
					//������� �������� � ������ ������ ���������
					tcpprop.data_size = strlen(error_header);
					//����� ������ ������ ���������
					tcpprop.data_size += sizeof(e404_htm);
				}
				tcpprop.cnt_rem_data_part = tcpprop.data_size / tcp_mss + 1;
				tcpprop.last_data_part_size = tcpprop.data_size % tcp_mss;
				//������ � ������������ ��������, ����� ����� ������ ������� �� ����������� ������ �������� ��� �������
				if(tcpprop.last_data_part_size==0)
				{
					tcpprop.last_data_part_size=tcp_mss;
					tcpprop.cnt_rem_data_part--;
				}
				tcpprop.cnt_data_part = tcpprop.cnt_rem_data_part;
				sprintf(str1,"data size:%lu; cnt data part:%u; last_data_part_size:%u\r\nport dst:%u\r\n",
					(unsigned long)tcpprop.data_size, tcpprop.cnt_rem_data_part, tcpprop.last_data_part_size,tcpprop.port_dst);
				Console_Log(str1);
				if (tcpprop.cnt_rem_data_part==1)
				{
					tcpprop.data_stat = DATA_ONE;
				}
				else if (tcpprop.cnt_rem_data_part>1)
				{
					tcpprop.data_stat = DATA_FIRST;
				}
				if(tcpprop.data_stat==DATA_ONE)
				{
					tcp_send_http_one(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
				}
				else if(tcpprop.data_stat==DATA_FIRST)
				{
					tcp_send_http_first(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
				}
			}
			//����� ������� ������
			else
			{
				tcp_send_data(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
			}
		}
	}
	if (tcp_pkt->fl == TCP_SYN)
	{
		tcp_send_synack(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
	}
	else if (tcp_pkt->fl == (TCP_FIN|TCP_ACK))
	{
		tcp_send_finack(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
	}
	else if (tcp_pkt->fl == (TCP_PSH|TCP_ACK))
	{
		//���� ������ ���
		if(!len_data)
		{
			tcp_send_finack(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
		}
	}
	else if (tcp_pkt->fl == TCP_ACK)
	{
		if (tcpprop.data_stat==DATA_END)
		{
			tcp_send_http_dataend(frame, ip_pkt->ipaddr_src, tcpprop.port_dst);
		}
		else if (tcpprop.data_stat==DATA_MIDDLE)
		{
			tcp_send_http_middle(frame, tcpprop.ipaddr_dst, tcpprop.port_dst);
		}
		else if (tcpprop.data_stat==DATA_LAST)
		{
			Console_Log("LAST\r\n");
			tcpprop.data_stat=DATA_COMPLETED;
			tcp_send_http_last(frame, tcpprop.ipaddr_dst, tcpprop.port_dst);
		}
		Console_Log("ACK\r\n");
	}
  return res;
}
//--------------------------------------------------
