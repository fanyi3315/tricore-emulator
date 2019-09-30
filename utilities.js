const debug = require('debug')('utilities')

exports.extractBits = (value, position, width) => {
  debug(`extractBits ${value.toString(16)} ${position} ${width}`)
  return (value >> position) & (0 >> (32 - width))
}

exports.zeroExtend = (value) => {
  debug(`zeroExtend ${value.toString(16)}`)
  return value // TODO: what is zero extending?
}

exports.signExtend = (value) => {
  debug(`signExtend ${value.toString(16)}`)
  return value // TODO: what is sign extending?
}

exports.leastSignificantBits = (value, bits) => {
  debug(`leastSignificantBits ${value.toString(16)} ${bits}`)
  return value // TODO
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
