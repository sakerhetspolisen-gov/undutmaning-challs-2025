#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the Outlook process");
    set_long(BSN("The room feels impossibly vast, cluttered with shelves, drawers, and filing cabinets that seem to stretch out into infinity. "+
                 "Papers, folders, and strange devices for sending, organizing, and losing emails and numerous other whatnots are scattered "+
                 "everywhere. It's a space that tries to do far too many things at once, as if someone had decided that what was really missing "+
                 "from their life was an all-in-one office, bakery, and zoo. Tiny, stressed figures dash about, trying to keep track of unread "+
                 "messages, flagged items, and calendars overburdened with meetings that no one ever attends. In one corner, a gargantuan 'Search' "+
                 "tool lumbers about, occasionally waking from its slumber to search for something — though what it finds rarely matches what you "+
                 "asked for. And in another stands a rickety blackboard, filled with what looks like hasty scribbled gibberish. Meanwhile, the "+
                 "room has a faint hum, a constant sense of background activity, as though the process is always running a multitude of "+
                 "sub-processes, most of which seem to be arguing amongst themselves about what is truly important. A yawning opening in the floor "+
                 "reveals a dark tube leading down, through which emails are occasionally funneled, though sometimes "+
                 "they seem to vanish into the abyss without explanation."));

    add_item(({"shelves", "drawers", "filing cabinets"}),
        BSN("The shelves, drawers, and filing cabinets are all filled to bursting with documents, files, and half-finished tasks. "+
            "No one seems to know exactly what's inside any of them, and there's a strong sense that anything stored within is unlikely "+
            "to ever be seen again. The drawers rattle ominously, as if they're hiding years' worth of forgotten correspondence."));

    add_item(({"papers", "folders", "strange devices"}),
        BSN("Papers flutter gently, stacked haphazardly on every available surface, and folders bulge with more documents than they were ever "+
            "meant to hold. Strange devices, intended to send, receive, or organize various data objects, are scattered throughout the room, "+
            "each one looking like it might do something useful — if anyone could figure out how it works. Most are adorned with blinking lights "+
            "and arcane buttons, their purposes long forgotten."));
        
    add_item(({"figures", "workers", "tiny figures"}),
        BSN("The figures in this room are overworked and underappreciated, constantly moving from one folder to another, attempting to organize the "+
            "chaos. They carry stacks of papers, most of which they don't appear to have time to actually look at, muttering to themselves about flagged "+
            "messages and overdue calendar invites. Some are trying, with visible frustration, to get the 'Search' function to work properly, but it seems "+
            "as confused as they are. Occasionally they fuss over the rickety blackboard, writing or erasing something."));

    add_item(({"search tool", "search", "search function"}),
        BSN("The 'Search' tool is a lumbering, oversized contraption that looks like it was assembled from parts of a dozen other machines. It occasionally "+
            "groans to life, running a search only to return something entirely unrelated to what was asked for. When it does manage to find something "+
            "useful, it's more by accident than design, and its proud, self-satisfied wheeze as it displays the result is almost comical."));

    add_item(({"blackboard","rickety blackboard","board"}),
        BSN("The rickety blackboard is covered in a chaotic scrawl of text, numbers, and symbols that have been written, erased, and rewritten so many times, "+
            "the surface is beginning to wear thin. The figures darting about the room occasionally rush past it, frantically erasing sections and scribbling new ones, "+
            "as if they're constantly trying to keep up with some impossible task. You can't help but wonder what vital information they are desperately trying to "+
            "track on this weary board, though it seems to change by the minute."));

    add_item(({"text","text on blackboard","scrawl","chaotic scrawl","numbers","symbols"}),
        "@@message_log");

    add_item(({"opening", "tube", "floor"}),
        BSN("The large opening in the floor leads down into a shadowy tube, through which packets of emails travel back and forth."));
            
    add_exit(NODES + "workstation_layer3", "down", 0, 0);

    object ob = clone_object(NPC + "workstation_layer4_mail");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));
    set_ip(({198,51,100,199,255}));
    set_hostname("workstation");
}

string message_log(void)
{
    return ".----------------------------------------------------------------------------.\n"+
        "|                          -=* Operations log *=-                            |\n"+
        "|      [4] days without incident. [3421] left until cake and lemonade!       |\n"+
        "|----------------------------------------------------------------------------|\n"+
        "| 11:29:01 [INFO] Initializing POP3 Client...                                |\n"+
        "| 11:29:02 [INFO] Connecting to POP3 server at mail.n3tw0rk.ex:110           |\n"+
        "| 11:29:02 [INFO] Sending USER command for authentication...                 |\n"+
        "| 11:29:03 [INFO] Sending PASS command for authentication...                 |\n"+
        "| 11:29:04 [INFO] Authentication successful. Logged in as alex@n3tw0rk.ex    |\n"+
        "| 11:31:05 [INFO] Retrieving mail from server...                             |\n"+
        "| 11:31:06 [INFO] Mail retrieval in progress...                              |\n"+
        "| 11:31:09 [INFO] Mail #11 - Subject: \"IMPORTANT\" from: \"kenneth@rymden.nu\"  |\n"+
        "| 11:32:49 [INFO] Disconnecting from POP3 server.                            |\n"+
        "| 11:32:50 [INFO] Logged out from POP3 server.                               |\n"+
        "| 11:35:31 [INFO] Displaying retrieved emails to user...                     |\n"+
        "| 11:41:25 [INFO] User selected \"IMPORTANT\" email for printing.              |\n"+
        "| 11:41:26 [INFO] Preparing email for printing...                            |\n"+
        "| 11:41:37 [INFO] Starting print job for \"IMPORTANT\" email...                |\n"+
        "| 11:41:38 [INFO] Opening printer connection: \"Printer@198.51.100.182\"       |\n"+
        "| 11:41:39 [INFO] Sending print job to spooler (spoolsv.exe)...              |\n"+
        "| 11:42:19 [INFO] Print job successfully sent to spooler. Job ID: 31355      |\n"+
        "| 11:42:19 [INFO] Waiting for printer to complete the job...                 |\n"+
        "| 11:48:22 [INFO] Print job completed with error. Status: Queued             |\n"+
        "| 11:48:23 [INFO] Closing printer connection.                                |\n"+
        "| 11:48:24 [INFO] Print job finished. Proceeding to delete email...          |\n"+
        "| 11:48:25 [INFO] Deleting \"IMPORTANT\" email from server...                  |\n"+
        "| 11:48:26 [INFO] Sending DELE command to POP3 server for email ID: 11       |\n"+
        "| 11:48:27 [INFO] Email deleted successfully.                                |\n"+
        "'----------------------------------------------------------------------------'\n";
}