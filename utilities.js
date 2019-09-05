exports.extractBits = (value, position, width) => value // TODO
exports.zeroExtend = (value) => value // TODO: what is zero extending?
exports.signExtend = (value) => value // TODO: what is sign extending?
exports.leastSignificantBits = (value, bits) => value // TODO
exports.determineOperandType = (operand) => isNaN(parseInt(operand, 10)) ? 'register' : 'value'
exports.parseAddressRegisterAndOffset = (operand) => {
  const [_, addressRegister, offset] = operand.split(' ')[0].match(/\[(a\d*)\](-?\d*)/)
  return [ addressRegister, offset ]
}
