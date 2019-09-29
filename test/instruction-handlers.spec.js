const assert = require('assert')
const instructionHandlers = require('../instruction-handlers')
const registers = require('../registers')
const { disassembleInput } = require('../disassemble')

describe('instruction-handlers', () => {
  const resetRegisters = () => {
    registers.a0 = 0
    registers.a1 = 0
    registers.a2 = 0
    registers.a3 = 0
    registers.a4 = 0
    registers.a5 = 0
    registers.a6 = 0
    registers.a7 = 0
    registers.a8 = 0
    registers.a9 = 0
    registers.a10 = 0
    registers.a11 = 0
    registers.a12 = 0
    registers.a13 = 0
    registers.a14 = 0
    registers.a15 = 0
    registers.d0 = 0
    registers.d1 = 0
    registers.d2 = 0
    registers.d3 = 0
    registers.d4 = 0
    registers.d5 = 0
    registers.d6 = 0
    registers.d7 = 0
    registers.d8 = 0
    registers.d9 = 0
    registers.d10 = 0
    registers.d11 = 0
    registers.d12 = 0
    registers.d13 = 0
    registers.d14 = 0
    registers.d15 = 0
    registers.pc = 0x00000000
    registers.cr = {}
    registers.returnAddress = 0x00000000
  }

  beforeEach(() => {
    resetRegisters()
  })

  describe('add', () => {
    // Add the contents of data register D[a] to the contents of either data register D[b] (instruction format RR) or const9 (instruction format RC) and put the result in data register D[c]. The operands are treated as 32-bit integers, and the const9 value is sign-extended before the addition is performed.
    it('Add', async () => {
      const input = 'c21f'
      const start = 0x80000000
      const [instruction] = await disassembleInput(input)
      instructionHandlers[instruction.mnemonic](instruction)
      assert(registers.d15 === 0x01)
      assert(registers.pc === instruction.size)
    })
  })

  describe('addi', () => {
    // Add the contents of data register D[a] to the value const16, and put the result in data register D[c]. The operands are treated as 32-bit signed integers. The value const16 is sign-extended before the addition is performed.
    it('Add Immediate', async () => {
      const input = '1b 00 0c 00'
      const start = 0x80000000
      const [instruction] = await disassembleInput(input)
      instructionHandlers[instruction.mnemonic](instruction)
      assert(registers.d0 === 0xC0)
      assert(registers.pc === instruction.size)
    })
  })

  describe('addih', () => {
    // Left-shift const16 by 16 bits, add the contents of data register D[a], and put the result in data register D[c]. The operands are treated as signed integers.
    it('Add Immediate High', async () => {
      const input = '9b0f00f8'
      const start = 0x80000000
      const [instruction] = await disassembleInput(input)
      instructionHandlers[instruction.mnemonic](instruction)
      assert(registers.d15 === -0x80000000)
      assert(registers.pc === instruction.size)
    })
  })

  describe('addsc.a', () => {
    // For ADDSC.A, left-shift the contents of data register D[a] by the amount specified by n, where n can be 0, 1, 2, or 3. Add that value to the contents of address register A[b] and put the result in address register A[c].
    it('Add Scaled Index to Address', async () => {
      throw new Error('TODO')
    })
  })

  describe('and', () => {
    // Compute the bitwise AND of the contents of data register D[a] and the contents of either data register D[b] (instruction format RR) or const9 (instruction format RC) and put the result in data register D[c]. The const9 value is zero-extended.
    it('Bitwise AND', async () => {
      throw new Error('TODO')
    })
  })

  describe('and.ne', () => {
    // Calculate the logical AND of D[c][0] and the boolean result of the NE operation on the contents of data register D[a] and either data register D[b] (instruction format RR) or const9 (instruction format RC). Put the result in D[c][0]. All other bits in D[c] are unchanged. The const9 value is sign-extended.
    it('Not Equal Accumulating', async () => {
      throw new Error('TODO')
    })
  })

  describe('call', () => {
    // Add the value specified by disp24, multiplied by two and sign-extended, to the address of the CALL instruction and jump to the resulting address. The target address range is ±16 MBytes relative to the current PC. In parallel withthe jump, save the caller’s Upper Context to an available Context Save Area (CSA). Set register A[11] (return address) to the address of the next instruction beyond the call.
    it('Call', async () => {
      throw new Error('TODO')
    })
  })

  describe('calla', () => {
    // Jump to the address specified by disp24. In parallel with the jump, save the caller’s Upper Context to an available Context Save Area (CSA). Set register A[11] (return address) to the address of the next instruction beyond the call.
    it('Call Absolute', async () => {
      throw new Error('TODO')
    })
  })

  describe('calli', () => {
    // Jump to the address specified by the contents of address register A[a]. In parallel with the jump save the caller’s Upper Context to an available Context Save Area (CSA). Set register A[11] (return address) to the address of the next instruction beyond the call.
    it('Call Indirect', async () => {
      throw new Error('TODO')
    })
  })

  describe('dsync', () => {
    // Forces all data accesses to complete before any data accesses associated with an instruction, semantically after the DSYNC is initiated
    it('Synchronize Data', async () => {
      throw new Error('TODO')
    })
  })

  describe('extr.u', () => {
    // Extract the number of consecutive bits specified by either E[d][36:32] (instruction format RRRR) or width (instruction formats RRRW and RRPW) from D[a], starting at the bit number specified by either E[d][4:0] (instruction format RRRR), D[d][4:0] (instruction format RRRW) or pos (instruction format RRPW). Put the result in D[c], zero-extended (EXTR.U).
    it('Extract Bit Field Unsigned', async () => {
      throw new Error('TODO')
    })
  })

  describe('isync', () => {
    // The ISYNC instruction forces completion of all previous instructions, then flushes the CPU pipelines and invalidates any cached pipeline state before proceeding to the next instruction.
    it('Synchronize Instructions', () => {
      throw new Error('TODO')
    })
  })

  describe('j', () => {
    // Add the value specified by disp24, sign-extended and multiplied by 2, to the contents of PC and jump to that address.
    it('Jump Unconditional', async () => {
      throw new Error('TODO')
    })
  })

  describe('jeq', () => {
    // If the contents of D[a] are equal to the contents of either D[b] or const4, then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address. The const4 value is signextended.
    it('Jump if Equal', async () => {
      throw new Error('TODO')
    })
  })

  describe('jge', () => {
    // If the contents of D[a] are greater than or equal to the contents of either D[b] (instruction format BRR) or const4 (instruction format BRC), then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address. Operands are treated as signed 32-bit integers. The const4 value is sign-extended.
    it('Jump if Greater Than or Equal', async () => {
      throw new Error('TODO')
    })
  })

  describe('jge.u', () => {
    // If the contents of D[a] are greater than or equal to the contents of either D[b] (instruction format BRR) or const4 (instruction format BRC), then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address. Operands are treated as unsigned 32-bit integers. The const4 value is zero-extended.
    it('Jump if Greater Than or Equal Unsigned', async () => {
      throw new Error('TODO')
    })
  })

  describe('jlt.u', () => {
    // If the contents of D[a] are less than the contents of either D[b] (instruction format BRR) or const4 (instruction format BRC), then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address. The operands are treated as unsigned, 32-bit integers. The const4 value is zero-extended.
    it('Jump if Less Than Unsigned', async () => {
      throw new Error('TODO')
    })
  })

  describe('jne', () => {
    // If the contents of D[a] are not equal to the contents of either D[b] (instruction format BRR) or const4 (instruction format BRC), then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address. The const4 value is sign-extended.
    it('Jump if Not Equal', async () => {
      throw new Error('TODO')
    })
  })

  describe('jnz', () => {
    // If contents of either D[b] (instruction format SBR) or D[15] (instruction format SB) are not equal to zero, then add value specified by either disp4 (format SBR) or disp8 (format SB), zero-extended (disp4) or sign-extended (disp8) and multiplied by 2, to the contents of PC and jump to that address.
    it('Jump if Not Equal to Zero (16-bit)', async () => {
      throw new Error('TODO')
    })
  })

  describe('jz', () => {
    // If the contents of either D[15] (instruction format SB) or D[b] (instruction format SBR) are equal to zero, then add the value specified by either disp8 (format SB) or disp4 (format SBR), sign-extended (disp8) or zero-extended (disp4) and multiplied by 2, to the contents of PC, and jump to that address.
    it('Jump if Zero (16-bit)', async () => {
      throw new Error('TODO')
    })
  })

  describe('jz.a', () => {
    // BRR: If the contents of A[a] are equal to zero then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address.
    // SBR: If the contents of A[b] are equal to zero then add the value specified by disp4, zero-extended and multiplied by 2, to the contents of PC and jump to that address.
    it('Jump if Zero Address', async () => {
      throw new Error('TODO')
    })
  })

  describe('jz.t', () => {
    // BRN: If bit n of register D[a] is equal to zero then add the value specified by disp15, sign-extended and multiplied by 2, to the contents of PC and jump to that address.
    // SBRN: If bit n of register D[15] is equal to zero then add the value specified by disp4, zero-extended and multiplied by 2, to the contents of PC and jump to that address
    it('Jump if Zero Bit', async () => {
      throw new Error('TODO')
    })
  })

  describe('ld.a', () => {
    // Load the word contents of the memory location specified by the addressing mode into address register A[a].
    it('Load Word to Address Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('ld.bu', () => {
    // Load the byte contents of the memory location specified by the addressing mode, sign-extended or zero-extended, into data register D[a].
    it('Load Byte Unsigned', async () => {
      throw new Error('TODO')
    })
  })

  describe('ld.hu', () => {
    // Load the half-word contents of the memory location specified by the addressing mode, sign-extended, into data register D[a].
    it('Load Half-word Unsigned', async () => {
      throw new Error('TODO')
    })
  })

  describe('ld.w', () => {
    // Load word contents of the memory location specified by the addressing mode into data register D[a].
    it('Load Word', async () => {
      throw new Error('TODO')
    })
  })

  describe('lea', () => {
    // Compute the absolute (effective) address defined by the addressing mode and put the result in address register A[a].
    it('Load Effective Address', async () => {
      throw new Error('TODO')
    })
  })

  describe('loop', () => {
    // If address register A[b] is not equal to zero, then add the value specified by disp15, multiplied by two and signextended, to the contents of PC and jump to that address. The address register is decremented unconditionally
    it('Loop', async () => {
      throw new Error('TODO')
    })
  })

  describe('mfcr', () => {
    // Move the contents of the Core Special Function Register (CSFR), selected by the value const16, to data register D[c]. The CSFR address is a const16 byte offset from the CSFR base address. It must be word-aligned (the leastsignificant two bits equal zero). Nonaligned addresses have an undefined effect.
    it('Move From Core Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('mov', () => {
    // Move the contents of either data register D[b] (instruction format RR) or const16 (instruction format RLC), to data register D[c]. The value const16 is sign-extended to 32-bits before it is moved. The syntax is also valid with a register pair as a destination. If there is a single source operand, it is sign-extended to 64-bits. If the source is a register pair the contents of data register D[a] go into E[c][63:32] and the contents of data register D[b] into E[c][31:0].
    it('Move', async () => {
      throw new Error('TODO')
    })
  })

  describe('mov.a', () => {
    // Move the contents of data register D[b] to address register A[c].
    it('Move Value to Address Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('mov.aa', () => {
    // Move the contents of address register A[b] to address register A[c].
    it('Move Address from Address Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('mov.d', () => {
    // Move the contents of address register A[b] to data register D[c].
    it('Move Address to Data Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('mov.u', () => {
    // Move the zero-extended value const16 to data register D[c].
    it('Move Unsigned', async () => {
      throw new Error('TODO')
    })
  })

  describe('movh', () => {
    // Move the value const16 to the most-significant half-word of data register D[c] and set the least-significant 16-bits to zero.
    it.only('Move High', async () => {
      const input = '7b 00 00 2d'
      const start = 0x80000000
      const [instruction] = await disassembleInput(input)
      instructionHandlers[instruction.mnemonic](instruction)
      assert(registers.d2 === 0xD0000000)
      assert(registers.pc === instruction.size)
    })
  })

  describe('movh.a', () => {
    // Move the value const16 to the most-significant half-word of address register A[c] and set the least-significant 16-bits to zero.
    it('Move High to Address', async () => {
      throw new Error('TODO')
    })
  })

  describe('mtcr', () => {
    // Move the value in data register D[a] to the Core Special Function Register (CSFR) selected by the value const16. The CSFR address is a const16 byte offset from the CSFR base address. It must be word-aligned (the leastsignificant two bits are zero). Non-aligned address have an undefined effect.
    it(' Move To Core Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('ne', () => {
    // If the contents of data register D[a] are not equal to the contents of either data register D[b] (instruction format RR) or const9 (instruction format RC), set the least-significant bit of D[c] to one and clear the remaining bits to zero; otherwise clear all bits in D[c]. The const9 value is sign-extended.
    it('Not Equal', async () => {
      throw new Error('TODO')
    })
  })

  describe('nop', () => {
    // Used to implement efficient low-power, non-operational instructions.
    it('No Operation', async () => {
      throw new Error('TODO')
    })
  })

  describe('or', () => {
    // Compute the bitwise OR of the contents of data register D[a] and the contents of either data register D[b] (instruction format RR) or const9 (instruction format RC). Put the result in data register D[c]. The const9 value is zero-extended.
    it('Bitwise OR', async () => {
      throw new Error('TODO')
    })
  })

  describe('or.ne', () => {
    // Calculate the logical OR of D[c][0] and the Boolean result of the NE operation on the contents of data register D[a] and either data register D[b] (instruction format RR) or const9 (instruction format RC). Put the result in D[c][0]. All other bits in D[c] are unchanged.
    it('Not Equal Accumulating', async () => {
      throw new Error('TODO')
    })
  })

  describe('ret', () => {
    // Return from a function that was invoked with a CALL instruction. The return address is in register A[11] (return address). The caller’s upper context register values are restored as part of the return operation.
    it('Return from Call', async () => {
      throw new Error('TODO')
    })
  })

  describe('sel', () => {
    // If the contents of data register D[d] are non-zero, copy the contents of data register D[a] to data register D[c]; otherwise copy the contents of either D[b] (instruction format RRR) or const9 (instruction format RCR), to D[c]. The value const9 (instruction format RCR) is sign-extended.
    it('Select', async () => {
      throw new Error('TODO')
    })
  })

  describe('sh', () => {
    // Shift the value in D[a] by the amount specified by shift count. If the shift count specified through the contents of either D[b] (instruction format RR) or const9 (instruction format RC) is greater than or equal to zero, then left-shift. Otherwise right-shift by the absolute value of the shift count. Put the result in D[c]. In both cases the vacated bits are filled with zeros and the bits shifted out are discarded.
    // The shift count is a 6-bit signed number, derived from either D[b][5:0] or const9[5:0]. The range for the shift count is therefore -32 to +31, allowing a shift left up to 31 bit positions and to shift right up to 32 bit positions (Note that a shift right by 32 bits leaves zeros in the result).
    it('Shift', async () => {
      throw new Error('TODO')
    })
  })

  describe('sha', () => {
    // If shift count specified through contents of either D[b] (instruction format RR) or const9 (instruction format RC) is greater than or equal to zero, then left-shift the value in D[a] by the amount specified by shift count. The vacated bits are filled with zeros and bits shifted out are discarded. If the shift count is less than zero, right-shift the value in D[a] by the absolute value of the shift count. The vacated bits are filled with the sign-bit (the most significant bit) and bits shifted out are discarded. Put the result in D[c].
    // The shift count is a 6-bit signed number, derived from either D[b][5:0] or const9[5:0]. The range for shift count is therefore -32 to +31, allowing a shift left up to 31 bit positions and a shift right up to 32 bit positions (a shift right by 32 bits leaves all zeros or all ones in the result, depending on the sign bit). On all 1-bit or greater shifts (left or right), PSW.C is set to the logical-OR of the shifted out bits. On zero-bit shifts C is cleared.
    it('Arithmetic Shift', async () => {
      throw new Error('TODO')
    })
  })

  describe('st.a', () => {
    // Store the value in address register A[a] to the memory location specified by the addressing mode.
    it('Store Word from Address Register', async () => {
      throw new Error('TODO')
    })
  })

  describe('st.b', () => {
    // Store the byte value in the eight least-significant bits of data register D[a] to the byte memory location specified by the addressing mode.
    it('Store Byte', async () => {
      throw new Error('TODO')
    })
  })

  describe('st.w', () => {
    // Store the word value in data register D[a] to the memory location specified by the addressing mode
    it('Store Word', async () => {
      throw new Error('TODO')
    })
  })

  describe('sub', () => {
    // Subtract the contents of data register D[b] from the contents of data register D[a] and put the result in data register D[c]. The operands are treated as 32-bit integers
    it('Subtract', async () => {
      throw new Error('TODO')
    })
  })

  describe('sub.a', () => {
    // Subtract the contents of address register A[b] from the contents of address register A[a] and put the result in address register A[c].
    it('Subtract Address', async () => {
      throw new Error('TODO')
    })
  })
})