//#include <iostream>
//#include <math.h>
//
//using namespace std;
//
//int n;
//
//double xi[300];
//double yi[300];
//
//double distant2(double x1,double y1,double x2,double y2)
//{
//	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
//}
//
//int search(int i,int j)
//{
//	double mx = (xi[i] + xi[j]) / 2,my = (yi[i] + yi[j]) / 2;
//	double diff2 = distant2(mx,my,xi[i],yi[i]);
//
//	if(diff2 > 1.0)
//		return 1; //1ŒÂ‚¾‚¯
//	double len = sqrt(1 - diff2);
//	double diff = sqrt(diff2);
//	double dx = len * (yi[i] - my) / diff,dy = len * (xi[i] - mx) / diff;
//	
//	int sign[] = {1,-1};
//	int counter[2] = {0};
//	for(int s = 0; s < 2; s++)
//	{
//		double x = mx - sign[s] * dx,y = my + sign[s] * dy;
//
//		for(int k = 0; k < n; k++){
//			if(k == i || k == j){counter[s]++; continue;}
//			if((x-xi[k])*(x-xi[k]) + (y-yi[k])*(y-yi[k])  <= 1.0)
//				counter[s]++;
//		}
//	}
//
//	return max(counter[0],counter[1]);
//}
//
//
//
//int solve()
//{
//	for(int i = 0; i < n; i++){
//		cin >> xi[i] >> yi[i];
//	}
//
//	int count = 0;
//
//	for(int i = 0; i < n; i++){
//		for(int j = i+1; j < n; j++){
//			count = max(count,search(i,j));
//		}
//	}
//
//	return count;
//}
//
//int main() {
//  while (cin >>n,n) {
//    cout << solve() << endl;
//  }
//
//  return 0;
//}

/**
 *  Circle and Points (PKU 1981)
 *  by Kenji Inoue, 2007-01-05
 **/

#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> P;

#define EPS (1e-6)

P p[300];
P tmp;

int main() {
  int n;
  while (cin >> n, n) {
    for (int i=0; i<n; i++) {
		double x,y;
		 cin >> x >> y;
		p[i].real(x);p[i].imag(y);
    }

    int ans = 1;
    for (int i=0; i<n; i++) {
      for (int j=i+1; j<n; j++) {
        P v = p[i] - p[j];
        double absv = abs(v);
        if (absv > 2.0 + EPS) { continue; }

        P m = p[j] + (v / 2.0);
        P unv = (v * P(0, 1)) / absv; // unit normal vector
        P nv = sqrt(1.0 - absv*absv/4.0) * unv;
        for (int s=0; s<2; s++) {
          nv *= -1;
          P c = m + nv; // center point of the circle

          int cnt = 0;
          for (int k=0; k<n; k++) {
            // if (abs(p[k] - c) < 1.0 + EPS) { cnt++; } // too slow
            tmp = p[k] - c;
            if ( tmp.real()*tmp.real() + tmp.imag()*tmp.imag() < 1.0 + EPS ) { cnt++; }
          }
          if (cnt > ans) { ans = cnt; }
        }
      }
    }

    cout << ans << endl;
  }

  return 0;
}
