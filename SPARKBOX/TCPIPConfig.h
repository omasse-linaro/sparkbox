/**********************************************************************************************************
 *								Projet Open Source  >> SPARKBOX <<
 *  SARL ADTEK
 **********************************************************************************************************
 * Author | Jean Arhainx  |  Date  19/03/2014   |
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * This work is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/ or
 * send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *********************************************************************************************************/
#ifndef __TCPIPCONFIG_H
#define __TCPIPCONFIG_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

#define ADT22

// =======================================================================
//   Application Options
// =======================================================================

/* Application Level Module Selection
 *   Uncomment or comment the following lines to enable or
 *   disabled the following high-level application modules.
 */
//#define STACK_USE_UART				// Application demo using UART for IP address display and stack configuration
//#define STACK_USE_UART2TCP_BRIDGE		// UART to TCP Bridge application example
//#define STACK_USE_IP_GLEANING
#define STACK_USE_ICMP_SERVER			// Ping query and response capability
//#define STACK_USE_ICMP_CLIENT			// Ping transmission capability
//#define STACK_USE_HTTP_SERVER			// Old HTTP server
#define STACK_USE_HTTP2_SERVER			// New HTTP server with POST, Cookies, Authentication, etc.
#define STACK_USE_SSL_SERVER			// SSL server socket support (Requires SW300052)
#define STACK_USE_SSL_CLIENT			// SSL client socket support (Requires SW300052)
//#define STACK_USE_AUTO_IP              // Dynamic link-layer IP address automatic configuration protocol
#define STACK_USE_DHCP_CLIENT			// Dynamic Host Configuration Protocol client for obtaining IP address and other parameters
//#define STACK_USE_DHCP_SERVER			// Single host DHCP server
//#define STACK_USE_FTP_SERVER			// File Transfer Protocol (old)
#define STACK_USE_SMTP_CLIENT			// Simple Mail Transfer Protocol for sending email
//#define STACK_USE_SNMP_SERVER			// Simple Network Management Protocol v2C Community Agent
//#define STACK_USE_TFTP_CLIENT			// Trivial File Transfer Protocol client
//#define STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE	// HTTP Client example in GenericTCPClient.c
//#define STACK_USE_GENERIC_TCP_SERVER_EXAMPLE	// ToUpper server example in GenericTCPServer.c
//#define STACK_USE_TELNET_SERVER		// Telnet server
#define STACK_USE_ANNOUNCE			// Microchip Embedded Ethernet Device Discoverer server/client
#define STACK_USE_DNS					// Domain Name Service Client for resolving hostname strings to IP addresses
//#define STACK_USE_DNS_SERVER			// Domain Name Service Server for redirection to the local device
#define STACK_USE_NBNS					// NetBIOS Name Service Server for repsonding to NBNS hostname broadcast queries
//#define STACK_USE_REBOOT_SERVER		// Module for resetting this PIC remotely.  Primarily useful for a Bootloader.
//#define STACK_USE_SNTP_CLIENT			// Simple Network Time Protocol for obtaining current date/time from Internet
//#define STACK_USE_UDP_PERFORMANCE_TEST	// Module for testing UDP TX performance characteristics.  NOTE: Enabling this will cause a huge amount of UDP broadcast packets to flood your network on the discard port.  Use care when enabling this on production networks, especially with VPNs (could tunnel broadcast traffic across a limited bandwidth connection).
//#define STACK_USE_TCP_PERFORMANCE_TEST	// Module for testing TCP TX performance characteristics
//#define STACK_USE_DYNAMICDNS_CLIENT		// Dynamic DNS client updater module
//#define STACK_USE_BERKELEY_API		// Berekely Sockets APIs are available
//#define STACK_USE_ZEROCONF_LINK_LOCAL	// Zeroconf IPv4 Link-Local Addressing
//#define STACK_USE_ZEROCONF_MDNS_SD	// Zeroconf mDNS and mDNS service discovery
//#define STACK_USE_UPNP 


