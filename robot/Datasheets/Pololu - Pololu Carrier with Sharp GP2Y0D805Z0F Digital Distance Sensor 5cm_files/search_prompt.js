function initSearchPrompt()
{
    var search_input = document.getElementById("search_input");

    if(search_input.value == "" || search_input.value == "Search")
    {
	search_input.value = "Search";
	search_input.style.color = "gray";
    }
}

function clearSearchPrompt()
{
    var search_input = document.getElementById("search_input");

    if(search_input.style.color == "gray")
    {
	search_input.value = "";
	search_input.style.color = "#333";
    }
}