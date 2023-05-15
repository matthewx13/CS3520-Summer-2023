// This is question 2 for hw 1 (Matthew Xue - 5/11)
// Compound interest calculations to see how much the mona lisa would be worth if the interest rate ranged from 2 to 12%
#include <iostream>
#include <iomanip>
#include <cmath> // standard math library
using namespace std;

int main()
{
   double principal = 11; // initial amount before interest
   int current_year = 2023;
   int selling_year = 1626;

   // display headers
   cout << "Years" << setw(16) << "Interest Rate" << setw(30) << "Amount on Deposit" << endl;

   // set floating-point number format
   cout << fixed << setprecision( 2 );

   // calculate value of deposit depending on the interest rate, 
   // it ranges from 2 to 12% and it increase at a 0.5% increment
   for (double rate = 2.0; rate <= 12.0; rate += 0.5)
   {
      // calculate new amount for specified year
      double amount = principal * pow((1.0 + rate/100), current_year - selling_year);
      // display the year and the amount
      cout << current_year - selling_year << setw(15) << rate << "%" << setw(30) << amount << endl;
   } // end for 
} // end main


/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/