#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
using namespace std;

// File Handlers//
ifstream fin("input2.txt");
ofstream fout("output2.txt");

// Memory//
class OS
{
private:
    char M[300][4];
    char buffer[40];
    char IR[4];
    char R[5];
    int IC;
    int C;
    int SI;
    int PI;
    int TI;
    int PTR;
    bool breakFlag;

public:
    void init();
    void read(int RA);
    void write(int RA);
    int addressMap(int VA);
    void execute_user_program();
    void start_execution();
    int allocate();
    void load();
    void Terminate(int EM, int EM2 = -1);
    int MOS(int RA = 0);
};

// Process Control Block//
struct PCB
{
    int job_id;
    int TTL;
    int TLL;
    int TTC;
    int LLC;

    void setPCB(int id, int ttl, int tll)
    {
        job_id = id;
        TTL = ttl;
        TLL = tll;
        TTC = 0;
        LLC = 0;
    }
};

PCB pcb;

// /Error Messages/
string error[7] = {"No Error", "Out of Data", "Line Limit Exceeded", "Time Limit Exceeded",
                   "Operation Code Error", "Operand Error", "Invalid Page Fault"};

void OS::init()
{
    memset(M, '\0', 1200);
    memset(IR, '\0', 4);
    memset(R, '\0', 5);
    C = 0;
    SI = 0;
    PI = 0;
    TI = 0;
    breakFlag = false;
}

void OS::Terminate(int EM, int EM2)
{
    fout << endl
         << endl;
    if (EM == 0)
        fout << " terminated normally. " << error[EM];
    else
    {
        fout << EM << " - " << error[EM] << (EM2 != -1 ? (". " + error[EM2]) : "") << endl;
        fout << "IC=" << IC << ", IR=" << IR << ", C=" << C << ", R=" << R << ", TTL=" << pcb.TTL << ", TTC=" << pcb.TTC << ", TLL=" << pcb.TLL << ", LLC=" << pcb.LLC << endl;
    }
}
void OS::read(int RA)
{
    fin.getline(buffer, 41);

    char temp[5];
    memset(temp, '\0', 5);
    memcpy(temp, buffer, 4);

    if (!strcmp(temp, "$END"))
    {
        Terminate(1);
        breakFlag = true;
    }
    else
        strcpy(M[RA], buffer);
}

void OS::write(int RA)
{
    if (pcb.LLC + 1 > pcb.TLL)
    {
        Terminate(2);
        breakFlag = true;
    }
    else
    {
        char str[40];
        int k = 0;
        for (int i = RA; i < (RA + 10); i++)
            for (int j = 0; j < 4; j++)
                str[k++] = M[i][j];

        fout << str << endl;

        pcb.LLC++;
    }
}

int OS::MOS(int RA)
{
    if (TI == 0)
    {
        if (SI != 0)
        {
            switch (SI)
            {
            case 1:
                read(RA);
                break;
            case 2:
                write(RA);
                break;
            case 3:
                Terminate(0);
                breakFlag = true;
                break;
            default:
                cout << "Error with SI." << endl;
            }
            SI = 0;
        }
        else if (PI != 0)
        {
            switch (PI)
            {
            case 1:
                Terminate(4);
                breakFlag = true;
                break;
            case 2:
                Terminate(5);
                breakFlag = true;
                break;
            case 3:
                PI = 0;
                // Page Fault checking
                char temp[3];
                memset(temp, '\0', 3);
                memcpy(temp, IR, 2);

                if (!strcmp(temp, "GD") || !strcmp(temp, "SR"))
                {
                    int m;
                    do
                    {
                        m = allocate();
                    } while (M[m * 10][0] != '\0');

                    int currPTR = PTR;
                    while (M[currPTR][0] != '*')
                        currPTR++;

                    itoa(m, M[currPTR], 10);

                    cout << "Valid Page Fault, page frame = " << m << endl;
                    cout << "PTR = " << PTR << endl;
                    for (int i = 0; i < 300; i++)
                    {
                        cout << "M[" << i << "] :";
                        for (int j = 0; j < 4; j++)
                            cout << M[i][j];
                        cout << endl;
                    }
                    cout << endl;

                    if (pcb.TTC + 1 > pcb.TTL)
                    {
                        TI = 2;
                        PI = 3;
                        MOS();
                        break;
                    }
                    pcb.TTC++;
                    return 1;
                }
                else if (!strcmp(temp, "PD") || !strcmp(temp, "LR") || !strcmp(temp, "H") || !strcmp(temp, "CR") || !strcmp(temp, "BT"))
                {
                    Terminate(6);
                    breakFlag = true;

                    if (pcb.TTC + 1 > pcb.TTL)
                    {
                        TI = 2;
                        PI = 3;
                        MOS();
                        break;
                    }
                    // pcb.TTC++;
                }
                else
                {
                    PI = 1;
                    MOS();
                }
                return 0;
            default:
                cout << "Error with PI." << endl;
            }
            PI = 0;
        }
    }
    else
    {
        if (SI != 0)
        {
            switch (SI)
            {
            case 1:
                Terminate(3);
                breakFlag = true;
                break;
            case 2:
                write(RA);
                if (!breakFlag)
                    Terminate(3);
                break;
            case 3:
                Terminate(0);
                breakFlag = true;
                break;
            default:
                cout << "Error with SI." << endl;
            }
            SI = 0;
        }
        else if (PI != 0)
        {
            switch (PI)
            {
            case 1:
                Terminate(3, 4);
                breakFlag = true;
                break;
            case 2:
                Terminate(3, 5);
                breakFlag = true;
                break;
            case 3:
                Terminate(3);
                breakFlag = true;
                break;
            default:
                cout << "Error with PI." << endl;
            }
            PI = 0;
        }
    }

    return 0;
}

