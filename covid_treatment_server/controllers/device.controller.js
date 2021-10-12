const Device = require('../models/device.model')

module.exports.createDevice = (req, res) => {
    var newDevice = {
        _id: req.query.key,
        room: req.query.room,
    };
    Device.create(newDevice)
}

module.exports.pushData = (req, res) => {
    var data = {
        $push: {
            spO2: [
                {
                    value: req.query.spO2,
                    time: new Date()
                }
            ],
            heartbeat: [
                {
                    value: req.query.heartbeat,
                    time: new Date()
                }
            ],
            hypothermia: [
                {
                    value: req.query.hypothermia,
                    time: new Date()
                }
            ],
        }
    };
    Device.updateOne({ _id: req.query.key }, data, function (err, res) {
        if (err) throw err;
        console.log("1 document updated");
    });
}

module.exports.getData = async(req, res) => {
    let id = req.query.key
    res.send(await Device.findById(id).exec())
}