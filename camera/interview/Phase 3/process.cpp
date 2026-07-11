#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  pid_t pid = fork();

  if (pid == 0) {
    // Child process
    std::cout << "Child process. PID: " << getpid()
              << ", Parent PID: " << getppid() << '\n';
  } else if (pid > 0) {
    // Parent process
    std::cout << "Parent process. PID: " << getpid() << ", Child PID: " << pid
              << '\n';
    wait(NULL); // Wait for child process to finish
  } else {
    std::cerr << "Fork failed!\n";
  }
  return 0;
}