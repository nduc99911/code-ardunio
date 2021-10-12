const express = require('express')

const device = require('../controllers/device.controller')

const router = express.Router()

router.get('/getdata', device.getData)
router.get('/pushdata', device.pushData)
router.get('/create', device.createDevice)

module.exports = router