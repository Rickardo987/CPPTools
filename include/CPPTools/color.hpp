//*  Copyright (c) 2021 Charles Richard Gonce
#pragma once
#include <array>

namespace CPPTools::color {
  const char                              BLACK[6]         = "\u001b[30m";
  const char                              RED[6]           = "\u001b[31m";
  const char                              GREEN[6]         = "\u001b[32m";
  const char                              ORANGE[6]        = "\u001b[33m";
  const char                              BLUE[6]          = "\u001b[34m";
  const char                              PURPLE[6]        = "\u001b[35m";
  const char                              CYAN[6]          = "\u001b[36m";
  const char                              WHITE[6]         = "\u001b[37m";
  const char                              BOLD[5]          = "\u001b[1m";
  const char                              UNDERLINE[5]     = "\u001b[4m";
  const char                              REVERSED[5]      = "\u001b[7m";
  const char                              RESET[5]         = "\u001b[0m";
  const char                              BRIGHT_RED[8]    = "\u001b[31;1m";
  const char                              BRIGHT_GREEN[8]  = "\u001b[32;1m";
  const char                              BRIGHT_ORANGE[8] = "\u001b[33;1m";
  const char                              BRIGHT_BLUE[8]   = "\u001b[34;1m";
  const char                              BRIGHT_PURPLE[8] = "\u001b[35;1m";
  const char                              BRIGHT_CYAN[8]   = "\u001b[36;1m";
  const char                              BRIGHT_WHITE[8]  = "\u001b[37;1m";
  const char                              LIGHT_GREY[8]    = "\u001b[90;1m";
  const std::array<const std::string, 16> colors{
    BLACK,         RED,         GREEN,        ORANGE,       BLUE,          PURPLE,
    CYAN,          WHITE,       BRIGHT_RED,   BRIGHT_GREEN, BRIGHT_ORANGE, BRIGHT_BLUE,
    BRIGHT_PURPLE, BRIGHT_CYAN, BRIGHT_WHITE, LIGHT_GREY
  }; // All avaliable colors (excluding control characters such as RESET and BOLD.)
} // namespace CPPTools::color