#include <chrono>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#define FIXED_FLOAT(x) std::fixed <<std::setprecision(2)<<(x)
#define NORMAL(x) std::fixed <<std::setprecision(0)<<(x)

using namespace std;

int random(int, int);

int main(int argc, char* argv[]) {
  int answer = 0;
  auto timer = std::chrono::high_resolution_clock::now();  // Init timer

  float elapsedTime = 0.0, recordTime = 999.9;

  string input = "";

  while (true) {
    int number = random(1, 99);

    cout << "What is the cubit root of " << NORMAL(pow(number, 3)) << "? ";
    timer = std::chrono::high_resolution_clock::now();

    getline(cin, input);
    if (input.length() == 1) {
      if (input[0] == 'q') break;
    }

    // This code converts from string to number safely.
    stringstream myStream(input);
    if (myStream >> answer) {
      // get elapsed miliseconds
      elapsedTime = (chrono::duration_cast<chrono::milliseconds>(
                        chrono::high_resolution_clock::now() - timer)
                        .count())/1000;

      if (answer == number) {
        cout << "Yep, that is correct!" << endl;
        if (elapsedTime < recordTime) {
          recordTime = elapsedTime;
          cout << "This is your best time yet " << FIXED_FLOAT(elapsedTime) << " ms" << endl;
        }
      } else {
        cout << "Nope, it is " << number << endl;
      }
    } else {
      cout << "Invalid number" << endl;
      cout << "Press 'q' to quit." << endl;
    }
  }
  return 0;
}

int random(int min, int max) {
  static bool first = true;
  if (first) {
    srand(time(NULL));  // seeding for the first time only!
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}