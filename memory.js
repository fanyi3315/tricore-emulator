const debug = require('debug')('memory')
const firmware = require('./firmware')

const baseAddress = 0x80000000

const memory = {
  '80010100': firmware[0x80010100 - baseAddress],
  '80010101': firmware[0x80010101 - baseAddress],
  '80010102': firmware[0x80010102 - baseAddress],
  '80010103': firmware[0x80010103 - baseAddress],
  '80010104': firmware[0x80010104 - baseAddress],
  '80010105': firmware[0x80010105 - baseAddress],
  '80010106': firmware[0x80010106 - baseAddress],
  '80010107': firmware[0x80010107 - baseAddress],
  '80010108': firmware[0x80010108 - baseAddress],
  '80010109': firmware[0x80010109 - baseAddress],
  '8001010a': firmware[0x8001010a - baseAddress],
  '8001010b': firmware[0x8001010b - baseAddress],
  '8001010c': firmware[0x8001010c - baseAddress],
  '8001010d': firmware[0x8001010d - baseAddress],
  '8001010e': firmware[0x8001010e - baseAddress],
  '8001010f': firmware[0x8001010f - baseAddress],
  '80010110': firmware[0x80010110 - baseAddress],
  '80010111': firmware[0x80010111 - baseAddress],
  '80010112': firmware[0x80010112 - baseAddress],
  '80010113': firmware[0x80010113 - baseAddress],
  '80010114': firmware[0x80010114 - baseAddress],
  '80010115': firmware[0x80010115 - baseAddress],
  '80010116': firmware[0x80010116 - baseAddress],
  '80010117': firmware[0x80010117 - baseAddress],
  '80010118': firmware[0x80010118 - baseAddress],
  '80010119': firmware[0x80010119 - baseAddress],
  '8001011a': firmware[0x8001011a - baseAddress],
  '8001011b': firmware[0x8001011b - baseAddress],
  '8001011c': firmware[0x8001011c - baseAddress],
  '8001011d': firmware[0x8001011d - baseAddress],
  '8001011e': firmware[0x8001011e - baseAddress],
  '8001011f': firmware[0x8001011f - baseAddress],
  '80010120': firmware[0x80010120 - baseAddress],
  '80010121': firmware[0x80010121 - baseAddress],
  '80010122': firmware[0x80010122 - baseAddress],
  '80010123': firmware[0x80010123 - baseAddress],
  '80010124': firmware[0x80010124 - baseAddress],
  '80010125': firmware[0x80010125 - baseAddress],
  '80010126': firmware[0x80010126 - baseAddress],
  '80010127': firmware[0x80010127 - baseAddress],
  '80010128': firmware[0x80010128 - baseAddress],
  '80010129': firmware[0x80010129 - baseAddress],
  '8001012a': firmware[0x8001012a - baseAddress],
  '8001012b': firmware[0x8001012b - baseAddress],
  '8001012c': firmware[0x8001012c - baseAddress],
  '8001012d': firmware[0x8001012d - baseAddress],
  '8001012e': firmware[0x8001012e - baseAddress],
  '8001012f': firmware[0x8001012f - baseAddress],
  '80010130': firmware[0x80010130 - baseAddress],
  '80010131': firmware[0x80010131 - baseAddress],
  '80010132': firmware[0x80010132 - baseAddress],
  '80010133': firmware[0x80010133 - baseAddress],
  '80010134': firmware[0x80010134 - baseAddress],
  '80010135': firmware[0x80010135 - baseAddress],
  '80010136': firmware[0x80010136 - baseAddress],
  '80010137': firmware[0x80010137 - baseAddress],
  '80010138': firmware[0x80010138 - baseAddress],
  '80010139': firmware[0x80010139 - baseAddress],
  '8001013a': firmware[0x8001013a - baseAddress],
  '8001013b': firmware[0x8001013b - baseAddress],
  '8001013c': firmware[0x8001013c - baseAddress],
  '8001013d': firmware[0x8001013d - baseAddress],
  '8001013e': firmware[0x8001013e - baseAddress],
  '8001013f': firmware[0x8001013f - baseAddress],

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
  if (size === 'word') {
    const byte1 = memory[address.toString(16)]
    const byte2 = memory[(address + 1).toString(16)]
    const byte3 = memory[(address + 2).toString(16)]
    const byte4 = memory[(address + 3).toString(16)]
    return (byte4 << 24) + (byte3 << 16) + (byte2 << 8) + byte1
  } else if (size === 'half-word') {
    const byte1 = memory[address.toString(16)]
    const byte2 = memory[(address + 1).toString(16)]
    return (byte2 << 8) + byte1
    throw new Error('TODO')
  } else if (size === 'byte') {
    return memory[address.toString(16)]
  } else {
    throw new Error('TODO')
  }
}

exports.setMemory = (address, size, value) => {
  debug(`setMemory ${address.toString(16)} ${size} ${value}`)
  memory[address] = value // TODO: respect size
}
