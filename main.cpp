//*  Copyright (c) 2021 Charles Richard Gonce

#include "include/CPPTools/CPPTools.hpp" //* This includes the whole library for you.
#include <iostream>

int main() {
  /*
  This is a demonstration of the safe input functions of the CPPTools library.

  The CPPTools library provides many tools, not just input tools. Full details can be found in the
  deoxygen documentation. main.cpp only demonstrates input functions.

  CPPTools was originally a high school project that has evoved slowly over the past two years. This
  is not to say I'm plagiarizing from myself, all of the input functions are new. The color
  definitions and debugging tools, however, were used in a different project. The code is still my
  original design, taking examples from StackOverflow here and there. References are provided under
  a REF: comment or via the @see directive where applicable.

  As this is a professional school project, it has been written with rigourous code style (see
  .clang-format) and is well documented in the common deoxygen comment style. This allows for
  autogenerated documentation as well as intellesense in common code editors such as vs code. The
  C++ standard library uses simular documentation style.

  Comments are best viewed color coded. I used "Better Comments" by Aaron Bond, a VS Code extension.
  This highlights certian comments in certian colors when a certian character is used. For example
  using '!' turns the line red. 'TODO' oarnge, and so on.
  */


  //! FEATURE ONE - Menu Selection.
  /*
  Provides a function to prompt the user via a menu. Pass a vector of strings (the options) and the
  function will prompt the user, ensure the input is valid, and then return the index of the
  selected option. You can also customize error messages. The menu is automatically sized depending
  on the number of options.
  Note: you must provide atleast 2 options and at most 9.
  */
  std::vector<std::string> options = { "Option A", "Option B", "Option C" }; // Options

  int menuSelection = CPPTools::input::menuSelection(options); // Prompt the user. 0-indexed

  std::cout << "You selected " << menuSelection << " -> \"" << options[menuSelection] << "\"."
            << std::endl;


  //! FEATURE TWO - Get Interger.
  /*
  Provoides a function to get an interger from the user. Unintresting at first glance, function
  arguments allow you to modify the minimum and maximum intergers allowed along with error messages.
  Note: Minimum value cannot be greater than the maximum value. Default is the min and max interger
  limits.
  */
  int intSelection = CPPTools::input::getIntSelective("Enter a number between 1-10: ", 10, 1);
  std::cout << "You entered: " << intSelection << std::endl;


  //! FEATURE THREE - Get Char.
  /*
  Provoides a function to get a char from the user. Again unintresting at first glance, function
  arguments allow you to modify the valid characters along with error messages.
  Note: Empty vector denotes any char as valid, and is the default param.
  */
  std::vector<char> validChars = { 'a', 'b', 'c' };
  char charSelection = CPPTools::input::getCharSelective("Enter a, b, or c: ", validChars);
  std::cout << "You entered: \'" << charSelection << "\'" << std::endl;


  //! FEATURE FOUR - Get Char Nonblocking.
  /*
  Arguably the most intresting of all the input functions. Via platform specific code, this function
  allows you to get a character from the user witthout requiring the user to press enter. The char
  is immediately flushed and returned to you as an int.
  It is returned as an int because special characters (such as function keys, esc, and the arrow
  keys) can be entered as well as the standard 26 engligh letters and 1-9. These keys have no formal
  symbol and should be checked via their corresponding ascii value according to an ascii chart. If
  you like, you can cast these to a char but as alluded to earlier, printing them to the console can
  produce unexpected behavior. Also, some keys work on lunux but not on windows and vise versa.
  Note: Returns NULL character (char '\0' or int 0) on error.
  */
  std::cout << "Press any key: ";
  intSelection = CPPTools::input::getCharUnbuffered();
  std::cout << std::endl
            << "You entered: \'" << (char) intSelection << "\' (ascii value " << intSelection << ")"
            << std::endl;


  //! ADDITIONAL FEATURES - Color
  /*
  This library also provides color codes.
  Note: Won't work on some more basic windows terminals. Should work universally on linux. Colors
  also appear differently on some systems, for example oarnge is sometimes yellow, idk.
  */
  std::cout << CPPTools::color::BLUE << "Color!" << CPPTools::color::RESET << std::endl;


  //! ADDITIONAL FEATURES - Print Bits
  /*
  Get the raw bits of any variable. Useful for debugging and teaching purposes.
  */
  auto bits = 'a';       // Print the bits of the 'a' char. Is an int internally with value 97.
  std::cout << "Bits: "; // auto optimizes this to a 1 byte int.
  CPPTools::tools::printBits(bits);

  //! ADDITIONAL FEATURES - Sleep
  /*
  Just sleeps or halts execution for the specified time in ms. Wrapper around a chrono function
  */
  std::cout << "Waiting 1 second... " << std::flush;
  CPPTools::tools::sleep(1000);
  std::cout << "Done!" << std::endl;

  std::cout << "Goodbye~" << std::endl;
  return EXIT_SUCCESS; // return 0
}