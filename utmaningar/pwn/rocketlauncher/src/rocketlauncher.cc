#include <signal.h>
#include <iostream>
#include <unistd.h>

#define BIG 1
#define SMALL 2

#define DIE(str) perror(str); exit(1);

using namespace std;

// Handler for when time is up
void alarmHandler(int pass) {
    cout << "TIMEOUT!" << endl;
    exit(1);
}

// Point to alarmHandler for SIGALRM and
// disable buffering on I/O
void setup() {
    struct sigaction act;
    act.sa_handler = alarmHandler;
    sigaction(SIGALRM, &act, NULL);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(60);
}

string part_names[8] = {"Main Engine", "Hull", "Booster", "Igniter", "Vertical Tail", "Payload", "Delta Wing", "Safety Hatch"};

typedef struct part {
    int width;
    int height;
} part;

class BaseRocket {
  public:
    int type;
	virtual void LaunchRocket() {}
};

#define BIG_ROCKET_NUM_PARTS 8
#define SMALL_ROCKET_NUM_PARTS 2

class BigRocket : public BaseRocket {
  public:
    part parts[BIG_ROCKET_NUM_PARTS];
    int type = BIG;

    BigRocket() {
        for (int i = 0; i < BIG_ROCKET_NUM_PARTS; i++) {
            this->parts[i].width = -1;
            this->parts[i].height = -1;
        }
    }

    void EditRocket() {
        for (int i = 0; i < BIG_ROCKET_NUM_PARTS; i++) {
            if (this->parts[i].width != -1) {
                cout << part_names[i] << " width (previously " << this->parts[i].width << ") = ";
            } else {
                cout << part_names[i] << " width = ";
            }
            cin >> this->parts[i].width;
            if (this->parts[i].height != -1) {
                cout << part_names[i] << " height (previously " << this->parts[i].height << ") = ";
            } else {
                cout << part_names[i] << " height = ";
            }
            cin >> this->parts[i].height;
        }
    }

    void LaunchRocket() {
        cout << "Vroooooooooooooom!" << endl; 
        return;
    }
};

class SmallRocket : public BaseRocket {
  public:
    int type = SMALL;
    part parts[SMALL_ROCKET_NUM_PARTS];

    SmallRocket() {
        for (int i = 0; i < SMALL_ROCKET_NUM_PARTS; i++) {
            this->parts[i].width = -1;
            this->parts[i].height = -1;
        }
    }
    
    void EditRocket() {
        for (int i = 0; i < SMALL_ROCKET_NUM_PARTS; i++) {
            if (this->parts[i].width != -1) {
                cout << part_names[i] << " width (previously " << this->parts[i].width << ") = ";
            } else {
                cout << part_names[i] << " width = ";
            }
            cin >> this->parts[i].width;
            if (this->parts[i].height != -1) {
                cout << part_names[i] << " height (previously " << this->parts[i].height << ") = ";
            } else {
                cout << part_names[i] << " height = ";
            }
            cin >> this->parts[i].height;
        }
    }

    void LaunchRocket() {
        cout << "Zooooooooooooooom!" << endl; 
        return;
    }
};

class PrivilegedRocket : public BaseRocket {
  public:
    void LaunchRocket() {
        cout << "Wooooooooooow!" << endl; 
        system("cat flag");
        return;
    }
};

void print_menu(){
cout << R"EOF(
1) Build rocket
2) Rebuild rocket
3) Launch rocket
4) Sign out)EOF" << endl;
}

#define MAX_ROCKETS 10
BaseRocket* Rockets[MAX_ROCKETS];

void list(int type) {
    switch (type){
        case BIG:
            cout << "Big rockets:" << endl;
            break;
        case SMALL:
            cout << "Small rockets:" << endl;
            break;
    }
    for (int i = 0; i < MAX_ROCKETS; i++) {
        switch (type){
            case BIG:
                if (Rockets[i] && dynamic_cast<BigRocket *>(Rockets[i]) != nullptr) {
                    cout << "  [" << i << "]" << endl;
                }
                break;
            case SMALL:
                if (Rockets[i] && dynamic_cast<SmallRocket *>(Rockets[i]) != nullptr) {
                    cout << "  [" << i << "]" << endl;
                }
                break;
        }
    }
}

int get_free_slot() {
    for (int i = 0; i < MAX_ROCKETS; i++) {
        if (Rockets[i] == 0) return i;
    }
    return -1;
}

void add() {
    int idx = get_free_slot();
    if (idx == -1) {
        cout << "no free slots!" << endl;
        return;
    }
    do {
        string size;
        cout << "big or small > ";
        cin >> size;
        if ( !size.compare("big") ) {
            BigRocket * r = new BigRocket();
            r->EditRocket();
            Rockets[idx] = r;
            break;
        }
        else if ( !size.compare("small") ) {
            SmallRocket * r = new SmallRocket();
            r->EditRocket();
            Rockets[idx] = r;
            break;
        }
    } while (true);

}

int get_rocket_idx(){
    int idx;
    cout << "Rocket index > ";
    cin >> idx;

    if (idx < 0 || idx >= MAX_ROCKETS) {
        cout << "Invalid index" << endl;
        return -1;
    }

    if (Rockets[idx] == 0) {
        cout << "No such rocket" << endl;
        return -1;
    }
    return idx;
}

void edit() {
    int idx;
    int type;
    string size;

    do {
        cout << "big or small > ";
        cin >> size;
        if ( !size.compare("big") ) {
            type=BIG;
            break;
        }
        else if ( !size.compare("small") ) {
            type=SMALL;
            break;
        }
    } while (true);

    list(type);

    if ( (idx = get_rocket_idx()) == -1 ) {
        return;
    }

    if (type == BIG){
            BigRocket * r = static_cast<BigRocket*>(Rockets[idx]);
            r->EditRocket();
    } else if (type == SMALL) {
            SmallRocket * r = static_cast<SmallRocket*>(Rockets[idx]);
            r->EditRocket();
    }
    
}

void launch() {
    int idx;
    if ( (idx = get_rocket_idx()) == -1 ) {
        return;
    }

    cout << "\n ** LAUNCH IMMINENT ** \n" << endl;
    sleep(1);
    Rockets[idx]->LaunchRocket();
    sleep(1);
    cout << "\n ** LAUNCH COMPLETE ** \n" << endl;
    sleep(1);
    delete Rockets[idx];
    Rockets[idx] = nullptr;
}


int main() {
    int choice;
    setup();
    PrivilegedRocket * Hmmmmmmmmmmmmmm = new PrivilegedRocket();

    while (choice != 4)  {
        list(SMALL);
        list(BIG);
        print_menu();
        cout << "> ";
        cin >> choice;
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                launch();
                break;
            default:
                cout << "\nBye!\n" << endl;
                return 0;
        }
    }
}
