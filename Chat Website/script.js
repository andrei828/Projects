var contor = 0;
var new_contor = 0;

function Check()
{
	var username = document.getElementById('usrnm').value;
console.log(username);
	roomsResponse = getRequest(serverUrl + "/api/rooms/list", tokenData);
	usersResponse = getRequest(serverUrl + "/api/users/list", tokenData);

	rooms = roomsResponse.responseJSON;
	users = usersResponse.responseJSON;

	for (room of rooms) {

		newMessage = {
			token: tokenString,
			content: "My message test"
		}
		console.log(newMessage);

		messages = getRequest(serverUrl + "/api/room/" + room.id + "/messages/list", tokenData)
		console.log(messages.responseJSON);
	}

	for (message of messages.responseJSON)
	{
		if (message.user.name == username)
		{
			Post_Message(message.content);
		}
		else 
		{
			Get_Message(message.content, message.user.name);
		}
	}
	new_contor = messages.responseJSON.length;
}

function Periodic()
{
	setInterval(Check(), 3000);
}

function Login()
{
	document.getElementsByClassName('leftmessage')[0].remove();
	document.getElementsByClassName('rightmessage')[0].remove();

	var username = document.getElementById('usr').value;
	var password = document.getElementById('pwd').value; 

	serverUrl = "http://127.0.0.0:8080";

	loginData = {
		name: username,
		pass: password
	}

	loginResponse = getRequest(serverUrl + "/api/login", loginData);
	tokenString = loginResponse.responseJSON;
	console.log(tokenString);

	tokenData = {
		token: tokenString
	}
	console.log(tokenData);
	roomsResponse = getRequest(serverUrl + "/api/rooms/list", tokenData);
	usersResponse = getRequest(serverUrl + "/api/users/list", tokenData);

	rooms = roomsResponse.responseJSON;
	users = usersResponse.responseJSON;

	console.log(rooms);
	console.log(users);

	for (room of rooms) {

		newMessage = {
			token: tokenString,
			content: "My message test"
		}
		console.log(newMessage);

		messages = getRequest(serverUrl + "/api/room/" + room.id + "/messages/list", tokenData)
		console.log(messages.responseJSON);
	}

	for (message of messages.responseJSON)
	{
		if (message.user.name == username)
		{
			Post_Message(message.content);
		}
		else 
		{
			Get_Message(message.content, message.user.name);
		}
	}
	contor = messages.responseJSON.length;

	Periodic();

	var display_name = document.getElementsByClassName('signspan')[0].innerHTML = username;
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

function Burger_Pressed() {
	
	var container = document.getElementById('container');
	var side_menu = document.getElementById('side-menu');
	
	var check = side_menu.style.marginLeft;
	
	var message_box = document.getElementsByClassName('input')[0];

	if (check !== "0%")
	{
		side_menu.style.marginLeft = "0%";
		container.style.width = "80%";
		container.style.marginLeft = "20%";
		message_box.style.marginLeft = "20%";
	}
	else {
		side_menu.style.marginLeft = "-20%";
		container.style.width = "100%";
		container.style.marginLeft = "0%";
		message_box.style.marginLeft = "0%";
	}
}

function Post_Message_Local()
{
	var text = document.getElementById("textarea").value;	
	var app = document.getElementById("listmsg");
	var li = document.createElement("li");
	var div = document.createElement("div");
	div.classList.add("rightmessage");
	div.innerHTML = text;
	li.appendChild(div);
	app.appendChild(li);
	document.getElementById("textarea").value = "";
	$('.background').animate({ scrollTop: $(app).height()}, 'slow');
	postRequest(serverUrl + "/api/room/" + room.id + "/messages/add", {token: tokenString, content: text});
}

function Post_Message(text)
{
	var app = document.getElementById("listmsg");
	var li = document.createElement("li");
	var div = document.createElement("div");
	div.classList.add("rightmessage");
	div.innerHTML = text;
	li.appendChild(div);
	app.appendChild(li);
	$('.background')[0].scrollTop = $(app).height()
}

function Get_Message(text, name)
{
	var app = document.getElementById("listmsg");
	var li = document.createElement("li");
	var div = document.createElement("div");
	var p = document.createElement("p");
	p.innerHTML = name;
	p.classList.add("span_mess");
	div.classList.add("leftmessage");
	div.innerHTML = text + "<br>";
	div.appendChild(p);
	div.innerHTML += "<br>";
	li.appendChild(div);
	app.appendChild(li);
	$('.background')[0].scrollTop = $(app).height()
}

