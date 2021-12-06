//*  Copyright (c) 2021 Charles Richard Gonce
#pragma once

#include <algorithm>
#include <array>
#include <assert.h>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "tools.hpp"

// resources for getCharUnbuffered()
#if defined(__linux__) // LINUX
#include <termios.h>
#include <unistd.h>   // For STDIN_FILENO
#elif defined(_WIN32) // WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#endif

namespace CPPTools::input {
  /**
   * @brief Prompt the user to select an option from a list. (SEE @a options !)
   * @details Prompt the user to select an option from a list of std::string
   * options. Will not return until a valid option is entered.
   * @return The index of the selected option (0 indexed to correspond to the
   * option in options. Note: Prompts given to the user are 1 indexed for ease
   * of use.)
   * @attention @a options must contain atleast 2 options and be have no more
   * than 9 options.
   * @param options The list of options (std::string) to choose from. (MUST
   * CONTAIN ATLEAST TWO OPTIONS) (CANNOT BE GREATER THAN 9)
   * @param prompt Optional: The prompt to display to the user. (default:
   * "Select an option: ")
   * @param errorInvalid Optional: The error message to display when an invalid
   * option is entered. (default: "Please enter a valid option!")
   */
  int menuSelection(const std::vector<std::string> options,
                    const std::string              prompt       = "Select an option: ",
                    const std::string              errorInvalid = "Please enter a valid option!") {
    // Check conditions
    assert(options.size() > 1);
    assert(options.size() < 10);

    // Print Menu (1-indexed)
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
      std::cout << i + 1 << ": " << options[i] << std::endl;
    }

    // Get Selection
    int u_selection;
    while (true) {
      std::cout << prompt;
      std::cin >> u_selection;

      if (!std::cin.fail() && u_selection > 0 && u_selection <= static_cast<int>(options.size())) {
        break;
      }

      std::cin.clear(); // Clear the fail state.
      // Ignore the rest of the wrong user input, till the end of the line.
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << errorInvalid << std::endl;
    }

