window.onload = function()
{
	runTest()
	LoadEventData()
	Update_Block()
}

serverUrl = "http://127.0.0.1:8080"

tokenData = {
	token: localStorage.token
}

var evt;

function runTest()
{
	
	notesResponse = getRequest(serverUrl + "/api/note/list",  tokenData)
	eventRespone  = getRequest(serverUrl + "/api/event/list", tokenData)
	todoResponse  = getRequest(serverUrl + "/api/todo/list",  tokenData)
	todoItemResponse = getRequest(serverUrl + "/api/todoitem/list", tokenData)

	notes  = notesResponse.responseJSON
	events = eventRespone.responseJSON
	todos  = todoResponse.responseJSON
	items  = todoItemResponse.responseJSON

	evt = events

	console.log(notes)
	console.log(events)
	console.log(todos)
	console.log(items)

	GetNoteList(notes)
	/*
	for (room of rooms) {

		newMessage = {
			token: tokenString,
			content: "My message test"
		}
		console.log(newMessage)
		postRequest(serverUrl + "/api/room/" + room.id + "/messages/add", newMessage)

		messages = getRequest(serverUrl + "/api/room/" + room.id + "/messages/list", tokenData)
		console.log(messages.responseJSON)
	}*/
}

function getRequest(url, data)
{
	return $.ajax({
		url: url,
		type: "GET",
		data: data,
		dataType: 'json',
		crossDomain: true,
		async: false,
		success: function(res) {
			return res
		}
	});
}

function postRequest(url, data)
{
	return $.ajax({
		url: url,
		type: "POST",
		data: data,
		crossDomain: true,
		async: false,
		success: function(res) {
			return res
		}
	});
}

function Username_Button()
{
	// save everything
}

function GetNoteList(note_list)
{
	// get from database
	for (note of note_list)
	{
		Create_Note(note.name, note.tag)
	}
}

function GetTodoList(todo_list)
{
	// get from database
}

function GetTodoItemList(todo_item_list)
{
	// get from database
}



var Months = [ ["January", 31], ["February", 29], ["March", 31],
				 ["April", 30], ["May", 31], ["June", 30], 
		  		 ["July", 31], ["August", 31], ["September", 30], 
		  		 ["October", 31], ["November", 30], ["December", 31] ];

function Event() {
	this.title;
	this.hour;
	this.minute;
	this.place;
	this.date;
	this.tag;
}

var copy_replace;
var copy_initial_children;

var EventList = [];

function LoadEventData()
{
		//  § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § 
	var date = new Date();
	var string_date = date.getDate() + " " + String(parseInt(date.getMonth())+1) + " " + date.getFullYear();
	
	// dummy data 
	var ev_1 = {
		title: "Meeting at lorem ipsum",
		tag: "event_blue",
		day: "1",
		month: "3",
		year: "2018"
	}

	var ev_2 = {
		title: "Lunch afer sample text",
		tag: "event_yellow",
		day: "1",
		month: "3",
		year: "2018"
	}

	var ev_3 = {
		title: "Meeting  tsgewg ir text data",
		tag: "event_red",
		day: "1",
		month: "3",
		year: "2018"
	}

	var ev_4 = {
		title: "Lunch afer wertg",
		tag: "event_yellow",
		day: "19",
		month: "8",
		year: "2018"
	}

	var ev_5 = {
		title: "Meeting sample text universal",
		tag: "event_red",
		day: "20",
		month: "8",
		year: "2018"
	}

	var ev_6 = {
		title: "Lunch afer lorem",
		tag: "event_yellow",
		date: "20 9 2018"
	}

	var ev_7 = {
		title: "Meeting ana are mere",
		tag: "event_blue",
		date: "20 9 2018"
	}
	
	EventList.push(ev_1);
	EventList.push(ev_2);
	EventList.push(ev_3);
	/*EventList.push(ev_4);
	EventList.push(ev_5);
	EventList.push(ev_6);
	EventList.push(ev_7);*/
	// end dummy data
	
	for (Event of evt)
	{
		EventList.push(Event);
	}
}

function GetEventList()
{
	
	return EventList;
}





