#include <mraa/aio.h>
#include <mraa/gpio.h>
#include <unistd.h>
#include <string>
#include <signal.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

void questions();
void storeTimeStamp(string time);
void storeResponse(int response, string question);
bool acceptedAlarm();
void alarm();
bool isYesButtonPressed();
bool isNoButtonPressed();
int time();
int timealarm();
string readTime(int time);
bool isJournalPeriod();
void journalSequence();
int scaledVal();
int listenForResponse();

string jfile = "journal.txt";

int main()
{
    cout << "\n\n\nHello!" << endl;
    while (1)
    {
        if (isYesButtonPressed())
        {
            usleep(100000);
            journalSequence();
            sleep(1);
        }
        else if (isJournalPeriod())
        {
            if (acceptedAlarm())
                journalSequence();
            usleep(500000);
        }
        else
        {
            cout << readTime(time()) << endl;
            sleep(60);
        }
    }
}

void questions()
{
    string prompt = "Please answer these 10 questions on a scale from 0-4. \n";
    string scaleExplained = "0 - not at all\n1 - somewhat\n2 - moderately\n3 - a lot\n4 - extremely\n";
    string q1 = "Are you feeling unhappy or blue?\n";
    string q2 = "Are you experiencing crying spells or tearfulness?\n";
    string q3 = "Are you feeling discouraged or hopeless?\n";
    string q4 = "Are you feeling worthless or inadequate?\n";
    string q5 = "Are you spending less time with family or friends?\n";
    string q6 = "Are you experiencing a loss of motivation?\n";
    string q7 = "Are you experiencing a loss of interest in work, school, or other activities?\n";
    string q8 = "Are you feeling tired?\n";
    string q9 = "Are you experiencing a decreased or increase appetite?\n";
    string q10 = "Do you have any suicidal thoughts?\n";
    int response;
    double total = 0;
    
    cout << prompt;
    cout << scaleExplained;
    
    sleep(1);
    
    cout << q1;
    response = listenForResponse();
    storeResponse(response, q1);
    total += response;
    usleep(300000);
    
    cout << q2;
    response = listenForResponse();
    storeResponse(response, q2);
    total += response;
    usleep(300000);
    
    cout << q3;
    response = listenForResponse();
    storeResponse(response, q3);
    total += response;
    usleep(300000);
    
    cout << q4;
    response = listenForResponse();
    storeResponse(response, q4);
    total += response;
    usleep(300000);
    
    cout << q5;
    response = listenForResponse();
    storeResponse(response, q5);
    total += response;
    usleep(300000);
    
    cout << q6;
    response = listenForResponse();
    storeResponse(response, q6);
    total += response;
    usleep(300000);
    
    cout << q7;
    response = listenForResponse();
    storeResponse(response, q7);
    total += response;
    usleep(300000);
    
    cout << q8;
    response = listenForResponse();
    storeResponse(response, q8);
    total += response;
    usleep(300000);
    
    cout << q9;
    response = listenForResponse();
    storeResponse(response, q9);
    total += response;
    usleep(300000);
    
    cout << q10;
    response = listenForResponse();
    storeResponse(response, q10);
    total += response;
    usleep(300000);
    
    int score = (int)((total * 100) / 40);
    
    ofstream jfile_out;
    jfile_out.open("journal.txt", ios::out |  ios::app);
    jfile_out << "Score: " << score << "\n";
    jfile_out.close();
    
    cout << "Thank you." << endl;
}

void storeTimeStamp(string time)
{
    ofstream jfile_out;
    jfile_out.open("journal.txt", ios::out | ios::app);
    jfile_out << "\n\n" << time << "\n";
    jfile_out.close();
}

void storeResponse(int response, string question)
{
    char answer = (char)response + 48;
    
    ofstream jfile_out;
    jfile_out.open("journal.txt", ios::out |  ios::app);
    jfile_out << question << answer << "\n";
    jfile_out.close();
}

bool acceptedAlarm()
{
    while (1)
    {
        alarm();
        if (isYesButtonPressed())
            return true;
        else if (isNoButtonPressed())
            return false;
    }
    return true;
}

bool isYesButtonPressed()
{
    mraa_gpio_context yesButton;
    yesButton = mraa_gpio_init(4);
    mraa_gpio_dir(yesButton, MRAA_GPIO_IN);
    return mraa_gpio_read(yesButton);
}

bool isNoButtonPressed()
{
    mraa_gpio_context noButton;
    noButton = mraa_gpio_init(8);
    mraa_gpio_dir(noButton, MRAA_GPIO_IN);
    
    return mraa_gpio_read(noButton);
}

void alarm()
{
    mraa_gpio_context buzzer;
    buzzer = mraa_gpio_init(7);
    mraa_gpio_dir(buzzer, MRAA_GPIO_OUT);
    
    mraa_gpio_write(buzzer, 1);
    sleep(1);
    mraa_gpio_write(buzzer, 0);
    sleep(1);
}

int time()
{
    time_t now;
    time(&now);
    return (int)now;
}


int timeAlarm()
{
    struct tm t;
    time_t t_of_day;
    t.tm_year = 2016 - 1900;
    t.tm_mon = 10;           // Month, 0 - jan
    t.tm_mday = 29;
    t.tm_hour = 18;
    t.tm_min = 00;
    t.tm_sec = 00;
    t.tm_isdst = 0;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);
    return (int)t_of_day;
}


string readTime(int time)
{
    time_t now;
    struct tm ts;
    char buf[80];
    
    now = (long)time;
    ts = *localtime(&now);
    
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    
    return buf;
}

bool isJournalPeriod()
{
    int timeNow = time();
    int alarm = timeAlarm();
    
    int timeSince = timeNow - alarm;
    int timePeriod = 60;        // 24 hours is 86400
    
    int timeSinceEpoch = timeSince%timePeriod;
    if (timeSinceEpoch == 0)
        return true;
    return false;
}


void journalSequence()
{
    storeTimeStamp(readTime(time()));
    questions();
}


int scaledVal()
{
    uint16_t value;
    mraa_aio_context rotary;
    rotary = mraa_aio_init(0);
    
    value = mraa_aio_read(rotary);
    
    mraa_aio_close(rotary);
    
    int val = (int)value;
    
    if (0 <= val && val <= 140)
        return 0;
    else if (val <= 280)
        return 1;
    else if (val <= 420)
        return 2;
    else if (val <= 560)
        return 3;
    else
        return 4;
}

int listenForResponse()
{
    int val = 0;
    int oldval = 5;
    while (!isYesButtonPressed())
    {
        val = scaledVal();
        
        if (oldval != val)
        {
            cout << val << endl;
            oldval = val;
        }
        usleep(100000);
    }
    
    return val;
}
