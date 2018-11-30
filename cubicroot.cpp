#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
bool voice_output = false;

int random(int, int);
void say(const char*);

int main(int argc, char** argv) {
  int answer = 0;
  auto timer = std::chrono::high_resolution_clock::now();  // Init timer

  float elapsedTime = 0.0, recordTime = 999.9;

  string input = "";

  while (true) {
    int number = random(1, 99);
    if (argc > 1) {
      if (string(argv[1]) == "listen")
        voice_output = true;
      else {
        std::cerr << "Usage: " << argv[0] << " [listen]" << std::endl;
        return 1;
      }
    }
    char buffer[50];
    sprintf(buffer, "What is the cubic root of %.0f? ", pow(number, 3));
    say(buffer);
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
                         .count()) /
                    1000;

      if (answer == number) {
        say("Yes, that is correct!\n");
        if (elapsedTime < recordTime) {
          recordTime = elapsedTime;
          sprintf(buffer, "This is your best time yet %.2f seconds!\n",
                  elapsedTime);
          say(buffer);
        }
      } else {
        sprintf(buffer, "Nope, it is  %d\n", number);
        say(buffer);
        cout << "Nope, it is " << number << endl;
      }
    } else {
      say("Invalid number");
      say("Press 'q' to quit.\n");
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

void say(const char* msg) {
  cout << msg;

  if (voice_output) {
    string cmd = "say ";
    string arg = msg;
    int rv = system((cmd + arg).c_str());
    if (rv != 0) {
      std::cout << "Say failed with result code: " << rv << "\n";
    }
  }
}