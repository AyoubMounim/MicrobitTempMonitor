
#ifndef DEVPINS
#define DEVPINS

#define DEVPIN(p, i) ((p << 5) + i)

#define ROW1 DEVPIN(0, 21)
#define ROW2 DEVPIN(0, 22)
#define ROW3 DEVPIN(0, 15)
#define ROW4 DEVPIN(0, 24)
#define ROW5 DEVPIN(0, 19)

#define USB_TX DEVPIN(0, 6)
#define USB_RX DEVPIN(1, 8)

#endif