// =======================================================================
//   Data Storage Options
// =======================================================================

#define STACK_USE_MPFS2

#define STACK_USE_MDD

#define MPFS_RESERVE_BLOCK				(137ul)

#define MAX_MPFS_HANDLES				(7ul)

// =======================================================================
//   Network Addressing Options
// =======================================================================

#define MY_DEFAULT_HOST_NAME			"SPARKBOX"

#define MY_DEFAULT_MAC_BYTE1            (0x00)	// Use the default of
#define MY_DEFAULT_MAC_BYTE2            (0x04)	// 00-04-A3-00-00-00 if using
#define MY_DEFAULT_MAC_BYTE3            (0xA3)	// an ENCX24J600 or MRF24WB0M
#define MY_DEFAULT_MAC_BYTE4            (0x00)	// and wish to use the internal
#define MY_DEFAULT_MAC_BYTE5            (0x00)	// factory programmed MAC
#define MY_DEFAULT_MAC_BYTE6            (0x00)	// address instead.

#define MY_DEFAULT_IP_ADDR_BYTE1        (192ul)
#define MY_DEFAULT_IP_ADDR_BYTE2        (168ul)
#define MY_DEFAULT_IP_ADDR_BYTE3        (0ul)
#define MY_DEFAULT_IP_ADDR_BYTE4        (160ul) // ADT donc 192.168.0.160

#define MY_DEFAULT_MASK_BYTE1           (255ul)
#define MY_DEFAULT_MASK_BYTE2           (255ul)
#define MY_DEFAULT_MASK_BYTE3           (255ul)
#define MY_DEFAULT_MASK_BYTE4           (0ul)

#define MY_DEFAULT_GATE_BYTE1           (192ul)
#define MY_DEFAULT_GATE_BYTE2           (168ul)
#define MY_DEFAULT_GATE_BYTE3           (0ul)
#define MY_DEFAULT_GATE_BYTE4           (1ul)

// OpenDNS1
#define MY_DEFAULT_PRIMARY_DNS_BYTE1	(192ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE2	(168ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE3	(0ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE4	(1ul)

// OpenDNS2
#define MY_DEFAULT_SECONDARY_DNS_BYTE1	(208ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE2	(67ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE3	(220ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE4	(220ul)

// =======================================================================
//   PIC32MX7XX/6XX MAC Layer Options
//   If not using a PIC32MX7XX/6XX device, ignore this section.
// =======================================================================
#define	ETH_CFG_LINK			0		// set to 1 if you need to config the link to specific following parameters
										// otherwise the default connection will be attempted
										// depending on the selected PHY
	#define	ETH_CFG_AUTO		1		// use auto negotiation
	#define	ETH_CFG_10			1		// use/advertise 10 Mbps capability
	#define	ETH_CFG_100			1		// use/advertise 100 Mbps capability
	#define	ETH_CFG_HDUPLEX		1		// use/advertise half duplex capability
	#define	ETH_CFG_FDUPLEX		1		// use/advertise full duplex capability
	#define	ETH_CFG_AUTO_MDIX	1		// use/advertise auto MDIX capability
	#define	ETH_CFG_SWAP_MDIX	1		// use swapped MDIX. else normal MDIX

#define EMAC_TX_DESCRIPTORS		2		// number of the TX descriptors to be created
#define EMAC_RX_DESCRIPTORS		8		// number of the RX descriptors and RX buffers to be created

#define	EMAC_RX_BUFF_SIZE		1536	// size of a RX buffer. should be multiple of 16
										// this is the size of all receive buffers processed by the ETHC
										// The size should be enough to accomodate any network received packet
										// If the packets are larger, they will have to take multiple RX buffers
										// The current implementation does not handle this situation right now and the packet is discarded.


// =======================================================================
//   Transport Layer Options
// =======================================================================

#define STACK_USE_TCP
#define STACK_USE_UDP
#define STACK_CLIENT_MODE


