const config = require('./config')
const express = require('express')
const mongoose = require('mongoose')
mongoose.connect(config.url);

const app = express()
app.use(express.json())

const deviceRoute = require('./routes/device.route')

app.use('/device', deviceRoute)

app.listen(config.serverport, () => {
    console.log(`Example app listening at http://localhost:${config.serverport}`)
})