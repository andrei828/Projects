function Login()
{
	var username = document.getElementById("username").value
	var password = document.getElementById("password").value

	serverUrl = "http://127.0.0.1:8080"

	loginData = {
		name: username,
		pass: password
	}

	loginResponse = getRequest(serverUrl + "/api/login", loginData)

	if (typeof(Storage) !== "undefined") 
	{
    	localStorage.setItem("token", loginResponse.responseJSON);
    	if (localStorage.token != "No such user in the database" && localStorage.token != "INVALID LOGIN" && localStorage.token != "undefined")
    		window.location.href = "Overview/index.html"
    	else
  		{
  			alert(localStorage.token)
  		}
	}
    else 
    	document.getElementById("result").innerHTML = "Sorry, your browser does not support Web Storage...";
}

function Register()
{	
	var email = document.getElementById("register_email").value
	var username = document.getElementById("register_username").value
	var password = document.getElementById("register_password").value
	var veirfy_pass = document.getElementById("register_verify_password").value

	if (password != veirfy_pass)
	{
		// handle bad password
	}
	else 
	{
		serverUrl = "http://127.0.0.1:8080"

		registerData = {
			name: username,
			pass: password,
			email: email
		}

		registerResponse = getRequest(serverUrl + "/api/register", registerData)

		if (typeof(Storage) !== "undefined") 
		{
    		localStorage.setItem("token", registerResponse.responseJSON);
    		if (localStorage.token != "Invalid register (bad username or password)" && localStorage.token != "Username already taken" && localStorage.token != "undefined")
    			window.location.href = "Overview/index.html"
    		else
  			{
  				alert(localStorage.token)
  			}
		}
    	else 
    		document.getElementById("result").innerHTML = "Sorry, your browser does not support Web Storage...";
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