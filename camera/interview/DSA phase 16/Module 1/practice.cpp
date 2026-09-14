#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void findMaxMin(vector<int> &a) {
  int min = INT_MAX;
  int max = INT_MIN;
  for (int i = 0; i < a.size(); i++) {
    if (min > a[i]) {
      min = a[i];
    } else {
      max = a[i];
    }
  }
  cout << "Min is " << min << " Max is " << max;
}

void selectionSort(vector<int> &a) {
  int n = a.size();
  int min = 0;

  for (int i = 0; i < n - 1; i++) {
    min = i;
    for (int j = i + 1; j < n; j++) {
      if (a[j] < a[min]) {
        min = j;
      }
    }
    swap(a[i], a[min]);
  }

  for (auto x : a) {
    cout << x << " " << endl;
  }
}

void bubbleSort(vector<int> &a) {

  int n = a.size();
  bool s = false;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (a[j] > a[j + 1]) {
        s = true;
        swap(a[j], a[j + 1]);
      }
    }
    if (!s) {
      cout << "already sorted";
      break;
    }
  }

  for (auto x : a) {
    cout << x << " " << endl;
  }
}

int main() {

  vector<int> a = {5, 2, 3, 4};
  bubbleSort(a);
  return 0;
}