const debug = require('debug')('instruction-handlers')
const registers = require('./registers')
const { getMemory, setMemory } = require('./memory')
const {
  extractBits,
  zeroExtend,
  signExtend,
  leastSignificantBits,
  determineOperandType,
  setBit,
  parseAddressRegisterAndOffset
} = require('./utilities')

module.exports = {
  'add': (instruction) => {
    // c2 1f  add        d15,#0x1
    const register = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    debug(`${registers.pc.toString(16)} add ${register} ${value.toString(16)}`)
    registers[register] += value
    registers.pc += instruction.size
  },
  'addi': (instruction) => {
    // addi       d2,d2,#-0x4a
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const value = parseInt(instruction.operands[2], 10)
    debug(`${registers.pc.toString(16)} addi ${destinationRegister} ${sourceRegister} ${value.toString(16)}`)
    registers[destinationRegister] = zeroExtend(registers[sourceRegister] + signExtend(value, 'word'), 'word')
    registers.pc += instruction.size
  },
  'addih': (instruction) => {
    // Add Immediate High
    // addih      d15,d15,#0x8000
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const value = parseInt(instruction.operands[2])
    debug(`${registers.pc.toString(16)} addih ${destinationRegister} ${sourceRegister} ${value.toString(16)}`)
    registers[destinationRegister] = (registers[sourceRegister] + (value << 16)) >>> 0
    registers.pc += instruction.size
  },
  'addsc.a': (instruction) => {
    // addsc.a    a3,a15,d2,#0x0
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const dataRegister = instruction.operands[2]
    const value = parseInt(instruction.operands[3], 10)
    debug(`${registers.pc.toString(16)} addsc.a ${destinationRegister} ${sourceRegister} ${dataRegister} ${value.toString(16)}`)
    if (value === 0) { // do not bit shift unnecessarily
      registers[destinationRegister] = registers[sourceRegister] + registers[dataRegister]
    } else {
      registers[destinationRegister] = registers[sourceRegister] + (registers[dataRegister] << value)
    }
    registers.pc += instruction.size
  },
  'and': (instruction) => {
    // and        d0,d1
    // and        d15,#0x3
    const destinationRegister = instruction.operands[0]
    const secondOperandType = determineOperandType(instruction.operands[1])
    if (secondOperandType === 'value') {
      const valueA = registers[destinationRegister]
      const valueB = parseInt(instruction.operands[1])
      debug(`${registers.pc.toString(16)} and ${destinationRegister} ${valueA.toString(16)} ${valueB.toString(16)}`)
      registers[destinationRegister] = valueA & valueB
    } else {
      const sourceRegister = instruction.operands[1]
      const valueA = registers[destinationRegister]
      const valueB = registers[sourceRegister]
      debug(`${registers.pc.toString(16)} and ${destinationRegister} ${sourceRegister} ${valueA.toString(16)} ${valueB.toString(16)}`)
      registers[destinationRegister] = valueA & valueB
    }
    registers.pc += instruction.size
  },
  'and.ne': (instruction) => {
    // and.ne     d15,d1,d0
    // and.ne     d15,d0,#0x2
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const thirdOperand = instruction.operands[2]
    const thirdOperandType = determineOperandType(thirdOperand)
    const value = thirdOperandType === 'register' ? parseInt(registers[thirdOperand], 10) : parseInt(thirdOperand, 10)
    const notEqualResult = sourceRegister !== thirdOperand ? 1 : 0
    const valueFirstBit = extractBits(value, 0, 1)
    const result = (valueFirstBit & notEqualResult) ? 1 : 0
    debug(`${registers.pc.toString(16)} and.ne ${destinationRegister} ${sourceRegister} ${thirdOperand} ${value.toString(16)}`)
    registers[destinationRegister] = setBit(registers[destinationRegister], 0, result)
    registers.pc += instruction.size
  },
  'call': (instruction) => {
    const address = parseInt(instruction.operands[0], 16)
    const returnAddress = registers.pc + instruction.size
    debug(`${registers.pc.toString(16)} call ${address.toString(16)} ${returnAddress.toString(16)}`)
    registers.returnAddresses.push(returnAddress)
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
    // TODO: this is effectively a no-op?
    debug(`${registers.pc.toString(16)} dsync`)
    registers.pc += instruction.size
  },
  'extr.u': (instruction) => {
    // extr.u     d4, d4, 0, 8
    // extr.u     d0,d0,#0x1c,#0x4
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const position = parseInt(instruction.operands[2])
    const width = parseInt(instruction.operands[3])
    const value = extractBits(registers[sourceRegister], position, width)
    debug(`${registers.pc.toString(16)} extr.u ${destinationRegister} ${sourceRegister} ${position.toString(16)} ${width.toString(16)} ${value.toString(16)}`)
    registers[destinationRegister] = zeroExtend(value, 'word')
    registers.pc += instruction.size
  },
  'isync': (instruction) => {
    // isync
    // TODO: this is effectively a no-op?
    debug(`${registers.pc.toString(16)} isync`)
    registers.pc += instruction.size
  },
  'j': (instruction) => {
    // j          LAB_800007d0
    const address = parseInt(instruction.operands[0])
    debug(`${registers.pc.toString(16)} j ${address.toString(16)}`)
    registers.pc = address
  },
  'jeq': (instruction) => {
    // jeq        d15,#0x2,LAB_800007de
    const register = instruction.operands[0]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(secondOperand)
    const value = secondOperandType === 'value' ? signExtend(parseInt(secondOperand), 'byte') : signExtend(registers[secondOperand], 'byte')
    const address = parseInt(instruction.operands[2])
    debug(`${registers.pc.toString(16)} jeq ${register} ${value.toString(16)} ${address.toString(16)}`)
    if (registers[register] === value) {
      registers.pc = address
    } else {
      registers.pc += instruction.size
    }
  },
  'jge': (instruction) => {
    // jge        d15,#0x2,LAB_8000078a
    throw new Error('TODO')
    registers.pc += instruction.size
  },
  'jge.u': (instruction) => {
    // jge.u      d5,d15,LAB_80000606
    const registerA = instruction.operands[0]
    const valueA = registers[registerA]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(secondOperand)
    const valueB = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    const address = parseInt(instruction.operands[2], 16)
    debug(`${registers.pc.toString(16)} jge.u ${registerA} ${valueA.toString(16)} ${secondOperand} ${valueB.toString(16)} ${address.toString(16)}`)
    const conditionMet = secondOperandType === 'value' ? (valueA >= zeroExtend(valueB, 'word')) : (valueA >= valueB)
    if (conditionMet) {
      registers.pc = address // TODO: is it supposed to be this instead: PC = PC + sign_ext(disp15) * 2; ?
    } else {
      registers.pc += instruction.size
    }
  },
  'jlt.u': (instruction) => {
    // 3f 0f 0f 80     jlt.u      d15,d0,LAB_8000035a
    // bf 4f 09 80     jlt.u      d15,#0x4,LAB_800004de
    const registerA = instruction.operands[0]
    const valueA = registers[registerA]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(secondOperand)
    const valueB = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    const address = parseInt(instruction.operands[2], 16)
    debug(`${registers.pc.toString(16)} jlt.u ${registerA} ${valueA.toString(16)} ${secondOperand} ${valueB.toString(16)} ${address.toString(16)}`)
    const conditionMet = secondOperandType === 'value' ? (valueA < zeroExtend(valueB, 'word')) : (valueA < valueB)
    if (conditionMet) {
      registers.pc = address // TODO: is it supposed to be this instead: PC = PC + sign_ext(disp15) * 2; ?
    } else {
      registers.pc += instruction.size
    }
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
    debug(`${registers.pc.toString(16)} jne ${registerA} ${valueA.toString(16)} ${secondOperand} ${valueB.toString(16)} ${address.toString(16)}`)
    if (valueA !== valueB) {
      registers.pc = address // TODO: is it supposed to be this instead: PC = PC + sign_ext(disp15) * 2; ?
    } else {
      registers.pc += instruction.size
    }
  },
  'jnz': (instruction) => {
    // jnz        d4,LAB_8000063e
    const register = instruction.operands[0]
    const address = parseInt(instruction.operands[1])
    debug(`${registers.pc.toString(16)} jnz ${register} ${address.toString(16)}`)
    if (registers[register] !== 0) {
      registers.pc = address
    } else {
      registers.pc += instruction.size
    }
  },
  'jz': (instruction) => {
    // jz         d2,LAB_80000766
    const register = instruction.operands[0]
    const address = parseInt(instruction.operands[1])
    debug(`${registers.pc.toString(16)} jz ${register} ${address.toString(16)}`)
    if (registers[register] === 0) {
      registers.pc = address
    } else {
      registers.pc += instruction.size
    }
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
    const address = registers[addressRegister]
    debug(`${registers.pc.toString(16)} ld.bu ${destinationRegister} ${addressRegister} ${address.toString(16)} ${offset.toString(16)}`)
    registers[destinationRegister] = signExtend(getMemory(address + offset, 'byte'), 'byte')
    registers.pc += instruction.size
  },
  'ld.hu': (instruction) => {
    // ld.hu      d0,[a15]0x18
    const destinationRegister = instruction.operands[0]
    const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[1])
    debug(`${registers.pc.toString(16)} ld.hu ${destinationRegister} ${addressRegister} ${offset.toString(16)}`)
    registers[destinationRegister] = signExtend(getMemory(registers[addressRegister] + offset, 'half-word'), 'half-word')
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
    const destinationRegister = instruction.operands[0]
    const memoryLocation = instruction.operands[1]
    if (memoryLocation.indexOf('+') !== -1) {
      if (memoryLocation === '[a2+]') {
        registers[destinationRegister] = getMemory(registers.a2, 'word')
        registers.a2 += 1
      } else {
        throw new Error('TODO')
      }
    } else {
       const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[1])
       registers[destinationRegister] = getMemory(registers[addressRegister] + offset, 'word')
    }
    registers.pc += instruction.size
  },
  'lea': (instruction) => {
    // c5 0f 3f 00     lea        a15,0x3f
    // d9 00 20 87     lea        a0,[a0]0x7220
    // watch out for inconsistent a10/sp naming from rasm2 diassembly
    const destinationRegister = instruction.operands[0]
    const mode = isNaN(parseInt(instruction.operands[1])) ? 'addressRegisterAndOffset' : 'absolute'
    if (mode === 'absolute') {
      const value = parseInt(instruction.operands[1])
      debug(`${registers.pc.toString(16)} lea ${destinationRegister} ${value.toString(16)}`)
      registers[destinationRegister] = value
    } else {
      const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[1])
      debug(`${registers.pc.toString(16)} lea ${destinationRegister} ${addressRegister} ${offset.toString(16)}`)
      registers[destinationRegister] = registers[addressRegister] + offset
    }
    registers.pc += instruction.size
  },
  'loop': (instruction) => {
    // loop       a2,LAB_80000616
    const addressRegister = instruction.operands[0]
    const address = parseInt(instruction.operands[1], 16)
    debug(`${registers.pc.toString(16)} loop ${addressRegister} ${address.toString(16)} ${registers[addressRegister].toString(16)}`)
    if (registers[addressRegister] !== 0) {
      registers.pc = address
    } else {
      registers.pc += instruction.size
    }
    registers[addressRegister] -= 1
  },
  'mfcr': (instruction) => {
    // Move From Core Register
    // MFCR D[c], const16 (RLC)
    // Move the contents of the Core Special Function Register (CSFR), selected by the value const16, to data register D[c].
    // mfcr       d15,#0xfe08
    const dataRegister = instruction.operands[0]
    const value = instruction.operands[1]
    debug(`${registers.pc.toString(16)} mfcr ${dataRegister} ${value.toString(16)}`)
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
    const secondOperandType = determineOperandType(secondOperand)
    const value = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    debug(`${registers.pc.toString(16)} mov ${destinationRegister} ${secondOperand} ${value.toString(16)}`)
    registers[destinationRegister] = value // TODO: zero_extend/sign_extend or something
    registers.pc += instruction.size
  },
  'mov.a': (instruction) => {
    // 60 ff           mov.a      a15,d15
    // a0 04           mov.a      a4,#0x0
    const destinationRegister = instruction.operands[0]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(secondOperand)
    const value = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10) // TODO: i don't know the initial values of registers
    debug(`${registers.pc.toString(16)} mov.a ${destinationRegister} ${secondOperand} ${value.toString(16)}`)
    registers[destinationRegister] = value // TODO: zero_extend or something
    registers.pc += instruction.size
  },
  'mov.aa': (instruction) => {
    // 40 34           mov.aa     a4,a3
    // 40 34           mov.aa     a4,a3
    // 40 a2           mov.aa     a2,a10
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    debug(`${registers.pc.toString(16)} mov.aa ${destinationRegister} ${sourceRegister}`)
    registers[destinationRegister] = registers[sourceRegister]
    registers.pc += instruction.size
  },
  'mov.d': (instruction) => {
    // mov.d      d1,a3
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    debug(`${registers.pc.toString(16)} mov.d ${destinationRegister} ${sourceRegister}`)
    registers[destinationRegister] = registers[sourceRegister]
    registers.pc += instruction.size
  },
  'mov.u': (instruction) => {
    // mov.u      d0,#0xfd01
    const dataRegister = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    debug(`${registers.pc.toString(16)} mov.u ${dataRegister} ${value.toString(16)}`)
    registers[dataRegister] = zeroExtend(value, 'word')
    registers.pc += instruction.size
  },
  'movh': (instruction) => {
    // movh       d15,#0x8000
    const dataRegister = instruction.operands[0]
    const value = parseInt(instruction.operands[1], 10)
    debug(`${registers.pc.toString(16)} movh ${dataRegister} ${value.toString(16)}`)
    registers[dataRegister] = parseInt(`${value.toString(16)}0000`, 16)
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
    debug(`${registers.pc.toString(16)} movh.a ${addressRegister} ${value.toString(16)}`)
    registers[addressRegister] = parseInt(`${value.toString(16)}0000`, 16)
    registers.pc += instruction.size
  },
  'mtcr': (instruction) => {
    // mtcr       #0xfe00,d0
    const value = parseInt(instruction.operands[0])
    const dataRegister = instruction.operands[1]
    registers.cr[value] = registers[dataRegister]
    registers.pc += instruction.size
  },
  'ne': (instruction) => {
    // ne         d15,d1,#0x0
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const value = parseInt(instruction.operands[2])
    const result = registers[sourceRegister] !== value
    debug(`${registers.pc.toString(16)} ne ${destinationRegister} ${sourceRegister} ${value.toString(16)}`)
    registers[destinationRegister] = result ? 1 : 0
    registers.pc += instruction.size
  },
  'nop': (instruction) => {
    // nop
    debug(`${registers.pc.toString(16)} nop`)
    registers.pc += instruction.size
  },
  'or': (instruction) => {
    // a6 01           or         d1,d0
    // a6 0f           or         d15,d0
    // a6 f0           or         d0,d15
    // 0f 0f a0 10     or         d1,d15,d0
    if (instruction.operands.length === 3) {
      const destinationRegister = instruction.operands[0]
      const registerA = instruction.operands[1]
      const registerB = instruction.operands[2]
      const valueA = registers[registerA]
      const valueB = registers[registerB]
      debug(`${registers.pc.toString(16)} or ${destinationRegister} ${registerA} ${registerB} ${valueA.toString(16)} ${valueB.toString(16)}`)
      registers[destinationRegister] = (registers[registerA] | registers[registerB]) >>> 0
    } else {
      const destinationRegister = instruction.operands[0]
      const sourceRegister = instruction.operands[1]
      const valueA = registers[destinationRegister]
      const valueB = registers[sourceRegister]
      debug(`${registers.pc.toString(16)} or ${destinationRegister} ${sourceRegister} ${valueA.toString(16)} ${valueB.toString(16)}`)
      registers[destinationRegister] = (valueA | valueB) >>> 0
    }
    registers.pc += instruction.size
  },
  'or.ne': (instruction) => {
    // or.ne      d0,d15,#0x0
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const thirdOperand = instruction.operands[2]
    const thirdOperandType = determineOperandType(thirdOperand)
    const value = thirdOperandType === 'register' ? parseInt(registers[thirdOperand], 10) : parseInt(thirdOperand, 10)
    const notEqualResult = sourceRegister != thirdOperand
    const result = extractBits(value, 0, 1) | (notEqualResult ? 1 : 0)
    debug(`${registers.pc.toString(16)} or.ne ${destinationRegister} ${sourceRegister} ${thirdOperand} ${value.toString(16)}`)
    registers[destinationRegister] = setBit(registers[destinationRegister], 0, result ? 1 : 0)
    registers.pc += instruction.size
  },
  'ret': (instruction) => {
    // ret
    debug(`${registers.pc.toString(16)} ret`)
    registers.pc = registers.returnAddresses.pop()
  },
  'sel': (instruction) => {
    // sel        d2,d4,d15,#0x0
    const destinationRegister = instruction.operands[0]
    const pivotRegister = instruction.operands[1]
    const ifNonZeroRegister = instruction.operands[2]
    const ifZeroValue = instruction.operands[3]
    debug(`${registers.pc.toString(16)} sel ${destinationRegister} ${pivotRegister} ${ifNonZeroRegister} ${ifZeroValue}`)
    registers[destinationRegister] = registers[pivotRegister] === 0 ? ifZeroValue : registers[ifNonZeroRegister]
    registers.pc += instruction.size
  },
  'sh': (instruction) => {
    // 06 a2           sh         d2,#-0x6
    // 06 ef           sh         d15,#-0x2
    // 8f 00 01 00     sh         d0,d0,#0x10
    // 8f 0f 1f f0     sh         d15,d15,#-0x10
    if (instruction.operands.length === 2) {
      const register = instruction.operands[0]
      const amount = parseInt(instruction.operands[1])
      if (amount >= 0) {
        registers[register] = (registers[register] << amount)
      } else {
        registers[register] = (registers[register] >> Math.abs(amount))
      }
    } else {
      const destinationRegister = instruction.operands[0]
      const sourceRegister = instruction.operands[1]
      const amount = parseInt(instruction.operands[2])
      if (amount >= 0) {
        registers[destinationRegister] = registers[sourceRegister] << amount
      } else {
        registers[destinationRegister] = registers[sourceRegister] >> Math.abs(amount)
      }
    }
    registers.pc += instruction.size
  },
  'sha': (instruction) => {
    // sha        d15,d15,#0x8
    const destinationRegister = instruction.operands[0]
    const sourceRegister = instruction.operands[1]
    const amount = parseInt(instruction.operands[2])
    if (amount >= 0) {
      debug(`${registers.pc.toString(16)} sha ${destinationRegister} ${sourceRegister} ${amount}`)
      registers[destinationRegister] = zeroExtend(registers[sourceRegister] << amount, 'word')
    } else {
      throw new Error('TODO')
    }
    registers.pc += instruction.size
  },
  'st.a': (instruction) => {
    // f4 34           st.a       [a3],a4
    if (instruction.operands[0] === '[a3]') {
      const address = registers.a3
      const addressRegister = instruction.operands[1]
      const value = leastSignificantBits(registers[addressRegister], 16)
      debug(`${registers.pc.toString(16)} st.a ${instruction.operands[0]} ${addressRegister} ${value.toString(16)}`)
      setMemory(address, 'word', value)
    } else {
      throw new Error('TODO')
    }
    registers.pc += instruction.size
  },
  'st.b': (instruction) => {
    // 24 5f           st.b       [a5+],d15
    // 28 2f           st.b       [a15]#0x2,d15
    const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[0])
    const address = registers[addressRegister]
    const dataRegister = instruction.operands[1]
    const value = leastSignificantBits(registers[dataRegister], 8)
    debug(`${registers.pc.toString(16)} st.b ${addressRegister} ${address.toString(16)} ${offset} ${dataRegister} ${value.toString(16)}`)
    setMemory(address + offset, 'byte', value)
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
    if (instruction.operands[0] === '[a2+]') {
      const addressRegister = 'a2'
      const address = registers[addressRegister]
      const dataRegister = instruction.operands[1]
      const value = registers[dataRegister]
      debug(`${registers.pc.toString(16)} st.w ${addressRegister} ${dataRegister} ${value.toString(16)}`)
      setMemory(registers[addressRegister], 'word', value)
      registers[addressRegister] += 1
    } else {
      const [addressRegister, offset] = parseAddressRegisterAndOffset(instruction.operands[0])
      const address = registers[addressRegister]
      const dataRegister = instruction.operands[1]
      const value = registers[dataRegister]
      debug(`${registers.pc.toString(16)} st.w ${addressRegister} ${address} ${offset} ${dataRegister} ${value.toString(16)}`)
      setMemory(address + offset, 'word', value)
    }
    registers.pc += instruction.size
  },
  'sub': (instruction) => {
    // sub        d2,d0
    const register = instruction.operands[0]
    const secondOperand = instruction.operands[1]
    const secondOperandType = determineOperandType(secondOperand)
    const value = secondOperandType === 'register' ? registers[secondOperand] : parseInt(secondOperand, 10)
    debug(`${registers.pc.toString(16)} sub ${register} ${value.toString(16)}`)
    registers[register] -= value
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
    debug(`${registers.pc.toString(16)} sub.a ${addressRegister} ${value.toString(16)}`)
    if (addressRegister === 'sp') {
      registers.sp -= value
    } else {
      throw new Error('TODO')
    }
    registers.pc += instruction.size
  },
}
