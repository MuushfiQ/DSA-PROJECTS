#include <bits/stdc++.h>
using namespace std;

void buildGraph(map<string, vector<pair<string, int>>> &G) {
    G["Farmgate"] = {
        {"Tsc", 5},
        {"Mirpur", 10}
    };

    G["Tsc"] = {
        {"Farmgate", 5},
        {"Mirpur", 20},
        {"Bashundhara", 18}
    };

    G["Mirpur"] = {
        {"TSC", 20},
        {"Farmgate", 10},
        {"Abdullahpur", 13},
        {"Tongi", 13}
    };

    G["Abdullahpur"] = {
        {"Mirpur", 13},
        {"Uttara", 1},
        {"Bashundhara", 10},
        {"Tongi", 12}
    };

    G["Uttara"] = {
        {"Abdullahpur", 1},
        {"Bashundhara", 5}
    };

    G["Bashundhara"] = {
        {"Uttara", 5},
        {"Abdullahpur", 10},
        {"Tsc", 20}
    };

    G["Tongi"] = {
        {"Abdullahpur", 12},
        {"Mirpur", 13}
    };
}

void printGraph(map<string, vector<pair<string, int>>> &G) {
    for ( auto &node : G) {
        cout << node.first << " shortest destination:\n";
        for (auto &edge : node.second) {
            cout << "  -> " << edge.first << " (distance " << edge.second << ")\n";
        }
        cout << endl;
    }
}

int TicketCost(int distance) {
    cout<<"\nPer Kilometer Cost : 20 Taka"<<endl;
    return distance * 20;
}
int ticketCoststudent(int distance){
    cout<<"\nPer Kilometer Cost :10 Taka (For STUDENTS ONLY);"<<endl;
    return distance*10;
}
void coinChange(int n,int cost) {
    vector<int> takas = {1000,500,200,100, 50, 20, 10,5,2,1};
    map<int, int> used;
    cost=n-cost;

    for (int a : takas) {
        if (cost >=a) {
            used[a] = cost / a;
            cost %= a;
        }
    }

    cout << "\nPlease Take your following Notes(tk)\n ";
    for (auto &a : used) {
        cout <<a.first << " ---> " << a.second <<" Notes"<< endl;
    }
}

int estimateTime(int distance) {
    int avgSpeed = 30;
    return (distance * 60) / avgSpeed;
}

void timeTable(string src, string dst, int estimatedTime) {
    cout << "\nDeparture Time for " << src << " to " << dst << endl << endl;
    cout << "1)8:00 AM \n2)10:45 AM\n3)12:30 PM\n4)3:00 PM" << endl << endl;
    cout << "Please Select your Time.  Ex:1,2,3,4" << endl;
    int k;
    cin >> k;

    int hour = 0, minute = 0;
    string am_pm;

    if (k == 1) {
        hour = 8; minute = 0; am_pm = "AM";
        cout << "\nSelected Time for " << src << " to " << dst << " is 8:00 AM" << endl;
    } else if (k == 2) {
        hour = 10; minute = 45; am_pm = "AM";
        cout << "\nSelected Time for " << src << " to " << dst << " is 10:45 AM" << endl;
    } else if (k == 3) {
        hour = 12; minute = 30; am_pm = "PM";
        cout << "\nSelected Time for " << src << " to " << dst << " is 12:30 PM" << endl;
    } else {
        hour = 3; minute = 0; am_pm = "PM";
        cout << "\nSelected Time for " << src << " to " << dst << " is 3:00 PM" << endl;
    }

    int totalMinutes = hour * 60 + minute + estimatedTime;
    int arrivalHour = (totalMinutes / 60) % 24;
    int arrivalMinute = totalMinutes % 60;

    string arrivalAmPm = (arrivalHour >= 12) ? "PM" : "AM";
    if (arrivalHour > 12) arrivalHour -= 12;
    if (arrivalHour == 0) arrivalHour = 12;

    cout << "Reach Time (Estimated Arrival): "
         << arrivalHour << ":" << (arrivalMinute < 10 ? "0" : "") << arrivalMinute
         << " " << arrivalAmPm << endl;
}

void dijkstra(map<string,vector<pair<string,int>>>&G,string source, string destination) {
    map<string, int> dist;
    map<string, string> parent;
    set<pair<int, string>> pq;

    for (auto &node : G) {
        dist[node.first] = INT_MAX;
    }
    dist[source] = 0;
    pq.insert({0, source});

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());

        for (auto &edge : G[u]) {
            string v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.insert({dist[v], v});
            }
        }
    }

    if (dist[destination] == INT_MAX) {
        cout << "No path found from " << source << " to " << destination << ".\n";
        return;
    }

    vector<string> path;
    for (string at = destination; at != source; at = parent[at]) {
        path.push_back(at);
    }
    path.push_back(source);
    reverse(path.begin(), path.end());

    cout << "\nShortest path from " << source << " to " << destination << ": ";
    for (auto &p : path) {
        cout << p;
        if (p != destination) cout << " -> ";
    }

    cout << "\n\nTotal Distance: " << dist[destination] << " KiloMeters\n";

    cout<<"\nAre you student?"<<endl;
    cout<<"1.YES\n2.NO"<<endl;
    int k;
    cin>>k;
    int cost;
    if(k==1) cost=ticketCoststudent(dist[destination]);
    else cost = TicketCost(dist[destination]);

    cout << "\nTicket Cost: " << cost << " Taka"<<endl;

    int estTime = estimateTime(dist[destination]);

    timeTable(source,destination,estTime);

    cout << "Estimated Travel Time: " << estTime << " Minutes\n";

    cout<<"\nPlease Input Your Payable amount?"<<endl;
    int n;
    cin>>n;

    coinChange(n,cost);
}
string lower(string s){
    for(int i=0;i<s.size();i++){
        s[i]=tolower(s[i]);
    }
    return s;
}


int main() {
    cout<<"************Welcome to Dhaka Metro Service software !**************"<<endl;
    map<string, vector<pair<string, int>>> G;

    buildGraph(G);
    printGraph(G);
    string source,destination;
    cout<<"Please give your Current location !!"<<endl;
    cin>>source;

    string src=lower(source);
    src[0]=toupper(src[0]);
    cout<<"Where you want to go?"<<endl;
    cin>>destination;
    string dst=lower(destination);
    dst[0]=toupper(dst[0]);
    dijkstra(G,src,dst);

    return 0;
}
