
const sqlservice = require('./sqlservice');

var functionality = {}

var users = []
var todos = []
var notes = []
var events = []

var tokens = {}

var nextUserId = 0

var setCORSHeaders = function(res) {
	res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE'); // If needed
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,contenttype'); // If needed
    res.setHeader('Access-Control-Allow-Credentials', true); // If needed
}

var getUserByToken = function(token) {
	return tokens[token]
}

var getUserByName = function(name) {
	for (user of users) {
		if (user.name == name) {
			return user
		}
	}
	return undefined
}

var generateToken = function()
{
	token = ""
	token += Math.random().toString(36).substr(2)
	token += Math.random().toString(36).substr(2)
	return token
}

var validateToken = function(token) {
	if (token == undefined || token == null)
		return false

	for (user of users) {
		if (user.token == token)
			return true
	}
	return false
}

functionality.help = function(req, res) {
	res.json(
		[
			{ 
				url: '/help',
				type: 'GET',
				param: []
			},
			{ 
				url: '/register',
				type: 'POST',
				param: ['name', 'pass', 'email']
			},
			{ 
				url: '/login',
				type: 'GET',
				param: ['name', 'pass']
			},
			{ 
				url: '/todo/list',
				type: 'GET',
				param: ['token']
			},
			{ 
				url: '/todo/add',
				type: 'POST',
				param: ['token', 'todo']
			},
			{ 
				url: '/todo/remove',
				type: 'POST',
				param: ['token', 'id']
			},
			{ 
				url: '/event/list',
				type: 'GET',
				param: ['token']
			},
			{ 
				url: '/event/add',
				type: 'POST',
				param: ['token', 'event']
			},
			{ 
				url: '/event/remove',
				type: 'POST',
				param: ['token', 'id']
			},
			{ 
				url: '/note/list',
				type: 'GET',
				param: ['token']
			},
			{ 
				url: '/note/add',
				type: 'GET',
				param: ['token', 'note']
			},
			{ 
				url: '/note/remove',
				type: 'POST',
				param: ['token', 'id']
			},
		]
	)
}

functionality.register = function(req, res) {
	setCORSHeaders(res)

	if (req.query.name == null || req.query.name == undefined || req.query.pass == null || req.query.pass == undefined) {
		res.json("Invalid register (bad username or password)")
		return 
	}

	
	new_user = {
		name: req.query.name,
		pass: req.query.pass,
		email: req.query.email
	}
	
	var printAndReturn = function(err, rows) {
		if(rows != undefined && rows.length > 0) {
			res.json("Username already taken")
			return
		}

	}

	sqlservice.getUserForRegister(printAndReturn, req.query.name)

	var addAndReturn = function(errs, rrows) {
		console.log(rrows)
		tkn = generateToken()
		tokens[tkn] = rrows[0].id
		res.json(tkn)
	}
		
	sqlservice.addUser(addAndReturn, new_user)
}

functionality.login = function(req, res) {
	setCORSHeaders(res)

	if (req.query.name == null || req.query.name == undefined
			|| req.query.pass == null || req.query.pass == undefined) {
		res.json("INVALID LOGIN")
		return
	}

	var printAndReturn = function(err, rows) {
		if (rows == undefined || rows.length < 1) 
    		res.json("No such user in the database")
    	else {
			tkn = generateToken()
			tokens[tkn] = rows[0].id
			res.json(tkn)
		}
	}

	sqlservice.getUserForLogin(printAndReturn, req.query.name, req.query.pass)
}

// all 4 list functions 
functionality.listUsers = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	var id = 23;
	sqlservice.getUserById(printAndReturn, id)
}

functionality.listTodos = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}

	var id = tokens[req.query.token];
	sqlservice.getTodosById(printAndReturn, id)
}

functionality.listTodoItems = function(req, res) {
	setCORSHeaders(res)
	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}

	var id = tokens[req.query.token];
	sqlservice.getTodoItemsById(printAndReturn, id)
}

functionality.listNotes = function(req, res) {
	setCORSHeaders(res)
	
	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	
	var id = tokens[req.query.token];
	sqlservice.getNotesById(printAndReturn, id)
}

