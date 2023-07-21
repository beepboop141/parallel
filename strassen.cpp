#include <iostream>
#include <sys/time.h>
#include <omp.h>
#include <vector> 
using namespace std; 
		
void printMat(const vector<vector<int>> &A) {
	for (int i=0;i<A.size();++i) {
		for (int j =0; j<A[0].size(); j++) {
			cout << A[i][j] << " ";
			}
		cout << endl; 
		}
}
vector<vector<int>> matMultiply(const vector<vector<int>>& A,const vector<vector<int>>& B) 
{
      int n = A.size(); 
	vector<vector<int>> result(n, vector<int>(n,0)); 
  	for (int i =0; i<n; ++i) {
		for (int j =0; j<n; ++j) {
			for (int k =0; k<n; ++k) {
				result[i][j] += A[i][k] * B[k][j]; 
			}
		}

	}
	return result; 

}


vector<vector<int>> matAdd(const vector<vector<int>> & A,const vector<vector<int>>& B) 
{
      int n = A.size(); 
	vector<vector<int>> result(n, vector<int>(n,0)); 
  	for (int i =0; i<n; ++i) {
		for (int j =0; j<n; ++j) {
		result[i][j] = A[i][j]+ B[i][j]; 
		}
	}
	return result; 
}	

vector<vector<int>> matSubtract(const vector<vector<int>>& A,const vector<vector<int>>& B) {
      int n = A.size(); 
	vector<vector<int>> result(n, vector<int>(n,0)); 
  	for (int i =0; i<n; ++i) {
		for (int j =0; j<n; ++j) {
		result[i][j] = A[i][j]- B[i][j]; 
		}
	}
	return result; 
}	

vector<vector<int>> strassenMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B) {
	int n = A.size(); 
	int half = n/2; 
	vector<vector<int>> A11(half, vector<int>(half)); 
	vector<vector<int>> A12(half, vector<int>(half));
       	vector<vector<int>> A21(half, vector<int>(half)); 
	vector<vector<int>> A22(half, vector<int>(half)); 
	vector<vector<int>> B11(half, vector<int>(half));
       	vector<vector<int>> B12(half, vector<int>(half)); 
	vector<vector<int>> B21(half, vector<int>(half));
       	vector<vector<int>> B22(half, vector<int>(half)); 

	if (n <= 2) {
		return matMultiply(A,B); 
	}

	for (int i =0; i<half; ++i) {
		for (int j =0; j<half; ++j) {
			A11[i][j] = A[i][j]; 
			A12[i][j] = A[i][j + half]; 
			A21[i][j] = A[i+half][j]; 
			A22[i][j] = A[i + half][j + half]; 
			B11[i][j] = B[i][j]; 
			B12[i][j] = B[i][j + half]; 
			B21[i][j] = B[i + half][j]; 
			B22[i][j] = B[i + half][j + half]; 
		}
	}

	vector<vector<int>> P1 = strassenMultiply(matAdd(A11, A22), matAdd(B11, B22)); 
	vector<vector<int>> P2 = strassenMultiply(matAdd(A21, A22), B11);
	vector<vector<int>> P3 = strassenMultiply(A11, matSubtract(B12, B22));
	vector<vector<int>> P4 = strassenMultiply(A22, matSubtract(B21, B11));
	vector<vector<int>> P5 = strassenMultiply(matAdd(A11, A12), B22);
	vector<vector<int>> P6 = strassenMultiply(matSubtract(A21, A11), matAdd(B11, B12));
	vector<vector<int>> P7 = strassenMultiply(matSubtract(A12, A22), matAdd(B21, B22));
    
	
	vector<vector<int>> C11 = matAdd(matSubtract(matAdd(P1, P4), P5), P7);
	vector<vector<int>> C12 = matAdd(P3, P5);
	vector<vector<int>> C21 = matAdd(P2, P4);
	vector<vector<int>> C22 = matAdd(matSubtract(matAdd(P1, P3), P2), P6);

    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            result[i][j] = C11[i][j];
            result[i][j + half] = C12[i][j];
            result[i + half][j] = C21[i][j];
            result[i + half][j + half] = C22[i][j];
        }
    }

    return result;
}



int main() {
	int n;
	cout << "Size n x n:  ";
	cin >> n; 
	double time;
	struct timeval ts, tf; 
	vector<vector <int>> A(n, vector<int>(n)); 
	vector<vector <int>> B(n, vector<int>(n)); 

	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {
			A[i][j] = rand()%100;
			B[i][j] = rand()%100;
		}
	}

	gettimeofday(&ts,NULL);
	vector<vector <int>> res(n, vector<int>(n));
        res= strassenMultiply(A,B);
	gettimeofday(&tf,NULL);
        time=(tf.tv_sec-ts.tv_sec)+(tf.tv_usec-ts.tv_usec)*0.000001;
	cout << "Time taken: " << time<< endl;
	if (n <=8) {
		cout << "A : " << endl;
		printMat(A); 
		cout << "B: " << endl;
		printMat(B);
		cout << "A x B = " << endl;
		printMat(res); 
	}
	return 0;
}



