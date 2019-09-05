const execa = require('execa')
const firmware = require('./firmware')

exports.disassembleRange = async (baseAddress, start, end) => {
  const slice = firmware.slice(start - baseAddress, end - baseAddress)
  const { stdout } = await execa('rasm2', ['-a', 'tricore', '-o', start, '-D', slice.toString('hex')])
  const lines = stdout.split('\n')
  return lines.map(line => {
    const [_, address, size, hex, assembly] = line.match(/0x([0-9a-f]*)\s*(\d)\s*([0-9a-f]*)\s*(.*)/)
    return {
      address,
      size: parseInt(size, 10),
      hex,
      assembly,
      mnemonic: assembly.split(' ')[0],
      operands: assembly.split(' ').slice(1).join(' ').split(', ')
    }
  })
}
