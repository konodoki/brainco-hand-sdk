#include <stdio.h>
#include <unistd.h>

#include "bxi_pci_drv.h"

int can_rx_call_test(void *arg, canfd_packet *msg){
    printf("can[%d] recv, id:%d, dlc:%d, data:", msg->bus, msg->frame.can_id, msg->frame.len);

    // for (size_t i = 0; i < msg->can_dlc; i++){
    //     printf("0x%x ", msg->data[i]);
    // }
    printf("\n");

    return 0;
}

int main(){

    if (-1 == bxi_pci_init(can_rx_call_test, NULL, -1)){
        return -1;
    }

    struct canfd_frame frame={
        .can_id=(0x03E00108& CAN_EFF_MASK) | CAN_EFF_FLAG,
        .flags=CANFD_BRS,
        .len=8,
        .data={
            0x01,0x04,0x0B,0xB8,0x00,0x0A,0x9E,0x75
        }
    };
    canfd_packet msg={
        .bus=0,
        .frame=frame
    };
    canfd_send_packet(&msg, 1);
    for (int i=0; i<3; i++) {
        sleep(1);
    }
    bxi_pci_exit();

    return 0;
}