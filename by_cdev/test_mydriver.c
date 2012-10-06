// Below code is from link: http://bbs.chinaunix.net/forum.php?mod=viewthread&tid=3772447
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int iDevId = open("/dev/MyDrv0", O_RDWR);
    if(iDevId > 0) {
        close(iDevId);
    } else {
        printf("Can't open /dev/MyDrv0.\n");
    }

    return 0;
}
