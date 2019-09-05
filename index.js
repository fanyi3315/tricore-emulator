const registers = require('./registers')
const instructionHandlers = require('./instruction-handlers')
const { disassembleRange } = require('./disassemble')

const handleInstruction = (instruction) => {
  if (!instructionHandlers[instruction.mnemonic]) {
    throw new Error(`Instruction handler not defined for mnemonic ${instruction.mnemonic}`)
  }
  return instructionHandlers[instruction.mnemonic](instruction)
}

const buildInstructionsMap = (functionRanges) => {
  const instructionsMap = {}
  for (let i = 0; i < functionRanges.length; ++i) {
    for (let x = 0; x < functionRanges[i].assembly.length; ++x) {
      const address = parseInt(functionRanges[i].assembly[x].address, 16)
      instructionsMap[address] = functionRanges[i].assembly[x]
    }
  }
  return instructionsMap
}

const run = async () => {
  const baseAddress = 0x80000000
  const functionRanges = [
    {start: 0x80000238, end: 0x80000244},
    {start: 0x80000246, end: 0x800003ac},
    {start: 0x800003ac, end: 0x80000472},
    {start: 0x80000472, end: 0x800004a4},
    {start: 0x800004a4, end: 0x80000584},
    {start: 0x80000584, end: 0x80000608},
    {start: 0x80000608, end: 0x8000062e},
    {start: 0x8000062e, end: 0x80000680},
    {start: 0x80000680, end: 0x800006fe},
    {start: 0x800006fe, end: 0x80000726},
    {start: 0x80000726, end: 0x80000750},
    {start: 0x80000750, end: 0x8000076a},
    {start: 0x8000076a, end: 0x800007e2},
  ]
  for (let i = 0; i < functionRanges.length; ++i) {
    functionRanges[i].assembly = await disassembleRange(baseAddress, functionRanges[i].start, functionRanges[i].end)
  }
  const instructionsMap = buildInstructionsMap(functionRanges)
  registers.pc = 0x800003ac
  for (;;) {
    const instruction = instructionsMap[registers.pc]
    if (!instruction) {
      throw new Error(`Instruction not found at ${registers.pc.toString(16)}`)
    }
    handleInstruction(instruction)
    console.log(registers.pc.toString(16))
  }
}

run()
