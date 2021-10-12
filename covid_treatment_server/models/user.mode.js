const mongoose = require('mongoose')

const userSchema = new mongoose.Schema({
    id: String,
    email: String,
    password: String,
    fullName: String,
    phone: String,
    room: Number,
    key: String
})

const User = mongoose.model('User', userSchema, 'user')

module.exports = User