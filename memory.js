const memory = {}

exports.getMemory = (address, size) => {
  return memory[address] // TODO: respect size
}

exports.setMemory = (address, size, value) => {
  memory[address] = value // TODO: respect size
}
