var ajaxObjects = new Array();
var url;

var locales_arr = new Array("en_US", "ja_JP", "zh_CN", "zh_TW", "ko_KR", "de_DE");
var tableTags_arr = [
		// English - en_US
		[	"Design Name", 
			"Actions", 
			"Type", 
			"NSID", 
			"Date", 
			"Item", 
			"Order ID", 
			"Quantity",
		],
		
		// Japanese -  ja_JP
		[	"&#22238;&#36335;&#21517;&#10;", 
			"&#12450;&#12463;&#12471;&#12519;&#12531;&#10;", 
			"&#31278;&#21029;&#10;", 
			"&#35069;&#21697;&#22411;&#30058;&#10;", 
			"&#26085;&#20184;&#10;", 
			"&#35069;&#21697;&#21517;&#10;", 
			"&#27880;&#25991;&#73;&#68;&#10;", 
			"&#25968;&#37327;&#10;",
		],
		
		// chinese - zh_CN
		[	"Design Name", 
			"Actions", 
			"Type", 
			"NSID", 
			"Date", 
			"Item", 
			"Order ID", 
			"Quantity",
		],
		
		// chinese traditional - zh_TW
		[	"Design Name", 
			"Actions", 
			"Type", 
			"NSID", 
			"Date", 
			"Item", 
			"Order ID", 
			"Quantity",
		],
		
		// korean - ko_KR
		[	"Design Name", 
			"Actions", 
			"Type", 
			"NSID", 
			"Date", 
			"Item", 
			"Order ID", 
			"Quantity",
		],
		
		// german - de_DE
		[	"Design Name", 
			"Actions", 
			"Type", 
			"NSID", 
			"Date", 
			"Item", 
			"Order ID", 
			"Quantity",
		],
	];

function GetCookie (name) {  
  var arg = name + "=";  
  var alen = arg.length;  
  var clen = document.cookie.length;  
  var i = 0;  
  while (i < clen) {    
	var j = i + alen;    
	if (document.cookie.substring(i, j) == arg)      
	  return getCookieVal (j);   
	i = document.cookie.indexOf(" ", i) + 1;    
	if (i == 0) break;   
  }  
  return null;
}	

function getLocaleTableString(index)
{
	var langChosen = GetCookie("lang_choosen");
	if(langChosen == null || langChosen == "")
	{
		langChosen = "en_US";
	}

	var i=0;
	for(i=0; i<locales_arr.length; i++)
	{
		if(locales_arr[i] == langChosen)
		{
			return tableTags_arr[i][index];
		}
	}

	return tableTags_arr[0][index];
}

function getIndexForStr(str)
{
	var i=0;
	for(i=0; i<tableTags_arr[0].length; i++)
	{
		if(tableTags_arr[0][i] == str)
		{
			return i;
		}
	}

	return 0;
}

function trim1(str)
{
	return str.replace(/^\s\s*/, '').replace(/\s\s*$/, '');
}
	

function getAjaxURLResponse(divname, serverUrl)
{
	var xmlHttpViewPF = null;
	url = serverUrl;

	xmlHttpViewPF = GetXmlHttpObject();
	if (xmlHttpViewPF == null)
	{
		alert ("Your browser does not support AJAX!");
		return;
	} 
	xmlHttpViewPF.onreadystatechange = function(){elementStateChanged(divname, xmlHttpViewPF)};

	//alert(url);
	xmlHttpViewPF.open("GET",url,true);
	xmlHttpViewPF.send(null);
		
}

function elementStateChanged(divname, pfElement) 
{ 
	if (pfElement.readyState==4)
	{ 
		if(pfElement.status == 404)
		{
			alert("Could not load URL - " + url);
		}

		if(divname != null)
		{
			var el = document.getElementById(divname);
			if( el != null)
			{
					//alert(el);
					//alert(pfElement.responseText);
					el.innerHTML = pfElement.responseText;
					el.style.display = "inline";
			}
		}
		else
		{
			if(pfElement.responseText != '')
				alert("Thank you for your comments!");
		}
	}

}