#if ( defined(ADT22) || defined (ADT18))		
	#define TCP_ETH_RAM_SIZE					(16384ul) // L'ENC 624 a 24K de RAM
	#define TCP_PIC_RAM_SIZE					(0ul)
	#define TCP_SPI_RAM_SIZE					(0ul)
	#define TCP_SPI_RAM_BASE_ADDRESS			(0x00)
#else
	#error Carte non definie
#endif	
	
// Define names of socket types
#define TCP_SOCKET_TYPES
	#define TCP_PURPOSE_GENERIC_TCP_CLIENT 0
	#define TCP_PURPOSE_GENERIC_TCP_SERVER 1
	#define TCP_PURPOSE_TELNET 2
	#define TCP_PURPOSE_FTP_COMMAND 3
	#define TCP_PURPOSE_FTP_DATA 4
	#define TCP_PURPOSE_TCP_PERFORMANCE_TX 5
	#define TCP_PURPOSE_TCP_PERFORMANCE_RX 6
	#define TCP_PURPOSE_UART_2_TCP_BRIDGE 7
	#define TCP_PURPOSE_HTTP_SERVER 8
	#define TCP_PURPOSE_DEFAULT 9
	#define TCP_PURPOSE_BERKELEY_SERVER 10
	#define TCP_PURPOSE_BERKELEY_CLIENT 11
	//#define TCP_PURPOSE_ADTEK_BDPV 100
#define END_OF_TCP_SOCKET_TYPES

#if defined(__TCP_C)
	#if (defined (ADT22) || defined (ADT18))
		#define TCP_CONFIGURATION
			ROM struct
			{
				BYTE vSocketPurpose;
				BYTE vMemoryMedium;
				WORD wTXBufferSize;
				WORD wRXBufferSize;
			} TCPSocketInitializer[] =
			{
				//{TCP_PURPOSE_GENERIC_TCP_CLIENT, TCP_PIC_RAM, 125, 1200},
				//{TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_PIC_RAM, 2500, 1000},
				//{TCP_PURPOSE_TELNET, TCP_PIC_RAM, 200, 150},
				//{TCP_PURPOSE_TELNET, TCP_PIC_RAM, 200, 150},
				//{TCP_PURPOSE_TELNET, TCP_PIC_RAM, 200, 150},
				//{TCP_PURPOSE_FTP_COMMAND, TCP_PIC_RAM, 100, 40},
				//{TCP_PURPOSE_FTP_DATA, TCP_PIC_RAM, 0, 128},
				//{TCP_PURPOSE_TCP_PERFORMANCE_TX, TCP_PIC_RAM, 2000, 1},
				//{TCP_PURPOSE_TCP_PERFORMANCE_RX, TCP_PIC_RAM, 40, 2000},
				//{TCP_PURPOSE_UART_2_TCP_BRIDGE, TCP_PIC_RAM, 256, 256},
				//{TCP_PURPOSE_HTTP_SERVER, TCP_PIC_RAM, 1000, 1000},
				{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 1492, 512},
				{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 1492, 512},
				//{TCP_PURPOSE_DEFAULT, TCP_PIC_RAM, 1000, 1000},
				{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 250, 250},
				{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 250, 250},
				{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 250, 250},
				//{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 250, 250},
				//{TCP_PURPOSE_ADTEK_BDPV, TCP_PIC_RAM, 300, 1024},
			};
		#define END_OF_TCP_CONFIGURATION
	#else
		#error Carte non definie	
	#endif
#endif

/* UDP Socket Configuration
 *   Define the maximum number of available UDP Sockets, and whether
 *   or not to include a checksum on packets being transmitted.
 */
#define MAX_UDP_SOCKETS     (15u)
#define UDP_USE_TX_CHECKSUM		// This slows UDP TX performance by nearly 50%, except when using the ENCX24J600, which has a super fast DMA and incurs virtually no speed pentalty.


