/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "boot/boot.h"
#include "boot/e820.h"
#include "boot/memcpy.h"
#include "boot/strings.h"
#include "mm.h"
#define CONFIG_DEBUG_PRINTF 0
#define CONFIG_DEBUG_ASSERT 0
#define CONFIG_USE_DEFAULT_CFG 1
#include "lwext4/ext4.h"
#include "lwext4/ext4_fs.h"

//static struct ext4_blockdev bd;
//static int block_proxy_open(struct ext4_blockdev *bdev)
//{
//    return 0;
//}
//    bd.bdif->open = block_proxy_open;


bool init_mm()
{
    
    struct ext4_fs *fs = bd.fs;
    if (isE820Available())
        getE820Memory();
    else
    {
        return false;
    }
    
    return true;        
}
