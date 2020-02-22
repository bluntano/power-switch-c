#include "common.h"
#include <strings.h>

int main(int argc, char **argv)
{
	int listenfd, connfd, n;
	struct sockaddr_in servaddr;
	uint8_t buff[MAXLINE + 1];
	uint8_t recvline[MAXLINE + 1];
	
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("socket error.");
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);
	
	if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		err_n_die("bind error.");
	
	if ((listen(listenfd, 10)) < 0)
		err_n_die("listen error.");
	
	for (;;)
	{
		struct sockaddr_in addr;
		socklen_t addr_len;
		char client_address[MAXLINE + 1];
		
		printf("waiting for a connection on port %d\n", SERVER_PORT);
		fflush(stdout);
		connfd = accept(listenfd, (SA *) &addr, &addr_len);
		
		inet_ntop(AF_INET, &addr, client_address, MAXLINE);
		printf("Client connection: %s\n", client_address);
		
		memset(recvline, 0, MAXLINE);
		
		while ((n = read(connfd, recvline, MAXLINE - 1)) > 0)
		{
			fprintf(stdout, "\n\n%s", recvline);
			
			if (recvline[n-1] == '\n')
			{
				break;
			}
			memset(recvline, 0, MAXLINE);
		}
		
		if (n < 0)
			err_n_die("read error.");
		
		///////////////////
		// THE REAL DEAL //
		///////////////////
		char response[] = "HTTP/1.0 200 OK\r\n";
		char *content;
		int time = 0;
		
		strcat(response, "Content-Type: ");
		
		/////////////
		// GET REQ //
		/////////////
		if (strstr(recvline, "GET /main.css HTTP/1.1"))
		{
			strcat(response, "text/css; charset=UTF-8\r\n\r\n");
			content = readFile("public/main.css");
		}
		else if (strstr(recvline, "GET / HTTP/1.1") || strstr(recvline, "GET /index.html HTTP/1.1"))
		{
			strcat(response, "text/html; charset=UTF-8\r\n\r\n");
			content = readFile("views/index.html");
		}

		////////////////
		// BUTTON REQ //
		////////////////
		else if (strstr(recvline, "GET /onoff?onoff=default HTTP/1.1"))
		{
			time = 1;
			strcat(response, "text/html; charset=UTF-8\r\n\r\n");
			content = readFile("views/onoff.html");
		}
		else if (strstr(recvline, "GET /onoff?onoff=force HTTP/1.1"))
		{
			time = 8;
			strcat(response, "text/html; charset=UTF-8\r\n\r\n");
			content = readFile("views/force.html");
		}
		
		strcat(response, content);
		
		// printf("%s\n\n", response);
		
		snprintf((char*)buff, sizeof(buff), response);
		write(connfd, (char*)buff, strlen((char *)buff));
		close(connfd);
		
		if (time != 0)
			switch_on_off(4, time);
	}
}