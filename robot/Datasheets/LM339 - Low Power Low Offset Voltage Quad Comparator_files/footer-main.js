
function urlSubmit()
{
	//alert(document.location.href);
	this.document.obsoletePartsForm.action = '/JS/searchDocument.do?obspart=' + document.obsoletePartsForm.obspart.value;
	 if(document.location.href.indexOf("lang_choosen=") != -1)
			this.document.search_wrap.action = this.document.obsoletePartsForm.action + "&lang_choosen=ja_JP";

	this.document.obsoletePartsForm.submit();
	 return false;
 }

function saveFooterContent()
{
	var src = document.getElementById("ft_bar").innerHTML;
	document.getElementById("hidden_div2").innerHTML = src;
	return false;
}


function getCookieVal (offset) {  
  var endstr = document.cookie.indexOf (";", offset);  
  if (endstr == -1)    
	endstr = document.cookie.length;  
  return unescape(document.cookie.substring(offset, endstr));
}

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

function Set_Cookie( name, value, expires, path, domain, secure ) {
  // set time, it's in milliseconds
  var today = new Date();
  today.setTime( today.getTime() );

  if ( expires ) {
	expires = expires * 1000 * 60 * 60;
  }
  var expires_date = new Date( today.getTime() + (expires) );

  //	( ( domain ) ? ";domain=" + domain : "" ) +
  document.cookie = name + "=" +escape( value ) +
	( ( expires ) ? ";expires=" + expires_date.toGMTString() : "" ) +
	( ( path ) ? ";path=" + path : "" ) +
	"; domain=.national.com" +
	( ( secure ) ? ";secure" : "" );
}

//	((domain) ? "; domain=" + domain : "") +
function delete_Cookie(name, path, domain) {
//alert("delete_Cookie=" + name);
	document.cookie = name + "=" +
	((path) ? "; path=" + path : "") +
	"; domain=.national.com" +
	"; expires=Thu, 01 Jan 1970 00:00:01 GMT";
}


function formSubmit(form)
{
	var uid = GetCookie("USERID");
	uid = uid.split(":::",1);
	alert(uid);

	alert(form.action);
	form.u1.value = uid;
	form.submit();
	return false;
 }

        function formSubmit2(form)
        {
                var uid = GetCookie("USERID");
                uid = uid.split(":::",1);
                alert(uid);

                alert(form.action);
                form.u1.value = uid;
                form.submit();
                return false;
         }

function saveComments()
{
	var val = document.getElementById('c1').value;
	document.forms['myform'].comments.value=val;
	document.forms['myform'].submit();
	return false;
 }

function bringToTop(num)
{
	var i = 0;
	while(i <= 5)
	{
		var el = document.getElementById("footer_box" + i);
		if(el != null)
		{
			el.style.display = "none";
		}


		var el2 = document.getElementById("ft_tab_" + i);
		if(el2 != null)
		{
			el2.className = "ft_tab_inactive";
		}
		i++;
	}

	el = document.getElementById("footer_box" + num);
	el.style.display = "block";


	el2 = document.getElementById("ft_tab_" + num);
	el2.className = "ft_tab_active";

//		window.location.hash="anc1";

	return false;
}