function Create_Block()
{
	var block = document.createElement("div");
	block.id = "event_list";
	block.classList.add("list_event_block");
	
	var div_children = document.createElement("div");
	div_children.id = "children";
// Add title ****************************
	var title = document.createElement("div");
	title.id = "event_title_div";
	title.classList.add("mdl-layout__header-row");
	
	var text_span = document.createElement("span");
	text_span.classList.add("mdl-layout-title");
	text_span.id = "event_list_title";
	text_span.innerHTML = "Events";
	
	title.appendChild(text_span);
	div_children.appendChild(title);
// end title *****************************
	
// Add the + button **************************
	var add_button = document.createElement("button");
	add_button.classList.add("mdl-button");
	add_button.classList.add("mdl-js-button"); 
	add_button.classList.add("mdl-button--fab");
	add_button.classList.add("mdl-js-ripple-effect");
	add_button.classList.add("mdl-button--colored");
	add_button.id = "add_event";
	add_button.onclick = Plus_Add_Event_Button();
	
	var i = document.createElement("i");
	i.classList.add("material-icons");
	i.innerHTML = "add";
	
	add_button.appendChild(i);
	div_children.appendChild(add_button);
// end + button ********************************
	
// Add Today label ****************************
	var title_today = document.createElement("div");
	title_today.id = "event_date";
	title_today.innerHTML = GetDateToday();
	
	div_children.appendChild(title_today);
// end add today label **************************
	
// Add events for today*******************************
	var events_today = Add_Event_Today(GetEventList());
	
	div_children.appendChild(events_today);
// end add events *******************************
	
// Add break **********************
	br = document.createElement("br");
	
	div_children.appendChild(br);
// end add break **************************
	
// Add upcoming label ***************************
	var upcoming_label = document.createElement("div");
	upcoming_label.id = "up_ev_title";
	upcoming_label.innerHTML = "Upcoming Events";
	
	div_children.appendChild(upcoming_label);
// end add upcoming label ***********************
	
// Add upcoming dates ***************************
	var event_list = GetEventList();
	var date_list = new Set();
	//var date = new Date();
	//var string_date = date.getDate() + " " + String(parseInt(date.getMonth())+1) + " " + date.getFullYear();
	
	var current_day = date.getDate()
	var current_month = date.getMonth()
	var current_year = date.getFullYear()

	for (event of event_list)
	{
		if (event.day === current_day && event.month === current_month && event.year === current_year)
			continue;
		else {
			var lst = {
				day: event.day,
				month: event.month,
				year: event.year
			}
			date_list.add(lst);
		}
	}
	for (date of date_list)
	{
		var event_up = Add_Upcoming_Events(date); 
		
		div_children.appendChild(event_up);
	}
// end add upcoming dates ***********************
	block.appendChild(div_children);
	return block;
}



function Create_Block_Full()
{
	document.body.appendChild(Create_Block());
}

function X_Cancel_Event_Button()
{
	var block = document.getElementById("event_list");
	var replace = document.getElementsByClassName("replace")[0];
	//repl.style.display = "inline";
	block.removeChild(copy_replace);
	block.appendChild(copy_initial_children);
}

function Add_event_database()
{
	var add_event_data = {
		token: tokenData.token,
		title: document.getElementById("new_event_name").value,
		place: document.getElementById("new_event_place").value,
		hour: document.getElementById("event_hour_add").value,
		tag: "event_" + document.getElementById("event_tag_add").value,
		day: document.getElementById("event_day_add").value,
		month: String(parseInt(document.getElementById("event_month_add").selectedIndex)+1),
		year: document.getElementById("event_year_add").value
	}
	//add event to database
	//  § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § 
	var d = new Date();
	if (add_event_data.title == null || add_event_data.title == undefined) {X_Cancel_Event_Button();return;}
	if (parseInt(add_event_data.year) < d.getFullYear()) {X_Cancel_Event_Button();return;}
	else if (parseInt(add_event_data.year) == d.getFullYear())
	{
		if (parseInt(add_event_data.month) < d.getMonth()) {X_Cancel_Event_Button();return;}
		else if (parseInt(add_event_data.month) == d.getMonth())
		{
			if (parseInt(add_event_data.day) < d.getDate()) {X_Cancel_Event_Button();return;}
		}	
	} 
		
	EventList.push(add_event_data);
	X_Cancel_Event_Button();
	Clear_Event_Data();
	Update_Block();
	add_event = getRequest(serverUrl + "/api/event/add",  add_event_data)
}



function GetDateToday()
{	
	var date = new Date();
	return "Today, " + date.getDate() + ' ' + Months[date.getMonth()][0];
}


