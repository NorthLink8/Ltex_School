#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <error.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>


int sock_raw=0;
FILE* logfile;
int tcp=0,
		udp=0,
		icmp=0,
		others=0,
		igmp=0,
		total=0;
struct sockaddr_in source, dest;

void ProcessPacket (unsigned char*, int);
void print_ip_header (unsigned char*, int);
void print_tcp_packet (unsigned char*, int);
void print_udp_packet (unsigned char*, int);
void print_icmp_packet (unsigned char*, int);
void PrintData (unsigned char*, int);


int main(void)
{
	int saddr_size=0, 
			data_size=0;
	struct sockaddr saddr;
	struct in_addr in;

	unsigned char* buffer=(unsigned char*)malloc(65536);
	logfile=fopen("log.txt", "w");
	if(logfile==NULL)
		perror("CREATE LOGFILE");
		//printf("Unable to create file");
	printf("Starting...\n");
	
	if((sock_raw=socket(AF_INET, SOCK_RAW, IPPROTO_TCP))<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");


	while(1)
	{
		saddr_size = sizeof(saddr);
		if((data_size=recvfrom(sock_raw, buffer, 65536, 0, &saddr, &saddr_size))<0)
		{
			perror("RECVFROM");
			exit(EXIT_FAILURE);
		}
		ProcessPacket(buffer, data_size);
	}
	//close(sock_raw);
	printf("Finished");
	return 0;
}

void ProcessPacket(unsigned char* buffer, int size)
{
	struct iphdr* iph=(struct iphdr*)buffer;
	++total;
	switch(iph->protocol)
	{
		case 1://ICMP protocol
			++icmp;
			break;
		case 2://IGMP protocol
			++igmp;
			break;
		case 6://TCP protocol
			++tcp;
			print_tcp_packet(buffer, size);
			break;
		case 17://UDP protocol
			++udp;
			print_udp_packet(buffer, size);
			break;
		default:
			++others;
			break;
	}
	printf("TCP:%d UDP:%d ICMP:%d IGMP:%d Others:%d Total:%d\r", 
			tcp,udp,icmp,igmp,others,total);
}

void print_ip_header(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen=0;
	struct iphdr* iph=(struct iphdr*)Buffer;
	iphdrlen=iph->ihl*4;

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr=iph->saddr;
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr=iph->daddr;

	fprintf(logfile, "\n");
	fprintf(logfile, "IP Header\n");
	fprintf(logfile, "|-IP Version					:%d\n", (unsigned)iph->version);
	fprintf(logfile, "|-IP Header Length		:%d DWORDS or %d Bytes\n", 
			(unsigned)iph->ihl, (((unsigned)(iph->ihl))*4));
	fprintf(logfile, "|-Type of service			:%d\n", (unsigned)iph->tos);
	fprintf(logfile, "|-IP Total Length			:%d Bytes(Size of Packet)\n", ntohs(iph->tot_len));
	fprintf(logfile, "|-Identification			:%d\n", htons(iph->id));
	fprintf(logfile, "|-TTL									:%d\n", (unsigned)iph->ttl);
	fprintf(logfile, "|-Protocol						:%d\n", (unsigned)iph->protocol);
	fprintf(logfile, "|-Checksum						:%d\n", ntohs(iph->check));
	fprintf(logfile, "|-Source IP						:%s\n", inet_ntoa(source.sin_addr));
	fprintf(logfile, "|-Destination IP			:%s\n", inet_ntoa(dest.sin_addr));
}

void print_tcp_packet(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen=0;
	struct iphdr* iph=(struct iphdr*)Buffer;
	iphdrlen=iph->ihl*4;
	
	struct tcphdr* tcph=(struct tcphdr*)(Buffer+iphdrlen);
	fprintf(logfile, 
			"\n\n**********************************TCP PACKET**********************************\n");
	print_ip_header(Buffer, Size);

	fprintf(logfile, "\n");
	fprintf(logfile, "TCP Header\n");
	fprintf(logfile, "|-Source Port					:%d\n", ntohs(tcph->source));
	fprintf(logfile, "|-Destination Port		:%d\n", ntohs(tcph->dest));
	fprintf(logfile, "|-Sequence Number			:%u\n", ntohs(tcph->seq));
	fprintf(logfile, "|-Acknowledge Number	:%u\n", ntohs(tcph->ack_seq));
	fprintf(logfile, "|-Header Length				:%d DWORDS or %d BYTES\n", 
			(unsigned)tcph->doff, (unsigned)tcph->doff*4);
	fprintf(logfile, "|-Urgent Flag					:%d\n", (unsigned)tcph->urg);
	fprintf(logfile, "|-Acknowledgement Flag:%d\n", (unsigned)tcph->ack);
	fprintf(logfile, "|-Push Flag						:%d\n", (unsigned)tcph->psh);
	fprintf(logfile, "|-Reset Flag					:%d\n", (unsigned)tcph->rst);
	fprintf(logfile, "|-Sychronise Flag			:%d\n", (unsigned)tcph->syn);
	fprintf(logfile, "|-Finish Flag					:%d\n", (unsigned)tcph->fin);
	fprintf(logfile, "|-Window							:%d\n", ntohs(tcph->window));
	fprintf(logfile, "|-Checksum						:%d\n", ntohs(tcph->check));
	fprintf(logfile, "|-Urgent Pointer			:%d\n", tcph->urg_ptr);
	fprintf(logfile, "\n		DATA Dump		\n");
	
	fprintf(logfile, "IP Header\n");
	PrintData(Buffer, iphdrlen);

	fprintf(logfile, "Data Payload\n");
	PrintData(Buffer+iphdrlen+tcph->doff*4, (Size - tcph->doff*4-iph->ihl*4));
	fprintf(logfile, "\n###############################################\n");
}

void print_udp_packet(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen=0;
	struct iphdr* iph=(struct iphdr*)Buffer;
	iphdrlen=iph->ihl*4;

	struct udphdr* udph=(struct udphdr*)(Buffer+iphdrlen);
	fprintf(logfile, 
			"\n\n**********************************UDP PACKET**********************************\n");
	print_ip_header(Buffer, Size);

	fprintf(logfile, "\nUDP Header\n");
	fprintf(logfile, "|-Source Port					:%d\n", ntohs(udph->source));
	fprintf(logfile, "|-Destination Port		:%d\n", ntohs(udph->dest));
	fprintf(logfile, "|-UDP Length					:%d\n", ntohs(udph->len));
	fprintf(logfile, "|-UDP Checksum				:%d\n", ntohs(udph->check));
	fprintf(logfile, "\n");
	fprintf(logfile, "IP Header\n");
	PrintData(Buffer, iphdrlen);
	
	fprintf(logfile, "UDP Header\n");
	PrintData(Buffer+iphdrlen, sizeof(udph));
	
	fprintf(logfile, "Data Payload\n");
	PrintData(Buffer+iphdrlen+sizeof(udph), (Size+sizeof(udph)-iph->ihl*4));
	fprintf(logfile, "\n###############################################\n");
}

void print_icmp_packet(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen=0;
	struct iphdr* iph=(struct iphdr*)Buffer;
	iphdrlen=iph->ihl*4;
	
	struct icmphdr* icmph=(struct icmphdr*)(Buffer+iphdrlen);
	fprintf(logfile, 
			"\n\n**********************************ICMP PACKET**********************************\n");
	print_ip_header(Buffer, Size);

	fprintf(logfile, "ICMP Packet");
	fprintf(logfile, "|-Type							:%d\n", (unsigned)(icmph->type));
	
	if(((unsigned)(icmph->type))==1L)
		fprintf(logfile, "	(TTL Expired)\n");
	else if(((unsigned)(icmph->type))==ICMP_ECHOREPLY)
		fprintf(logfile, "	(ICMP Echo Reply)");

	fprintf(logfile, "|-Code							:%d\n", (unsigned)(icmph->code));
	fprintf(logfile, "|-Checksum					:%d\n", ntohs(icmph->checksum));
	fprintf(logfile, "\n");
	
	fprintf(logfile, "IP Header\n");
	PrintData(Buffer, Size);
	
	fprintf(logfile, "UDP Header\n");
	PrintData(Buffer+iphdrlen, sizeof(icmph));
	
	fprintf(logfile, "Data payload\n");
	PrintData(Buffer+iphdrlen+sizeof(icmph), (Size-sizeof(icmph)-iph->ihl*4));
	fprintf(logfile, "\n###############################################\n");
}

void PrintData(unsigned char* data, int Size)
{
	for(unsigned i=0; i<Size; i++)
	{
		if(i!=0 && i%16==0)
		{
			fprintf(logfile, "				");
			for(unsigned j=i-16; j<i; j++)
			{
				if(data[j]>=32 && data[j]<=128)
					fprintf(logfile, "%c", (unsigned char)data[j]);
				else
					fprintf(logfile, ".");
			}
			fprintf(logfile, "\n");
		}
		if(i%16==0)
			fprintf(logfile, "		");
		fprintf(logfile, "%02X", (unsigned)data[i]);
		
		if(i==Size-1)
		{
			for(unsigned j=0; j<15-i%16; j++)
				fprintf(logfile, "		");
			fprintf(logfile, "				");
			
			for(unsigned j=i-i%16; j<=i; j++)
			{
				if(data[j]>=32 && data[j]<=128)
					fprintf(logfile, "%c", (unsigned char)data[j]);
				else
					fprintf(logfile, ".");
			}
			fprintf(logfile,"\n");
		}
		
	}
}