functionality.listEvents = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}

	var id = tokens[req.query.token];
	sqlservice.getEventsById(printAndReturn, id)
}
// end all 4 list functions


// all 4 add functions
functionality.addUser = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}

	user = {};
	sqlservice.addUser(printAndReturn, user)
}
 
functionality.addEvent = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}

	event = {
		id: tokens[req.query.token],
		title: req.query.title,
		day: req.query.day,
		month: req.query.month,
		year: req.query.year,
		hour: req.query.hour,
		tag: req.query.tag,
		place: req.query.place
	};
	sqlservice.addEvent(printAndReturn, event)
}
 
functionality.addTodo = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	todo = {
		id: 55,
		name: "TEXTSAMPLE",
		tag: "blue"
	};
	sqlservice.addTodo(printAndReturn, todo)
}

functionality.addTodoItem = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	item = {
		id: 35,
		content: "ITEMSAPLCE",
		checked: "Blue"
	};
	sqlservice.addTodoItem(printAndReturn, item)
}

functionality.addNote = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	note = {
		id: tokens[req.query.token],
		name: req.query.title,
		content: req.query.content
	}
	sqlservice.addNote(printAndReturn, note)
}
// end all add functions


// all 4 delete functions
functionality.removeUser = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	var id = tokens[req.query.token];
	sqlservice.removeUserById(printAndReturn, id)
}

functionality.removeNote = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json("Note removed")
	}
	var id = tokens[req.query.token]
	var title = req.query.title
	var content = req.query.content
	
	sqlservice.removeNoteById(printAndReturn, id, title, content)
}

functionality.removeTodo = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json("Todo removed")
	}
	var id = tokens[req.query.token];
	sqlservice.removeTodoById(printAndReturn, id)
}

functionality.removeTodoItem = function(req, res) {
	setCORSHeaders(res)

	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	var id = tokens[req.query.token];
	sqlservice.removeTodoItemById(printAndReturn, id)
}

functionality.removeEvent = function(req, res) {
	setCORSHeaders(res)
	
	
	var printAndReturn = function(err, rows) {
		console.log(rows)
		res.json(rows)
	}
	var id = tokens[req.query.token];
	var title = req.query.title;
	var day = req.query.day;
	var month = req.query.month;
	var year = req.query.year;

	sqlservice.removeEventById(printAndReturn, id, title, day, month, year)
}

// end all 4 delete functions
functionality.mock = function() {
}



/*
functionality.listMessagesInRoom = function(req, res) {
	setCORSHeaders(res);

	if (validateToken(req.query.token)) {
		roomId = req.params.id

		messagesSummary = []
		// build a list of users with (id, name)
		for (message of rooms[roomId].messages) {
			messagesSummary.push({
				id: message.id,
				user: {
					id: message.user.id,
					name: message.user.name
				},
				content: message.content
			})
		}

		res.json(messagesSummary);
	}
	else {
		res.json("NOPE INVALID TOKEN")
	}
}

functionality.addMessageToRoom = function(req, res) {
	setCORSHeaders(res);

	roomId = req.params.id
	poster = getUserByToken(req.body.token)

	if (poster == undefined) {
		res.json("NOPE, NOT LOGGED IN OR INVALID TOKEN")
	}
	else {
		rooms[roomId].messages.push({
			id: rooms[roomId].messages.length,
			user: poster,
			content: req.body.content
		})

		res.json("OK");
	}
}

functionality.mock = function() {

	var admin = {
		id: 0,
		name: "Admin",
		pass: "boss",
		token: generateToken()
	}

	var message1 = {
		id: 0,
		user: admin,
		content: "Hi, my name is admin."
	}

	var message2 = {
		id: 1,
		user: admin,
		content: "This room has been created."
	}

	var globalroom = {
		id: 0,
		name: "Global Room",
		users: [admin],
		messages: [message1, message2]
	}

	users[nextUserId++] = admin
	rooms[nextRoomId++] = globalroom
}
*/

module.exports = functionality