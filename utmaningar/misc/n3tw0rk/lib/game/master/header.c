/* 
 * This is a standard header object to inherit for other headers.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "/game/master/defs.h"
#include <std.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

/*
 * Global variable. 
 */
static string protocol;
static int layer;
static mixed *fields = ({ });

int used_as_data = 0;

int destruct_alarm = 0;

public string query_protocol(void);
public int query_layer(void);
public void set_protocol(string p,int uad = 0);
public void set_layer(int l);

/* field array is
    ({ "name", "type" or size, value, "description" })
*/

void set_use_as_data(void)
{
    used_as_data = 1;
}

void init(void)
{
    ::init();
    add_action("do_manipulate","manipulate");
}

// al - alignment -1 for left, 0 for middle, 1 for right
public string pad_string(string str, int len, int al = 0)
{
    int alternate = 1;
    int padLen = len - strlen(str);
    if(padLen < 1)
        return str;

    for(int i = 0; i < padLen; i++)
    {
        if(al < 0 || (!al && alternate))
            str = " " + str;
        else
            str += " ";
        alternate = !alternate;
    }
    return str;
}

public mixed get_field(int num)
{
    if(num > sizeof(fields))
        return 0;

    return fields[num];
}

public string get_field_name(int num)
{
    if(num > sizeof(fields))
        return 0;

    return fields[num][0];
}

public mixed get_field_type(int num)
{
    if(num > sizeof(fields))
        return 0;

    return fields[num][1];
}

public mixed get_field_value(int num)
{
    if(num > sizeof(fields))
        return 0;

    return fields[num][2];
}

public string get_field_desc(int num)
{
    if(num > sizeof(fields))
        return 0;

    return fields[num][3];
}

public mixed get_field_by_name(string str)
{
    foreach(mixed field: fields)
    {
        if(field[0] == str)
            return field;
    }

    return 0;
}

public mixed get_field_value_by_name(string str)
{
    foreach(mixed field: fields)
    {
        if(field[0] == str)
            return field[2];
    }

    return 0;
}

void set_field_value(int num, mixed val)
{
    if(num > sizeof(fields))
        return;

    fields[num][2] = val;
}

int get_num_fields(void)
{
    return sizeof(fields);
}

void destruct_header(void)
{
    remove_alarm(destruct_alarm);
    tell_room(ENV(TO),"The " + (used_as_data ? "data" : QN) + " fizzles out of existance.\n");
    destruct();
    return;
}

void enter_env(object dest, object old)
{
    if(!living(dest) && living(old))
    {
        if(!destruct_alarm)
            destruct_alarm = set_alarm(0.0, 0.0, destruct_header);
    }
    return;
}

/*
 * Function name: create_header
 * Description  : Call this function to create the header. Since you may not
 *                mask the function create_object, you must mask this one.
 */
public void
create_header()
{
}

/*
 * Function name: create_object
 * Description  : Initialize this object. It will set a few default
 *                variables. You may not mask this function. Define the
 *                function create_header() instead.
 */
nomask void
create_object()
{
    set_name("header");
    set_pname("headers");
    add_prop(OBJ_M_NO_GIVE,1);
    create_header();
}

nomask void
add_field(string n, mixed t, mixed v, string d)
{
    fields += ({ ({ n, t, v, d }) });
}

public string
format_data()
{
    // Implement this in each header
    return "<undefined>";
}

public string
long()
{
    return ::long() + "\n" + format_data() + 
        "\nYou could probably 'manipulate' its contents if you wanted.\n";
}


/*
 * Function name: reset_key
 * Description  : This function should hold the code that is to be executed
 *                when this header resets. In order for reset to work, you
 *                must call enable_reset() from your create_header.
 */
public void
reset_header()
{
}

/*
 * Function name: reset_object
 * Description  : You may not mask this function to make the key reset.
 *                Rather define the function reset_key.
 */
nomask void
reset_object()
{
    reset_header();
}

public string
query_protocol()
{
    return protocol;
}

public int 
query_layer()
{
    return layer;
}

