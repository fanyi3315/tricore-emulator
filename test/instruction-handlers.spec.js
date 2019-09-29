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
    it('should add value to register', async () => {
      const input = 'c21f'
      const start = 0x80000000
      const [instruction] = await disassembleInput(input)
      instructionHandlers.add(instruction)
      assert(registers.d15 === 0x01)
      assert(registers.pc === 0x02)
    })
  })

  describe('addi', () => {

  })

  describe('addih', () => {

  })

  describe('addsc.a', () => {

  })

  describe('and', () => {

  })

  describe('and.ne', () => {

  })

  describe('call', () => {

  })

  describe('calla', () => {

  })

  describe('calli', () => {

  })

  describe('dsync', () => {

  })

  describe('extr.u', () => {

  })

  describe('isync', () => {

  })

  describe('j', () => {

  })

  describe('jeq', () => {

  })

  describe('jge', () => {

  })

  describe('jge.u', () => {

  })

  describe('jlt.u', () => {

  })

  describe('jne', () => {

  })

  describe('jnz', () => {

  })

  describe('jz', () => {

  })

  describe('jz.a', () => {

  })

  describe('jz.t', () => {

  })

  describe('ld.a', () => {

  })

  describe('ld.bu', () => {

  })

  describe('ld.hu', () => {

  })

  describe('ld.w', () => {

  })

  describe('lea', () => {

  })

  describe('loop', () => {

  })

  describe('mfcr', () => {

  })

  describe('mov', () => {

  })

  describe('mov.a', () => {

  })

  describe('mov.aa', () => {

  })

  describe('mov.d', () => {

  })

  describe('mov.u', () => {

  })

  describe('movh', () => {

  })

  describe('movh.a', () => {

  })

  describe('mtcr', () => {

  })

  describe('ne', () => {

  })

  describe('nop', () => {

  })

  describe('or', () => {

  })

  describe('or.ne', () => {

  })

  describe('ret', () => {

  })

  describe('sel', () => {

  })

  describe('sh', () => {

  })

  describe('sha', () => {

  })

  describe('st.a', () => {

  })

  describe('st.b', () => {

  })

  describe('st.w', () => {

  })

  describe('sub', () => {

  })

  describe('sub.a', () => {

  })
})