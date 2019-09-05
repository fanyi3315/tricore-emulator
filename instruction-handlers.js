const registers = require('./registers')
const { getMemory, setMemory } = require('./memory')
const {
  extractBits,
  zeroExtend,
  signExtend,
  leastSignificantBits,
  determineOperandType,
  parseAddressRegisterAndOffset
} = require('./utilities')

module.exports = {
  'add': (instruction) => {
    // add        d0,#0x1
    const register = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    registers[register] += value
    registers.pc += instruction.size
  },
  'addi': (instruction) => {
    // addi       d2,d2,#-0x4a
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const value = parseInt(instruction.operands[2], 10)
    registers[destinationRegister] = registers[sourceRegister] + signExtend(value)
    registers.pc += instruction.size
  },
  'addih': (instruction) => {
    // Add Immediate High
    // addih      d15,d15,#0x8000
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const value = parseInt(instruction.operands[2])
    registers[destinationRegister] = registers[sourceRegister] + (value << 16)
    registers.pc += instruction.size
  },
  'addsc.a': (instruction) => {
    // addsc.a    a3,a15,d2,#0x0
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const dataRegister = instruction.operands[2]
    const value = parseInt(instruction.operands[3], 10)
    registers[destinationRegister] = sourceRegister + (dataRegister << value)
    registers.pc += instruction.size
  },
  'and': (instruction) => {
    // and        d0,d1
    // and        d15,#0x3
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'and.ne': (instruction) => {
    // and.ne     d15,d1,d0
    // and.ne     d15,d0,#0x2
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'call': (instruction) => {
    const address = parseInt(instruction.operands[0], 16)
    registers.returnAddress = registers.pc + instruction.size
    registers.pc = address
    // call       FUN_800004a4
  },
  'calla': (instruction) => {
    // calla      SUB_d0002c6e
    throw new Error('TODO')
  },
  'calli': (instruction) => {
    // calli      a15
    throw new Error('TODO')
  },
  'dsync': (instruction) => {
    // dsync
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'extr.u': (instruction) => {
    // extr.u     d0,d0,#0x1c,#0x4
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const position = parseInt(instruction.operands[2])
    const width = parseInt(instruction.operands[3])
    const value = extractBits(registers[sourceRegister], position, width)
    registers[destinationRegister] = zeroExtend(value)
    registers.pc += instruction.size
  },
  'isync': (instruction) => {
    // isync
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'j': (instruction) => {
    // j          LAB_800007d0
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jeq': (instruction) => {
    // jeq        d15,#0x2,LAB_800007de
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jge': (instruction) => {
    // jge        d15,#0x2,LAB_8000078a
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jge.u': (instruction) => {
    // jge.u      d5,d15,LAB_80000606
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jlt.u': (instruction) => {
    // 3f 0f 0f 80     jlt.u      d15,d0,LAB_8000035a
    // bf 4f 09 80     jlt.u      d15,#0x4,LAB_800004de
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jne': (instruction) => {
    // 5e 68           jne        d15,#0x6,LAB_80000418
    // 5f f0 0c 80     jne        d0,d15,LAB_80000418
    const registerA = instruction.operands[0]
    const valueA = registers[registerA]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(secondOperand)
    const valueB = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    const address = parseInt(instruction.operands[2], 16)
    if (valueA !== valueB) {
      registers.pc = address // TODO: is it supposed to be this instead: PC = PC + sign_ext(disp15) * 2; ?
    } else {
      registers.pc += instruction.size
    }
  },
  'jnz': (instruction) => {
    // jnz        d4,LAB_8000063e
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jz': (instruction) => {
    // jz         d2,LAB_80000766
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jz.a': (instruction) => {
    // jz.a       a3,LAB_80000364
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jz.t': (instruction) => {
    // jz.t       d4,#0x0,LAB_8000065e
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'ld.a': (instruction) => {
    // d8 01           ld.a       a15,[a10]#0x4=>local_4
    // c8 43           ld.a       a3,[a15]#0x10
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'ld.bu': (instruction) => {
    // 0c f0           ld.bu      d15,[a15]#0x0
    // 0c f1           ld.bu      d15,[a15]#offset DAT_80000001
    // 0c f3           ld.bu      d15,[a15]#offset DAT_80000003
    // 0c f6           ld.bu      d15,[a15]#0x6
    // 0c f9           ld.bu      d15,[a15]#offset DAT_80000009
    // 0c f9           ld.bu      d15,[a15]#offset DAT_80018009
    // 0c fb           ld.bu      d15,[a15]#offset DAT_8000000b                    = 80h
    // 0c fb           ld.bu      d15,[a15]#offset DAT_8001800b
    // 04 2f           ld.bu      d15,[a2+]
    // 04 4f           ld.bu      d15,[a4+]
    // 08 00           ld.bu      d0,[a15]#0x0                       = 30h
    // 08 00           ld.bu      d0,[a15]#0x0
    // 08 20           ld.bu      d0,[a15]#offset DAT_80000002
    // 08 80           ld.bu      d0,[a15]#offset DAT_80000008
    // 08 80           ld.bu      d0,[a15]#offset DAT_80018008
    // 08 a0           ld.bu      d0,[a15]#offset DAT_8000000a                     = 02h
    // 08 a0           ld.bu      d0,[a15]#offset DAT_8001800a
    // 09 f0 50 08     ld.bu      d0,[a15]offset DAT_80018010
    // 09 f0 52 08     ld.bu      d0,[a15]offset DAT_80018012
    // 09 f0 61 08     ld.bu      d0,[a15]0x21
    // 09 ff 5f 08     ld.bu      d15,[a15]0x1f
    // 09 ff 51 08     ld.bu      d15,[a15]offset DAT_80018011
    // 09 ff 53 08     ld.bu      d15,[a15]offset DAT_80018013
    // 09 ff 58 08     ld.bu      d15,[a15]offset DAT_80000018                     = 05h
    // 09 ff 58 08     ld.bu      d15,[a15]offset DAT_80018018
    const destinationRegister = instruction.operands[0]
    const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[1])
    registers[destinationRegister] = getMemory(registers[addressRegister] + offset, 'byte')
    registers.pc += instruction.size
  },
  'ld.hu': (instruction) => {
    // ld.hu      d0,[a15]0x18
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'ld.w': (instruction) => {
    // 4c 31           ld.w       d15,[a3]#0x4                       = 20h
    // 4c 31           ld.w       d15,[a3]#0x4                       = 30h    0
    // 4c 42           ld.w       d15,[a4]#0x8                       = 80h
    // 4c f1           ld.w       d15,[a15]#0x4
    // 19 40 04 00     ld.w       d0,[a4]0x4
    // 44 2f           ld.w       d15,[a2+]
    // 44 2f           ld.w       d15,[a2+]
    // 48 02           ld.w       d2,[a15]#0x0
    // 48 44           ld.w       d4,[a15]#0x10
    // 54 30           ld.w       d0,[a3]                            = 20h
    // 54 30           ld.w       d0,[a3]                            = 40h    @
    // 54 41           ld.w       d1,[a4]                        = 800007e8
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'lea': (instruction) => {
    // c5 0f 3f 00     lea        a15,0x3f
    // d9 00 20 87     lea        a0,[a0]0x7220
    const destinationRegister = instruction.operands[0]
    const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[1])
    registers[destinationRegister] = registers[addressRegister + offset]
    registers.pc += instruction.size
  },
  'loop': (instruction) => {
    // loop       a2,LAB_80000616
    const addressRegister = instruction.operands[0]
    const address = parseInt(instruction.operands[1], 16)
    if (registers[addressRegister] != 0) {
      registers.pc = registers.pc + signExtend(2 * address)
    }
    registers[addressRegister] -= 1
    registers.pc += instruction.size
  },
  'mfcr': (instruction) => {
    // Move From Core Register
    // MFCR D[c], const16 (RLC)
    // Move the contents of the Core Special Function Register (CSFR), selected by the value const16, to data register D[c].
    // mfcr       d15,#0xfe08
    const dataRegister = instruction.operands[0]
    const value = instruction.operands[1]
    registers[dataRegister] = registers.cr[value] // TODO: do not know the contents of CR
    registers.pc += instruction.size
  },
  'mov': (instruction) => {
    // 02 2f           mov        d15,d2
    // 02 28           mov        d8,d2
    // 02 82           mov        d2,d8
    // 02 f2           mov        d2,d15
    // 3b 00 00 52     mov        d5,#0x2000
    // 3b 00 01 40     mov        d4,#0x10
    // 3b 00 02 40     mov        d4,#0x20
    // 3b 00 04 40     mov        d4,#0x40
    // 3b 00 06 10     mov        d1,#0x60
    // 3b 50 00 f2     mov        d15,#0x2005
    // 3b 60 02 50     mov        d5,#0x26
    // 3b 80 00 50     mov        d5,#0x8
    // 3b d0 00 50     mov        d5,#0xd
    // 3b e0 00 50     mov        d5,#0xe
    // 3b f0 03 03     mov        d0,#0x303f
    // 82 00           mov        d0,#0x0
    // 82 0f           mov        d15,#0x0
    // 82 01           mov        d1,#0x0
    // 82 02           mov        d2,#0x0
    // 82 2f           mov        d15,#0x2
    // 82 03           mov        d3,#0x0
    // 82 3f           mov        d15,#0x3
    // 82 04           mov        d4,#0x0
    // 82 4f           mov        d15,#0x4
    // 82 05           mov        d5,#0x0
    // 82 06           mov        d6,#0x0
    // 82 08           mov        d8,#0x0
    // 82 14           mov        d4,#0x1
    // 82 18           mov        d8,#0x1
    // 82 55           mov        d5,#0x5
    // 82 64           mov        d4,#0x6
    // 82 65           mov        d5,#0x6
    // 82 75           mov        d5,#0x7
    // da da           mov        d15,#0xda
    const destinationRegister = instruction.operands[0]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(instruction.operands[2])
    const value = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    registers[destinationRegister] = value // TODO: zero_extend/sign_extend or something
    registers.pc += instruction.size
  },
  'mov.a': (instruction) => {
    // 60 ff           mov.a      a15,d15
    // a0 04           mov.a      a4,#0x0
    const destinationRegister = instruction.operands[0]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(instruction.operands[2])
    const value = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    registers[destinationRegister] = value // TODO: zero_extend or something
    registers.pc += instruction.size
  },
  'mov.aa': (instruction) => {
    // 40 34           mov.aa     a4,a3
    // 40 34           mov.aa     a4,a3
    // 40 a2           mov.aa     a2,a10
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'mov.d': (instruction) => {
    // mov.d      d1,a3
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'mov.u': (instruction) => {
    // mov.u      d0,#0xfd01
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'movh': (instruction) => {
    // movh       d15,#0x8000
    const dataRegister = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    registers[dataRegister] = parseInt(`${value.toString(16)}0000`, 16)
    registers.pc += instruction.size
    registers.pc += instruction.size
  },
  'movh.a': (instruction) => {
    // Move High to Address
    // Move the value const16 to the most-significant half-word of address register A[c] and set the least-significant 16-bits to zero
    // A[c] = {const16, 16’h0000};
    // MOVH.A A[c], const16 (RLC)
    // movh.a     a10,#0xd000
    const addressRegister = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    registers[addressRegister] = parseInt(`${value.toString(16)}0000`, 16)
    registers.pc += instruction.size
  },
  'mtcr': (instruction) => {
    // mtcr       #0xfe00,d0
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'ne': (instruction) => {
    // ne         d15,d1,#0x0
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'nop': (instruction) => {
    // nop
    registers.pc += instruction.size
  },
  'or': (instruction) => {
    // a6 01           or         d1,d0
    // a6 0f           or         d15,d0
    // a6 f0           or         d0,d15
    // 0f 0f a0 10     or         d1,d15,d0
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'or.ne': (instruction) => {
    // or.ne      d0,d15,#0x0
    throw new Error('TODO')
  },
  'ret': (instruction) => {
    // ret
    registers.pc = registers.returnAddress
  },
  'sel': () => {
    // sel        d2,d4,d15,#0x0
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'sh': (instruction) => {
    // 06 a2           sh         d2,#-0x6
    // 06 ef           sh         d15,#-0x2
    // 8f 00 01 00     sh         d0,d0,#0x10
    // 8f 0f 1f f0     sh         d15,d15,#-0x10
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'sha': (instruction) => {
    // sha        d15,d15,#0x8
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'st.a': (instruction) => {
    // 06 a2           sh         d2,#-0x6
    // 06 ef           sh         d15,#-0x2
    // 8f 00 01 00     sh         d0,d0,#0x10
    // 8f 0f 1f f0     sh         d15,d15,#-0x10
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'st.b': (instruction) => {
    // 24 5f           st.b       [a5+],d15
    // 28 2f           st.b       [a15]#0x2,d15
    const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[0])
    const dataRegister = instruction.operands[1]
    const value = leastSignificantBits(dataRegister, 8)
    setMemory(registers[addressRegister] + zeroExtend(offset), 'byte', value)
    registers.pc += instruction.size
  },
  'st.w': (instruction) => {
    // 59 02 24 60     st.w       [a0]0x1a4,d2
    // 59 a2 04 00     st.w       [a10]0x4,d2
    // 59 f2 2c 1b     st.w       [a15]-0x4f94,d2
    // 59 f2 38 a8     st.w       [a15]-0x7d48,d2
    // 59 ff f0 ef     st.w       [a15]-0x50,d15
    // 59 ff f0 ef     st.w       [a15]-0x50,d15       = 30h
    // 64 2f           st.w       [a2+],d15
    // 64 3f           st.w       [a3+],d15
    // 64 6f           st.w       [a6+],d15
    // 64 21           st.w       [a2+],d1
    // 74 31           st.w       [a3],d1
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'sub': (instruction) => {
    // sub        d2,d0
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'sub.a': (instruction) => {
    // Subtract Address
    // Subtract the contents of address register A[b] from the contents of address register A[a] and put the result in address register A[c].
    // SUB.A A[c], A[a], A[b] (RR)
    // A[c] = A[a] - A[b];
    // sub.a      a10,#0x40
    const addressRegister = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    if (addressRegister === 'sp') {
      registers.sp -= value
    } else {
      throw new Error('TODO')
    }
    registers.pc += instruction.size
  },
}