//======================================================================================
//  Code to submit URL, no response needed.
//======================================================================================
function submitAjaxURL(serverUrl, id, type, login)
{
	var xmlHttpViewPF = null;
	url = serverUrl;

	var f1 = "&f1=" + type;

	var el = document.getElementById(id);
	if( el != null)
	{
		if(el.value == '')
		{
			alert("Please enter a comment.");
			return;
		}
			
		//url = url + "?type=feedback&c1=" + escape(el.value) + f1;
		url = url + "?type=feedback&c1=" + encodeURIComponent(el.value) + f1;
		//url = url + "?type=feedback&c1=" + el.value + f1;
		//url = url + "?type=feedback&c1=" + escape( encodeURIComponent(el.value) ) + f1;
	}
	//alert("escape - " + url);
	//alert("encodeURI - " + url);
	//alert("encodeURIComponent - " + url);
	//alert("escape+encodeURIComponent - " + url);

	var email = document.forms['myform'].email.value;
	//alert(email);
	if(email != '')
		url = url + "&email=" + email;

	xmlHttpViewPF = GetXmlHttpObject();
	if (xmlHttpViewPF == null)
	{
		alert ("Your browser does not support AJAX!");
		return;
	} 

	//alert('submitting response');
	xmlHttpViewPF.onreadystatechange = function(){elementStateChangedNoWait(xmlHttpViewPF)};
	xmlHttpViewPF.open("POST",url,true);
	xmlHttpViewPF.setRequestHeader("Content-Type","application/x-www-form-urlencoded;charset=UTF-8"); 
	xmlHttpViewPF.send(null);
}


// Changed submitComment to accept an extra param to handle the modal box. For the first request repeat = false.
// So the modal is shown. Aftre that repeat=false. Then no modal and it proceeds to submit request.
function submitComment(serverUrl, id, type, login, repeat)
{
	var xmlHttpViewPF = null;
	var url = "http://wwwd.national.com/feedbacks/websitecomm.nsf/comments_processing?openagent";
	
	var el = document.getElementById(id);
	if( el != null)
	{
		if(el.value == '')
		{
			alert("Please enter a comment.");
			return;
		}
	}

	if(repeat == false && login == false)
	{
		showModal(serverUrl, id, type, login, true);
		return;
	}

	var email = document.forms['myform'].email.value;
	//alert(email);
	if(email != '')
		url = url + "&email=" + email;

	var langChosen = GetCookie("lang_choosen");
	if(langChosen == null || langChosen == "")
	{
		langChosen = "en_US";
	}
	if(!(langChosen == "ja_JP" || langChosen == "zh_CN"))
	{
		submitAjaxURL(serverUrl, id, type, login);
		
		return;
	}

	if(langChosen == "ja_JP")
	{
		url = "http://wwwd.national.com/feedbacks/jpn_websitecomm.nsf/comments_processing";
		//url = "http://wwwd.national.com/feedbacks/jpn_websitecomm.nsf/test_processing";
		//url = "http://wwwd.national.com/feedbacks/jpn_websitecomm.nsf/commentsfeednew?createdocument";
	}
	if(langChosen == "zh_CN")
	{
		//url = "http://wwwd.national.com/feedbacks/china_websitecomm.nsf/comments_processing";
		url = "http://wwwd.national.com/feedbacks/china_websitecomm.nsf/comments_processing";
	}


	if(userid != null)
	{
		userid = userid.split(":::",1);
		//userid = "&userid=" + userid;
	}
	else
	{
		userid = "";
	}
	
	document.forms['myform'].u1.value=userid;
	document.forms['myform'].action = url;
	document.forms['myform'].submit();
	return false;
}

function showModal(serverUrl, id, type, login)
{
	Modalbox.show($('modal'), {title: 'Enter Email', width: 700, height: 200}); 
	return false;
}

function saveEmail(serverUrl, id, type, login, alert)
{
	var val = document.getElementById('modalEmail').value;
	if(alert && val == '')
	{
		alert("Please enter your email address.");
		return;
	}
	document.forms['myform'].email.value=val;
	document.forms['myform'].referer.value=document.referrer;
	//alert(document.forms['myform'].email.value);
	Modalbox.hide();
	submitComment(serverUrl, id, type, login, true);
}

function submitFeedbackURL(id, login)
{
	var langChosen = GetCookie("lang_choosen");
	if(langChosen == null || langChosen == "")
	{
		langChosen = "en_US";
	}


	var url = "http://wwwd.national.com/feedbacks/newfeed.nsf/NewFeedback?OpenForm&cat=Technical&c1=";
	if(langChosen == "ja_JP")
		url = "http://wwwd.national.com/feedbacks/jpnfeed.nsf/NewSiteFeedback?OpenForm&cat=Technical&c1=";
	else if(langChosen == "zh_CN")
		url = "http://wwwd.national.com/feedbacks/feedchina.nsf/NewFeedback?OpenForm&cat=Technical&c1=";

	// if login is true, redirect to login page with the next param.
	if(login == true)
		url = "http://www.national.com/profile/login.cgi?next=" + url;

	var el = document.getElementById(id);
	//alert(escape(el.value));
	if( el != null)
	{
		url = url + escape(el.value);
	}
	//alert(url);

	window.location = url;		
}

