#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char buff[512];
	char buff2[512];
	
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	
	
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	serv_adr.sin_port = htons(9080);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 2) < 0)
		printf("Error en el Listen");
	
	int i;
	
	for(i=0;i<7;i++){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		
		
		ret=read(sock_conn,buff, sizeof(buff));
		printf ("Recibido\n");
		
		
		buff[ret]='\0';
		
		
		
		printf ("Se ha conectado: %s\n",buff);
		
		
		char *p = strtok( buff, "/");
		int codigo =  atoi (p);
		p = strtok( NULL, "/");
		char nombre[20];
		strcpy (nombre, p);
		printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
		
		if (codigo ==1) 
			sprintf (buff2,"%d",strlen (nombre));
		
		if (codigo == 2)
		{
			
			if((nombre[0]=='P') || (nombre[0]=='O'))
			strcpy (buff2,"SI");
			else
				strcpy (buff2,"NO");
			
		}
			
		if (codigo == 3)
		{
	
			  
			  float altura1 = atoi(p);
			  printf ("%d\n", altura1);
			  if (altura1 > 170)
				  sprintf (buff2, "Eres alto");
			  else
				  sprintf (buff2, "eres bajo");
		}
		
			printf ("%s\n", buff2);
			write (sock_conn,buff2, strlen(buff2));
			close(sock_conn); 
	}
}
