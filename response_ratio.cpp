#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <pair.h>

using namespace std;

struct node{
    int arrival,start,waiting,end,prior,burst;
    node(){
        waiting = 0;
        end = 10000000;
    }
};

node Process[100];
int n,cur_time = 0;

void print()
{
    cout<<"\nTime : "<<cur_time<<"\n";
    for(int i=0; i<n; i++)
    {
        if(Process[i].end <= cur_time)
            cout<<"P"<<i+1<<" - Finished\n";
        else if(Process[i].start <= cur_time)
            cout<<"P"<<i+1<<" - Running\n";
        else if(Process[i].arrival < cur_time)
            cout<<"P"<<i+1<<" - Ready\n";
        else
           cout<<"P"<<i+1<<" - New\n";
    }
}

int main()
{
    cout<<"Enter The number of Process :\n";
    cin>>n;
    cout<<"Enter Process Data :\n";
    cout<<"Arrival Time - CPU Time - Priority: \n";
    for(int i=0; i<n; i++)
        cin>>Process[i].arrival>>Process[i].burst>>Process[i].prior;

    priority_queue< pair< pair< long double , int> , int>  > pq;
    set<int> ready;
    ready.clear();
    set<int>::iterator it;
    int i = 0;
    cur_time = Process[i].arrival;
    while(Process[i].arrival <= cur_time && i<n)
    {
        pq.push( make_pair( make_pair(1 , 3 - Process[i].prior), i) );
        ready.insert(i);
        i++;
    }
    vector< pair<int,int> > v;
    while(!pq.empty())
    {
        int ind = pq.top().second;
        pq.pop();
        ready.erase(ind);
        Process[ind].start = cur_time;
        v.push_back(make_pair(cur_time, ind));
        cur_time += Process[ind].burst;
        Process[ind].end = cur_time;

        if(Process[i].arrival> cur_time && ready.empty() && i<n)
        {
            cur_time = Process[i].arrival;
        }
        while(Process[i].arrival <= cur_time && i<n)
        {
            cout<<i<<"\n";
            ready.insert(i);
            i++;
        }
        while(!pq.empty())
            pq.pop();
        for(it = ready.begin(); it!=ready.end(); it++)
        {
            int wait = cur_time - Process[*it].arrival;
            long double rr = (long double)(wait + Process[*it].burst)/(long double)Process[*it].burst;
            pq.push( make_pair( make_pair(rr , 3 - Process[*it].prior), *it) );
        }
        print();
    }

    cout<<"\nFinal Output \n";
    long double wait_time = 0;
    for(int i=0; i<n; i++)
    {
        cout<<"PID  - AT  - ST  - EndT - WT\n";
        cout<<"P"<<i+1<<" -   "<<Process[i].arrival<<" -   "<<Process[i].start<<" -   "<<Process[i].end<<" -  "<<(Process[i].end - Process[i].arrival) - Process[i].burst<<"\n";
        wait_time += Process[i].end - Process[i].arrival - Process[i].burst;
    }
    long double avg = wait_time/n;
    cout<<"Average Waiting Time : "<<fixed<<avg<<"\n";

    cout<<"Gant Chart \n";
    for(int i= 0 ;i<v.size(); i++)
        cout<<v[i].first<<" - ";
    cout<<"\n";
    for(int i= 0 ;i<v.size(); i++)
        cout<<"P"<<v[i].second+1<<" - ";
    cout<<"\n";

    return 0;
}
