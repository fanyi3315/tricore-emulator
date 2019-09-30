const debug = require('debug')('utilities')

exports.extractBits = (value, position, width) => {
  debug(`extractBits ${value.toString(16)} ${position} ${width}`)
  const mask = (1 << (width - position)) - 1
  return (value >> position) & mask
}

exports.zeroExtend = (value, size) => { // TODO; this whole function is terrible
  debug(`zeroExtend ${value.toString(16)}`)
  /*if (size === 'word') {
    const expectedLength = 8 // 32 bits
    const length = Math.abs(value).toString(16).length
    const difference = expectedLength - length
    const input = `${value.toString(16)}${'0'.repeat(difference)}`
    debug(`zeroExtend ${value.toString(16)} ${input}`)
    const signedInteger = parseInt(`${value.toString(16)}${'0'.repeat(difference)}`, 16)
    return signedInteger >>> 0
  } else {
    throw new Error('TOOO')
  }*/
  return value
}

exports.signExtend = (value, size) => {
  debug(`signExtend ${value.toString(16)} ${size}`)
  if (size === 'byte') {

  } else if (size === 'half-word') {

  } else if (size === 'word') {

  } else {
    throw new Error('TODO')
  }
  return value
}

exports.leastSignificantBits = (value, bits) => {
  debug(`leastSignificantBits ${value.toString(16)} ${bits}`)
  return value // TODO
}

exports.setBit = (value, position, bit) => {
  debug(`setBit ${value.toString(16)} ${position} ${bit}`)
  const mask = value << position
  return (value & ~mask) | ((bit << position) & mask)
}

exports.determineOperandType = (operand) => isNaN(parseInt(operand, 10)) ? 'register' : 'value'

exports.parseAddressRegisterAndOffset = (operand) => {
  debug(`parseAddressRegisterAndOffset ${operand}`)
    operand = operand.replace('sp', 'a10') // watch out for sp/a10 naming debacle
  if (operand.match(/^\[(a\d*)\]$/)) {
    return [ operand.replace('[', '').replace(']', ''), 0]
  }
  const addressRegisterAndOffset = operand.split(' ')[0]
  const [_, addressRegister, offset] = addressRegisterAndOffset.match(/\[(a\d*)\](-?\d*)/)
  return [ addressRegister, parseInt(offset, 10) ]
}
