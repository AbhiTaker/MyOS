#include <iostream>>
#include <queue>>

using namespace std;

struct node{
    int arrival, runtime, start,end, state,first_time,last,wait;
    node()
    {
        end = 1000000;
        first_time =0;
        wait = 0;
    }
};

node Process[100];

int n,cur_time=0;

void Print()
{
    cout<<"TIME : "<<cur_time<<"\n";
    cout<<"PROCESS - STATE :\n";
    for(int i=0; i<n; i++)
    {
        if(Process[i].end<= cur_time)
            cout<<"P"<<i+1<<"   - TERMINATED \n";
        else if(Process[i].state == 1)
            cout<<"P"<<i+1<<"   - RUNNING \n";
        else if(Process[i].arrival <= cur_time)
            cout<<"P"<<i+1<<"   - READY \n";
        else
            cout<<"P"<<i+1<<"   - NEW \n";
    }
}

int main()
{
    int i=1,proc = 1;
    cout<<"Enter the Number of Process:\n";
    cin>>n;
    cout<<"Enter the Process:\n";
    cout<<"Arrival Time - CPU Time :\n";
    for(i=0; i<n; i++)
    {
        cin>>Process[i].arrival>>Process[i].runtime;
        Process[i].last = Process[i].arrival;
    }

    queue<int> Ready;
    cur_time = Process[0].arrival;
    Process[0].start = Process[0].arrival;
    Process[0].first_time = 1;
    Process[0].state = 1;
    Ready.push(0);
    i=1;
    Print();
    while(!Ready.empty())
    {
        int ind = Ready.front();
        Ready.pop();
        int flag = 0;
        if(cur_time + 4 >= cur_time + Process[ind].runtime)
        {
            cur_time = cur_time + Process[ind].runtime;
            Process[ind].end = cur_time;
        }
        else
        {
            Process[ind].runtime -= 4;
            cur_time += 4;
            Process[ind].last = cur_time;
            flag = 1;
        }
        Process[ind].state = 0;
        while(cur_time >= Process[i].arrival && i<n)
        {
            Ready.push(i);
            i++;
        }

        if(flag)
            Ready.push(ind);
        if(Ready.empty())
            break;

        ind = Ready.front();
        Process[ind].wait += cur_time - Process[ind].last;
        if(Process[ind].first_time != 1)
        {
            Process[ind].start = cur_time;
            Process[ind].first_time = 1;
        }
        Process[ind].state = 1;
        Print();
    }
    Print();

    cout<<"\nFINAL OUTPUT :\n";
    cout<<"PID - AT - ST - CT - WT - TAT:\n";
    long double avg_wait = 0, avg_turn = 0;
    for(i=0; i<n; i++)
    {
        cout<<"P"<<i+1<<"  - "<<Process[i].arrival<<" - "<<Process[i].start<<" - "<<Process[i].end<<" -  "<<Process[i].wait<<" - "<<Process[i].end - Process[i].arrival<<"\n";
        avg_wait += Process[i].wait;
        avg_turn += Process[i].end - Process[i].arrival;
    }
    avg_wait = avg_wait/n;
    avg_turn = avg_turn/n;
    cout<<"AVERAGE WAIT TIME : "<<avg_wait<<"\n";
    cout<<"AVERAGE TURN AROUND TIME : "<<avg_turn<<"\n";
    return 0;
}
