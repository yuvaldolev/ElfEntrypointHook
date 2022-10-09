#include <elf.h>
#include <link.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "dobby.h"
#include "elf_util.hpp"

auto test(int argc, const char *const argv[]) -> int {
  printf("Replaced main of %s\n", argv[0]);
  return 0;
}

static auto get_self_address() -> void * {
  FILE *fp = fopen("/proc/self/maps", "r");
  if (nullptr == fp) {
    return nullptr;
  }

  ElfW(Addr) base_address;
  fscanf(fp, "%lx-", &base_address);

  return reinterpret_cast<void *>(base_address);
}

__attribute__((constructor)) static void init() {
  printf("Loaded\n");

  pid_t pid = getpid();
  std::string command = "cat /proc/" + std::to_string(pid) + "/maps";
  system(command.c_str());

  // auto *addr = get_self_address();
  // mprotect(addr, 4096, PROT_READ | PROT_WRITE);

  // printf("Base address: %p\n", addr);
  // auto *header = reinterpret_cast<ElfW(Ehdr) *>(addr);
  // printf("Entry: 0x%lx\n", header->e_entry);
  // header->e_entry = reinterpret_cast<ElfW(Addr)>(test);
  // printf("Replaced entry to: 0x%lx\n", header->e_entry);
  // sleep(500);
  //

  auto elf = SandHook::ElfImg{"main"};
  printf("Elf: %s\n", elf.name().c_str());
  void *main_address = elf.getSymbAddress("main");
  printf("main: %p\n", main_address);
  dobby_dummy_func_t original_main;
  DobbyHook(main_address, reinterpret_cast<dobby_dummy_func_t>(test),
            &original_main);
  printf("After hooking\n");
}
