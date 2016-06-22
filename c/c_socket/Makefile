default_target: all

all: serv_u cli_u serv_t cli_t 

serv_u:
	$(CC) socket_udp_serv.c  -o build/socket_u_serv

cli_u:
	$(CC) socket_udp_cli.c  -o build/socket_u_cli

serv_t:
	$(CC) socket_tcp_serv.c  -o build/socket_t_serv

cli_t:
	$(CC) socket_tcp_cli.c  -o build/socket_t_cli
