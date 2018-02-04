
var express = require('express');
var bodyParser = require('body-parser');

var app = express();

var port = 8080;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded());

var router = express.Router();

var functionality = require('./functionality');
var sqlservice = require('./sqlservice');

router.get('/help', functionality.help);

router.get('/register', functionality.register);
router.get('/login', functionality.login);

router.get('/todo/list', functionality.listTodos);
router.get('/user/list', functionality.listUsers);
router.get('/note/list', functionality.listNotes);
router.get('/event/list', functionality.listEvents);

router.get('/user/add', functionality.addUser);
router.get('/event/add', functionality.addEvent);
router.get('/todo/add', functionality.addTodo);
router.get('/note/add', functionality.addNote);

router.get('/todo/remove', functionality.removeTodo);
router.get('/user/remove', functionality.removeUser);
router.get('/event/remove', functionality.removeEvent);
router.get('/note/remove', functionality.removeNote);


sqlservice.initialize();

functionality.mock();

app.use('/api', router);

app.listen(port);
console.log('Server up');
