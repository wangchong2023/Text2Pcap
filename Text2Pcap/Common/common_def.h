#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include <QString>
#include <QDateTime>

#define PERCENT_100 100.0

#define APP_NAME_TEXT2CAP                   "text2pcap"
#define APP_NAME_WIRESHARK                  "Wireshark"
#define APP_NAME_DISPLAY_WIRESHARK          "DisplayWireshark"
#define WIRESHARK_CUSTOMED_CONFIG           "CustomedWiresharkPath"
#define WIRESHARK_CUSTOMED_DISPLAY_CONFIG   "CustomedDisplayWiresharkPath"
#define WIRESHARK_PCAP_STORAGE_CONFIG       "PcapStoragePath"
#define WIRESHARK_PCAP_Format_CONFIG        "PcapFormat"

#define CONFIG_FILE_NAME "config.ini"

#define PACKET_CONTENT_MAX_SIZE (256 * 1024)

#define REG_EXPRESS_BLANK "\\s"
#define QSTRING_PARAM_FIRST "%1"

#define STRING_CHAR_BLANK ' '
#define STRING_CHAR_ZERO '0'
#define STRING_EMPTY ""
#define STRING_COMMA ", "
#define STRING_SLASH "/"
#define STRING_BLANK " "
#define STRING_CRLF "\r\n"

#define WIRESHARK_TEXT2CAP_FILL_WIDTH 6
#define TIME_FORMAT_SIMPLE_SEC                "yyyy-MM-dd-hh-mm-ss"
#define TIME_FORMAT_SIMPLE_MSEC               "yyyy-MM-dd-hh:mm:ss.zzz"
#define TIME_FORMAT_SIMPLE_DAY                "yyyy-MM-dd"
#define TIME_FORMAT_SIMPLE_MSEC_UNDERLINE     "yyyyMMdd_hhmmsszzz"
#define TIME_WAIT_READY_READ_MSEC  (-1)
#define MAX_TEXT2PCAP_START_RETRY_TIMES 0xFFFFFFFF
#define MAX_WIRESHARK_START_RETRY_TIMES 0xFFFFFFFF
#define MAX_TIMER_LOOP_TIMES 0xFFFFFFFF

#define TIMER_TYPE_INFO_PROCESS           1
#define TIMER_INTERVAL_MSEC_INFO_PROCESS  100

#define LOG_TYPE_RUNNING           tr("running")
#define LOG_PATH_RUNNING           tr("log")
#define LOG_OUTPUT_FORMAT_FL       "File:(%1) Line:(%2)"
#define LOG_OUTPUT_FORMAT_TFL      "%{type} %{time [yyyy-MM-dd hh:mm:ss]} %{file}:%{line} %{message}"
#define LOG_DIR                    "/log"

#define FILE_SEP_UNDERLINE         "_"
#define FILE_SUFFIX_DOT            "."
#define FILE_SUFFIX_DOT_LOG        ".log"
#define FILE_EXTENTION_TXT         "txt"
#define FILE_EXTENTION_PCAP        "pcap"
#define FILE_EXTENTION_PCAPNG      "pcapng"
#define FILE_NAME_PREFIX           "file"

#define TEXT2PCAP_OPT_ETH           "-e "
#define TEXT2PCAP_OPT_IP_PRPOTO     "-i "
#define TEXT2PCAP_OPT_TCP_PORT      "-T "
#define TEXT2PCAP_OPT_UDP_PORT      "-u "

#define PACKET_PAD_TYPE_NONE           0
#define PACKET_PAD_TYPE_LINK           1
#define PACKET_PAD_TYPE_IPV4           2
#define PACKET_PAD_TYPE_IPV6           3
#define PACKET_PAD_TYPE_TCP            4
#define PACKET_PAD_TYPE_UDP            5

#define LINK_TYPE_ETH           1
#define LINK_TYPE_ETH_IPV4      0X0800
#define LINK_TYPE_ETH_IPV6      0X86DD
#define LINK_TYPE_MIN           0
#define LINK_TYPE_MAX           65535
#define IP_PROTO_NUM_MIN        0
#define IP_PROTO_NUM_MAX        255
#define PORT_NUM_MIN            0
#define PORT_NUM_MAX            65535

#define STRING_FILL_NUM_ZERO_VAL  0
#define STRING_FILL_STR_ZERO_VAL '0'
#define RADIX_BIN 2
#define RADIX_OCT 8
#define RADIX_DEC 10
#define RADIX_HEX 16

#define TEXT2CAP_LINE_CHAR_NUM       32
#define TEXT2CAP_LINE_CHAR_INDEX     (TEXT2CAP_LINE_CHAR_NUM - 1)
#define TEXT2CAP_SEP_CHAR_NUM        2
#define TEXT2CAP_BYTE_TO_CHARS_NUM   2

#define TEXT2CAP_VERSION     "V0.90-alpha2"
#define TEXT2CAP_APP_NAME    "Text2Pcap"
#define TEXT2CAP_ORG_NAME    "Constantine"
#define TEXT2CAP_ORG_DOMAIN  "org.constantine"

#endif // COMMON_DEF_H
