/* File name: bl_common.h
 *
 * Description: base library common head file
 *
 * Create by henuyx on 2015-04-27
 *
 */

#ifndef __BL_COMMON_H__
#define __BL_COMMON_H__

/*******************INCLUDE*******************************/

/*******************GLOBAL********************************/

namespace BL_NS
{

// base data type
typedef unsigned long long  uint64;
typedef unsigned int  uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef long long  int64;
typedef int  int32;
typedef short int16;
typedef char int8;

// max ip size
const uint32 BL_MAX_IP_SIZE=16;
// SOCKET BLOCK SIZE 10M
const uint32 BL_SOCKET_BLOCK_SIZE=1024*1024*10;

}

#endif

/*******************EOF***********************************/
