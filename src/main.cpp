#include <elf.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

auto get_self_address() -> void* {
  auto maps = std::ifstream{"/proc/self/maps"};
  std::string line;
  std::getline(maps, line);
  std::cout << line << std::endl;

  auto address_hex = line.substr(0, line.find('-'));

  auto address_stream = std::stringstream{};
  address_stream << std::hex << address_hex;

  long address;
  address_stream >> address;

  return reinterpret_cast<void*>(address);
}

auto main() -> int {
  auto* addr = get_self_address();

  auto* header = reinterpret_cast<Elf64_Ehdr*>(addr);
  std::cout << std::hex << header->e_entry << std::endl;
  std::cout << std::hex << reinterpret_cast<void*>(main) << std::endl;
  return 0;
}
