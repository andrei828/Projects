

function runTest()
{
	serverUrl = "http://192.168.1.163:8080"

	loginData = {
		name: "Dragos",
		pass: "test"
	}

	loginResponse = getRequest(serverUrl + "/api/login", loginData)
	tokenString = loginResponse.responseJSON;
	console.log(tokenString)

	tokenData = {
		token: tokenString
	}
	console.log(tokenData)
	roomsResponse = getRequest(serverUrl + "/api/rooms/list", tokenData)
	usersResponse = getRequest(serverUrl + "/api/users/list", tokenData)

	rooms = roomsResponse.responseJSON
	users = usersResponse.responseJSON

	console.log(rooms)
	console.log(users)

	for (room of rooms) {

		newMessage = {
			token: tokenString,
			content: "My message test"
		}
		console.log(newMessage)
		postRequest(serverUrl + "/api/room/" + room.id + "/messages/add", newMessage)

		messages = getRequest(serverUrl + "/api/room/" + room.id + "/messages/list", tokenData)
		console.log(messages.responseJSON)
	}
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