int OS::addressMap(int VA)
{
    if (0 <= VA && VA < 100)
    {
        int pte = PTR + VA / 10;
        if (M[pte][0] == '*')
        {
            PI = 3;
            return 0;
        }
        cout << "In addressMap(), VA = " << VA << ", pte = " << pte << ", M[pte] = " << M[pte] << endl;
        return atoi(M[pte]) * 10 + VA % 10;
    }
    PI = 2;
    return 0;
}

void OS::execute_user_program()
{
    char temp[3], loca[2];
    int locIR, RA;

    while (true)
    {
        if (breakFlag)
            break;

        RA = addressMap(IC);
        if (PI != 0)
        {
            if (MOS())
                continue;

            break;
        }
        cout << "IC = " << IC << ", RA = " << RA << endl;
        memcpy(IR, M[RA], 4); // Memory to IR, instruction fetched
        IC += 1;

        memset(temp, '\0', 3);
        memcpy(temp, IR, 2);
        for (int i = 0; i < 2; i++)
        {
            if (!((47 < IR[i + 2] && IR[i + 2] < 58) || IR[i + 2] == 0))
            {
                PI = 2;
                break;
            }
            loca[i] = IR[i + 2];
        }

        if (PI != 0)
        {
            MOS();
            break;
        }

        // loca[0] = IR[2];
        // loca[1] = IR[3];
        locIR = atoi(loca);

        RA = addressMap(locIR);
        if (PI != 0)
        {
            if (MOS())
            {
                IC--;
                continue;
            }
            break;
        }

        cout << "IC = " << IC << ", RA = " << RA << ", IR = " << IR << endl;
        if (pcb.TTC + 1 > pcb.TTL)
        {
            TI = 2;
            PI = 3;
            MOS();
            break;
        }

        if (!strcmp(temp, "LR"))
        {
            memcpy(R, M[RA], 4);
            pcb.TTC++;
        }
        else if (!strcmp(temp, "SR"))
        {
            memcpy(M[RA], R, 4);
            pcb.TTC++;
        }
        else if (!strcmp(temp, "CR"))
        {
            if (!strcmp(R, M[RA]))
                C = 1;
            else
                C = 0;
            pcb.TTC++;
        }
        else if (!strcmp(temp, "BT"))
        {
            if (C == 1)
                IC = RA;
            pcb.TTC++;
        }
        else if (!strcmp(temp, "GD"))
        {
            SI = 1;
            MOS(RA);
            pcb.TTC++;
        }
        else if (!strcmp(temp, "PD"))
        {
            SI = 2;
            MOS(RA);
            pcb.TTC++;
        }
        else if (!strcmp(temp, "H"))
        {
            SI = 3;
            MOS();
            pcb.TTC++;
            break;
        }
        else
        {
            PI = 1;
            MOS();
            break;
        }
        memset(IR, '\0', 4);
    }
}

void OS::start_execution()
{
    IC = 0;
    execute_user_program();
}

int OS::allocate()
{
    srand(time(0));
    return (rand() % 30);
}

void OS::load()
{
    int m;        // Variable to hold memory location
    int currPTR;  // Points to the last empty location in Page Table Register
    char temp[5]; // Temporary Variable to check for $AMJ, $DTA, $END
    memset(buffer, '\0', 40);

    while (!fin.eof())
    {
        fin.getline(buffer, 41);
        memset(temp, '\0', 5);
        memcpy(temp, buffer, 4);

        if (!strcmp(temp, "$AMJ"))
        {
            init();

            int jobId, TTL, TLL;
            memcpy(temp, buffer + 4, 4);
            jobId = atoi(temp);
            memcpy(temp, buffer + 8, 4);
            TTL = atoi(temp);
            memcpy(temp, buffer + 12, 4);
            TLL = atoi(temp);
            pcb.setPCB(jobId, TTL, TLL);

            PTR = allocate() * 10;
            memset(M[PTR], '*', 40);
            currPTR = PTR;
        }
        else if (!strcmp(temp, "$DTA"))
            start_execution();
        else if (!strcmp(temp, "$END"))
            continue;
        else
        {
            if (breakFlag)
                continue;
            do
            {
                m = allocate();
            } while (M[m * 10][0] != '\0');

            itoa(m, M[currPTR], 10);
            currPTR++;

            strcpy(M[m * 10], buffer);

            cout << "PTR = " << PTR << endl;
            for (int i = 0; i < 300; i++)
            {
                cout << "M[" << i << "] :";
                for (int j = 0; j < 4; j++)
                    cout << M[i][j];
                cout << endl;
            }
            cout << endl;
        }
    }
}

int main()
{

    OS os;

    os.load();
    fin.close();
    fout.close();
    return 0;
}