function Add_Event_Today_Tag(tag_color)
{
	var tag = document.createElement("div");
	tag.id = "event_color";
	tag.classList.add(tag_color);

	return tag;
}


function Add_Event_Today_Title(content)
{
	var title = document.createElement("div");
	title.id = "event_title";
	title.innerHTML = content;

	return title;
}



function Add_Event_Today(event_list)
{
	//  § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § 

	var event = document.createElement("div");
	event.id = "event";
	var date = new Date();
	var string_date = date.getDate() + " " + String(parseInt(date.getMonth())) + " " + date.getFullYear();
	

	for (evnt of event_list)
	{
		if (evnt.day == date.getDate() && evnt.month == String(parseInt(date.getMonth())+1) && evnt.year == date.getFullYear()) {

			var tag_div = Add_Event_Today_Tag(evnt.tag);
			var title_div = Add_Event_Today_Title(evnt.title);
			var br = document.createElement("br");
			event.appendChild(tag_div);
			event.appendChild(title_div);
			event.appendChild(br);
		}
	}
	return event;
}





function Add_Event()
{
	var event = document.createElement("div");
	event.id = "event";
	
// Add tag **************************
	var tag = document.createElement("div");
	tag.id = "event_color";
	tag.classList.add("event_blue");
	
	event.appendChild(tag);
// end add tag ***********************

// Add tag **************************
	var title = document.createElement("div");
	title.id = "event_title";
	title.innerHTML = "Meeting at lorem upsum";
	
	event.appendChild(title);
// end add tag **********************	

	return event;
}


function Add_Upcoming_Events(date) 
{
	//  § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § 
	var event_upcom = document.createElement("div");
	event_upcom.id = "event_up";
	
	var event_up_date = document.createElement("div");
	event_up_date.id = "event_up_date";
	
	var date_ob = new Date();
	var current_year = date_ob.getFullYear();
	
	event_up_date.innerHTML = date.day + " " + Months[parseInt(date.month)-1][0];

	if (current_year != date.year)
		event_up_date.innerHTML += "<i>" + date.year + "</i>";

	event_upcom.appendChild(event_up_date);
	
	var event_list = GetEventList();
	for (event of event_list)
	{
		if (date.day == event.day && date.month == event.month && date.year == event.year)
		{
			var tag_div = Add_Event_Today_Tag(event.tag);
			var title_div = Add_Event_Today_Title(event.title);
			var br = document.createElement("br");
			event_upcom.appendChild(tag_div);
			event_upcom.appendChild(title_div);
			event_upcom.appendChild(br);
		}
	}
	
	return event_upcom;
}

function Plus_Add_Event_Button()
{
	var block = document.getElementById("event_list");
	var replace = document.getElementsByClassName("replace")[0];
	
	block_initial_children = document.getElementById("children");
	
	copy_replace = replace.cloneNode(true);
	copy_replace.style.display = "block";
	copy_initial_children = block_initial_children.cloneNode(true);
	
	block.removeChild(block_initial_children);
	
	block.appendChild(copy_replace);
}

function Clear_Event_Data()
{
	var myNode = document.getElementById("event");
	while (myNode.firstChild) 
    	myNode.removeChild(myNode.firstChild);
	var myNode = document.getElementById("upcoming_events");
	while (myNode.firstChild) 
    	myNode.removeChild(myNode.firstChild);
}

function Update_Block()
{	

// Add Today label ****************************
	var title_today = document.getElementById("event_date");
	title_today.innerHTML = GetDateToday();

// end add today label **************************
	
// Add events for today*******************************
	var event_list_today = document.getElementById("event");
	var events_today = Add_Event_Today(GetEventList());
	
	event_list_today.appendChild(events_today);
// end add events *******************************
	
// Add upcoming dates ***************************
	var upcoming_events = document.getElementById("upcoming_events");
	var event_list = GetEventList();
	var date_list = new Set();
	var date = new Date();
	//  § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § § 

	var current_day = date.getDate()
	var current_month = String(parseInt(date.getMonth())+1)
	var current_year = date.getFullYear()

	for (event of event_list)
	{
		if (event.day == current_day && event.month == current_month && event.year == current_year)
			continue;
		else {
			var lst = {
				day: event.day,
				month: event.month,
				year: event.year
			}
			date_list.add(lst);
		}
	}
	for (date of date_list)
	{
		if(date != "SampleDATE")
		{
			var event_up = Add_Upcoming_Events(date); 
			upcoming_events.appendChild(event_up);
		}
	}
// end add upcoming dates ***********************
}