    return u_selection - 1; // Account for 0-indexing
  }

  /**
   * @brief Get an interger from the user.
   * @details Get an integer from the user while ensuring that the user enters a
   * valid integer and that it is within the specified range. Will not return
   * until a valid integer is entered.
   * @attention Error messages for input that is too big or too small will not
   * be shown if they are at default values (numeric limits. This is because
   * numbers bigger than this are automantically caught by cin.fail()).
   * @return The integer.
   * @param prompt Optional: The prompt to display to the user. (default: "Enter
   * an integer: ")
   * @param max Optional: The maximum value the user can enter. (default:
   * numeric_limits<int>::max())
   * @param min Optional: The minimum value the user can enter. (default:
   * numeric_limits<int>::min())
   * @param errorInvalid Optional: The error message to display if the user
   * enters an invalid input (not an integer). (default: "Invalid input. Try
   * again!")
   * @param errorTooBig Optional: The error message to display if the user
   * enters a value that is bigger than the specified maximum. (default: "Input
   * too big. Try again!")
   * @param errorTooSmall Optional: The error message to display if the user
   * enters a value that is smaller than the specified minimum. (default: "Input
   * too small. Try again!")
   */
  int getIntSelective(const std::string prompt        = "Enter an integer: ",
                      const int         max           = std::numeric_limits<int>::max(),
                      const int         min           = std::numeric_limits<int>::min(),
                      const std::string errorInvalid  = "Invalid input. Try again!",
                      const std::string errorTooBig   = "Input too big. Try again!",
                      const std::string errorTooSmall = "Input too small. Try again!") {
    assert(min < max);
    int p_input = 0;
    while (true) {
      std::cout << prompt;
      std::cin >> p_input;

      if (std::cin.fail()) {
        std::cin.clear(); // Clear the fail state.
        // Ignore the rest of the wrong user input, till the end of the line.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << errorInvalid << std::endl;
      } else if (p_input > max) {
        std::cout << errorTooBig << std::endl;
      } else if (p_input < min) {
        std::cout << errorTooSmall << std::endl;
      } else {
        break;
      }
    }
    return p_input;
  }

  /**
   * @brief Get a char from the user, optionaly checking input against a list of
   * valid characters.
   * @details This function will get a char from the user while ensuring that
   * the user enters a valid character (and optionally if that char is contained
   * within a list). Will not return until a valid character is entered.
   * @return The character.
   * @param prompt Optional: The prompt to display to the user. (default: "Enter
   * a character: ")
   * @param validChars Optional: The list of valid characters. To get any valid
   * character, use empty list ({}). (default: {})
   * @param errorInvalid Optional: The error message to display if the user
   * enters an invalid input (not a character). (default: "Input is not a
   * character. Try again!")
   * @param errorNotInList Optional: The error message to display if the user
   * enters a character that is not in the array of valid characters. (default:
   * "Invalid input. Try again!")
   */
  char getCharSelective(const std::string       prompt      = "Enter a char: ",
                        const std::vector<char> valid_chars = {},
                        const std::string errorInvalid   = "Input is not a character. Try again!",
                        const std::string errorNotInList = "Invalid input. Try again!") {
    char p_input;
    while (true) {
      std::cout << prompt;
      std::cin >> p_input;
      if (std::cin.fail()) {
        std::cin.clear(); // Clear the fail state.
        // Ignore the rest of the wrong user input, till the end of the line.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << errorInvalid << std::endl;
      } else if ((valid_chars.size() != 0) &&
                 (std::find(std::begin(valid_chars), std::end(valid_chars), p_input) ==
                  std::end(valid_chars))) {
        // If array isnt empty, and the input isnt in the array
        std::cout << errorNotInList << std::endl;
      } else {
        break;
      }
    }
    return p_input;
  }

  /**
   * @brief Get a key from the user without requiring enter. Works on Windows and Linux using
   * platform specific code. Ascii characters only.
   * @see
   * https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed/67038432#67038432.
   * @return The key pressed. '\0' (null byte) on error (ASCII 0)
   */
  int getCharUnbuffered() {
#if defined(__linux__)
    //* Linux
    // Should support everything, maybe not everything in certian rare cases.
    /**
     * Note: STDIN_FILENO is almost certianly 0, but im using it anyway just to be safe.
     * See
     * https://stackoverflow.com/questions/15102992/what-is-the-difference-between-stdin-and-stdin-fileno
     */

    // disable buffering (and echo)
    struct termios terminal_config;                     // struct to hold the terminal config
    tcgetattr(STDIN_FILENO, &terminal_config);          // get terminal attributes
    terminal_config.c_lflag &= ~(ICANON | ECHO);        // disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &terminal_config); // set terminal attributes
    setbuf(stdin, NULL);                                // clear buffer (redundant?)

    int key = static_cast<int>(std::getchar()); // get the key

    // re-enable buffering
    terminal_config.c_lflag |= (ICANON | ECHO); // turn on (re-enable) line buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &terminal_config); // set terminal attributes
    return key;
#elif defined(_WIN32)
    //* Michaelsoft Binbows
    // Supported all the way back and including Windows 2000.
    KEY_EVENT_RECORD keyevent;
    INPUT_RECORD     irec;
    DWORD            events;
    HANDLE           hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE) { // Ensure handle is valid
      return '\0';                        // Error
    }

    while (true) {
      bool rc = ReadConsoleInput(hStdin, &irec, 1, &events); // Read input
      if (!rc) {
        return '\0';
      }
      if (irec.EventType == KEY_EVENT && irec.Event.KeyEvent.bKeyDown) { // If key pressed
        keyevent = irec.Event.KeyEvent;
        return static_cast<char>(keyevent.uChar.AsciiChar); // This conversion should work...
      }
      CPPTools::tools::sleep(1); // Sleep for 1ms
      // 100% CPU didn't seem to occur with testing, but it's still probably a good idea to sleep.
    }
#else
    //* Other
    //! NOT IMPLEMENTED
    static_assert(false, "getCharUnbuffered() not implemented for this platform!");
    return '\0';
#endif // Windows/Linux
  }
} // namespace CPPTools::input
