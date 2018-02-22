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
  /*
  cout << " --- w1[" << w1.start_t << "-" << w1.end_t << "]";
  cout << " vs w2[" << w2.start_t << "-" << w2.end_t << "] --- ";
  */
  //
  return (w1.start_t<w2.start_t)?
    ( (w1.end_t<=w2.start_t)? false: true ): 
    ( (w1.start_t>w2.start_t)? 
      ( (w1.start_t>=w2.end_t)? false: true): true );
  //
  /*
  if (w1.start_t<w2.start_t) {
    if (w1.end_t<=w2.start_t)
      return false;
    else
      return true;
  } else if (w1.start_t>w2.start_t) {
    if (w1.start_t>=w2.end_t)
      return false;
    else
      return true;
  } else
    return true;
  */    
}

bool is_overlaped_with_set(const Workshop& w, Available_Workshops* ptr, vector<int>& aws_id) {
  bool overlaped = false;
  for (auto ita_id = aws_id.begin(); ita_id<aws_id.end(); ita_id++)
    if (is_overlaped(ptr->ws[*ita_id],w)) {
      overlaped=true;
      break;
    }
  return overlaped;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
  int total = 0;
  
  for (int k = 0; k<ptr->n; k++) {
    vector<int> aws_id;
    aws_id.push_back(k);
    for (int i=0;i<ptr->n;i++) {
      if (aws_id[0]==i)
	continue;
      if ( !is_overlaped_with_set(ptr->ws[i],ptr,aws_id) )
	aws_id.push_back(i);
    }
    cout << "the final set k=" << k << " is for [";
    for (auto it=aws_id.begin();it<aws_id.end();it++)
      cout << *it <<",";
    cout << "]" << endl;
    total = (total<aws_id.size())? aws_id.size(): total;
  }
  cout << "the maximum total aws is: ";
  return total;
}

void comb(int N, int K)
{
  std::string bitmask(K, 1); // K leading 1's
  bitmask.resize(N, 0); // N-K trailing 0's
 
  // print integers and permute bitmask
  do {
    for (int i = 0; i < N; ++i) // [0..N-1] integers
      {
	if (bitmask[i]) std::cout << " " << i;
      }
    std::cout << std::endl;
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
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

  comb(n,n-1);
  /*  
      comb(5,4);
      comb(5,3);
      comb(5,2);
  */
  
  return 0;
}

