#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-DEBUG_-_Sans_Bootloader.mk)" "nbproject/Makefile-local-DEBUG_-_Sans_Bootloader.mk"
include nbproject/Makefile-local-DEBUG_-_Sans_Bootloader.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=DEBUG_-_Sans_Bootloader
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../HTTP_Teleinfo.c ../HTTP_Reseau.c ../HTTP_Mynetmemo.c ../HTTP_Password.c ../HTTP_log.c ../HTTP_cmd.c ../HTTP_Parametres.c ../HTTP_Donnees.c ../HTTP_Index.c ../HTTP_ADTEK.c "../../Microchip/TCPIP Stack/Announce.c" "../../Microchip/TCPIP Stack/ARP.c" "../../Microchip/TCPIP Stack/Delay.c" "../../Microchip/TCPIP Stack/DHCP.c" "../../Microchip/TCPIP Stack/DHCPs.c" "../../Microchip/TCPIP Stack/DNS.c" "../../Microchip/TCPIP Stack/DynDNS.c" "../../Microchip/TCPIP Stack/FTP.c" "../../Microchip/TCPIP Stack/Hashes.c" "../../Microchip/TCPIP Stack/Helpers.c" "../../Microchip/TCPIP Stack/HTTP2.c" "../../Microchip/TCPIP Stack/ICMP.c" "../../Microchip/TCPIP Stack/IP.c" "../../Microchip/TCPIP Stack/MPFS2.c" "../../Microchip/TCPIP Stack/NBNS.c" "../../Microchip/TCPIP Stack/SMTP.c" "../../Microchip/TCPIP Stack/SNMP.c" "../../Microchip/TCPIP Stack/SNTP.c" "../../Microchip/TCPIP Stack/SPIEEPROM.c" "../../Microchip/TCPIP Stack/SPIFlash.c" "../../Microchip/TCPIP Stack/SPIRAM.c" "../../Microchip/TCPIP Stack/StackTsk.c" "../../Microchip/TCPIP Stack/TCP.c" "../../Microchip/TCPIP Stack/Telnet.c" "../../Microchip/TCPIP Stack/TFTPc.c" "../../Microchip/TCPIP Stack/Tick.c" "../../Microchip/TCPIP Stack/UART.c" "../../Microchip/TCPIP Stack/UDP.c" ../MPFSImg2.c "../../Microchip/TCPIP Stack/Random.c" "../../Microchip/TCPIP Stack/RSA.c" "../../Microchip/TCPIP Stack/SSL.c" "../../Microchip/TCPIP Stack/ARCFOUR.c" "../../Microchip/TCPIP Stack/BigInt.c" "../../Microchip/TCPIP Stack/BigInt_helper_C32.S" "../../Microchip/TCPIP Stack/AutoIP.c" "../../Microchip/TCPIP Stack/DNSs.c" "../../Microchip/TCPIP Stack/ENCX24J600.c" "../../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c" "../../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c" "../../Microchip/TCPIP Stack/ETHPIC32IntMac.c" ../rs232.c ../Mynetmemo.c ../Eeprom_i2c.c ../Temperature.c ../Teleinfo.c ../log.c ../SSLCert.c ../divers.c ../SST25VF016.c ../drv_spi.c ../mcp7941.c ../RTC.c ../0_SparkBox.c ../Lcd.c ../Analogique.c ../Evse.c ../i2c.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o ${OBJECTDIR}/_ext/1472/HTTP_Password.o ${OBJECTDIR}/_ext/1472/HTTP_log.o ${OBJECTDIR}/_ext/1472/HTTP_cmd.o ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o ${OBJECTDIR}/_ext/1472/HTTP_Index.o ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o ${OBJECTDIR}/_ext/1295770447/Announce.o ${OBJECTDIR}/_ext/1295770447/ARP.o ${OBJECTDIR}/_ext/1295770447/Delay.o ${OBJECTDIR}/_ext/1295770447/DHCP.o ${OBJECTDIR}/_ext/1295770447/DHCPs.o ${OBJECTDIR}/_ext/1295770447/DNS.o ${OBJECTDIR}/_ext/1295770447/DynDNS.o ${OBJECTDIR}/_ext/1295770447/FTP.o ${OBJECTDIR}/_ext/1295770447/Hashes.o ${OBJECTDIR}/_ext/1295770447/Helpers.o ${OBJECTDIR}/_ext/1295770447/HTTP2.o ${OBJECTDIR}/_ext/1295770447/ICMP.o ${OBJECTDIR}/_ext/1295770447/IP.o ${OBJECTDIR}/_ext/1295770447/MPFS2.o ${OBJECTDIR}/_ext/1295770447/NBNS.o ${OBJECTDIR}/_ext/1295770447/SMTP.o ${OBJECTDIR}/_ext/1295770447/SNMP.o ${OBJECTDIR}/_ext/1295770447/SNTP.o ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o ${OBJECTDIR}/_ext/1295770447/SPIFlash.o ${OBJECTDIR}/_ext/1295770447/SPIRAM.o ${OBJECTDIR}/_ext/1295770447/StackTsk.o ${OBJECTDIR}/_ext/1295770447/TCP.o ${OBJECTDIR}/_ext/1295770447/Telnet.o ${OBJECTDIR}/_ext/1295770447/TFTPc.o ${OBJECTDIR}/_ext/1295770447/Tick.o ${OBJECTDIR}/_ext/1295770447/UART.o ${OBJECTDIR}/_ext/1295770447/UDP.o ${OBJECTDIR}/_ext/1472/MPFSImg2.o ${OBJECTDIR}/_ext/1295770447/Random.o ${OBJECTDIR}/_ext/1295770447/RSA.o ${OBJECTDIR}/_ext/1295770447/SSL.o ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o ${OBJECTDIR}/_ext/1295770447/BigInt.o ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o ${OBJECTDIR}/_ext/1295770447/AutoIP.o ${OBJECTDIR}/_ext/1295770447/DNSs.o ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/1472/rs232.o ${OBJECTDIR}/_ext/1472/Mynetmemo.o ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o ${OBJECTDIR}/_ext/1472/Temperature.o ${OBJECTDIR}/_ext/1472/Teleinfo.o ${OBJECTDIR}/_ext/1472/log.o ${OBJECTDIR}/_ext/1472/SSLCert.o ${OBJECTDIR}/_ext/1472/divers.o ${OBJECTDIR}/_ext/1472/SST25VF016.o ${OBJECTDIR}/_ext/1472/drv_spi.o ${OBJECTDIR}/_ext/1472/mcp7941.o ${OBJECTDIR}/_ext/1472/RTC.o ${OBJECTDIR}/_ext/1472/0_SparkBox.o ${OBJECTDIR}/_ext/1472/Lcd.o ${OBJECTDIR}/_ext/1472/Analogique.o ${OBJECTDIR}/_ext/1472/Evse.o ${OBJECTDIR}/_ext/1472/i2c.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d ${OBJECTDIR}/_ext/1472/HTTP_Password.o.d ${OBJECTDIR}/_ext/1472/HTTP_log.o.d ${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d ${OBJECTDIR}/_ext/1472/HTTP_Index.o.d ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d ${OBJECTDIR}/_ext/1295770447/Announce.o.d ${OBJECTDIR}/_ext/1295770447/ARP.o.d ${OBJECTDIR}/_ext/1295770447/Delay.o.d ${OBJECTDIR}/_ext/1295770447/DHCP.o.d ${OBJECTDIR}/_ext/1295770447/DHCPs.o.d ${OBJECTDIR}/_ext/1295770447/DNS.o.d ${OBJECTDIR}/_ext/1295770447/DynDNS.o.d ${OBJECTDIR}/_ext/1295770447/FTP.o.d ${OBJECTDIR}/_ext/1295770447/Hashes.o.d ${OBJECTDIR}/_ext/1295770447/Helpers.o.d ${OBJECTDIR}/_ext/1295770447/HTTP2.o.d ${OBJECTDIR}/_ext/1295770447/ICMP.o.d ${OBJECTDIR}/_ext/1295770447/IP.o.d ${OBJECTDIR}/_ext/1295770447/MPFS2.o.d ${OBJECTDIR}/_ext/1295770447/NBNS.o.d ${OBJECTDIR}/_ext/1295770447/SMTP.o.d ${OBJECTDIR}/_ext/1295770447/SNMP.o.d ${OBJECTDIR}/_ext/1295770447/SNTP.o.d ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d ${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d ${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d ${OBJECTDIR}/_ext/1295770447/StackTsk.o.d ${OBJECTDIR}/_ext/1295770447/TCP.o.d ${OBJECTDIR}/_ext/1295770447/Telnet.o.d ${OBJECTDIR}/_ext/1295770447/TFTPc.o.d ${OBJECTDIR}/_ext/1295770447/Tick.o.d ${OBJECTDIR}/_ext/1295770447/UART.o.d ${OBJECTDIR}/_ext/1295770447/UDP.o.d ${OBJECTDIR}/_ext/1472/MPFSImg2.o.d ${OBJECTDIR}/_ext/1295770447/Random.o.d ${OBJECTDIR}/_ext/1295770447/RSA.o.d ${OBJECTDIR}/_ext/1295770447/SSL.o.d ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d ${OBJECTDIR}/_ext/1295770447/BigInt.o.d ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d ${OBJECTDIR}/_ext/1295770447/AutoIP.o.d ${OBJECTDIR}/_ext/1295770447/DNSs.o.d ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d ${OBJECTDIR}/_ext/1472/rs232.o.d ${OBJECTDIR}/_ext/1472/Mynetmemo.o.d ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d ${OBJECTDIR}/_ext/1472/Temperature.o.d ${OBJECTDIR}/_ext/1472/Teleinfo.o.d ${OBJECTDIR}/_ext/1472/log.o.d ${OBJECTDIR}/_ext/1472/SSLCert.o.d ${OBJECTDIR}/_ext/1472/divers.o.d ${OBJECTDIR}/_ext/1472/SST25VF016.o.d ${OBJECTDIR}/_ext/1472/drv_spi.o.d ${OBJECTDIR}/_ext/1472/mcp7941.o.d ${OBJECTDIR}/_ext/1472/RTC.o.d ${OBJECTDIR}/_ext/1472/0_SparkBox.o.d ${OBJECTDIR}/_ext/1472/Lcd.o.d ${OBJECTDIR}/_ext/1472/Analogique.o.d ${OBJECTDIR}/_ext/1472/Evse.o.d ${OBJECTDIR}/_ext/1472/i2c.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o ${OBJECTDIR}/_ext/1472/HTTP_Password.o ${OBJECTDIR}/_ext/1472/HTTP_log.o ${OBJECTDIR}/_ext/1472/HTTP_cmd.o ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o ${OBJECTDIR}/_ext/1472/HTTP_Index.o ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o ${OBJECTDIR}/_ext/1295770447/Announce.o ${OBJECTDIR}/_ext/1295770447/ARP.o ${OBJECTDIR}/_ext/1295770447/Delay.o ${OBJECTDIR}/_ext/1295770447/DHCP.o ${OBJECTDIR}/_ext/1295770447/DHCPs.o ${OBJECTDIR}/_ext/1295770447/DNS.o ${OBJECTDIR}/_ext/1295770447/DynDNS.o ${OBJECTDIR}/_ext/1295770447/FTP.o ${OBJECTDIR}/_ext/1295770447/Hashes.o ${OBJECTDIR}/_ext/1295770447/Helpers.o ${OBJECTDIR}/_ext/1295770447/HTTP2.o ${OBJECTDIR}/_ext/1295770447/ICMP.o ${OBJECTDIR}/_ext/1295770447/IP.o ${OBJECTDIR}/_ext/1295770447/MPFS2.o ${OBJECTDIR}/_ext/1295770447/NBNS.o ${OBJECTDIR}/_ext/1295770447/SMTP.o ${OBJECTDIR}/_ext/1295770447/SNMP.o ${OBJECTDIR}/_ext/1295770447/SNTP.o ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o ${OBJECTDIR}/_ext/1295770447/SPIFlash.o ${OBJECTDIR}/_ext/1295770447/SPIRAM.o ${OBJECTDIR}/_ext/1295770447/StackTsk.o ${OBJECTDIR}/_ext/1295770447/TCP.o ${OBJECTDIR}/_ext/1295770447/Telnet.o ${OBJECTDIR}/_ext/1295770447/TFTPc.o ${OBJECTDIR}/_ext/1295770447/Tick.o ${OBJECTDIR}/_ext/1295770447/UART.o ${OBJECTDIR}/_ext/1295770447/UDP.o ${OBJECTDIR}/_ext/1472/MPFSImg2.o ${OBJECTDIR}/_ext/1295770447/Random.o ${OBJECTDIR}/_ext/1295770447/RSA.o ${OBJECTDIR}/_ext/1295770447/SSL.o ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o ${OBJECTDIR}/_ext/1295770447/BigInt.o ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o ${OBJECTDIR}/_ext/1295770447/AutoIP.o ${OBJECTDIR}/_ext/1295770447/DNSs.o ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/1472/rs232.o ${OBJECTDIR}/_ext/1472/Mynetmemo.o ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o ${OBJECTDIR}/_ext/1472/Temperature.o ${OBJECTDIR}/_ext/1472/Teleinfo.o ${OBJECTDIR}/_ext/1472/log.o ${OBJECTDIR}/_ext/1472/SSLCert.o ${OBJECTDIR}/_ext/1472/divers.o ${OBJECTDIR}/_ext/1472/SST25VF016.o ${OBJECTDIR}/_ext/1472/drv_spi.o ${OBJECTDIR}/_ext/1472/mcp7941.o ${OBJECTDIR}/_ext/1472/RTC.o ${OBJECTDIR}/_ext/1472/0_SparkBox.o ${OBJECTDIR}/_ext/1472/Lcd.o ${OBJECTDIR}/_ext/1472/Analogique.o ${OBJECTDIR}/_ext/1472/Evse.o ${OBJECTDIR}/_ext/1472/i2c.o

# Source Files
SOURCEFILES=../HTTP_Teleinfo.c ../HTTP_Reseau.c ../HTTP_Mynetmemo.c ../HTTP_Password.c ../HTTP_log.c ../HTTP_cmd.c ../HTTP_Parametres.c ../HTTP_Donnees.c ../HTTP_Index.c ../HTTP_ADTEK.c ../../Microchip/TCPIP Stack/Announce.c ../../Microchip/TCPIP Stack/ARP.c ../../Microchip/TCPIP Stack/Delay.c ../../Microchip/TCPIP Stack/DHCP.c ../../Microchip/TCPIP Stack/DHCPs.c ../../Microchip/TCPIP Stack/DNS.c ../../Microchip/TCPIP Stack/DynDNS.c ../../Microchip/TCPIP Stack/FTP.c ../../Microchip/TCPIP Stack/Hashes.c ../../Microchip/TCPIP Stack/Helpers.c ../../Microchip/TCPIP Stack/HTTP2.c ../../Microchip/TCPIP Stack/ICMP.c ../../Microchip/TCPIP Stack/IP.c ../../Microchip/TCPIP Stack/MPFS2.c ../../Microchip/TCPIP Stack/NBNS.c ../../Microchip/TCPIP Stack/SMTP.c ../../Microchip/TCPIP Stack/SNMP.c ../../Microchip/TCPIP Stack/SNTP.c ../../Microchip/TCPIP Stack/SPIEEPROM.c ../../Microchip/TCPIP Stack/SPIFlash.c ../../Microchip/TCPIP Stack/SPIRAM.c ../../Microchip/TCPIP Stack/StackTsk.c ../../Microchip/TCPIP Stack/TCP.c ../../Microchip/TCPIP Stack/Telnet.c ../../Microchip/TCPIP Stack/TFTPc.c ../../Microchip/TCPIP Stack/Tick.c ../../Microchip/TCPIP Stack/UART.c ../../Microchip/TCPIP Stack/UDP.c ../MPFSImg2.c ../../Microchip/TCPIP Stack/Random.c ../../Microchip/TCPIP Stack/RSA.c ../../Microchip/TCPIP Stack/SSL.c ../../Microchip/TCPIP Stack/ARCFOUR.c ../../Microchip/TCPIP Stack/BigInt.c ../../Microchip/TCPIP Stack/BigInt_helper_C32.S ../../Microchip/TCPIP Stack/AutoIP.c ../../Microchip/TCPIP Stack/DNSs.c ../../Microchip/TCPIP Stack/ENCX24J600.c ../../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c ../../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c ../../Microchip/TCPIP Stack/ETHPIC32IntMac.c ../rs232.c ../Mynetmemo.c ../Eeprom_i2c.c ../Temperature.c ../Teleinfo.c ../log.c ../SSLCert.c ../divers.c ../SST25VF016.c ../drv_spi.c ../mcp7941.c ../RTC.c ../0_SparkBox.c ../Lcd.c ../Analogique.c ../Evse.c ../i2c.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-DEBUG_-_Sans_Bootloader.mk dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX695F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o: ../../Microchip/TCPIP\ Stack/BigInt_helper_C32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.ok ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d" "${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d"  -o ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o "../../Microchip/TCPIP Stack/BigInt_helper_C32.S"  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1 -I".." -I"." -gdwarf-2
	
else
${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o: ../../Microchip/TCPIP\ Stack/BigInt_helper_C32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.ok ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d" "${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.d"  -o ${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o "../../Microchip/TCPIP Stack/BigInt_helper_C32.S"  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1295770447/BigInt_helper_C32.o.asm.d" -I".." -I"." -gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o: ../HTTP_Teleinfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o ../HTTP_Teleinfo.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Reseau.o: ../HTTP_Reseau.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o ../HTTP_Reseau.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o: ../HTTP_Mynetmemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o ../HTTP_Mynetmemo.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Password.o: ../HTTP_Password.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Password.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Password.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Password.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Password.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Password.o ../HTTP_Password.c   
	
${OBJECTDIR}/_ext/1472/HTTP_log.o: ../HTTP_log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_log.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_log.o ../HTTP_log.c   
	
${OBJECTDIR}/_ext/1472/HTTP_cmd.o: ../HTTP_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_cmd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_cmd.o ../HTTP_cmd.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Parametres.o: ../HTTP_Parametres.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o ../HTTP_Parametres.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Donnees.o: ../HTTP_Donnees.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o ../HTTP_Donnees.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Index.o: ../HTTP_Index.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Index.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Index.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Index.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Index.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Index.o ../HTTP_Index.c   
	
${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o: ../HTTP_ADTEK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o ../HTTP_ADTEK.c   
	
${OBJECTDIR}/_ext/1295770447/Announce.o: ../../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Announce.o.d" -o ${OBJECTDIR}/_ext/1295770447/Announce.o "../../Microchip/TCPIP Stack/Announce.c"   
	
${OBJECTDIR}/_ext/1295770447/ARP.o: ../../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ARP.o.d" -o ${OBJECTDIR}/_ext/1295770447/ARP.o "../../Microchip/TCPIP Stack/ARP.c"   
	
${OBJECTDIR}/_ext/1295770447/Delay.o: ../../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Delay.o.d" -o ${OBJECTDIR}/_ext/1295770447/Delay.o "../../Microchip/TCPIP Stack/Delay.c"   
	
${OBJECTDIR}/_ext/1295770447/DHCP.o: ../../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DHCP.o.d" -o ${OBJECTDIR}/_ext/1295770447/DHCP.o "../../Microchip/TCPIP Stack/DHCP.c"   
	
${OBJECTDIR}/_ext/1295770447/DHCPs.o: ../../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DHCPs.o.d" -o ${OBJECTDIR}/_ext/1295770447/DHCPs.o "../../Microchip/TCPIP Stack/DHCPs.c"   
	
${OBJECTDIR}/_ext/1295770447/DNS.o: ../../Microchip/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DNS.o.d" -o ${OBJECTDIR}/_ext/1295770447/DNS.o "../../Microchip/TCPIP Stack/DNS.c"   
	
${OBJECTDIR}/_ext/1295770447/DynDNS.o: ../../Microchip/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DynDNS.o.d" -o ${OBJECTDIR}/_ext/1295770447/DynDNS.o "../../Microchip/TCPIP Stack/DynDNS.c"   
	
${OBJECTDIR}/_ext/1295770447/FTP.o: ../../Microchip/TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/FTP.o.d" -o ${OBJECTDIR}/_ext/1295770447/FTP.o "../../Microchip/TCPIP Stack/FTP.c"   
	
${OBJECTDIR}/_ext/1295770447/Hashes.o: ../../Microchip/TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Hashes.o.d" -o ${OBJECTDIR}/_ext/1295770447/Hashes.o "../../Microchip/TCPIP Stack/Hashes.c"   
	
${OBJECTDIR}/_ext/1295770447/Helpers.o: ../../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Helpers.o.d" -o ${OBJECTDIR}/_ext/1295770447/Helpers.o "../../Microchip/TCPIP Stack/Helpers.c"   
	
${OBJECTDIR}/_ext/1295770447/HTTP2.o: ../../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/HTTP2.o.d" -o ${OBJECTDIR}/_ext/1295770447/HTTP2.o "../../Microchip/TCPIP Stack/HTTP2.c"   
	
${OBJECTDIR}/_ext/1295770447/ICMP.o: ../../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ICMP.o.d" -o ${OBJECTDIR}/_ext/1295770447/ICMP.o "../../Microchip/TCPIP Stack/ICMP.c"   
	
${OBJECTDIR}/_ext/1295770447/IP.o: ../../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/IP.o.d" -o ${OBJECTDIR}/_ext/1295770447/IP.o "../../Microchip/TCPIP Stack/IP.c"   
	
${OBJECTDIR}/_ext/1295770447/MPFS2.o: ../../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/MPFS2.o.d" -o ${OBJECTDIR}/_ext/1295770447/MPFS2.o "../../Microchip/TCPIP Stack/MPFS2.c"   
	
${OBJECTDIR}/_ext/1295770447/NBNS.o: ../../Microchip/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/NBNS.o.d" -o ${OBJECTDIR}/_ext/1295770447/NBNS.o "../../Microchip/TCPIP Stack/NBNS.c"   
	
${OBJECTDIR}/_ext/1295770447/SMTP.o: ../../Microchip/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SMTP.o.d" -o ${OBJECTDIR}/_ext/1295770447/SMTP.o "../../Microchip/TCPIP Stack/SMTP.c"   
	
${OBJECTDIR}/_ext/1295770447/SNMP.o: ../../Microchip/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SNMP.o.d" -o ${OBJECTDIR}/_ext/1295770447/SNMP.o "../../Microchip/TCPIP Stack/SNMP.c"   
	
${OBJECTDIR}/_ext/1295770447/SNTP.o: ../../Microchip/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SNTP.o.d" -o ${OBJECTDIR}/_ext/1295770447/SNTP.o "../../Microchip/TCPIP Stack/SNTP.c"   
	
${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o: ../../Microchip/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d" -o ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o "../../Microchip/TCPIP Stack/SPIEEPROM.c"   
	
${OBJECTDIR}/_ext/1295770447/SPIFlash.o: ../../Microchip/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d" -o ${OBJECTDIR}/_ext/1295770447/SPIFlash.o "../../Microchip/TCPIP Stack/SPIFlash.c"   
	
${OBJECTDIR}/_ext/1295770447/SPIRAM.o: ../../Microchip/TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d" -o ${OBJECTDIR}/_ext/1295770447/SPIRAM.o "../../Microchip/TCPIP Stack/SPIRAM.c"   
	
${OBJECTDIR}/_ext/1295770447/StackTsk.o: ../../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/StackTsk.o.d" -o ${OBJECTDIR}/_ext/1295770447/StackTsk.o "../../Microchip/TCPIP Stack/StackTsk.c"   
	
${OBJECTDIR}/_ext/1295770447/TCP.o: ../../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/TCP.o.d" -o ${OBJECTDIR}/_ext/1295770447/TCP.o "../../Microchip/TCPIP Stack/TCP.c"   
	
${OBJECTDIR}/_ext/1295770447/Telnet.o: ../../Microchip/TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Telnet.o.d" -o ${OBJECTDIR}/_ext/1295770447/Telnet.o "../../Microchip/TCPIP Stack/Telnet.c"   
	
${OBJECTDIR}/_ext/1295770447/TFTPc.o: ../../Microchip/TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/TFTPc.o.d" -o ${OBJECTDIR}/_ext/1295770447/TFTPc.o "../../Microchip/TCPIP Stack/TFTPc.c"   
	
${OBJECTDIR}/_ext/1295770447/Tick.o: ../../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Tick.o.d" -o ${OBJECTDIR}/_ext/1295770447/Tick.o "../../Microchip/TCPIP Stack/Tick.c"   
	
${OBJECTDIR}/_ext/1295770447/UART.o: ../../Microchip/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/UART.o.d" -o ${OBJECTDIR}/_ext/1295770447/UART.o "../../Microchip/TCPIP Stack/UART.c"   
	
${OBJECTDIR}/_ext/1295770447/UDP.o: ../../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/UDP.o.d" -o ${OBJECTDIR}/_ext/1295770447/UDP.o "../../Microchip/TCPIP Stack/UDP.c"   
	
${OBJECTDIR}/_ext/1472/MPFSImg2.o: ../MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MPFSImg2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/MPFSImg2.o.d" -o ${OBJECTDIR}/_ext/1472/MPFSImg2.o ../MPFSImg2.c   
	
${OBJECTDIR}/_ext/1295770447/Random.o: ../../Microchip/TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Random.o.d" -o ${OBJECTDIR}/_ext/1295770447/Random.o "../../Microchip/TCPIP Stack/Random.c"   
	
${OBJECTDIR}/_ext/1295770447/RSA.o: ../../Microchip/TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/RSA.o.d" -o ${OBJECTDIR}/_ext/1295770447/RSA.o "../../Microchip/TCPIP Stack/RSA.c"   
	
${OBJECTDIR}/_ext/1295770447/SSL.o: ../../Microchip/TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SSL.o.d" -o ${OBJECTDIR}/_ext/1295770447/SSL.o "../../Microchip/TCPIP Stack/SSL.c"   
	
${OBJECTDIR}/_ext/1295770447/ARCFOUR.o: ../../Microchip/TCPIP\ Stack/ARCFOUR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d" -o ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o "../../Microchip/TCPIP Stack/ARCFOUR.c"   
	
${OBJECTDIR}/_ext/1295770447/BigInt.o: ../../Microchip/TCPIP\ Stack/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/BigInt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/BigInt.o.d" -o ${OBJECTDIR}/_ext/1295770447/BigInt.o "../../Microchip/TCPIP Stack/BigInt.c"   
	
${OBJECTDIR}/_ext/1295770447/AutoIP.o: ../../Microchip/TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/AutoIP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/AutoIP.o.d" -o ${OBJECTDIR}/_ext/1295770447/AutoIP.o "../../Microchip/TCPIP Stack/AutoIP.c"   
	
${OBJECTDIR}/_ext/1295770447/DNSs.o: ../../Microchip/TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNSs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNSs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DNSs.o.d" -o ${OBJECTDIR}/_ext/1295770447/DNSs.o "../../Microchip/TCPIP Stack/DNSs.c"   
	
${OBJECTDIR}/_ext/1295770447/ENCX24J600.o: ../../Microchip/TCPIP\ Stack/ENCX24J600.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d" -o ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o "../../Microchip/TCPIP Stack/ENCX24J600.c"   
	
${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o: ../../Microchip/TCPIP\ Stack/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o "../../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c"   
	
${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o: ../../Microchip/TCPIP\ Stack/ETHPIC32ExtPhyDP83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d" -o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o "../../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c"   
	
${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o: ../../Microchip/TCPIP\ Stack/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o "../../Microchip/TCPIP Stack/ETHPIC32IntMac.c"   
	
${OBJECTDIR}/_ext/1472/rs232.o: ../rs232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/rs232.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rs232.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rs232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/rs232.o.d" -o ${OBJECTDIR}/_ext/1472/rs232.o ../rs232.c   
	
${OBJECTDIR}/_ext/1472/Mynetmemo.o: ../Mynetmemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Mynetmemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Mynetmemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Mynetmemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Mynetmemo.o.d" -o ${OBJECTDIR}/_ext/1472/Mynetmemo.o ../Mynetmemo.c   
	
${OBJECTDIR}/_ext/1472/Eeprom_i2c.o: ../Eeprom_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d" -o ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o ../Eeprom_i2c.c   
	
${OBJECTDIR}/_ext/1472/Temperature.o: ../Temperature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Temperature.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Temperature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Temperature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Temperature.o.d" -o ${OBJECTDIR}/_ext/1472/Temperature.o ../Temperature.c   
	
${OBJECTDIR}/_ext/1472/Teleinfo.o: ../Teleinfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Teleinfo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Teleinfo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Teleinfo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Teleinfo.o.d" -o ${OBJECTDIR}/_ext/1472/Teleinfo.o ../Teleinfo.c   
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c   
	
${OBJECTDIR}/_ext/1472/SSLCert.o: ../SSLCert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SSLCert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SSLCert.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SSLCert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/SSLCert.o.d" -o ${OBJECTDIR}/_ext/1472/SSLCert.o ../SSLCert.c   
	
${OBJECTDIR}/_ext/1472/divers.o: ../divers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/divers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/divers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/divers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/divers.o.d" -o ${OBJECTDIR}/_ext/1472/divers.o ../divers.c   
	
${OBJECTDIR}/_ext/1472/SST25VF016.o: ../SST25VF016.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SST25VF016.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SST25VF016.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SST25VF016.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/SST25VF016.o.d" -o ${OBJECTDIR}/_ext/1472/SST25VF016.o ../SST25VF016.c   
	
${OBJECTDIR}/_ext/1472/drv_spi.o: ../drv_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/drv_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/drv_spi.o.d" -o ${OBJECTDIR}/_ext/1472/drv_spi.o ../drv_spi.c   
	
${OBJECTDIR}/_ext/1472/mcp7941.o: ../mcp7941.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/mcp7941.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mcp7941.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/mcp7941.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/mcp7941.o.d" -o ${OBJECTDIR}/_ext/1472/mcp7941.o ../mcp7941.c   
	
${OBJECTDIR}/_ext/1472/RTC.o: ../RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RTC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RTC.o.d" -o ${OBJECTDIR}/_ext/1472/RTC.o ../RTC.c   
	
${OBJECTDIR}/_ext/1472/0_SparkBox.o: ../0_SparkBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/0_SparkBox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/0_SparkBox.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/0_SparkBox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/0_SparkBox.o.d" -o ${OBJECTDIR}/_ext/1472/0_SparkBox.o ../0_SparkBox.c   
	
${OBJECTDIR}/_ext/1472/Lcd.o: ../Lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Lcd.o.d" -o ${OBJECTDIR}/_ext/1472/Lcd.o ../Lcd.c   
	
${OBJECTDIR}/_ext/1472/Analogique.o: ../Analogique.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Analogique.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Analogique.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Analogique.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Analogique.o.d" -o ${OBJECTDIR}/_ext/1472/Analogique.o ../Analogique.c   
	
${OBJECTDIR}/_ext/1472/Evse.o: ../Evse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Evse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Evse.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Evse.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Evse.o.d" -o ${OBJECTDIR}/_ext/1472/Evse.o ../Evse.c   
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c   
	
else
${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o: ../HTTP_Teleinfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Teleinfo.o ../HTTP_Teleinfo.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Reseau.o: ../HTTP_Reseau.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Reseau.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Reseau.o ../HTTP_Reseau.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o: ../HTTP_Mynetmemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Mynetmemo.o ../HTTP_Mynetmemo.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Password.o: ../HTTP_Password.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Password.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Password.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Password.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Password.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Password.o ../HTTP_Password.c   
	
${OBJECTDIR}/_ext/1472/HTTP_log.o: ../HTTP_log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_log.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_log.o ../HTTP_log.c   
	
${OBJECTDIR}/_ext/1472/HTTP_cmd.o: ../HTTP_cmd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_cmd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_cmd.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_cmd.o ../HTTP_cmd.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Parametres.o: ../HTTP_Parametres.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Parametres.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Parametres.o ../HTTP_Parametres.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Donnees.o: ../HTTP_Donnees.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Donnees.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Donnees.o ../HTTP_Donnees.c   
	
${OBJECTDIR}/_ext/1472/HTTP_Index.o: ../HTTP_Index.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Index.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_Index.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_Index.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_Index.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_Index.o ../HTTP_Index.c   
	
${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o: ../HTTP_ADTEK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o.d" -o ${OBJECTDIR}/_ext/1472/HTTP_ADTEK.o ../HTTP_ADTEK.c   
	
${OBJECTDIR}/_ext/1295770447/Announce.o: ../../Microchip/TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Announce.o.d" -o ${OBJECTDIR}/_ext/1295770447/Announce.o "../../Microchip/TCPIP Stack/Announce.c"   
	
${OBJECTDIR}/_ext/1295770447/ARP.o: ../../Microchip/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ARP.o.d" -o ${OBJECTDIR}/_ext/1295770447/ARP.o "../../Microchip/TCPIP Stack/ARP.c"   
	
${OBJECTDIR}/_ext/1295770447/Delay.o: ../../Microchip/TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Delay.o.d" -o ${OBJECTDIR}/_ext/1295770447/Delay.o "../../Microchip/TCPIP Stack/Delay.c"   
	
${OBJECTDIR}/_ext/1295770447/DHCP.o: ../../Microchip/TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DHCP.o.d" -o ${OBJECTDIR}/_ext/1295770447/DHCP.o "../../Microchip/TCPIP Stack/DHCP.c"   
	
${OBJECTDIR}/_ext/1295770447/DHCPs.o: ../../Microchip/TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DHCPs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DHCPs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DHCPs.o.d" -o ${OBJECTDIR}/_ext/1295770447/DHCPs.o "../../Microchip/TCPIP Stack/DHCPs.c"   
	
${OBJECTDIR}/_ext/1295770447/DNS.o: ../../Microchip/TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DNS.o.d" -o ${OBJECTDIR}/_ext/1295770447/DNS.o "../../Microchip/TCPIP Stack/DNS.c"   
	
${OBJECTDIR}/_ext/1295770447/DynDNS.o: ../../Microchip/TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DynDNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DynDNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DynDNS.o.d" -o ${OBJECTDIR}/_ext/1295770447/DynDNS.o "../../Microchip/TCPIP Stack/DynDNS.c"   
	
${OBJECTDIR}/_ext/1295770447/FTP.o: ../../Microchip/TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/FTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/FTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/FTP.o.d" -o ${OBJECTDIR}/_ext/1295770447/FTP.o "../../Microchip/TCPIP Stack/FTP.c"   
	
${OBJECTDIR}/_ext/1295770447/Hashes.o: ../../Microchip/TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Hashes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Hashes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Hashes.o.d" -o ${OBJECTDIR}/_ext/1295770447/Hashes.o "../../Microchip/TCPIP Stack/Hashes.c"   
	
${OBJECTDIR}/_ext/1295770447/Helpers.o: ../../Microchip/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Helpers.o.d" -o ${OBJECTDIR}/_ext/1295770447/Helpers.o "../../Microchip/TCPIP Stack/Helpers.c"   
	
${OBJECTDIR}/_ext/1295770447/HTTP2.o: ../../Microchip/TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/HTTP2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/HTTP2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/HTTP2.o.d" -o ${OBJECTDIR}/_ext/1295770447/HTTP2.o "../../Microchip/TCPIP Stack/HTTP2.c"   
	
${OBJECTDIR}/_ext/1295770447/ICMP.o: ../../Microchip/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ICMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ICMP.o.d" -o ${OBJECTDIR}/_ext/1295770447/ICMP.o "../../Microchip/TCPIP Stack/ICMP.c"   
	
${OBJECTDIR}/_ext/1295770447/IP.o: ../../Microchip/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/IP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/IP.o.d" -o ${OBJECTDIR}/_ext/1295770447/IP.o "../../Microchip/TCPIP Stack/IP.c"   
	
${OBJECTDIR}/_ext/1295770447/MPFS2.o: ../../Microchip/TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/MPFS2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/MPFS2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/MPFS2.o.d" -o ${OBJECTDIR}/_ext/1295770447/MPFS2.o "../../Microchip/TCPIP Stack/MPFS2.c"   
	
${OBJECTDIR}/_ext/1295770447/NBNS.o: ../../Microchip/TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/NBNS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/NBNS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/NBNS.o.d" -o ${OBJECTDIR}/_ext/1295770447/NBNS.o "../../Microchip/TCPIP Stack/NBNS.c"   
	
${OBJECTDIR}/_ext/1295770447/SMTP.o: ../../Microchip/TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SMTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SMTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SMTP.o.d" -o ${OBJECTDIR}/_ext/1295770447/SMTP.o "../../Microchip/TCPIP Stack/SMTP.c"   
	
${OBJECTDIR}/_ext/1295770447/SNMP.o: ../../Microchip/TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNMP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SNMP.o.d" -o ${OBJECTDIR}/_ext/1295770447/SNMP.o "../../Microchip/TCPIP Stack/SNMP.c"   
	
${OBJECTDIR}/_ext/1295770447/SNTP.o: ../../Microchip/TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SNTP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SNTP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SNTP.o.d" -o ${OBJECTDIR}/_ext/1295770447/SNTP.o "../../Microchip/TCPIP Stack/SNTP.c"   
	
${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o: ../../Microchip/TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o.d" -o ${OBJECTDIR}/_ext/1295770447/SPIEEPROM.o "../../Microchip/TCPIP Stack/SPIEEPROM.c"   
	
${OBJECTDIR}/_ext/1295770447/SPIFlash.o: ../../Microchip/TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SPIFlash.o.d" -o ${OBJECTDIR}/_ext/1295770447/SPIFlash.o "../../Microchip/TCPIP Stack/SPIFlash.c"   
	
${OBJECTDIR}/_ext/1295770447/SPIRAM.o: ../../Microchip/TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SPIRAM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SPIRAM.o.d" -o ${OBJECTDIR}/_ext/1295770447/SPIRAM.o "../../Microchip/TCPIP Stack/SPIRAM.c"   
	
${OBJECTDIR}/_ext/1295770447/StackTsk.o: ../../Microchip/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/StackTsk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/StackTsk.o.d" -o ${OBJECTDIR}/_ext/1295770447/StackTsk.o "../../Microchip/TCPIP Stack/StackTsk.c"   
	
${OBJECTDIR}/_ext/1295770447/TCP.o: ../../Microchip/TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TCP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TCP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/TCP.o.d" -o ${OBJECTDIR}/_ext/1295770447/TCP.o "../../Microchip/TCPIP Stack/TCP.c"   
	
${OBJECTDIR}/_ext/1295770447/Telnet.o: ../../Microchip/TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Telnet.o.d" -o ${OBJECTDIR}/_ext/1295770447/Telnet.o "../../Microchip/TCPIP Stack/Telnet.c"   
	
${OBJECTDIR}/_ext/1295770447/TFTPc.o: ../../Microchip/TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/TFTPc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/TFTPc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/TFTPc.o.d" -o ${OBJECTDIR}/_ext/1295770447/TFTPc.o "../../Microchip/TCPIP Stack/TFTPc.c"   
	
${OBJECTDIR}/_ext/1295770447/Tick.o: ../../Microchip/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Tick.o.d" -o ${OBJECTDIR}/_ext/1295770447/Tick.o "../../Microchip/TCPIP Stack/Tick.c"   
	
${OBJECTDIR}/_ext/1295770447/UART.o: ../../Microchip/TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/UART.o.d" -o ${OBJECTDIR}/_ext/1295770447/UART.o "../../Microchip/TCPIP Stack/UART.c"   
	
${OBJECTDIR}/_ext/1295770447/UDP.o: ../../Microchip/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/UDP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/UDP.o.d" -o ${OBJECTDIR}/_ext/1295770447/UDP.o "../../Microchip/TCPIP Stack/UDP.c"   
	
${OBJECTDIR}/_ext/1472/MPFSImg2.o: ../MPFSImg2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/MPFSImg2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/MPFSImg2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/MPFSImg2.o.d" -o ${OBJECTDIR}/_ext/1472/MPFSImg2.o ../MPFSImg2.c   
	
${OBJECTDIR}/_ext/1295770447/Random.o: ../../Microchip/TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/Random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/Random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/Random.o.d" -o ${OBJECTDIR}/_ext/1295770447/Random.o "../../Microchip/TCPIP Stack/Random.c"   
	
${OBJECTDIR}/_ext/1295770447/RSA.o: ../../Microchip/TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/RSA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/RSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/RSA.o.d" -o ${OBJECTDIR}/_ext/1295770447/RSA.o "../../Microchip/TCPIP Stack/RSA.c"   
	
${OBJECTDIR}/_ext/1295770447/SSL.o: ../../Microchip/TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/SSL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/SSL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/SSL.o.d" -o ${OBJECTDIR}/_ext/1295770447/SSL.o "../../Microchip/TCPIP Stack/SSL.c"   
	
${OBJECTDIR}/_ext/1295770447/ARCFOUR.o: ../../Microchip/TCPIP\ Stack/ARCFOUR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ARCFOUR.o.d" -o ${OBJECTDIR}/_ext/1295770447/ARCFOUR.o "../../Microchip/TCPIP Stack/ARCFOUR.c"   
	
${OBJECTDIR}/_ext/1295770447/BigInt.o: ../../Microchip/TCPIP\ Stack/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/BigInt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/BigInt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/BigInt.o.d" -o ${OBJECTDIR}/_ext/1295770447/BigInt.o "../../Microchip/TCPIP Stack/BigInt.c"   
	
${OBJECTDIR}/_ext/1295770447/AutoIP.o: ../../Microchip/TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/AutoIP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/AutoIP.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/AutoIP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/AutoIP.o.d" -o ${OBJECTDIR}/_ext/1295770447/AutoIP.o "../../Microchip/TCPIP Stack/AutoIP.c"   
	
${OBJECTDIR}/_ext/1295770447/DNSs.o: ../../Microchip/TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNSs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/DNSs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/DNSs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/DNSs.o.d" -o ${OBJECTDIR}/_ext/1295770447/DNSs.o "../../Microchip/TCPIP Stack/DNSs.c"   
	
${OBJECTDIR}/_ext/1295770447/ENCX24J600.o: ../../Microchip/TCPIP\ Stack/ENCX24J600.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ENCX24J600.o.d" -o ${OBJECTDIR}/_ext/1295770447/ENCX24J600.o "../../Microchip/TCPIP Stack/ENCX24J600.c"   
	
${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o: ../../Microchip/TCPIP\ Stack/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhy.o "../../Microchip/TCPIP Stack/ETHPIC32ExtPhy.c"   
	
${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o: ../../Microchip/TCPIP\ Stack/ETHPIC32ExtPhyDP83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o.d" -o ${OBJECTDIR}/_ext/1295770447/ETHPIC32ExtPhyDP83848.o "../../Microchip/TCPIP Stack/ETHPIC32ExtPhyDP83848.c"   
	
${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o: ../../Microchip/TCPIP\ Stack/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1295770447 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/1295770447/ETHPIC32IntMac.o "../../Microchip/TCPIP Stack/ETHPIC32IntMac.c"   
	
${OBJECTDIR}/_ext/1472/rs232.o: ../rs232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/rs232.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rs232.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rs232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/rs232.o.d" -o ${OBJECTDIR}/_ext/1472/rs232.o ../rs232.c   
	
${OBJECTDIR}/_ext/1472/Mynetmemo.o: ../Mynetmemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Mynetmemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Mynetmemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Mynetmemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Mynetmemo.o.d" -o ${OBJECTDIR}/_ext/1472/Mynetmemo.o ../Mynetmemo.c   
	
${OBJECTDIR}/_ext/1472/Eeprom_i2c.o: ../Eeprom_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Eeprom_i2c.o.d" -o ${OBJECTDIR}/_ext/1472/Eeprom_i2c.o ../Eeprom_i2c.c   
	
${OBJECTDIR}/_ext/1472/Temperature.o: ../Temperature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Temperature.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Temperature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Temperature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Temperature.o.d" -o ${OBJECTDIR}/_ext/1472/Temperature.o ../Temperature.c   
	
${OBJECTDIR}/_ext/1472/Teleinfo.o: ../Teleinfo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Teleinfo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Teleinfo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Teleinfo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Teleinfo.o.d" -o ${OBJECTDIR}/_ext/1472/Teleinfo.o ../Teleinfo.c   
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c   
	
${OBJECTDIR}/_ext/1472/SSLCert.o: ../SSLCert.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SSLCert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SSLCert.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SSLCert.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/SSLCert.o.d" -o ${OBJECTDIR}/_ext/1472/SSLCert.o ../SSLCert.c   
	
${OBJECTDIR}/_ext/1472/divers.o: ../divers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/divers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/divers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/divers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/divers.o.d" -o ${OBJECTDIR}/_ext/1472/divers.o ../divers.c   
	
${OBJECTDIR}/_ext/1472/SST25VF016.o: ../SST25VF016.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/SST25VF016.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/SST25VF016.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/SST25VF016.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/SST25VF016.o.d" -o ${OBJECTDIR}/_ext/1472/SST25VF016.o ../SST25VF016.c   
	
${OBJECTDIR}/_ext/1472/drv_spi.o: ../drv_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/drv_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/drv_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/drv_spi.o.d" -o ${OBJECTDIR}/_ext/1472/drv_spi.o ../drv_spi.c   
	
${OBJECTDIR}/_ext/1472/mcp7941.o: ../mcp7941.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/mcp7941.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mcp7941.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/mcp7941.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/mcp7941.o.d" -o ${OBJECTDIR}/_ext/1472/mcp7941.o ../mcp7941.c   
	
${OBJECTDIR}/_ext/1472/RTC.o: ../RTC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/RTC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/RTC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/RTC.o.d" -o ${OBJECTDIR}/_ext/1472/RTC.o ../RTC.c   
	
${OBJECTDIR}/_ext/1472/0_SparkBox.o: ../0_SparkBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/0_SparkBox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/0_SparkBox.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/0_SparkBox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/0_SparkBox.o.d" -o ${OBJECTDIR}/_ext/1472/0_SparkBox.o ../0_SparkBox.c   
	
${OBJECTDIR}/_ext/1472/Lcd.o: ../Lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Lcd.o.d" -o ${OBJECTDIR}/_ext/1472/Lcd.o ../Lcd.c   
	
${OBJECTDIR}/_ext/1472/Analogique.o: ../Analogique.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Analogique.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Analogique.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Analogique.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Analogique.o.d" -o ${OBJECTDIR}/_ext/1472/Analogique.o ../Analogique.c   
	
${OBJECTDIR}/_ext/1472/Evse.o: ../Evse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Evse.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/Evse.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Evse.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/Evse.o.d" -o ${OBJECTDIR}/_ext/1472/Evse.o ../Evse.c   
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -I".." -I"../../Microchip" -I"../../Microchip/Include" -I"../../Microchip/Include/TCPIP Stack" -I"../../Microchip/Include/MDD File System" -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_REAL_ICE=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,-L"../../../../../../../../../Program Files/Microchip/MPLAB C32 Suite/lib",-L"../../../../../../../../../Program Files/Microchip/MPLAB C32 Suite/pic32mx/lib",-L".",-Map="${DISTDIR}/sparkbox.X.${IMAGE_TYPE}.map",--report-mem,--warn-section-align
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-L"../../../../../../../../../Program Files/Microchip/MPLAB C32 Suite/lib",-L"../../../../../../../../../Program Files/Microchip/MPLAB C32 Suite/pic32mx/lib",-L".",-Map="${DISTDIR}/sparkbox.X.${IMAGE_TYPE}.map",--report-mem,--warn-section-align
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/sparkbox.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/DEBUG_-_Sans_Bootloader
	${RM} -r dist/DEBUG_-_Sans_Bootloader

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
