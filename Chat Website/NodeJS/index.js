

var express = require('express');
var bodyParser = require('body-parser');

var app = express();

var port = 8080;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded());

var router = express.Router();

var functionality = require('./functionality');

router.get('/help', functionality.help);
router.get('/login', functionality.login);
router.get('/rooms/list', functionality.listRooms);
router.get('/users/list', functionality.listUsers);
router.get('/room/:id/messages/list', functionality.listMessagesInRoom);
router.post('/room/:id/messages/add', functionality.addMessageToRoom);

functionality.mock();

app.use('/api', router);

app.listen(port);
console.log('Server up');