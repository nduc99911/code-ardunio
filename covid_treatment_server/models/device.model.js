const mongoose = require('mongoose')

const deviceSchema = new mongoose.Schema({
    _id: String,
    room: Number,
    spO2: [
        {
            value: Number,
            time: Date
        }
    ],
    heartbeat: [
        {
            value: Number,
            time: Date
        }
    ],
    hypothermia: [
        {
            value: Number,
            time: Date
        }
    ],
})

const Device = mongoose.model('Patient', deviceSchema, 'patient')

module.exports = Device