function submitSFDCAjaxURL(serverUrl, id, redirect)
{
	var xmlHttpViewPF = null;
	url = serverUrl;

	var el = document.getElementById(id);
	
	var langChosen = GetCookie("lang_choosen");
	if(langChosen == null || langChosen == "")
	{
		langChosen = "en_US";
	}

	//alert(escape(el.value));
	if( el != null && langChosen == "en_US")
	{
		url = url + "?category=Technical Support&comments=" + escape(el.value);
	}
	//alert(url);

	if(redirect == true)
	{
		//alert("redirecting");
		window.location = url;
	}
	else
	{

		xmlHttpViewPF = GetXmlHttpObject();
		if (xmlHttpViewPF == null)
		{
			alert ("Your browser does not support AJAX!");
			return;
		} 
	    //xmlHttpViewPF.setRequestHeader("Content-Type","application/x-javascript; charset:UTF-8"); 
		xmlHttpViewPF.onreadystatechange = function(){elementStateChangedNoWait(xmlHttpViewPF)};

		xmlHttpViewPF.open("GET",url,true);
		xmlHttpViewPF.send(null);
	}

		
}

function postSFDCAjaxURL(serverUrl, id, redirect)
{
	var xmlHttpViewPF = null;
	url = serverUrl;
	var params = "";
	
	var el = document.getElementById(id);
	
	var langChosen = GetCookie("lang_choosen");
	if(langChosen == null || langChosen == "")
	{
		langChosen = "en_US";
	}

	if( el != null && langChosen == "en_US")
	{
		params = "category=Technical Support&comments=" + el.value;
	}

	if(redirect == true)
	{
		window.location = url;
	}
	else
	{

		xmlHttpViewPF = GetXmlHttpObject();
		if (xmlHttpViewPF == null)
		{
			alert ("Your browser does not support AJAX!");
			return;
		} 
		xmlHttpViewPF.onreadystatechange = function(){elementStateChangedNoWait(xmlHttpViewPF)};

		alert ("params=" + params);
		xmlHttpViewPF.open("POST",url,true);

		//Send the proper header information along with the request
		xmlHttpViewPF.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
		xmlHttpViewPF.setRequestHeader("Content-length", params.length);
		xmlHttpViewPF.setRequestHeader("Connection", "close");

		xmlHttpViewPF.send(params);
	}

		
}

function elementStateChangedNoWait(pfElement) 
{ 
	if (pfElement.readyState==4)
	{ 
		if(pfElement.status == 404)
		{
			alert("Error in contacting server - " + url);
		}

		// Instead of alert, put the reponse into a div.
		var el = document.getElementById("feedback_resp");
		if( el != null)
		{
			//el.innerHTML = trim1(pfElement.responseText);
			el.innerHTML = "<b><font color='#008800'>" + trim1(pfElement.responseText) +"</font>";
			
		}


		// Clear the feedbox textarea.
		el = document.getElementById("c1");
		if( el != null)
		{
			//alert(el.value);
			el.value = "";
		}


		//alert(trim1(pfElement.responseText));
	}

}

//======================================================================================
//  Code to get the data AND format it.
//======================================================================================
function getAjaxURLResponseAndFormat(divname, serverUrl, myHeader, urlMore, textMore, type)
{
	var xmlHttpViewPF = null;
	url = serverUrl;

	xmlHttpViewPF = GetXmlHttpObject();
	if (xmlHttpViewPF == null)
	{
		alert ("Your browser does not support AJAX!");
		return;
	} 
    //xmlHttpViewPF.setRequestHeader("Content-Type","application/x-javascript; charset:UTF-8"); 
	xmlHttpViewPF.onreadystatechange = function(){elementStateChangedAndFormat(divname, xmlHttpViewPF, myHeader, urlMore, textMore, type)};

//	alert(type);
	xmlHttpViewPF.open("GET",url,true);
	xmlHttpViewPF.send(null);
		
}

 
function elementStateChangedAndFormat(divname, pfElement, myHeader, urlMore, textMore, type) 
{ 
	if (pfElement.readyState==4)
	{ 
		if(pfElement.status == 404)
		{
			alert("Could not load URL - " + url);
		}

		var el = document.getElementById(divname);
		if( el != null)
		{
				//alert(pfElement.responseText);
				el.innerHTML = renderAjaxContent(pfElement.responseText, myHeader, urlMore, textMore, type);
				//el.style.display = "inline";
		}

		el.style.display = "block";
		if(divname.length > 1)
		{
			var ind = divname.substring(divname.length - 1);
			bringToTop(ind);
		}
	}

}

