#include <Cspider.h>

ssl_t * Cspider_Create_Openssl(int webfd)
{
	ssl_t * ssl = (ssl_t *)malloc(sizeof(ssl_t));
	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_ssl_algorithms();
	ssl->sslctx = SSL_CTX_new(SSLv23_method());
	ssl->sslsocket = SSL_new(ssl->sslctx);
	SSL_set_fd(ssl->sslsocket,webfd);
	SSL_connect(ssl->sslsocket);
	printf("[*6] Create SSL Success..\n");
	return ssl;
}
