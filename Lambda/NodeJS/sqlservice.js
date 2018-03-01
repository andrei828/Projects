
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
		tag text NOT NULL											\
	);'

	let createEvents = 'CREATE TABLE IF NOT EXISTS events (			\
		id integer PRIMARY KEY,										\
		id_user integer NOT NULL,									\
		title text NOT NULL,										\
		day text NOT NULL,											\
		month text NOT NULL,										\
		year text NOT NULL,											\
		hour integer NOT NULL,										\
		tag text NOT NULL,											\
		place text													\
	);'

	let createToDoItems = 'CREATE TABLE IF NOT EXISTS todo_items (	\
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

sqlservice.getUserForLogin = function(callback, name, pass) {
	var query = 'SELECT * FROM users WHERE name=(?) AND pass=(?)'

	this.db.all(query, name, pass, callback) 
}

sqlservice.getUserForRegister = function(callback, name) {
	var query = 'SELECT * FROM users WHERE name=(?)'

	this.db.all(query, name, callback)
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
	var query = 'DELETE FROM events WHERE id=(?) AND title=""'
	this.db.run(query, id)

	var query = 'SELECT * FROM events WHERE id_user=(?) ORDER BY year ASC, month ASC, day ASC'

	this.db.all(query, id, callback)
}

sqlservice.getTodosById = function(callback, id) {
	var query = 'SELECT * FROM todos WHERE id_user=(?)'

	this.db.all(query, id, callback)
}

sqlservice.getTodoItemsById = function(callback, id) {
	var query = 'SELECT * FROM todo_items WHERE id_todo=(?)'

	this.db.all(query, id, callback)
}
// end all 5 list functions 


// add functions
sqlservice.addUser = function(callback, user) {
	// add data from user parameter
	var add_user = 'INSERT INTO users(name, pass, email) VALUES ((?), (?), (?))' 
	this.db.run(add_user, user.name, user.pass, user.email)

	var query = 'SELECT * FROM users WHERE name=(?)'
	this.db.all(query, user.name, callback)
} 

sqlservice.addEvent = function(callback, event) {
	// add data from event parameter
	var add_event = 'INSERT INTO events(id_user, title, day, month, year, hour, tag, place) VALUES ((?), (?), (?), (?), (?), (?), (?), (?))'
	this.db.run(add_event, event.id, event.title, event.day, event.month, event.year, event.hour, event.tag, event.place)

	var query = 'SELECT * FROM events WHERE id_user=(?)'
	this.db.all(query, event.id, callback)
}

sqlservice.addTodo = function(callback, todo) {
	// add data from todo parameter
	var add_todo = 'INSERT INTO todos(id_user, name, tag) VALUES ((?), (?), (?))'
	this.db.run(add_todo, todo.id, todo.name, todo.tag)

	var query = 'SELECT * FROM todos WHERE id_user=(?)'
	this.db.all(query, todo.id, callback)
}

sqlservice.addTodoItem = function(callback, item) {
	// add data from item parameter
	var add_item = 'INSERT INTO todo_items(id_todo, content, checked) VALUES ((?), (?), (?))'
	this.db.run(add_item, item.id, item.content, item.checked)

	var query = 'SELECT * FROM todo_items WHERE id_todo=(?)'
	this.db.all(query, item.id, callback)
}

sqlservice.addNote = function(callback, note) {
	// add data from note parameter
	var add_note = 'INSERT INTO notes(id_user, name, tag) VALUES ((?), (?), (?))'
	this.db.run(add_note, note.id, note.name, note.content)
	
	var query = 'SELECT * FROM notes WHERE id_user=(?)'
	this.db.all(query, note.id, callback)
}
// end add functions


// all 4 remove functions
sqlservice.removeUserById = function(callback, id) {
	var query = 'DELETE FROM users WHERE id=(?)'
	this.db.run(query, id)

	var query = 'SELECT * FROM users'
	this.db.all(query, callback)
}

sqlservice.removeNoteById = function(callback, id, title, content) {
	var query = 'DELETE FROM notes WHERE id_user=(?) AND name=(?) AND tag=(?)'
	this.db.run(query, id, title, content)

	var query = 'SELECT * FROM notes WHERE id_user=(?)'
	this.db.all(query, callback)
}

sqlservice.removeTodoById = function(callback, id) {
	var query = 'DELETE FROM todos WHERE id=(?)'
	this.db.run(query, id)
	
	var query = 'SELECT * FROM todos'
	this.db.all(query, callback)
}

sqlservice.removeTodoItemById = function(callback, id) {
	var query = 'DELETE FROM todo_items WHERE id=(?)'
	this.db.run(query, id)

	var query = 'SELECT * FROM todo_items'
	this.db.all(query, callback)
}

sqlservice.removeEventById = function(callback, id, title, day, month, year) {
	var query = 'DELETE FROM events WHERE id=(?) AND title=(?) AND day=(?) AND month=(?) AND year=(?)'
	this.db.run(query, id, title, day, month, year)

	var query = 'SELECT * FROM events'
	this.db.all(query, callback)
}
// end all 4 remove functions


module.exports = sqlservice