public void
set_protocol(string p, int uad = 0)
{
    protocol = p;
    used_as_data = uad;

    if(used_as_data)
    {
        set_short(p + " header data");
        set_long(C(p) + " header data.");
        set_name(p + " header data");
        add_name("data");
        add_name(lower_case(p) + " header data");
    }
    else
    {
        set_short(p + " header");
        set_long(C(LANG_ADDART(p)) + " header.");
        set_name(p + " header");
        add_name("header");
        add_name(lower_case(p) + " header");
    }
}

public void 
set_layer(int l)
{
    layer = l;
}

void signal_change(void)
{
    ENV(TO)->catch_tell("The contents of your " + query_short() + " alters!\n");
}

public int 
update_checksum(void)
{
    // This is up to each protocol
    return 1; // 1 for ok, 0 for fail
}

public int 
verify_checksum(void)
{
    // This is up to each protocol
    return 1; // 
}

public int 
verify_header(void)
{
    // This is up to each protocol
    return 1;
}

int calculate_checksum(void) 
{
    // This is up to each protocol
    return -1; // Return -1 for fail   
}

// Return an byte array of all field values in the header
int *serialize_header(void)
{
    int *binary_header = ({ });

    // Construct the binary representation of the header
    for(int i = 0 ; i < get_num_fields() ; i++) 
    {
        string field_name = get_field_name(i);
        mixed field_size_or_type = get_field_type(i);
        mixed field_value = get_field_value(i);

        // Convert the field to binary
        if (intp(field_value)) 
        {
            int field_size = field_size_or_type;
            if (field_size > 8) 
            {
                // Handle splitting values larger than 8 bits
                for (int j = field_size - 8; j >= 0; j -= 8) 
                {
                    binary_header += ({ (field_value >> j) & 0xFF });            
                }
            } 
            else 
            {
                // Handle fields 8 bits or smaller
                binary_header += ({ field_value & 0xFF });
            }
        }
        else if (pointerp(field_value)) 
        {
            binary_header += field_value;
        }

    }    
    return binary_header;
}

int match_fieldname(mixed arg, string str)
{
    if(!pointerp(arg))
        return 0;
    return (arg[0] == str);
}

int parse_hex(string str)
{
    string hex = lower_case(str);
    int value = 0;
    int digit;

    for(int i = 0; i < strlen(hex); i++)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
        {
            digit = hex[i] - '0';
        }
        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            digit = hex[i] - 'a' + 10;
        }
        else
        {
            // Not hex!
            return -1;
        }
        value = (value << 4) | digit;
    }
    return value;
}

