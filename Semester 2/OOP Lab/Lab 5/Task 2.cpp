#include <iostream>
using namespace std;

class LoanHelper {
private:
    const float interest_rate = 0.005;
    float loan_amount;
    int months;

public:
    LoanHelper(float loan_amount, int months) {
        this->loan_amount = loan_amount;
        this->months = months;
    }

    void calculateMonthlyPayment() {
        float total_payment = (loan_amount / months) + ((loan_amount / months) * interest_rate);
        cout << "You have to pay " << total_payment << " every month for " << months << " months to repay your loan" << endl;
    }
};

int main() {
    LoanHelper loan(10000, 10);
    loan.calculateMonthlyPayment();
    return 0;
}
