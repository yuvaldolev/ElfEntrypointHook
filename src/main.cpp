#include <stdio.h>

auto main() -> int {
  printf("In main: %p\n", main);
  // header->e_entry = reinterpret_cast<ElfW(Addr)>(test);
  // std::cout << std::hex << header->e_entry << std::endl;
  // std::cout << std::hex << reinterpret_cast<void*>(main) << std::endl;
  return 0;
}
