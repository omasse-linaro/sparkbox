/*********************************************************************
 Header file for Helpers.c
 
 FileName:      Helpers.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18, PIC24, dsPIC, PIC32
 Compiler:      Microchip C18, C30, C32
 Company:       Microchip Technology, Inc.

 Software License Agreement

 Copyright (C) 2002-2011 Microchip Technology Inc.  All rights
 reserved.

 Microchip licenses to you the right to use, modify, copy, and
 distribute:
 (i)  the Software when embedded on a Microchip microcontroller or
      digital signal controller product ("Device") which is
      integrated into Licensee's product; or
 (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
		used in conjunction with a Microchip ethernet controller for
		the sole purpose of interfacing with the ethernet controller.

 You should refer to the license agreement accompanying this
 Software for additional information regarding your rights and
 obligations.

 THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.

 ********************************************************************
 File Description:
 
 Change History:
 
  Rev         Description
  ----------  -------------------------------------------------------
  1.0 - 5.31  Initial release
  5.36        Updated compile time check for ultoa();
 ********************************************************************/
#ifndef __HELPERS_H
#define __HELPERS_H


#if !defined(__18CXX) || defined(HI_TECH_C)
	char *strupr(char* s);
#endif



#if defined(DEBUG)
	#define DebugPrint(a)	{putrsUART(a);}
#else
	#define DebugPrint(a)
#endif

DWORD	LFSRSeedRand(DWORD dwSeed);
WORD	LFSRRand(void);
DWORD	GenerateRandomDWORD(void);
void 	uitoa(WORD Value, BYTE* Buffer);
void 	UnencodeURL(BYTE* URL);
WORD 	Base64Decode(BYTE* cSourceData, WORD wSourceLen, BYTE* cDestData, WORD wDestLen);
WORD	Base64Encode(BYTE* cSourceData, WORD wSourceLen, BYTE* cDestData, WORD wDestLen);
BOOL	StringToIPAddress(BYTE* str, IP_ADDR* IPAddress);
BYTE 	ReadStringUART(BYTE* Dest, BYTE BufferLen);
BYTE	hexatob(WORD_VAL AsciiChars);
BYTE	btohexa_high(BYTE b);
BYTE	btohexa_low(BYTE b);
signed char stricmppgm2ram(BYTE* a, ROM BYTE* b);
char * 	strnchr(const char *searchString, size_t count, char c);
size_t  strncpy_m(char* destStr, size_t destSize, int nStrings, ...);

#if defined(__18CXX)
	BOOL	ROMStringToIPAddress(ROM BYTE* str, IP_ADDR* IPAddress);
#else
	// Non-ROM variant for C30 and C32
	#define ROMStringToIPAddress(a,b)	StringToIPAddress((BYTE*)a,b)
#endif


WORD    swaps(WORD v);

#if defined(__C32__)
DWORD   __attribute__((nomips16)) swapl(DWORD v);
#else
DWORD   swapl(DWORD v);
#endif

WORD    CalcIPChecksum(BYTE* buffer, WORD len);


#if defined(__18CXX)
	DWORD leftRotateDWORD(DWORD val, BYTE bits);
#else
	// Rotations are more efficient in C30 and C32
	#define leftRotateDWORD(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#endif

void FormatNetBIOSName(BYTE Name[16]);


// Protocols understood by the ExtractURLFields() function.  IMPORTANT: If you 
// need to reorder these (change their constant values), you must also reorder 
// the constant arrays in ExtractURLFields().
typedef enum
{
	PROTOCOL_HTTP = 0u,
	PROTOCOL_HTTPS,
	PROTOCOL_MMS,
	PROTOCOL_RTSP
} PROTOCOLS;

BYTE ExtractURLFields(BYTE *vURL, PROTOCOLS *protocol, BYTE *vUsername, WORD *wUsernameLen, BYTE *vPassword, WORD *wPasswordLen, BYTE *vHostname, WORD *wHostnameLen, WORD *wPort, BYTE *vFilePath, WORD *wFilePathLen);
SHORT Replace(BYTE *vExpression, ROM BYTE *vFind, ROM BYTE *vReplacement, WORD wMaxLen, BOOL bSearchCaseInsensitive);

#endif
