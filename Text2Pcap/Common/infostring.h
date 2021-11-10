#ifndef INFOSTRING_H
#define INFOSTRING_H

/* 消息对话框提示信息 */
#define INFO_STRING_INPUT_INVALID_NOT_DIGITAL     tr("输入参数不是数字")
#define INFO_STRING_INPUT_INVALID_NOT_HEX_DIGITAL tr("输入参数不是16进制数字")
#define INFO_STRING_INPUT_INVALID_EMPTY           tr("输入参数为空")
#define INFO_STRING_INPUT_INVALID                 tr("输入参数非法")
#define INFO_STRING_LINK_TYPE_EXCEED_MAX          tr("链路层类型大于了0XFFFF")
#define INFO_STRING_IP_PROTO_NUM_EXCEED_MAX       tr("IP协议号大于了255")
#define INFO_STRING_SRC_PORT_NUM_EXCEED_MAX       tr("源端口号大于了65535")
#define INFO_STRING_DST_PORT_NUM_EXCEED_MAX       tr("目的端口号大于了65535")
#define INFO_STRING_SAVE_DIR_FAILED               tr("保存路径失败，路径不存在。")
#define INFO_STRING_GET_FILE_NAME_FAILED          tr("获取文件名失败。")
#define INFO_STRING_FILE_IS_NOT_WIRESHARK         tr("指定的文件不是Wireshark。")
#define INFO_STRING_WIRESHARK_PATH_INVALID        tr("Wireshark路径不合法。")
#define INFO_STRING_PCAP_SAVE_PATH_INVALID        tr("解析文件的保存路径非法。")
#define INFO_STRING_PATH_IS_NOT_DIR               tr("选择的不是文件夹。")
#define INFO_STRING_PACKET_CONTENT_EMPTY          tr("报文内容为空，请重新输入。")
#define INFO_STRING_PACKET_CONTENT_TRIM_EMPTY     tr("报文内容去除空格后为空，请重新输入。")
#define INFO_STRING_PACKET_LENGTH_EXCEED          tr("报文内容过大（超过64K），请重新输入。")
#define INFO_STRING_PACKET_CONTENT_INVALID        tr("报文内容报文包含非法字符（非16进制字符），请重新输入。")
#define INFO_STRING_CONFIRM_DEL_PCAP_DIR          tr("此操作将会删除本目录下的所有.pcap和.pcapng文件，请确认是否执行此操作？")
#define INFO_STRING_DEL_PCAP_DIR_OK              "删除完成。共计删除%d个文件。"

#define INFO_STRING_PARSE_PARAMS_INVALID          tr("停止解析，解析参数非法。")
#define INFO_STRING_PARSE_TEXT2PCAP_RETRY_EXCEED  tr("停止解析，超出最大Text2Pcap启动次数。")
#define INFO_STRING_PARSE_WIRESHARK_RETRY_EXCEED  tr("停止解析，超出最大Wireshark启动次数。")

/* ToolTip信息 */
#define INFO_STRING_TOOLTIP_PARSE_ETHERNET       tr("大多数场景下报文都是以太网类型的帧格式")
#define INFO_STRING_TOOLTIP_TYPE_NO_PAD          tr("不填充")
#define INFO_STRING_TOOLTIP_TYPE_PAD_IP          tr("填充IP层信息")
#define INFO_STRING_TOOLTIP_TYPE_PAD_TCP         tr("填充TCP传输层信息")
#define INFO_STRING_TOOLTIP_TYPE_PAD_UDP         tr("填充UDP传输层信息")

#define INFO_STRING_TOOLTIP_LINK_TYPE_RANGE       tr("取值范围：0-0XFFFF")
#define INFO_STRING_TOOLTIP_IP_PROTO_NUM_RANGE   tr("取值范围：0-255")
#define INFO_STRING_TOOLTIP_PORT_NUM_RANGE       tr("取值范围：0-65535")

#define INFO_STRING_TOOLTIP_CONTENT_TYPE_HEX_STREAM       tr("16进制数据格式举例："\
                                                            "\n021a11f0c83b60334b13c55808004500001c26ef000040015831c0a82b0908080808080020c4d73b0000")
#define INFO_STRING_TOOLTIP_CONTENT_TYPE_HEX_DUMP         tr("16进制Hex Dump数据格式举例："\
                                                             "\n0000   02 1a 11 f0 c8 3b 60 33 4b 13 c5 58 08 00 45 00"\
                                                             "\n0010   00 1c 26 ef 00 00 40 01 58 31 c0 a8 2b 09 08 08"\
                                                             "\n0020   08 08 08 00 20 c4 d7 3b 00 00")
#define INFO_STRING_TOOLTIP_PACKET_CONTENT       tr("报文内容，最大支持256K有效数据长度。")

#define INFO_STRING_TOOLTIP_WIRESHARK_PATH       tr("默认检测到的Wireshark安装路径（也可以自定义设置）")
#define INFO_STRING_TOOLTIP_PCAP_STORAGE_PATH    tr("指定解析后文件的存放路径")

#endif // INFOSTRING_H
