const debug = require('debug')('registers')

const handler = {
  get: function (obj, prop) {
    if (prop === 'sp') {
      prop = 'a10'
    }
    const value = obj[prop]
    if (prop !== 'cr' && prop !== 'returnAddresses') {
      if (value === undefined) {
        throw new Error(`Attempt to read undefined from register ${prop}`)
      }
      if (isNaN(value)) {
        throw new Error(`Attempt to read NaN from register ${prop}`)
      }
    }
    if (prop !== 'pc' && prop !== 'returnAddresses') {
      debug(`getRegister ${prop} ${value.toString(16)}`)
    }
    return value
  },
  set: function (obj, prop, value) {
    if (prop === 'sp') {
      prop = 'a10'
    }
    if (prop !== 'pc') {
      debug(`setRegister ${prop} ${value.toString(16)}`)
    }
    if (isNaN(value)) {
      console.log(`Attempt to set register ${prop} to NaN`)
    }
    if (value === undefined) {
      throw new Error(`Attempt to set register ${prop} to undefined`)
    }
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
    '65032': 0, // TODO: this is an assumption
    '65024': 0 // TODO: this is an assumption
  },

  'returnAddresses': []
}, handler)

module.exports = registers
