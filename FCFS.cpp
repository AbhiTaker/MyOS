#include <vector>
#include <iostream>
#include <queue>
#include <set>


using namespace std;

struct node{

    int arrival, runtime, start,end;
    node(){
        start = end = 100000000;
    }
};

node Process[1000];
int n,cur_time=0;

void Print()
{
    cout<<"TIME : "<<cur_time<<"\n";
    cout<<"PROCESS - STATE :\n";
    for(int i=0; i<n; i++)
    {
        if(Process[i].end<= cur_time)
            cout<<"P"<<i+1<<"   - TERMINATED \n";
        else if(Process[i].start<= cur_time)
            cout<<"P"<<i+1<<"   - RUNNING \n";
        else if(Process[i].arrival <= cur_time)
            cout<<"P"<<i+1<<"   - READY \n";
        else
            cout<<"P"<<i+1<<"   - NEW \n";
    }
}

int main()
{
    int i=0,proc = 1;
    cout<<"Enter the Number of Process:\n";
    cin>>n;
    cout<<"Enter the Process:\n";
    cout<<"Arrival Time - CPU Time :\n";
    for(i=0; i<n; i++)
        cin>>Process[i].arrival>>Process[i].runtime;

    queue<int> run,wait;
    run.push(0);
    Process[0].start = Process[0].arrival;
    cur_time = Process[0].arrival;
    while(!run.empty())
    {
        int ind = run.front();
        int print = 0;
        if(Process[ind].start + Process[ind].runtime == cur_time)
        {
            print = 1;
            run.pop();
            Process[ind].end = cur_time;
        }

        while(cur_time == Process[proc].arrival)
        {
            wait.push(proc);
            proc++;
        }
        int flag = 0;
        if(run.empty() && !wait.empty())
        {
            int ind2 = wait.front();
            if(Process[ind2].arrival <= cur_time)
            {
                flag = 1;
                Process[ind2].start = cur_time;
                ind = ind2;
                run.push(ind2);
                wait.pop();
            }
        }

        if(print)
           Print();

        if(print==0 && proc<n)
            cur_time = min(Process[ind].start + Process[ind].runtime, Process[proc].arrival);
        else if(flag && proc<n)
            cur_time = min(Process[ind].start + Process[ind].runtime, Process[proc].arrival);
         else if(!flag && !wait.empty() && print!=0)
         {
             int ind2 = wait.front();
             Process[ind2].start = cur_time;
             ind = ind2;
             run.push(ind2);
             wait.pop();
             if(proc<n)
                 cur_time = min(Process[ind].start + Process[ind].runtime, Process[proc].arrival);
            else
                cur_time = Process[ind].start + Process[ind].runtime;
         }
         else if(wait.empty() && proc<n && print!=0)
         {
             Process[proc].start = Process[proc].arrival;
             run.push(proc);
             ind = proc;
             proc++;
             if(proc<n)
                 cur_time = min(Process[ind].start + Process[ind].runtime, Process[proc].arrival);
            else
                cur_time = Process[ind].start + Process[ind].runtime;
         }
         else
            cur_time = Process[ind].start + Process[ind].runtime;


    }


    cout<<"\nFINAL OUTPUT :\n";
    cout<<"PID - AT - ST - CT - WT :\n";
    for(i=0; i<n; i++)
        cout<<"P"<<i+1<<"  - "<<Process[i].arrival<<" - "<<Process[i].start<<" - "<<Process[i].end<<" -  "<<(Process[i].start - Process[i].arrival) - Process[i].burst<<"\n";


    return 0;
}