/* Berkeley API Sockets Configuration
 *   Note that each Berkeley socket internally uses one TCP or UDP socket
 *   defined by MAX_UDP_SOCKETS and the TCPSocketInitializer[] array.
 *   Therefore, this number MUST be less than or equal to MAX_UDP_SOCKETS + the
 *   number of TCP sockets defined by the TCPSocketInitializer[] array
 *   (i.e. sizeof(TCPSocketInitializer)/sizeof(TCPSocketInitializer[0])).
 *   This define has no effect if STACK_USE_BERKELEY_API is not defined and
 *   Berkeley Sockets are disabled.  Set this value as low as your application
 *   requires to avoid waisting RAM.
 */
#define BSD_SOCKET_COUNT (5u)


// =======================================================================
//   Application-Specific Options
// =======================================================================

// -- HTTP2 Server options -----------------------------------------------

	// Maximum numbers of simultaneous HTTP connections allowed.
	// Each connection consumes 2 bytes of RAM and a TCP socket
	#define MAX_HTTP_CONNECTIONS	(2u)

	// Indicate what file to serve when no specific one is requested
	#define HTTP_DEFAULT_FILE		"index.htm"
	#define HTTPS_DEFAULT_FILE		"index.htm"
	#define HTTP_DEFAULT_LEN		(10u)		// For buffer overrun protection.
												// Set to longest length of above two strings.

	// Configure MPFS over HTTP updating
	// Comment this line to disable updating via HTTP
	#define HTTP_MPFS_UPLOAD		"mpfsupload"
	//#define HTTP_MPFS_UPLOAD_REQUIRES_AUTH	// Require password for MPFS uploads
		// Certain firewall and router combinations cause the MPFS2 Utility to fail
		// when uploading.  If this happens, comment out this definition.

	// Define which HTTP modules to use
	// If not using a specific module, comment it to save resources
	#define HTTP_USE_POST					// Enable POST support
	//#define HTTP_USE_COOKIES				// Enable cookie support
	#define HTTP_USE_AUTHENTICATION			// Enable basic authentication support

	//#define HTTP_NO_AUTH_WITHOUT_SSL		// Uncomment to require SSL before requesting a password
	#define HTTP_SSL_ONLY_CHAR		(0xFF)	// Files beginning with this character will only be served over HTTPS
											// Set to 0x00 to require for all files
											// Set to 0xff to require for no files

    // Define the listening port for the HTTP server
  	#define HTTP_PORT               (80u)
	
    // Define the listening port for the HTTPS server (if STACK_USE_SSL_SERVER is enabled)
	#define HTTPS_PORT				(443u)
	
    // Define the maximum data length for reading cookie and GET/POST arguments (bytes)
	#define HTTP_MAX_DATA_LEN		(100u)
	
    // Define the minimum number of bytes free in the TX FIFO before executing callbacks
	#define HTTP_MIN_CALLBACK_FREE	(16u)

	//	#define STACK_USE_HTTP_APP_RECONFIG		// Use the AppConfig web page in the Demo App (~2.5kb ROM, ~0b RAM)
	//	#define STACK_USE_HTTP_MD5_DEMO			// Use the MD5 Demo web page (~5kb ROM, ~160b RAM)
	//	#define STACK_USE_HTTP_EMAIL_DEMO		// Use the e-mail demo web page
	
	// -- SSL Options --------------------------------------------------------

	#define MAX_SSL_CONNECTIONS		(2ul)	// Maximum connections via SSL
	#define MAX_SSL_SESSIONS		(2ul)	// Max # of cached SSL sessions
	#define MAX_SSL_BUFFERS			(4ul)	// Max # of SSL buffers (2 per socket)
	#define MAX_SSL_HASHES			(5ul)	// Max # of SSL hashes  (2 per, plus 1 to avoid deadlock)

	// Bits in SSL RSA key.  This parameter is used for SSL sever
	// connections only.  The only valid value is 512 bits (768 and 1024
	// bits do not work at this time).  Note, however, that SSL client
	// operations do currently work up to 1024 bit RSA key length.
	#define SSL_RSA_KEY_SIZE		(512ul)


	// -- Telnet Options -----------------------------------------------------

	// Number of simultaneously allowed Telnet sessions.  Note that you
	// must have an equal number of TCP_PURPOSE_TELNET type TCP sockets
	// declared in the TCPSocketInitializer[] array above for multiple
	// connections to work.  If fewer sockets are available than this
	// definition, then the the lesser of the two quantities will be the
	// actual limit.
	#define MAX_TELNET_CONNECTIONS	(1u)

	// Default local listening port for the Telnet server.  Port 23 is the
	// protocol default.
	#define TELNET_PORT				23

	// Default local listening port for the Telnet server when SSL secured.
	// Port 992 is the telnets protocol default.
	#define TELNETS_PORT			992

	// Force all connecting clients to be SSL secured and connected via
	// TELNETS_PORT.  Connections on port TELNET_PORT will be ignored.  If
	// STACK_USE_SSL_SERVER is undefined, this entire setting is ignored
	// (server will accept unsecured connections on TELNET_PORT and won't even
	// listen on TELNETS_PORT).
	//#define TELNET_REJECT_UNSECURED

	// Default username and password required to login to the Telnet server.
	#define TELNET_USERNAME			"admin"
	#define TELNET_PASSWORD			"admin"


	// -- SNMP Options -------------------------------------------------------

	// Comment following line if SNMP TRAP support is needed
	//#define SNMP_TRAP_DISABLED

	// This is the maximum length for community string.
	// Application must ensure that this length is observed.
	// SNMP module adds one byte extra after SNMP_COMMUNITY_MAX_LEN
	// for adding '\0' NULL character.
	#define SNMP_COMMUNITY_MAX_LEN  	(8u)
	#define SNMP_MAX_COMMUNITY_SUPPORT	(3u)
	#define NOTIFY_COMMUNITY_LEN		(SNMP_COMMUNITY_MAX_LEN)

	// Default SNMPv2C community names.  These can be overridden at run time if
	// alternate strings are present in external EEPROM or Flash (actual
	// strings are stored in AppConfig.readCommunity[] and
	// AppConfig.writeCommunity[] arrays).  These strings are case sensitive.
	// An empty string means disabled (not matchable).
	// For application security, these default community names should not be
	// used, but should all be disabled to force the end user to select unique
	// community names.  These defaults are provided only to make it easier to
	// start development.  Specifying more strings than
	// SNMP_MAX_COMMUNITY_SUPPORT will result in the later strings being
	// ignored (but still wasting program memory).  Specifying fewer strings is
	// legal, as long as at least one is present.  A string larger than
	// SNMP_COMMUNITY_MAX_LEN bytes will be ignored.
	#define SNMP_READ_COMMUNITIES		{"public", "read", ""}
	#define END_OF_SNMP_READ_COMMUNITIES
	#define SNMP_WRITE_COMMUNITIES     	{"private", "write", "public"}
	#define END_OF_SNMP_WRITE_COMMUNITIES
	#define SNMP_STACK_USE_V2_TRAP
	
	// SNTP -- Définitions SNTP (Attention, il faut commenter celle qui sont dans SNTP.c)
	
	#define NTP_SERVER	"0.pool.ntp.org"
	
	// Defines how frequently to resynchronize the date/time (default: 10 minutes) 
	#define NTP_QUERY_INTERVAL		(60ull*60ull * TICK_SECOND) // 60 minutes

	// Defines how long to wait to retry an update after a failure.
	// Updates may take up to 6 seconds to fail, so this 15 second delay is actually only an 9-second retry.
	#define NTP_FAST_QUERY_INTERVAL	(15ull * TICK_SECOND)
	
	// Port for contacting NTP servers
	#define NTP_SERVER_PORT			(123ul)
	
	// Reference Epoch to use.  (default: 01-Jan-1970 00:00:00)
	#define NTP_EPOCH 				(86400ul * (365ul * 70ul + 17ul))
	
	// Defines how long to wait before assuming the query has failed
	#define NTP_REPLY_TIMEOUT		(6ul*TICK_SECOND)	
#endif

