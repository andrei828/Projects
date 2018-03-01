
var functionality = {};

var rooms = []
var users = []

var nextUserId = 0
var nextRoomId = 0

var setCORSHeaders = function(res) {
	res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE'); // If needed
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,contenttype'); // If needed
    res.setHeader('Access-Control-Allow-Credentials', true); // If needed
}

var getUserByToken = function(token) {
	for (user of users) {
		if (user.token == token) {
			return user
		}
	}
	return undefined
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
				url: '/login',
				type: 'GET',
				param: []
			},
			{ 
				url: '/rooms/list',
				type: 'GET',
				param: ['token']
			},
			{ 
				url: '/users/list',
				type: 'GET',
				param: ['token']
			},
			{ 
				url: '/room/:id/messages/list',
				type: 'GET',
				param: ['token']
			},
			{ 
				url: '/room/:id/messages/add',
				type: 'POST',
				param: ['token', 'content']
			},
		]
	)
}

functionality.login = function(req, res) {
	setCORSHeaders(res)

	usr = getUserByName(req.query.name)
	tkn = generateToken()

	if (req.query.name == null || req.query.name == undefined
			|| req.query.pass == null || req.query.pass == undefined) {
		res.json("NOPE INVALID LOGIN")
		return
	}

	if (usr == undefined) {
		usr = {
			id: nextUserId++,
			name: req.query.name,
			pass: req.query.pass,
			token: tkn
		}
		users.push(usr)
		res.json(tkn)
	}
	else {
		usr.token = tkn
		res.json(tkn)
	}
}

functionality.listRooms = function(req, res) {
	setCORSHeaders(res)

	if (validateToken(req.query.token)) {
		// build a list of rooms with (id, name)
		roomSummary = []
		for (room of rooms) {
			roomSummary.push({
				id: room.id,
				name: room.name
			})
		}

		res.json(roomSummary)
	}
	else {
		res.json("NOPE INVALID TOKEN")
	}
}

functionality.listUsers = function(req, res) {
	setCORSHeaders(res)

	if (validateToken(req.query.token)) {
		// build a list of rooms with (id, name)
		userSummary = []
		for (user of users) {
			userSummary.push({
				id: user.id,
				name: user.name
			})
		}

		res.json(userSummary)
	}
	else {
		res.json("NOPE INVALID TOKEN")
	}
}

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

module.exports = functionality;