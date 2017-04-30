//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_INFORMATION_HPP_HPP
#define CPP_PLAZZA_INFORMATION_HPP_HPP

#include <array>

enum Information
{
  PHONE_NUMBER,
  EMAIL_ADDRESS,
  IP_ADDRESS
};

static const std::array<Information, 4>	TO_INFORMATION = {PHONE_NUMBER, EMAIL_ADDRESS, IP_ADDRESS};

#endif //CPP_PLAZZA_INFORMATION_HPP_HPP
