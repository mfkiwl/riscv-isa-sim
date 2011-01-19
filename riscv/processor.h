#ifndef _RISCV_PROCESSOR_H
#define _RISCV_PROCESSOR_H

#include "decode.h"
#include <cstring>
#include "trap.h"
#include "mmu.h"

class sim_t;

class processor_t
{
public:
  processor_t(sim_t* _sim, char* _mem, size_t _memsz);
  void init(uint32_t _id);
  void step(size_t n, bool noisy);

private:
  sim_t* sim;

  // architected state
  reg_t XPR[NXPR];
  freg_t FPR[NFPR];

  // privileged control registers
  reg_t pc;
  reg_t epc;
  reg_t badvaddr;
  reg_t cause;
  reg_t evec;
  reg_t tohost;
  reg_t fromhost;
  reg_t pcr_k0;
  reg_t pcr_k1;
  uint32_t id;
  uint32_t sr;
  uint32_t count;
  uint32_t compare;
  uint32_t interrupts_pending;

  // unprivileged control registers
  uint32_t fsr;

  // # of bits in an XPR (32 or 64). (redundant with sr)
  int xprlen;

  // shared memory
  mmu_t mmu;

  // counters
  reg_t counters[32];

  // functions
  void set_sr(uint32_t val);
  void set_fsr(uint32_t val);
  void take_trap(trap_t t, bool noisy);
  void disasm(insn_t insn, reg_t pc);

  friend class sim_t;
};

#endif