function renderAjaxContent(myValues, myHeader, urlMore, textMore, type) 
{
	//var itemBox = "<table class='ft_box'><tr><td valign='middle' align='center'><div id='inner_table'><table border='0' class='datatable' width='100%' cellspacing='0' cellpadding='0'><tr>";
	var itemBox = "<div id='inner_table'><table border='0' class='datatable' width='100%' cellspacing='0' cellpadding='0'><tr>";

	var headerItems = myHeader.split('\|');
	
	//var bar = "<tr><td colspan=" + headerItems.length + " id='ft_bar'>" + document.getElementById("hidden_div2").innerHTML + "</td></tr>";
	var bar = "";
	
	myValues = myValues.replace(/^\s+|\s+$/g,"")
	
	if(myValues == '')
	{
	  	itemBox = itemBox + "<td><span class='ft_signon'><br>" + "We could not find requested data for your current profile." + "<br><br></span></td></tr><tr>" +
	  							bar + "</table>";
		return itemBox;
	}
		
	for (i=0;i<headerItems.length;i++) 
	{
		var wid = "";
		if(i == 0)
			wid = "width='" + 500 + "'";
		else if(headerItems[i] == 'NSID')
			wid = "width='" + 150 + "'";
		else if(headerItems[i] == 'Type')
			wid = "width='" + 150 + "'";
		else if(headerItems[i] == 'Date')
			wid = "width='" + 100 + "'";
		else if(headerItems[i] == 'Quantity')
			wid = "width='" + 100 + "'";

		var ind = getIndexForStr(headerItems[i]);
		var str1 = getLocaleTableString(ind);
		//alert(str1);
				
	  	//itemBox = itemBox + "<th " + wid + " >" + headerItems[i] + "</th>";
	  	itemBox = itemBox + "<th " + wid + " align='center' >" + str1 + "</th>";
	}
	itemBox = itemBox + "</tr>";

	var lineItems = myValues.split('\n');
	for (i=0;i<lineItems.length;i++) 
	{
		if(lineItems[i] == '')
			continue;
		
		if((i % 2) == 0)
			itemBox = itemBox + "<tr>";
		else
			itemBox = itemBox + "<tr class='altrow'>";

		var eachItems = lineItems[i].split('\|');
		for (j=0;j<eachItems.length;j++) 
		{
			var str = eachItems[j];
			// split the design id for designs
			if(type == 'designs' && j ==1)
			{
				str = '<a href="http://webench.national.com/webench5/power/webench5.cgi?DesignId=' + str + '">' + '<img src="http://www.national.com/analogs/images/national3/webench_button.gif" align="absmiddle" title="New! Power Designer"></a>';
				
			}
			else if(type == 'briefcase')
			{
				if(j == 0)
					str = '<a href="http://www.national.com/pf/' + eachItems[j].substring(0, 2) + '/' + eachItems[j] + '.html' + '">' + eachItems[j] + '</a>';
				if(j == 1 && str != '')
				{
					str = '<a href="http://www.national.com/ENG/cgi-bin/ePitchPak/form.html?base_pn=' + eachItems[j] + '"> <img src="http://www.national.com/images/epitchpak.gif"></a> ';
				}
				
			}
			else if(type == 'samples' && j ==0)
			{
				str = '<a href="http://www.national.com/samples/invoice?order_id=' + str + '">' + str + '</a>';
				
			}
			itemBox = itemBox + "<td align='left' >" + str + "</td>";
		}

		itemBox = itemBox + "</tr>";

	}


	if(urlMore != '')
	{
	  	itemBox = itemBox + "<tr><td><a href='" + urlMore + "'>" + textMore + "</a></td>";
		for (i=1;i<headerItems.length;i++) 
		{
			itemBox = itemBox + "<td></td>";
		}
		itmBox = itemBox + "</tr>";
	}
	
	itemBox = itemBox + bar;

	//itemBox = itemBox + "</table></div></td></tr></table><a name='anc1'></a>";
	itemBox = itemBox + "</table><div><a name='anc1'></a>";
	
	//window.location.hash="anc1";

	//alert(itemBox);
	
	return itemBox;
}
  

//======================================================================================
function GetXmlHttpObject()
{
	var xmlHttp=null;
	try
	{
		// Firefox, Opera 8.0+, Safari
		xmlHttp=new XMLHttpRequest();
	}
	catch (e)
	{
		// Internet Explorer
		try
		{
			xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
		}
		catch (e)
		{
			xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
		}
	}
	return xmlHttp;
}

