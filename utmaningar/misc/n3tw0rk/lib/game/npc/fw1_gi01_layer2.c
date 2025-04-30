#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("diligent security officer");
    add_name("officer");
    add_name("security officer");
    set_short("A diligent security officer");
    set_long(BSN("A steadfast presence of data, taking the form of a meticulous and conscientious "+
        "security officer. With a gaze as sharp as a freshly debugged algorithm, it observes every "+
        "packet that passes by with the careful scrutiny of someone who values precision and order. "+
        "While its demeanor may seem imposing, it's more about maintaining harmony than instilling "+
        "fear. A thin wire, subtly integrated into its attire, suggests a quiet connection to unseen "+
        "channels of communication. Despite its vigilant stance, it's open to requests for assistance "+
        "or information, provided they're approached with respect and clarity."));

    add_item(({"wire","ear","earpiece"}),
        BSN("A delicate wire, likely linked to a communications device, keeping the officer in touch "+
            "with its team and ensuring smooth operations."));

    set_chat_time(10);

    add_chat("Greetings, packets! Please keep moving and avoid unnecessary delays.");   
    add_chat("Kindly line up and be patient. We're all here to keep things running smoothly.");
    add_chat("Notice anything unusual? Please report it promptly so we can address it swiftly.");
    add_chat("Ensure your belongings are secured. Unattended items will be looked into.");
    add_chat("Have your identification ready and visible. We aim for efficiency here.");
    add_chat("A well-organized packet is a joy to work with. Let's keep everything in order.");
    add_chat("No lingering! We've got a schedule to keep, and every packet plays a part.");
    add_chat("Stay alert and follow the protocol. A smooth operation benefits everyone.");

    set_act_time(10);

    add_act("emote adjusts its uniform with a practiced motion, ensuring everything is in place.");
    add_act("emote listens attentively to the wire in its ear, receiving updates from its team.");
    add_act("emote scans the area with a careful eye, maintaining an overall sense of order.");
    add_act("emote takes a moment to straighten a few misplaced items, reinforcing a tidy environment.");
    add_act("emote subtly nods as if acknowledging some unseen directive, a sign of its ongoing vigilance.");
    add_act("emote checks an invisible watch, a gentle reminder that time management is crucial here.");
}
