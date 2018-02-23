#include <bits/stdc++.h>

using namespace std;

struct Workshop {
  int start_t, duration, end_t;
};

struct Available_Workshops {
  int n;
  Workshop* ws;
};

Available_Workshops* initialize(int start_time[], int duration[], int n) {
  Available_Workshops* res = new Available_Workshops;
  res->n = n;
  res->ws = new Workshop[n];
  for (int i=0;i<n;i++) {
    res->ws[i].start_t = start_time[i];
    res->ws[i].duration = duration[i];
    res->ws[i].end_t = start_time[i]+duration[i];
  }
  return res;
}

bool is_overlaped(const Workshop& w1, const Workshop& w2) {
  return (w1.start_t<w2.start_t)?
    ( (w1.end_t<=w2.start_t)? false: true ): 
    ( (w1.start_t>w2.start_t)? 
      ( (w1.start_t>=w2.end_t)? false: true): true );
}

bool is_overlaped_the_set(Available_Workshops* ptr,
			  vector<int>& aws_id,
			  vector<vector<int>>& overlaped_matrix) {
  for (auto it=aws_id.begin();it<aws_id.end();it++)
    for (auto jt=it+1;jt<aws_id.end();jt++)
      if (overlaped_matrix[*it][*jt])
	return true;
  return false;
}

void print_set(vector<int>& aws_id) {
  for (auto it=aws_id.begin();it<aws_id.end();it++)
    cout << *it << ",";
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
  int total=0, N=ptr->n;
  vector<vector<int>> overlaped_matrix(N,vector<int>(N,0));
  for (int i=0;i<N;i++)
    for (int j=i+1;j<N;j++)
      if (is_overlaped( ptr->ws[i], ptr->ws[j]))
	overlaped_matrix[i][j]=1;
  for (int K=N;K>0; K--) {
    string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
    // print integers and permute bitmask
    bool overlaped_set = true;
    do {
      vector<int> aws_id;
      for (int i = 0; i < N; ++i) // [0..N-1] integers
	if (bitmask[i])
	  aws_id.push_back(i);
      //print_set(aws_id);
      if ( overlaped_set=is_overlaped_the_set(ptr,aws_id,overlaped_matrix) ) {
	//cout << "Fail!!!" << endl;
	continue;
      }
      else {
	//cout << "Works!!!" << endl;
	break;
      }
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
    cout << K << endl;
    if (!overlaped_set) {
      total = K;
      break;
    }
  }
  return total;
}

int main( int argc, char *argv[]) {
  
  int n; // number of workshops
  cin >> n;
  // create arrays of unknown size n
  int* start_time = new int[n];
  int* duration = new int[n];

  for (int i=0; i<n; i++)
    cin >> start_time[i];
  for (int i=0; i<n; i++)
    cin >> duration[i];

  Available_Workshops* ptr;
  ptr = initialize(start_time, duration, n);
  cout << CalculateMaxWorkshops(ptr) << endl;
  
  return 0;
}

