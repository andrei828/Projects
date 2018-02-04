
const sqlite3 = require('sqlite3').verbose();

var sqlservice = {}

sqlservice.initialize = function() {

	sqlservice.db = new sqlite3.Database('./database.db', (err) => {
	  if (err) {
	    return console.error(err.message);
	  }
	});

	console.log("Initializing database")


	let createUsers = 'CREATE TABLE IF NOT EXISTS users (			\
		id integer PRIMARY KEY,										\
		name text NOT NULL,											\
		pass text NOT NULL,											\
		email text NOT NULL											\
	);'

	let createNotes = 'CREATE TABLE IF NOT EXISTS notes (			\
		id integer PRIMARY KEY,										\
		id_user integer NOT NULL,									\
		name text NOT NULL,											\
		content text NOT NULL,										\
		tag text NOT NULL											\
	);'

	let createEvents = 'CREATE TABLE IF NOT EXISTS events (			\
		id integer PRIMARY KEY,										\
		id_user integer NOT NULL,									\
		title text NOT NULL,										\
		date text NOT NULL,											\
		hour integer NOT NULL,										\
		tag text NOT NULL,											\
		place text													\
	);'

	let createToDoItems = 'CREATE TABLE IF NOT EXISTS todo_item (	\
		id integer PRIMARY KEY,										\
		id_todo NOT NULL,											\
		content text NOT NULL,										\
		checked text NOT NULL										\
	);'

	let createToDos = 'CREATE TABLE IF NOT EXISTS todos (			\
		id integer PRIMARY KEY,										\
		id_user	integer NOT NULL,									\
		name text NOT NULL,											\
		tag text NOT NULL											\
	);'

	this.db.run(createUsers)
	this.db.run(createNotes)
	this.db.run(createEvents)
	this.db.run(createToDoItems)
	this.db.run(createToDos)
}


// all 5 list functions
sqlservice.getUserById = function(callback, id) {
	var query = 'SELECT * FROM users WHERE id=(?)'

	this.db.all(query, id, callback)
}

sqlservice.getNotesById = function(callback, id) {
	var query = 'SELECT * FROM notes WHERE id_user=(?)'

	this.db.all(query, id, callback)
}

sqlservice.getEventsById = function(callback, id) {
	var query = 'SELECT * FROM events WHERE id_user=(?)'

	this.db.all(query, id, callback)
}

sqlservice.getTodosbyId = function(callback, id) {
	var query = 'SELECT * FROM todos WHERE id_user=(?)'

	this.db.all(query, id, callback)
}

sqlservice.getTodoItemsById = function(callback, id) {
	var query = 'SELECT * FROM todo_item WHERE id_todo=(?)'

	this.db.all(query, [id], callback)
}
// end all 5 list functions 


// add functions
sqlservice.addUser = function(callback, user) {
	// add data from user parameter
	var add_user = 'INSERT INTO users(name, pass, email) VALUES ("call_by_add_func", "first_note", "blue@gmail.com")' 
	this.db.run(add_user)

	var query = 'SELECT * FROM users'
	this.db.all(query, callback)
}

sqlservice.addEvent = function(callback, event) {
	// add data from event parameter
	var add_event = 'INSERT INTO events(id_user, title, date, hour, tag, place) VALUES (2, "call_by_func_evnt", "29 12 2007", 20, "blue", "work")'
	this.db.run(add_event)

	var query = 'SELECT * FROM events'
	this.db.all(query, callback)
}

sqlservice.addTodo = function(callback, todo) {
	// add data from todo parameter
	var add_todo = 'INSERT INTO todos(id_user, name, tag) VALUES (2, "add_by_func_todo", "blue")'
	this.db.run(add_todo)

	var query = 'SELECT * FROM todos'
	this.db.all(query, callback)
}

sqlservice.addNote = function(callback, note) {
	// add data from note parameter
	var add_note = 'INSERT INTO notes(id_user, name, content,tag) VALUES (2, "add_by_func_note", "Forgot to add NOte... content" ,"blue")'
	this.db.run(add_note)

	var query = 'SELECT * FROM notes'
	this.db.all(query, callback)
}
// end add functions


// all 4 remove functions
sqlservice.removeUserById = function(callback, id) {
	var query = 'DELETE FROM users WHERE id=(?)'
	this.db.run(query, id)

	var query = 'SELECT * FROM users'
	this.db.all(query, callback)
}

sqlservice.removeNoteById = function(callback, id) {
	var query = 'DELETE FROM notes WHERE id=(?)'
	this.db.run(query, id)

	var query = 'SELECT * FROM notes'
	this.db.all(query, callback)
}

sqlservice.removeTodoById = function(callback, id) {
	var query = 'DELETE FROM todos WHERE id=(?)'
	this.db.run(query, id)
	
	var query = 'SELECT * FROM todos'
	this.db.all(query, callback)
}

sqlservice.removeEventById = function(callback, id) {
	var query = 'DELETE FROM events WHERE id=(?)'
	this.db.run(query, id)

	var query = 'SELECT * FROM events'
	this.db.all(query, callback)
}
// end all 4 remove functions


module.exports = sqlservice