int do_manipulate(string str)
{
    if(!str)
    {
        return notify_fail("Manipulate what, and how? Type 'help manipulate' for help.\n");
    }

    string what;
    string cmd;

    if(id(lower_case(str)))
    {
        write("|-----------------------------------------------------------------------------|\n");
        write("|      Name      | Type/Size | Description                                    |\n");
        write("|-----------------------------------------------------------------------------|\n");
        foreach(mixed field: fields)
        {
            string type;
            if(stringp(field[1]))
                type = field[1];
            else
                type = sprintf("%d",field[1]);
            string tmp = break_string(field[3],46);
            if(!tmp)
                continue;
            string *desc = explode(tmp,"\n");
            if(!desc || !sizeof(desc))
                continue;
            write(sprintf("| %|14s | %|9s | %-46s |\n",field[0],type,desc[0]));
            for(int i = 1; i < sizeof(desc); i++)
                write(sprintf("|                |           | %-46s |\n",desc[i]));
            write("|-----------------------------------------------------------------------------|\n");
        }
        return 1;
    } 

    if(used_as_data)
    {
        if(sscanf(str,"%s header data %s",what,cmd) < 2 && sscanf(str,"%s data %s",what,cmd))
        {
            return notify_fail("Your command did not make any sense. Type 'help manipulate' for help.\n");       
        }
    }
    else if(sscanf(str,"%s header %s",what,cmd) < 2)
    {
        return notify_fail("Your command did not make any sense. Type 'help manipulate' for help.\n");       
    }

    if(!id(lower_case(what +  " header" + (used_as_data ? " data" :  ""))))
    {
        return notify_fail("What are you trying to manipulate?\n");
    }    

    int fieldindex;
    string fieldname;
    string valarg;

    if(sscanf(cmd,"%d:%s",fieldindex,valarg) < 2)
    {
        if(sscanf(cmd,"%s:%s",fieldname,valarg) < 2)
        {
            write("Your command did not make any sense. Type 'help manipulate' for help.\n");
            return 1;
        }
    }

    int cnt = 1;

    for(int j = 0; j < sizeof(fields) ; j++)
    {
        if(fields[j][0] == fieldname || fieldindex == cnt)
        {
            int val = 0;
            if(intp(fields[j][1]))
            {
                string tmp;
                int max_value = (1 << fields[j][1]) - 1;
                if(sscanf(valarg,"0x%s",tmp) == 1)
                {
                    val = parse_hex(tmp);
                    if(val < 0)
                    {
                        write("The value seems incorrect.\n");
                        return 1;
                    }
                }
                else if(sscanf(valarg,"%d",val) == 1)
                {
                    // Ok
                }
                else
                {
                    write("The value should be an integer.\n");
                    return 1;
                }
                if(val < 0)
                {
                    write("The value must be positive.\n");
                    return 1;
                }
                if(val > max_value)
                {
                    write("The value is too large for that field (max is "+max_value+").\n");
                    return 1;
                }
                fields[j][2] = val;
                write("You manipulate the content of the "+fields[j][0]+" field.\n");
                return 1;
             
            }
            else
            {
                int *addr = ({ 0,0,0,0,0,0 });
                switch(fields[j][1])
                {
                case "mac":
                    string *tmp = ({ "","","","","","" });
                    if(sscanf(valarg,"%s:%s:%s:%s:%s:%s",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]) != 6)
                    {
                        write("The value should be a MAC address with valid format.\n");
                        return 1;
                    }
                    else
                    {
                        for(int i ; i < 6; i++)
                        {
                            addr[i] = parse_hex(tmp[i]);
                            if(addr[i] < 0 || addr[i] > 0xFF)
                            {
                                write("The value should be a MAC address with valid format.\n");
                                return 1;
                            }
                        }

                        fields[j][2][0] = addr[0];
                        fields[j][2][1] = addr[1];
                        fields[j][2][2] = addr[2];
                        fields[j][2][3] = addr[3];
                        fields[j][2][4] = addr[4];
                        fields[j][2][5] = addr[5];
                        write("You manipulate the content of the "+fields[j][0]+" field.\n");
                    }
                    return 1;

                case "ip":
                    if(sscanf(valarg,"%d.%d.%d.%d",addr[0],addr[1],addr[2],addr[3]) != 4)
                    {
                        write("The value should be an IP address with valid format.\n");
                    }
                    else
                    {
                        fields[j][2][0] = addr[0];
                        fields[j][2][1] = addr[1];
                        fields[j][2][2] = addr[2];
                        fields[j][2][3] = addr[3];
                        write("You manipulate the content of the "+fields[j][0]+" field.\n");
                    }
                    return 1;

                default:
                    write("Unable to locate the correct field type.\n");       
                    return 1;
                }
            }
        }
        cnt++;
    }

    if(fieldname)
        write("There is no field named "+fieldname+" in the "+QN+".\n");       
    else 
        write("You can't find that field in the "+QN+".\n");       
    return 1;
}

int hlpr_calculate_checksum(int *data) 
{
    int checksum = 0;
    int size = sizeof(data);

    // Iterate over each 16-bit word in the data
    for (int i = 0; i < size; i += 2) 
    {
        int word = data[i] << 8;

        if(i + 1 < size)
            word += data[i + 1];

        checksum += word;

        // Handle carry-over
        if (checksum > 0xFFFF) 
        {
            checksum = (checksum & 0xFFFF) + (checksum >> 16);
        }
    }

    // One's complement
    return ~checksum & 0xFFFF;
}
