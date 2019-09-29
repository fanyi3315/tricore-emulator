const debug = require('debug')('registers')

const handler = {
  get: function (obj, prop) {
    return obj[prop]
  },
  set: function (obj, prop, value) {
    debug(`setRegister ${prop} ${value.toString(16)}`)
    obj[prop] = value
  }
}

const registers =  new Proxy({
  'a0': 0,
  'a1': 0,
  'a2': 0,
  'a3': 0,
  'a4': 0,
  'a5': 0,
  'a6': 0,
  'a7': 0,
  'a8': 0,
  'a9': 0,
  'a10': 0, // sp
  'a11': 0,
  'a12': 0,
  'a13': 0,
  'a14': 0,
  'a15': 0,

  'd0': 0,
  'd1': 0,
  'd2': 0,
  'd3': 0,
  'd4': 0,
  'd5': 0,
  'd6': 0,
  'd7': 0,
  'd8': 0,
  'd9': 0,
  'd10': 0,
  'd11': 0,
  'd12': 0,
  'd13': 0,
  'd14': 0,
  'd15': 0,

  'pc': 0x00000000,
  'cr': {
    '65032': 0 // TODO: this is an assumption
  },

  'returnAddress': 0x00000000
}, handler)

module.exports = registers
