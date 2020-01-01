#ifndef PROTOCOL_H
#define PROTOCOL_H

/**
* 数据通信帧头，每一帧数据长度（不）固定
*/
struct Package {
    unsigned int syncWord : 6;         // 同步字  0x2a [b101010]
    unsigned int type : 2;             // 数据包类型 0:客户端数据请求  1:服务器应答请求
    unsigned int cmd : 8;              // 命令
    unsigned int parity : 1;           // 奇偶校验位，除该位之外，其他数据奇偶校验位
    unsigned int errorCode : 5;        // 错误代码
    unsigned int dataLen : 10;         // 数据长度
};


#endif // PROTOCOL_H