var current_note;

function Plus_Add_Note_Button()
{
	
	if (document.getElementById("note_change_icon").innerHTML == "create")
	{
		document.getElementById("note_list_title").value = "Untitled"
		document.getElementById("note_list_title").readOnly = false;
		document.getElementById("note_list_title").onfocus = function() {
		if (document.getElementById("note_list_title").value == "Untitled")
			document.getElementById("note_list_title").value = null
		}
		var center = document.createElement("center");
		center.id = "hide_center_id"
		var note = document.createElement("div")
		note.id = "biu_div"
		document.getElementById("note_list").style.display = "none";
		boldButton = document.createElement('button')
		boldButton.classList.add("mdl-button")
		boldButton.classList.add("mdl-js-button")
		boldButton.classList.add("mdl-button--raised")
		boldButton.classList.add("lmb-button")
		boldButton.style.backgroundColor = "white";
		boldButton.onclick = function() {
			document.execCommand('bold',false,null)
		}
		boldButton.innerHTML = "<strong>B</strong>"
		note.appendChild(boldButton)		
		italicButton = document.createElement('button')
		italicButton.classList.add('mdl-button')
		italicButton.classList.add('mdl-js-button')
		italicButton.classList.add('mdl-button--raised')
		italicButton.classList.add('lmd-button')
		italicButton.style.backgroundColor = "white";
		italicButton.onclick = function () {
		  document.execCommand('italic', false, null);
		}
		italicButton.innerHTML = "<italic>I</italic>"
		note.appendChild(italicButton)	

 		underlineButton = document.createElement('button')
 		underlineButton.classList.add('mdl-button')
 		underlineButton.classList.add('mdl-js-button')
 		underlineButton.classList.add('mdl-button--raised')
 		underlineButton.classList.add('lmd-button')
 		underlineButton.style.backgroundColor = "white";
 		underlineButton.onclick = function () {
 		  document.execCommand('underline', false, null);
 		}
 		underlineButton.innerHTML = "<u>U</u>"
  		note.appendChild(underlineButton)
		center.appendChild(note)
		document.getElementById("note").appendChild(center)
		
		noteContent = document.createElement('div')
		noteContent.id = "textarea_div"
		noteContent.classList.add('mdl-textfield__input')
		noteContent.classList.add('note_content')
		noteContent.contentEditable = 'true'
		noteContent.style.backgroundColor = "rgb(202, 247, 187)";
		noteContent.type = 'text'
		noteContent.rows = '3'
		noteContent.onfocus = function() {
			if (noteContent.innerHTML == "Type your note here...")
			noteContent.innerHTML = null
		}
		noteContent.innerHTML = "Type your note here..."
		document.getElementById("note").appendChild(noteContent)
		
		document.getElementById("note_change_icon").innerHTML = "archive"
	}
	else if(document.getElementById("note_change_icon").innerHTML == "archive")
	{
		var title = document.getElementById("note_list_title").value
		var content = document.getElementById("textarea_div").innerHTML
		document.getElementById("note_list_title").value = "Notes"
		document.getElementById("note_list_title").readOnly = true;
		document.getElementById("note_list").style.display = "block";
		document.getElementById("note_list").scrollTop = 1;
		var remove = document.getElementById("hide_center_id")
		var remove_2 = document.getElementById("textarea_div")
		document.getElementById("note").removeChild(remove)
		document.getElementById("note").removeChild(remove_2)
		document.getElementById("note_change_icon").innerHTML = "create"
		Create_Note(title, content)

		// update database
		add_data = {
			token: tokenData.token,
			title: title,
			content: content
		}

		add_note = getRequest(serverUrl + "/api/note/add",  add_data)
	}
	else if (document.getElementById("note_change_icon").innerHTML == "check")
	{ 
		var title = document.getElementById("note_list_title").value
		var content = document.getElementById("textarea_div").innerHTML
		document.getElementById("note_list_title").value = "Notes"
		document.getElementById("note_list_title").readOnly = true;
		
		var i1 = document.getElementById("hide_center_id")
		var i2 = document.getElementById("textarea_div")
		document.getElementById("note").removeChild(i1)
		document.getElementById("note").removeChild(i2)
		var note = document.getElementById("note_list")
		note.style.display = "block"
		note.scrollTop = 1;
		document.getElementById("note_change_icon").innerHTML = "create"
		Create_Note(title, content)

		// update database
		add_data = {
			token: tokenData.token,
			title: title,
			content: content
		}

		add_note = getRequest(serverUrl + "/api/note/add",  add_data)
	}
}

