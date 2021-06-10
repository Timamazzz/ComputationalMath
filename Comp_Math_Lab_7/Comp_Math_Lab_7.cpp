#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// This functions finds the determinant of Matrix
double determinantOfMatrix(double mat[3][3])
{
    double ans;
    ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
        - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
        + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
    return ans;
}

// This function finds the solution of system of
// linear equations using cramer's rule
void findSolution(double coeff[3][4], double& a0, double& a1, double& a2)
{
    // Matrix d using coeff as given in cramer's rule
    double d[3][3] = {
        { coeff[0][0], coeff[0][1], coeff[0][2] },
        { coeff[1][0], coeff[1][1], coeff[1][2] },
        { coeff[2][0], coeff[2][1], coeff[2][2] },
    };
    // Matrix d1 using coeff as given in cramer's rule
    double d1[3][3] = {
        { coeff[0][3], coeff[0][1], coeff[0][2] },
        { coeff[1][3], coeff[1][1], coeff[1][2] },
        { coeff[2][3], coeff[2][1], coeff[2][2] },
    };
    // Matrix d2 using coeff as given in cramer's rule
    double d2[3][3] = {
        { coeff[0][0], coeff[0][3], coeff[0][2] },
        { coeff[1][0], coeff[1][3], coeff[1][2] },
        { coeff[2][0], coeff[2][3], coeff[2][2] },
    };
    // Matrix d3 using coeff as given in cramer's rule
    double d3[3][3] = {
        { coeff[0][0], coeff[0][1], coeff[0][3] },
        { coeff[1][0], coeff[1][1], coeff[1][3] },
        { coeff[2][0], coeff[2][1], coeff[2][3] },
    };

    // Calculating Determinant of Matrices d, d1, d2, d3
    double D = determinantOfMatrix(d);
    double D1 = determinantOfMatrix(d1);
    double D2 = determinantOfMatrix(d2);
    double D3 = determinantOfMatrix(d3);

    // Case 1
    if (D != 0) {
        // Coeff have a unique solution. Apply Cramer's Rule
        a0 = D1 / D;
        a1 = D2 / D;
        a2 = D3 / D;
        cout << "Value of a0 is : " << a0 << endl;
        cout << "Value of a1 is : " << a1 << endl;
        cout << "Value of a2 is : " << a2 << endl;
        cout << endl;

        cout << "The resulting approximating function: " << endl;
        cout << "y=" << a0 << "+" << a1 << "*x^2" << "+" << a2 << "*cos(x)" << endl;

    }
    // Case 2
    else {
        if (D1 == 0 && D2 == 0 && D3 == 0)
            cout << "Infinite solutions" << endl;
        else if (D1 != 0 || D2 != 0 || D3 != 0)
            cout << "No solutions" << endl;
    }

    
}

double Phi1(double x)
{
    return x * x;
}

double Phi2(double x)
{
    return cos(x);
}

int main()
{
    int i;
    int const N = 5;
    double x[N] = { 0,0.2,0.4,0.6,0.8 };
    double y[N] = { 2.1,2.01,2.30,2.71,3.25 };
    double sumPhi1 = 0;
    double sumPhi1_2 = 0;
    double sumPhi1Phi2 = 0;
    double sumPhi2 = 0;
    double sumPhi2_2 = 0;
    double a0=0, a1=0, a2=0;

    double sumY = 0;
    double sumPhi1Y = 0;
    double sumPhi2Y = 0;

    cout <<"Experimental points for the  function:" << endl;
    for (int i = 0; i != N; ++i)
        cout << "x" << i << " = " << x[i] << setw(3) << "y" << i << " = "<< y[i] << endl;

    cout << endl; 


    for (i = 0; i < N; i++)
    {
        sumPhi1 = sumPhi1 + Phi1(x[i]);
        sumPhi1_2 = sumPhi1_2 + Phi1(x[i]) * Phi1(x[i]);
        sumPhi1Phi2 = sumPhi1Phi2 + Phi1(x[i]) * Phi2(x[i]);
        sumPhi2 = sumPhi2 + Phi2(x[i]);
        sumPhi2_2 = sumPhi2_2 + Phi2(x[i]) * Phi2(x[i]);

        sumY = sumY + y[i];
        sumPhi1Y = sumPhi1Y + Phi1(x[i]) * y[i];
        sumPhi2Y = sumPhi2Y + Phi2(x[i]) * y[i];
    }

    // storing coefficients of linear equations in coeff matrix
    double coeff[3][4] = {
        { N, sumPhi1, sumPhi2, sumY },
        { sumPhi1, sumPhi1_2, sumPhi1Phi2, sumPhi1Y },
        { sumPhi2, sumPhi1Phi2, sumPhi2_2, sumPhi2Y },
    };

    findSolution(coeff, a0, a1, a2);
   

    cout << endl << "Experimental points for the approximating function:" << endl;
    for (int i = 0; i != N; ++i)
        cout << "x" << i << " = " << x[i] << setw(3) << "y" << i << " = " << a0 + a1 * pow(x[i], 2) + a2 * cos(x[i]) << endl;
    
    
    system("Pause");
}
