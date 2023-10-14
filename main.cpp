#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <windows.h>

using namespace std;

int HoursToMinutes(int h, int min)
{
    return h * 60 + min;
}

void afisare_ora()
{
    int i, j, h, minn, day, cls, min_st, min_end, min, min_st2;
    string hour, minute;
    struct class_time
    {
        int hour_start, minute_start, hour_end, minute_end;
    } prog[7];

    time_t now = time(NULL);
    tm *time = localtime(&now);

    string a[8][5];
    ifstream f("orar.txt");
    for (i = 0; i < 8; i++)
        for (j = 0; j < 5; j++)
            f >> a[i][j];
    f.close();

    day = time->tm_wday;
    day--;
    h = time->tm_hour;
    minn = time->tm_min;

    if (day == 5 || day == -1)
        cout << "Este weekend. Enjoy! :)";
    else
    {
        cout << h << ":" << minn << endl;

        ifstream g("interval_orar.txt");
        for (i = 0; i < 2; i++)
            for (j = 0; j < 7; j++)
            {
                getline(g, hour, ':');
                getline(g, minute, ' ');
                if (i == 0)
                {
                    prog[j].hour_start = stoi(hour);
                    prog[j].minute_start = stoi(minute);
                }
                else
                {
                    prog[j].hour_end = stoi(hour);
                    prog[j].minute_end = stoi(minute);
                }
            }
        min = HoursToMinutes(h, minn);
        for (cls = 0; cls < 7; cls++)
        {
            min_st = HoursToMinutes(prog[cls].hour_start, prog[cls].minute_start);
            min_end = HoursToMinutes(prog[cls].hour_end, prog[cls].minute_end);
            min_st2 = HoursToMinutes(prog[cls + 1].hour_start, prog[cls + 1].minute_start);
            if (min >= min_st && min <= min_end)
            {
                cout << "Ora: " << a[cls + 1][day];
                cout << "\nOra viitoare: " << a[cls + 2][day] << " care incepe la " << prog[cls + 1].hour_start << ":" << prog[cls + 1].minute_start;
            }
            else if (min > min_end && min < min_st2)
            {
                cout << "Pauza care se termina la " << prog[cls + 1].hour_start << ":" << prog[cls + 1].minute_start;
                cout << "\nOra viitoare " << a[cls + 2][day];
            }
        }
       
    }
}
int main()
{
    afisare_ora();
    cout << endl;
    system("pause");
    return 0;
}