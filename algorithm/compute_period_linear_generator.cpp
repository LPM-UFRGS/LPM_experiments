#include <cmath>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

using Integer = long long;
using Vector = vector<Integer>;
using Matrix = vector<Vector>;

ostream& operator<<(ostream& out, const Matrix& A) {
	out << "[\n";
	for (const Vector& v: A) {
		for (int u: v) {
			out << "\t" << u;
		}
		out << "\n";
	}
	out << "]\n";
	return out;
}

Integer mul_inv(Integer a, Integer b)
{
	Integer b0 = b, t, q;
	Integer x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

//Group Generator to linear congruence recurrency  z[n] = (z[n-1] * a + c) mod m
class GroupGenerator {
public:
	friend Matrix pow(const GroupGenerator& G, const Matrix& A, Integer n);

	GroupGenerator(Integer a, Integer c, Integer m)
	: c(c), m(m), M(m + 1), z0(1)
	{
		A = {{1, 0},
		     {1, a}};
		inv();
		print();
	}

	Integer mulMod(Integer v1, Integer v2)
	{
		return ((v1 % m) * (v2 % m)) % m;
	}

	void inv() 
	{
		Integer x, y, z, w;

		Integer a = A[0][0];
		Integer b = A[0][1];
		Integer c = A[1][0];
		Integer d = A[1][1];

		Integer inv_a = mul_inv(a, m);
		Integer inv_c = mul_inv(c, m);


		Integer det =  (m + mulMod(b, inv_a) - mulMod(d, inv_c)) % m;
		Integer invDet = mul_inv(det, m);

		Integer det2 = (m - mulMod(b, inv_a) + mulMod(d, inv_c)) % m;
		Integer invDet2 = mul_inv(det2, m);

		z = mulMod(inv_a, invDet);
		x = mulMod(m - mulMod(d, inv_c), z);

		w = mulMod(inv_c, invDet2);
		y = mulMod(m - mulMod(b, inv_a), w);

		Ainv = {{x, y},
			{z, w}};
	}


	void print() {
		cout << "A = " << A;
		cout << "Ainv = " << Ainv;
	}

	Matrix& getA() {
		return A;
	}

	Matrix& getAinv() {
		return Ainv;
	}

	Matrix mul(const Matrix& A, const Matrix& B) const {
	return {{((A[0][0] * B[0][0]) % m + (A[0][1] * B[1][0]) % m) % m, 
		 ((A[0][0] * B[0][1]) % m + (A[0][1] * B[1][1]) % m) % m},
		{((A[1][0] * B[0][0]) % m + (A[1][1] * B[1][0]) % m) % m, 
		 ((A[1][0] * B[0][1]) % m + (A[1][1] * B[1][1]) % m) % m}};

	
	}

	Vector mul(const Matrix& A, const Vector& z) {
		return {((A[0][0] * z[0]) % m + (A[0][1] * z[1]) % m) % m, 
		((A[1][0] * z[0]) % m + (A[1][1] * z[1]) % m ) % m};
	}

	void setMaxRange(Integer MaxValue) {
		M = MaxValue;
	}

	void setZ0(Integer zo) {
		z0 = zo;
	}

	void set(Integer c_, Integer zo_) {
		c = c_;
		z0 = zo_;
	}

	Integer calcPeriod() {
		Integer T = littleStep();
		if (T > -1) return T;
		T = giantStep();
		return T;
	}

private:
	Integer littleStep() {
		Integer n = static_cast<Integer>(sqrt(M));		
		Vector z = {c, z0};
		H.clear();
		H[z[1]] = 0;
		for (Integer i = 1; i <= n; ++i) {
			z = mul(A, z);
			if (z[1] == z0) return i;
			if (H.find(z[1]) == H.end()) H[z[1]] = i;
		}
		return -1;
	}

	Integer giantStep() {
		Integer n = static_cast<Integer>(sqrt(M));
		Matrix B = pow(*this, Ainv, n);
		Vector z = {c, z0};
		for (Integer i = 1; i  <= n; ++i) {
			z = mul(B, z);
			if (H.find(z[1]) != H.end()) {
				if (H[z[1]] == n) return n;
				return i * n + H[z[1]];
			}
		}
		return -1;
	}

	Integer c;	
	Integer m;

	Integer M; //Max range search
	Integer z0;
	
	Matrix A;
	Matrix Ainv;
	std::map<Integer, Integer> H;
};


Matrix pow(const GroupGenerator& G, const Matrix& A, Integer n) {
	Matrix I{{1, 0},{0, 1}};
	if (n == 0) return I;
	if (n == 1) return A;

	Matrix v = pow(G, A, n / 2);

	if (n % 2) {
		return G.mul(G.mul(v, v), A);
	} 

	return G.mul(v, v);
}

int main()
{
	// Compute period of a congruence pseudo random number generator
	Integer a, c, m;	
	Integer z0;

	cout << "z[n] = (a * z[n - 1]  + c) mod m\n";
	cout << "a: "; cin >> a;
	cout << "c: "; cin >> c;
	cout << "m: "; cin >> m;

	cout << "Z[0]: "; cin >> z0;

	GroupGenerator G(a, c, m);

	G.setZ0(z0);

	cout << G.mul(G.getA(), G.getAinv()) << "\n";

	Integer T = G.calcPeriod();

	cout << "T = " << T << "\n";

	Integer z = z0;

	// Verify solution
	for (Integer i = 1; i <= T; ++i) {
		z = (a * z + c) % m;
		if (z == z0) cout << i << "\n";
	}
	return 0;
}
