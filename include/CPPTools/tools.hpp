//*  Copyright (c) 2021 Charles Richard Gonce
#pragma once

#include <chrono>
#include <thread>

// REF: https://wiki.rdkcentral.com/display/RDK/Doxygen+Documentation+Guide (Doxygen)

namespace CPPTools::tools {
  /**
   * @brief Sleep for a given amount of time
   * @param time Time to sleep in milliseconds
   */
  inline void sleep(const unsigned int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
  }

  /**
   * @brief Print bytes of an object seperated into 8-bit chunks.
   * @param obj Object to print the bits of
   */
  template <typename T>
  void printBits(T const& obj) {
    for (size_t i = 0; i < sizeof(T); ++i) {
      for (size_t j = 0; j < 8; ++j) {
        std::cout << ((obj >> (i * 8 + j)) & 1);
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
} // namespace CPPTools::tools
