function h1Change(num)
{
	h1 = document.getElementById("dynamic-header");
	if (num === '1')
	{
		h1.innerHTML = "Sortat dupa pret crescator";
	}
	else if (num === '2')
	{
		h1.innerHTML = "Sortat dupa pret descrescator";
	}
	else if (num === '3')
	{
		h1.innerHTML = "Sortat dupa noutati";
	}
	console.log(num);
}

function getLaptops()
{
	
	laptops = [];
	
	laptop1 = {
		img_link: "images/laptops/L1.jpg",
		img_size: "65%", 
		specs: ["Procesor", "RAM", "Memorie SSD", "Rezolutie ecran"],
		price: 2300,
		old_price: 2800
	};
	
	laptop2 = {
		img_link: "images/laptops/L2.png",
		img_size: "65%", 
		specs: ["Procesor", "RAM", "Memorie SSD", "Rezolutie ecran"],
		price: 3100,
		old_price: 4050
	};
	
	laptops.push(laptop1);
	laptops.push(laptop2); 
	
	return laptops;
}

function writeRows()
{
	data = getLaptops();
	
	var sample = document.getElementsByClassName("container-fluid test")[0];


	for (laptop of data)
	{
		// create row
		var row = document.createElement("div");
		row.className = "row";
		
		// create col
		var col = document.createElement("div");
		col.className = "col-sm-3";
		col.innerHTML = "<center>";
		
		// create img
		var img = document.createElement("IMG");
		img.setAttribute("src", laptop.img_link);
		img.setAttribute("width", laptop.img_size);

		// append img
		col.appendChild(img);

		row.appendChild(col);
		sample.appendChild(row);
		console.log("Finish");
	}	
}