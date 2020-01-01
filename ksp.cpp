#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <stack>

using namespace std;

class SP_graph{
private:
	int v_num;
	list<pair<int,int> > *adjlists;
	vector<int> pre, dis;
	vector<bool> visited;
public:
	SP_graph(int v);
	void add_edge(int src, int dest, int weight);
	void output(vector<int> &vec, vector<int> &weight);
	void relax(int src, int dest, int weight);
	void dijkstra();
  int cut(int src, int dest);
  void recover(int src, int dest, int weight);
};

SP_graph::SP_graph(int v){
	v_num = v;
	adjlists = new list<pair<int,int> >[v];
	for(int i = 0; i < v; i++){
		pre.push_back(-1);
		dis.push_back(-1);
		visited.push_back(0);
	}
	dis[0] = 0;
}

void SP_graph::add_edge(int src, int dest, int weight){
	adjlists[src].push_back(make_pair(dest, weight));
}

int SP_graph::cut(int src, int dest){
  for(auto &i: adjlists[src]){
    if(i.first == dest){
      int re = i.second; 
      i.second = 9999999;
      return re;
    }
  }
}

void SP_graph::recover(int src, int dest, int weight){
  for(auto &i: adjlists[src]){
    if(i.first == dest)
      i.second = weight;
  }
}

void SP_graph::output(vector<int> &vec,vector<int> &weight){
	int i = v_num-1;
	if(dis[i] == -1)
		cout << "impossible" << endl;
	else{
		stack<int> s;
		s.push(i);
		int root = i;
		while(true){
			if(pre[root] == -1)
				break;
			s.push(pre[root]);
			root = pre[root];
		}
		int size = s.size();
		for(int j = 0; j < size-1; j++){
      vec.push_back(s.top());
			s.pop();
		}
		vec.push_back(s.top());
		weight.push_back(dis[i]);
	}
}

void SP_graph::relax(int src, int dest, int weight){
	if(dis[dest] > dis[src] + weight || dis[dest] == -1){
		dis[dest] = dis[src] + weight;
		pre[dest] = src;
	}
}

void SP_graph::dijkstra(){
	for(int i = 0; i < v_num; i++){
		pre[i] = -1;
		dis[i] = -1;
		visited[i] = 0;
	}
  dis[0] = 0;
  for(int c = 0; c < v_num; c++){
		int min = -2;
		int ind;
		for(int i =0; i < v_num; i++){
			if(dis[i] >= 0 && visited[i] == 0){
				if(min == -2){
					min = dis[i];
					ind = i;
				}
				else if(dis[i] < min){
					min = dis[i];
					ind = i;
				}
			}
		}
		visited[ind] = 1;
		for(list<pair<int,int> >::iterator it = adjlists[ind].begin(); it != adjlists[ind].end(); it++){
			relax(ind, (*it).first, (*it).second);
		}
	}
}

int main(){
  int flag = 0;
	while(flag == 0){
		int v, e, k;
		cout << "input number of vertexes : ";
		cin >> v;
		cout << "input number of edge : ";
		cin >> e;
		SP_graph SP(v);
		for(int i = 0; i < e; i++){
			int src, dest, weight;
			cout << "intput one edge : ";
			cin >> src >> dest >> weight;
      src -= 1;
      dest -= 1;
			SP.add_edge(src, dest, weight);
		}
    cin >> k;
		SP.dijkstra();
    vector<int> vec1,weight1;
		SP.output(vec1,weight1);
    cout << endl;
    for(int i = 0; i < vec1.size(); i++){
      cout << vec1[i]+1 << " ";
    }
    cout << endl;

    vector<int> vec2[vec1.size()-1];
    vector<int> weight2;
    for(int i = 0; i < vec1.size()-1; i++){
      int temp = SP.cut(vec1[i],vec1[i+1]);
      SP.dijkstra();
      SP.output(vec2[i],weight2);
      SP.recover(vec1[i],vec1[i+1],temp);
    }
    int o_count = 1;
    vector<int> out;
    while(o_count < k){
      int min = 9999999;
      int temp_i;
      for(int i = 0; i < weight2.size(); i++){
        if(weight2[i] < min){
          min = weight2[i];
          temp_i = i;
        }
      }
      int oflag = 0;
      if(!out.empty()){
        for(int i = 0; i < out.size(); i++){
          int oflag2 = 0;
          for(int j = 0; j < vec2[out[i]].size(); j++){
            if(vec2[out[i]][j] != vec2[temp_i][j])
              oflag2 = 1;
          }
          if(oflag2 == 0)
            oflag = 1;
        }
      }
      else
        oflag = 0;
      if(oflag == 1)
        weight2[temp_i] = 9999999;
      else{
        out.push_back(temp_i);
        weight2[temp_i] = 9999999;
        o_count++;
      }
    }
		for(int i = 0; i < out.size(); i++){
      for(int j = 0; j < vec2[i].size(); j++){
        cout << vec2[out[i]][j]+1 << " ";
      }
      cout << endl;
    }
    cout << endl;
    cout << out.size();
    
    flag = 1;
	}
	return 0;
}