function Open_Note_Preview(div_summary)
{
	var title = div_summary.children[0].innerHTML
	var content = div_summary.children[1].innerHTML
	div_summary.remove()

	document.getElementById("note_list_title").value = title
	document.getElementById("note_list_title").readOnly = false;
	document.getElementById("note_list_title").onfocus = function() {
		if (document.getElementById("note_list_title") == "Untitled")
			document.getElementById("note_list_title").value = null
	}
	var center = document.createElement("center");
	center.id = "hide_center_id"
	var note = document.createElement("div")
	note.id = "biu_div"
	document.getElementById("note_list").style.display = "none";
	boldButton = document.createElement('button')
	boldButton.classList.add("mdl-button")
	boldButton.classList.add("mdl-js-button")
	boldButton.classList.add("mdl-button--raised")
	boldButton.classList.add("lmb-button")
	boldButton.style.backgroundColor = "white";
	boldButton.onclick = function() {
		document.execCommand('bold',false,null)
	}
	boldButton.innerHTML = "<strong>B</strong>"
	note.appendChild(boldButton)		
	italicButton = document.createElement('button')
	italicButton.classList.add('mdl-button')
	italicButton.classList.add('mdl-js-button')
	italicButton.classList.add('mdl-button--raised')
	italicButton.classList.add('lmd-button')
	italicButton.style.backgroundColor = "white";
	italicButton.onclick = function () {
	  document.execCommand('italic', false, null);
	}
	italicButton.innerHTML = "<italic>I</italic>"
	note.appendChild(italicButton)	
 	underlineButton = document.createElement('button')
 	underlineButton.classList.add('mdl-button')
 	underlineButton.classList.add('mdl-js-button')
 	underlineButton.classList.add('mdl-button--raised')
 	underlineButton.classList.add('lmd-button')
 	underlineButton.style.backgroundColor = "white";
 	underlineButton.onclick = function () {
 	  document.execCommand('underline', false, null);
 	}
 	underlineButton.innerHTML = "<u>U</u>"
  	note.appendChild(underlineButton)
	center.appendChild(note)
	document.getElementById("note").appendChild(center)
	
	noteContent = document.createElement('div')
	noteContent.id = "textarea_div"
	noteContent.classList.add('mdl-textfield__input')
	noteContent.classList.add('note_content')
	noteContent.contentEditable = 'true'
	noteContent.style.backgroundColor = "rgb(202, 247, 187)";
	noteContent.type = 'text'
	noteContent.rows = '3'
	noteContent.onfocus = function() {
		if (noteContent.innerHTML == "Type your note here...")
		noteContent.innerHTML = null
	}
	noteContent.innerHTML = content
	document.getElementById("note").appendChild(noteContent)
	
	document.getElementById("note_change_icon").innerHTML = "check"

	// update database
	remove_data = {
		token: tokenData.token,
		title: title,
		content, content
	}
	console.log(remove_data)
	remove_note = getRequest(serverUrl + "/api/note/remove",  remove_data)
}



function Create_Note(title, content)
{
	if (title == "Untitled" && content == "Type your note here...") return
	if (title != "Untitled" && content == "Type your note here...") content = null
	Note = {}
	Note.name = title
	Note.content = content
	Note.tag = "blue"

	var note_summary = document.createElement("div")
	note_summary.classList.add("note_summary")

	var note_summary_title = document.createElement("div")
	note_summary_title.innerHTML = title
	note_summary_title.classList.add("note_summary_title")
	note_summary.appendChild(note_summary_title)
	
	var note_summary_preview = document.createElement("div")
	note_summary_preview.innerHTML = content
	note_summary_preview.classList.add("note_summary_preview")
	note_summary.appendChild(note_summary_preview)
	note_summary.setAttribute("onclick", "Open_Note_Preview(this)");

	document.getElementById("note_list").insertBefore(note_summary, document.getElementById("note_list").firstChild);
}



























