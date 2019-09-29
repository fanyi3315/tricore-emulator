const debug = require('debug')('memory')
const firmware = require('./firmware')

const baseAddress = 0x80000000

const memory = {
  '80018000': firmware[0x80018000 - baseAddress],
  '80018008': firmware[0x80018008 - baseAddress],
  '80018009': firmware[0x80018009 - baseAddress],
  '8001800a': firmware[0x8001800a - baseAddress],
  '8001800b': firmware[0x8001800b - baseAddress],

  '80028000': firmware[0x80028000 - baseAddress],
  '80028008': firmware[0x80028008 - baseAddress],
  '80028009': firmware[0x80028009 - baseAddress],
  '8002800a': firmware[0x8002800a - baseAddress],
  '8002800b': firmware[0x8002800b - baseAddress]
}

exports.getMemory = (address, size) => {
  debug(`getMemory ${address.toString(16)} ${size}`)
  return memory[address.toString(16)] // TODO: respect size
}

exports.setMemory = (address, size, value) => {
  debug(`setMemory ${address.toString(16)} ${size} ${value}`)
  memory[address] = value // TODO: respect size
}
