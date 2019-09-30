const debug = require('debug')('memory')
const firmware = require('./firmware')

const baseAddress = 0x80000000

const memory = {}

exports.getMemory = (address, size) => {
  debug(`getMemory ${address.toString(16)} ${size}`)
  if (memory[address.toString(16)] === undefined) {
    if (firmware[address - baseAddress] === undefined) {
      throw new Error('Undefined memory access')
    }
    if (size === 'byte') {
      memory[address.toString(16)] = firmware[address - baseAddress]
    } else if (size === 'half-word') {
      memory[(address).toString(16)] = firmware[address - baseAddress]
      memory[(address + 1).toString(16)] = firmware[address + 1 - baseAddress]
    } else if (size === 'word') {
      memory[(address).toString(16)] = firmware[address - baseAddress]
      memory[(address + 1).toString(16)] = firmware[address + 1 - baseAddress]
      memory[(address + 2).toString(16)] = firmware[address + 2- baseAddress]
      memory[(address + 3).toString(16)] = firmware[address + 3- baseAddress]
    }
  }
  if (size === 'word') {
    const byte1 = memory[address.toString(16)]
    const byte2 = memory[(address + 1).toString(16)]
    const byte3 = memory[(address + 2).toString(16)]
    const byte4 = memory[(address + 3).toString(16)]
    return ((byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1) >>> 0
  } else if (size === 'half-word') {
    const byte1 = memory[address.toString(16)]
    const byte2 = memory[(address + 1).toString(16)]
    return (byte2 << 8) | byte1
  } else if (size === 'byte') {
    return memory[address.toString(16)]
  } else {
    throw new Error('TODO')
  }
}

exports.setMemory = (address, size, value) => {
  debug(`setMemory ${address.toString(16)} ${size} ${value.toString(16)}`)
  if (size === 'byte') {
    memory[address] = value // TODO: respect size
  } else if (size === 'half-word') {
    memory[address] = value & 0xFF
    memory[address + 1] = value >> 8
  } else if (size === 'word') {
    memory[address] = value & 0xFF
    memory[address + 1] = value >> 8
    memory[address + 2] = value >> 16
    memory[address + 3] = value >> 24
  } else {
    throw new Error('TODO')
  }

}
