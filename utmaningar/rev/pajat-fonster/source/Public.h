/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_Driver1,
    0x6950947c,0x9781,0x45a6,0xa6,0x9d,0x07,0x0b,0x31,0xdc,0x2c,0x2f);
// {6950947c-9781-45a6-a69d-070b31dc2c2f}
